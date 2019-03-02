#include "ManagedDevice.h"

using namespace System::Collections::Generic;
using namespace CLGraph;


Device::Device(NativeDevice* device) : m_device(device)
{
}

CLGraph::Device::!Device()
{
	delete m_device;
}

CLGraph::Device::Device(Device^ device) : Device(device->m_device)
{
}

Device::Type Device::GetType()
{
	cl_graph::Device::Type type = m_device->get_type();
	switch (type)
	{
	case cl_graph::Device::DEFAULT:
		return Type::DEFAULT;
	case cl_graph::Device::GPU:
		return Type::GPU;
	case cl_graph::Device::FPGA:
		return Type::FPGA;
	case cl_graph::Device::CPU:
		return Type::CPU;
	case cl_graph::Device::NOT_CL_CPU:
		return Type::NOT_CL_CPU;
	default:
		return Type::INVALID;
	}
}

SIZE_T Device::GetId()
{
	return m_device->get_id();
}

array<Device^>^ Device::GetAllDevices()
{
	std::vector<NativeDevice> umAllDevices = NativeDevice::get_all_devices();
	array<Device^>^ allDevices = gcnew array<Device^>(umAllDevices.size());
	for (int i = 0; i < umAllDevices.size(); ++i)
		allDevices[i] = gcnew Device(new NativeDevice(umAllDevices[i]));
	return allDevices;
}

Device^ CLGraph::Device::GetDefault()
{
	return gcnew Device(new NativeDevice(NativeDevice::get_default()));
}

const void Device::SetDefault(Device^ device)
{
	NativeDevice::set_default(NativeDevice(*device->m_device));
}

const NativeDevice *Device::GetNativeDevice()
{
	return m_device;
}
