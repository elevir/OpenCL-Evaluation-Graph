#include "src/helpers/opencl.h"
#include "Device.h"
#include "DeviceImpl.h"

namespace cl_graph {

Device Device::default_device{};
std::vector<Device> Device::all_devices{};

Device::Device()
{ }

Device::Device(const Device & other) : m_device_impl(other.m_device_impl)
{ }

Device::Device(std::shared_ptr<DeviceImpl> device) :m_device_impl(std::move(device))
{ }

OPENCL_EVAL_G_API std::vector<Device> Device::get_all_devices()
{
    if (all_devices.empty()) {
        all_devices.push_back(Device(std::make_shared<DeviceImpl>(Type::NOT_CL_CPU)));
        cl_uint countOfPatforms;
        clGetPlatformIDs(0, nullptr, &countOfPatforms);
        std::vector<cl_platform_id> all_platforms;
        all_platforms.resize(countOfPatforms);
        clGetPlatformIDs(countOfPatforms, all_platforms.data(), nullptr);
        std::vector<cl_device_id> all_cl_devices;
        for (auto platform : all_platforms) {
            cl_uint countOfDevices;
            clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, nullptr, &countOfDevices);
            std::vector<cl_device_id> all_devices_for_platform(countOfDevices);
            clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, countOfDevices, all_devices_for_platform.data(), nullptr);
            all_cl_devices.insert(all_cl_devices.end(), all_devices_for_platform.begin(),
                                  all_devices_for_platform.end());
        }
        all_devices.reserve(all_cl_devices.size());
        for (const auto & cl_device : all_cl_devices) {
            all_devices.push_back(Device(std::make_shared<DeviceImpl>(cl_device)));
        }
    }
    return all_devices;
}

OPENCL_EVAL_G_API Device Device::get_default()
{
    if (default_device.get_type() == INVALID) {
        for (const auto & device : get_all_devices()) {
            if (device.get_type() == DEFAULT) {
                default_device = device;
                break;
            }
        }
    }
	return default_device;
}

OPENCL_EVAL_G_API const void Device::set_default(Device & device)
{
	default_device = device;
}

size_t Device::get_id() const
{
	return (size_t)(&*m_device_impl);
}

Device::Type Device::get_type() const
{
    if (m_device_impl) {
        return m_device_impl->get_type();
    }
    return INVALID;
}


}
