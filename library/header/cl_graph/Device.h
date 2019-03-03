#pragma once

#include "Definitions.h"

#include <ostream>
#include <memory>
#include <vector>

namespace cl_graph {

/**
 * Object describing the device
 */
class OPENCL_EVAL_G_API Device
{
public:

    /** Type of device */
	enum Type {
		DEFAULT = 0,        /**< Default type */
		GPU = 1,            /**< GPU Device */
		FPGA = 2,           /**< FPGE Device */
		CPU = 4,            /**< CPU Device */
		NOT_CL_CPU = 8,     /**< CPU Device with CL */
		INVALID = -1        /**< Invalid device */
	};

public:
	Device();
	Device(const Device &);
	Device(Device &&) noexcept;
	virtual ~Device();

	Device & operator=(const Device & other);
    Device & operator=(Device && other) noexcept;

    const char * get_device_name() const;
	Type get_type() const;
	size_t get_id() const;
    const std::shared_ptr<DeviceImpl> & get_impl() const { return m_device_impl; }

    // static methods, not thread safe:
	static std::vector<Device> get_all_devices();
	static Device get_default();
	static void set_default(const Device& device);

	void print(std::ostream & oss) const;
    OPENCL_EVAL_G_API friend std::ostream & operator<<(std::ostream & oss, const Device & device);

private:
	explicit Device(Type type);
	Device(std::shared_ptr<DeviceImpl> device);

	static Device default_device;
	static std::vector<Device> all_devices;

	std::shared_ptr<DeviceImpl> m_device_impl;
};

}
