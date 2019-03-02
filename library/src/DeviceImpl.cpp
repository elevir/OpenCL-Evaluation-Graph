#include "DeviceImpl.h"

#include "helpers/CLTypeConverters.h"

#include <iostream>

namespace cl_graph {

DeviceImpl::DeviceImpl(const cl_device_id & device_id) : m_device_id(device_id)
{
    cl_device_type ret_type;
    clGetDeviceInfo(device_id, CL_DEVICE_TYPE, sizeof(cl_device_type), &ret_type, nullptr);
    m_type = helpers::fromCL2OLEG(ret_type);
    size_t max_work_items_dimentions = 0;
    cl_int err = clGetDeviceInfo(device_id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(size_t), &max_work_items_dimentions, nullptr);
    if (err) {
        throw std::exception();
    }
    m_local_work_size.resize(max_work_items_dimentions);
    clGetDeviceInfo(device_id, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(size_t) * max_work_items_dimentions, m_local_work_size.data(), nullptr);
    clGetDeviceInfo(device_id, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &m_global_work_size, nullptr);
    char clver[128];
    cl_platform_id platform_id;
    err = clGetDeviceInfo(device_id, CL_DEVICE_NAME, sizeof(clver), &clver, nullptr);
    if (err == CL_SUCCESS) {
        m_device_name = clver;
        m_device_name += " ";
    }
    err = clGetDeviceInfo(device_id, CL_DEVICE_OPENCL_C_VERSION, sizeof(clver), &clver, nullptr);
    if (err != CL_SUCCESS) {
        throw std::exception();
    }
    m_device_name += clver;
    m_cl_ver = (clver[9] - '0') * 10 + (clver[11] - '0');

    m_context = clCreateContext(nullptr, 1, &m_device_id, nullptr, nullptr, &err);
    if (m_cl_ver >= 20) {
        #ifndef __APPLE_CL__
            m_queue = clCreateCommandQueueWithProperties(m_context, device_id, 0, &err);
        #else
            m_queue = clCreateCommandQueueWithPropertiesAPPLE(m_context, device_id, 0, &err);
        #endif
    } else {
        m_queue = clCreateCommandQueue(m_context, device_id, 0, &err);
    }
    if (m_device_id && release_retain_supported())
        clRetainDevice(m_device_id);
}

DeviceImpl::~DeviceImpl()
{
    if (m_queue)
        clReleaseCommandQueue(m_queue);
    if (m_context)
        clReleaseContext(m_context);
    if (m_device_id && release_retain_supported())
        clReleaseDevice(m_device_id);
}

cl_kernel DeviceImpl::get_kernel(const std::pair<const char *, const char *> & program) const
{
    std::lock_guard lock(m_cache_mutex);
    const auto it = m_cache.find(program.second);
    if (it != m_cache.end()) {
        return do_get_kernel(it->second, program.second);
    }
    cl_int err;
    const char * prg = program.first;
    auto compiled_program = clCreateProgramWithSource(m_context, 1, &prg, NULL, &err);
    auto err_2 = clBuildProgram(compiled_program, 0, NULL, NULL, NULL, NULL);
    if (err == CL_SUCCESS && err_2 == CL_SUCCESS) {
        m_cache.emplace(program.second, compiled_program);
        return do_get_kernel(compiled_program, program.second);
    } else {
        size_t len;
        char buffer[4096];
        clGetProgramBuildInfo(compiled_program, m_device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
        std::cerr << "Cannot compile program: " << buffer;
    }
    return do_get_kernel(compiled_program, program.second);
}

cl_kernel DeviceImpl::do_get_kernel(cl_program program, const char * name) const
{
    cl_int err;
    auto kernel = clCreateKernel(program, name, &err);
    if (err == CL_SUCCESS) {
        return kernel;
    }
    return nullptr;
}

namespace {
template <class T>
struct TypeWrapper
{
    using Type = T;
};

template <class T>
class Printer
{
public:
    Printer(const T & val) : m_val(val) {}

    friend std::ostream & operator<<(std::ostream & oss, const Printer & printer)
    {
        printer.print(oss);
        return oss;
    }

private:
    void print(std::ostream & oss) const
    {
        using Type = typename std::remove_reference<T>::type;
        if constexpr (std::is_array<Type>::value
            && !std::is_convertible<Type, const char *>::value
            && !std::is_pointer    <Type>::value)
        {
            bool first = true;
            for (const auto & el : m_val) {
                if (!first) {
                    oss << " | ";
                }
                first = false;
                oss << el;
            }
        } else {
            oss << m_val;
        }
    }

private:
    const T & m_val;
};

}

#ifndef PRINT_DEVICE_PARAMETER
#define PRINT_DEVICE_PARAMETER(TYPE, PARAMETER, STRING) \
{\
    TypeWrapper<TYPE>::Type param; \
    oss << "  " STRING << " : "; \
    auto err = clGetDeviceInfo(m_device_id, PARAMETER, sizeof(TypeWrapper<TYPE>::Type), &param, nullptr); \
    if (err == CL_SUCCESS) { \
        oss << Printer<TypeWrapper<TYPE>::Type>(param); \
    } else { \
        oss << "<cannot extract> err=[" << err << "]"; \
    } \
    oss << "\n"; \
}
#endif

#ifndef PRINT_DEVICE_STRING_PARAMETER
#define PRINT_DEVICE_STRING_PARAMETER(PARAMETER) PRINT_DEVICE_PARAMETER(char[256], PARAMETER, #PARAMETER)
#endif

#ifndef PRINT_DEVICE_TYPED_PARAMETER
#define PRINT_DEVICE_TYPED_PARAMETER(PARAMETER, TYPE) PRINT_DEVICE_PARAMETER(TYPE, PARAMETER, #PARAMETER)
#endif

void DeviceImpl::print(std::ostream & oss) const
{
    oss << "Device {\n";
    if (m_device_id) {
        PRINT_DEVICE_STRING_PARAMETER(CL_DEVICE_NAME);
        PRINT_DEVICE_STRING_PARAMETER(CL_DEVICE_VENDOR);
        PRINT_DEVICE_STRING_PARAMETER(CL_DRIVER_VERSION);
        PRINT_DEVICE_TYPED_PARAMETER(CL_DEVICE_TYPE, cl_device_type);
        PRINT_DEVICE_TYPED_PARAMETER(CL_DEVICE_MAX_COMPUTE_UNITS, int);
        PRINT_DEVICE_TYPED_PARAMETER(CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, int);
        PRINT_DEVICE_TYPED_PARAMETER(CL_DEVICE_MAX_WORK_ITEM_SIZES, size_t[3]);
        PRINT_DEVICE_TYPED_PARAMETER(CL_DEVICE_MAX_CLOCK_FREQUENCY, int);
        PRINT_DEVICE_TYPED_PARAMETER(CL_DEVICE_ADDRESS_BITS, int);
        PRINT_DEVICE_TYPED_PARAMETER(CL_DEVICE_MAX_MEM_ALLOC_SIZE, size_t[3]);
        PRINT_DEVICE_TYPED_PARAMETER(CL_DEVICE_GLOBAL_MEM_SIZE, size_t[3]);
        PRINT_DEVICE_TYPED_PARAMETER(CL_DEVICE_ERROR_CORRECTION_SUPPORT, int);
        PRINT_DEVICE_STRING_PARAMETER(CL_DEVICE_LOCAL_MEM_TYPE);
        PRINT_DEVICE_TYPED_PARAMETER(CL_DEVICE_LOCAL_MEM_SIZE, size_t);
        PRINT_DEVICE_TYPED_PARAMETER(CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, size_t);
        PRINT_DEVICE_TYPED_PARAMETER(CL_DEVICE_QUEUE_PROPERTIES, cl_command_queue_properties);
        PRINT_DEVICE_TYPED_PARAMETER(CL_DEVICE_IMAGE_SUPPORT, int);
        PRINT_DEVICE_TYPED_PARAMETER(CL_DEVICE_MAX_READ_IMAGE_ARGS, int);
        PRINT_DEVICE_TYPED_PARAMETER(CL_DEVICE_MAX_WRITE_IMAGE_ARGS, int);
    } else {
        oss << "  NOT CL DEVICE\n";
    }
    oss << "}";
}
#undef PRINT_DEVICE_PARAMETER
}