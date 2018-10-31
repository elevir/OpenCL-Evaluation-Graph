#pragma once

#include "dll_macros.h"
#include <vector>
#include <CL/cl.h>

namespace cl_graph {

class Device
{
public:
    enum Type {
        DEFAULT,
        GPU,
        FPGA,
        CPU,
        NOT_CL_CPU,
        INVALID
    };

    // static methods, not thread safe:
	OPENCL_EVAL_G_API static std::vector<Device> get_all_devices();
	OPENCL_EVAL_G_API static const Device & get_default();
	OPENCL_EVAL_G_API static const void set_default(Device & device);

	OPENCL_EVAL_G_API Type get_type() const { return m_type; }

private:
    Device(Type type);
	Device(cl_device_id clType);

private:
    static Device default_device;
	
    Type m_type = NOT_CL_CPU;
	cl_device_id m_device_id;
};

}