#include "dll_macros.h"
#include "Device.h"

namespace cl_graph {

Device Device::default_device{NOT_CL_CPU};

OPENCL_EVAL_G_API Device::Device(Device::Type type) : m_type(type)
{

}

}