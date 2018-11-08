#pragma once

#include "dll_macros.h"
#include <vector>

namespace cl_graph {

class DeviceImpl;

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

public:
	OPENCL_EVAL_G_API Device(const Device &);

	OPENCL_EVAL_G_API Type get_type() const;
	OPENCL_EVAL_G_API size_t get_id() const;

    // static methods, not thread safe:
	OPENCL_EVAL_G_API static std::vector<Device> get_all_devices();
	OPENCL_EVAL_G_API static Device get_default();
	OPENCL_EVAL_G_API static const void set_default(Device & device);

private:
    explicit Device();
	explicit Device(Type type);
	Device(std::shared_ptr<DeviceImpl> device);

	static Device default_device;
	static std::vector<Device> all_devices;

	std::shared_ptr<DeviceImpl> m_device_impl;
};

}