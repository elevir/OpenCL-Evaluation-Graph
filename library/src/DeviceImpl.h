#pragma once
#include "helpers/opencl.h"

#include "Device.h"

#include <map>
#include <mutex>

namespace cl_graph {

class DeviceImpl {
public:
    DeviceImpl() = delete;
    DeviceImpl(Device::Type type) : m_type(type) { if (m_type != Device::NOT_CL_CPU) { throw std::exception(); } } // CPU
    DeviceImpl(const DeviceImpl &) = delete;
    DeviceImpl(DeviceImpl &&) = default;
    explicit DeviceImpl(const cl_device_id & device_id);
    ~DeviceImpl();

    const char * get_device_name() const { return m_device_name.c_str(); }
    Device::Type get_type() const { return m_type; }

    cl_context get_context() const { return m_context; }
    cl_command_queue get_queue() const { return m_queue; }
    cl_device_id get_device_id() const { return m_device_id; }

    size_t get_max_global_work_size() const { return m_global_work_size; }
    std::vector<size_t> get_max_local_work_size() const { return m_local_work_size; }

    cl_kernel get_kernel(const std::pair<const char *, const char *> & program) const;

    void print(std::ostream & oss) const;

private:
    cl_kernel do_get_kernel(cl_program program, const char * name) const;

    bool release_retain_supported() const { return m_cl_ver >= 12; }

private:
    Device::Type m_type = Device::NOT_CL_CPU;

    cl_device_id m_device_id = nullptr;
    cl_context m_context = nullptr;
    cl_command_queue m_queue = nullptr;

    std::string m_device_name = "NOT CL DEVICE";
    uint8_t m_cl_ver;

    std::vector<size_t> m_local_work_size;
    size_t m_global_work_size;

    mutable std::mutex m_cache_mutex;
    mutable std::map<std::string, cl_program> m_cache;
};

}