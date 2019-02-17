#pragma once

namespace cl_graph { namespace helpers {

cl_device_info fromOLEG2CL(const Device::Type& type) {
    switch (type) {
        case Device::Type::CPU:
            return CL_DEVICE_TYPE_CPU;
        case Device::Type::GPU:
            return CL_DEVICE_TYPE_GPU;
        case Device::Type::FPGA:
            throw std::invalid_argument("FPGA not supported yet");
        case Device::Type::INVALID:
        default:
            return CL_DEVICE_TYPE_DEFAULT;
    }
}

Device::Type fromCL2OLEG(const cl_device_type & cl_type) {
    switch (cl_type)
    {
        case CL_DEVICE_TYPE_CPU:
            return Device::Type::CPU;
        case CL_DEVICE_TYPE_GPU:
            return Device::Type::GPU;
        case CL_DEVICE_TYPE_ALL:
        default:
            return Device::Type::DEFAULT;
    }
}

}}