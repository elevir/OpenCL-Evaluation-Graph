#include "DeviceImpl.h"

#include "src/helpers/CLTypeConverters.h"

namespace cl_graph {

DeviceImpl::DeviceImpl(const cl_device_id & device_id) : m_device_id(device_id)
{
    cl_device_type ret_type;
    clGetDeviceInfo(device_id, CL_DEVICE_TYPE, sizeof(cl_device_type), &ret_type, nullptr);
    m_type = helpers::fromCL2OLEG(ret_type);
}

}