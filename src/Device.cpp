#include "Device.h"
#include <CL/cl.h>
#include "CLHelper.h"

namespace cl_graph {

cl_device_info fromOLEG2CL(const Device::Type& type) {
	switch (type) {
	case Device::CPU:
		return CL_DEVICE_TYPE_CPU;
	case Device::GPU:
		return CL_DEVICE_TYPE_GPU;
	case Device::FPGA:
		throw std::exception("FPGA not supported");
	case Device::INVALID:
	default:
		return CL_DEVICE_TYPE_DEFAULT;
	}
}



Device::Type fromCL2OLEG(const cl_device_info& cl_type) {
	switch (cl_type) 
	{
	case CL_DEVICE_TYPE_CPU:
		return Device::CPU;
	case CL_DEVICE_TYPE_GPU:
		return Device::GPU;
	case CL_DEVICE_TYPE_ALL:
	default:
		return Device::DEFAULT;
	}
}

Device Device::default_device {	CLHelper::get_default() };

Device::Device(cl_device_id deviceId) {
	m_type = fromCL2OLEG(CLHelper::get_device_type(deviceId));
	m_device_id = deviceId;
}

OPENCL_EVAL_G_API std::vector<Device> Device::get_all_devices() {
	std::vector<cl_device_id> all_cl_devices = CLHelper::get_all_devices();
	std::vector<Device> all_devices(all_cl_devices.size());
	all_devices.insert(all_devices.begin(), all_cl_devices.begin(), all_cl_devices.end());
	return all_devices; 
}

OPENCL_EVAL_G_API const Device & Device::get_default() {
	return default_device; 
}

OPENCL_EVAL_G_API const void Device::set_default(Device & device) {
	default_device = device;
}

}