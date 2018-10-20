#pragma once

#include <vector>

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
    static std::vector<Device> get_all_devices() { return {NOT_CL_CPU}; } // TODO: implement get_all_devices
    static const Device & get_default() { return default_device; }
    static const void set_default(Device & device) { default_device = device; }

    Type get_type() const { return m_type; }

private:
    Device(Type type);

private:
    static Device default_device;

    Type m_type = NOT_CL_CPU;
};

}