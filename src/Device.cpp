#include "Device.h"

namespace cl_graph {

Device Device::default_device{NOT_CL_CPU};

Device::Device(Device::Type type) : m_type(type)
{

}

}