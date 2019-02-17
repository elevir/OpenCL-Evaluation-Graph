#pragma once

#include "Definitions.h"

#include <vector>
#include <memory>

namespace cl_graph {

/**
 * Object describing the device
 */
class OPENCL_EVAL_G_API Device
{
public:

    /** Type of device */
    enum Type {
        DEFAULT,        /**< Default type */
        GPU,            /**< GPU Device */
        FPGA,           /**< FPGE Device */
        CPU,            /**< CPU Device */
        NOT_CL_CPU,     /**< CPU Device with CL */
        INVALID         /**< Invalid device */
    };

public:
	Device(const Device &);

	Type get_type() const;
	size_t get_id() const;
    const std::shared_ptr<DeviceImpl> & get_impl() const { return m_device_impl; }

    // static methods, not thread safe:
	static std::vector<Device> get_all_devices();
	static Device get_default();
	static const void set_default(Device & device);

private:
    explicit Device();
	explicit Device(Type type);
	Device(std::shared_ptr<DeviceImpl> device);

	static Device default_device;
	static std::vector<Device> all_devices;

	std::shared_ptr<DeviceImpl> m_device_impl;
};

}
