#pragma once
#include "src/helpers/opencl.h"

#include "Device.h"

namespace cl_graph {

class DeviceImpl {

public:
    DeviceImpl() = delete;
    DeviceImpl(const DeviceImpl &) = delete;
    DeviceImpl(DeviceImpl &&) = default;
    DeviceImpl(const cl_device_id & device_id);

    Device::Type get_type() const { return m_type; }

private:
    Device::Type m_type = Device::NOT_CL_CPU;
    const cl_device_id m_device_id;
};

}