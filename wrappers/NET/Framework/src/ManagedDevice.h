#pragma once

#include "Device.h"
#include "Utilities.hpp"

namespace CLGraph {

	typedef cl_graph::Device NativeDevice;

	public ref class Device sealed
	{
	public:
		enum class Type
		{
			DEFAULT,        /**< Default type */
			GPU,            /**< GPU Device */
			FPGA,           /**< FPGE Device */
			CPU,            /**< CPU Device */
			NOT_CL_CPU,     /**< CPU Device with CL */
			INVALID         /**< Invalid device */
		};
		!Device();
		Device(Device^ device);

		Type GetType();
		SIZE_T GetId();

		// static methods, not thread safe:
		static array<Device^>^ GetAllDevices();
		static Device^ GetDefault();
		static const void SetDefault(Device^ device);

	internal:
		Device(NativeDevice* device);
		const NativeDevice* GetNativeDevice();

	private:
		NativeDevice* m_device;
	};

}