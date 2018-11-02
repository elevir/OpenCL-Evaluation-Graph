#include "CLHelper.h"

std::vector<cl_platform_id> CLHelper::m_all_platforms;
std::vector<cl_device_id> CLHelper::m_all_devices;
cl_device_id CLHelper::m_default;

CLHelper::CLHelper() {
	cl_uint countOfPatforms;
	clGetPlatformIDs(0, NULL, &countOfPatforms);
	m_all_platforms.resize(countOfPatforms);
	clGetPlatformIDs(countOfPatforms, m_all_platforms.data(), NULL);
	for(auto &platform : m_all_platforms) {
		cl_uint countOfDevices;
		clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, NULL, &countOfDevices);
		std::vector<cl_device_id> all_devices_for_platform(countOfDevices);
		clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, countOfDevices, all_devices_for_platform.data(), NULL);
		m_all_devices.insert(m_all_devices.end(), all_devices_for_platform.begin(), all_devices_for_platform.end());
	}
}

cl_device_id CLHelper::get_default() {
	return m_default;
}

std::vector<cl_device_id> CLHelper::get_all_devices() {
	return m_all_devices;
}

std::vector<cl_platform_id> CLHelper::get_all_platforms() {
	return m_all_platforms;
}

std::string CLHelper::get_device_name(const cl_device_id& device_id) {
	size_t nameLength;
	clGetDeviceInfo(device_id, CL_DEVICE_NAME, 0, NULL, &nameLength);
	char* name = new char[nameLength];
	clGetDeviceInfo(device_id, CL_DEVICE_NAME, nameLength, name, NULL);
	return name;
}

cl_device_info CLHelper::get_device_type(const cl_device_id& device_id) {
	cl_device_info type;
	clGetDeviceInfo(device_id, CL_DEVICE_TYPE, sizeof(cl_device_info), &type, NULL);
	return type;
}