#include "Device.h"

namespace cl_graph {

Device Device::default_device{NOT_CL_CPU};

Device::Device(Device::Type type) : m_type(type)
{

}

OPENCL_EVAL_G_API std::vector<Device> Device::get_all_devices() {
	return { Device(NOT_CL_CPU) }; 
}

OPENCL_EVAL_G_API const Device & Device::get_default() {
	return default_device; 
}

OPENCL_EVAL_G_API const void Device::set_default(Device & device) {
	default_device = device; 
}

}