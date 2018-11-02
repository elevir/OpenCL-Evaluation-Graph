#pragma once
#include <vector>
#include <CL/cl.h>

static class CLHelper
{
public:
	CLHelper();
	static cl_device_id get_default();
	static std::vector<cl_device_id> get_all_devices();
	static std::vector<cl_platform_id> get_all_platforms();
	static std::string get_device_name(const cl_device_id& device_id);
	static cl_device_info get_device_type(const cl_device_id& device_id);

private:
	static std::vector<cl_platform_id> m_all_platforms;
	static std::vector<cl_device_id> m_all_devices;
	static cl_device_id m_default;
};