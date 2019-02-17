#include "DeviceImpl.h"

#include "helpers/CLTypeConverters.h"

#include <iostream>

namespace cl_graph {

DeviceImpl::DeviceImpl(const cl_device_id & device_id) : m_device_id(device_id)
{
    cl_device_type ret_type;
    clGetDeviceInfo(device_id, CL_DEVICE_TYPE, sizeof(cl_device_type), &ret_type, nullptr);
    size_t max_work_items_dimentions;
    clGetDeviceInfo(device_id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(size_t), &max_work_items_dimentions, nullptr);
    m_local_work_size.resize(max_work_items_dimentions);
    clGetDeviceInfo(device_id, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(size_t) * max_work_items_dimentions, m_local_work_size.data(), nullptr);
    clGetDeviceInfo(device_id, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &m_global_work_size, nullptr);

    m_type = helpers::fromCL2OLEG(ret_type);
    cl_int err;
    m_context = clCreateContext(nullptr, 1, &m_device_id, nullptr, nullptr, &err);
    m_queue = clCreateCommandQueue(m_context, device_id, 0, &err);
}

DeviceImpl::~DeviceImpl()
{
    if (m_queue)
        clReleaseCommandQueue(m_queue);
    if (m_context)
        clReleaseContext(m_context);
    if (m_device_id)
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

}