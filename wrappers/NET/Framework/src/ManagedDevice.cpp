#include "ManagedDevice.h"

using namespace System::Collections::Generic;
using namespace CLGraph;

Device::Device(const NativeDevice& device) : m_device(new NativeDevice(device))
{}

CLGraph::Device::!Device()
{
	delete m_device;
}

CLGraph::Device::Device(Device^ device) : Device(*device->m_device)
{}

Device::DeviceType Device::GetDeviceType()
{
	cl_graph::Device::Type type = m_device->get_type();
	switch (type)
	{
	case cl_graph::Device::DEFAULT:
		return DeviceType::DEFAULT;
	case cl_graph::Device::GPU:
		return DeviceType::GPU;
	case cl_graph::Device::FPGA:
		return DeviceType::FPGA;
	case cl_graph::Device::CPU:
		return DeviceType::CPU;
	case cl_graph::Device::NOT_CL_CPU:
		return DeviceType::NOT_CL_CPU;
	default:
		return DeviceType::INVALID;
	}
}

SIZE_T Device::GetId()
{
	return m_device->get_id();
}

array<Device^>^ Device::GetAllDevices()
{
	std::vector<NativeDevice> umAllDevices = NativeDevice::get_all_devices();
	auto allDevices = gcnew array<Device^>(umAllDevices.size());
	for (int i = 0; i < umAllDevices.size(); ++i)
		allDevices[i] = gcnew Device(umAllDevices[i]);
	return allDevices;
}

Device^ CLGraph::Device::GetDefault()
{
	return gcnew Device(NativeDevice::get_default());
}

const void Device::SetDefault(Device^ device)
{
	NativeDevice::set_default(*device->m_device);
}

const NativeDevice &Device::GetNativeDevice()
{
	return *m_device;
}
