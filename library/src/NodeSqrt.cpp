//
// Created by pav on 2019-02-17.
//

#include "NodeSqrt.h"

#include "DataImpl.h"
#include "DeviceImpl.h"

#include "helpers/ClKernelsDefinitions.h"

#include <cmath>

namespace cl_graph {

NodeSqrt::NodeSqrt(cl_graph::Node op, const cl_graph::Device & device)
    : m_node(std::move(op)),
      m_device(device) {}

Data cl_graph::NodeSqrt::evaluate() {
    Data data_node = m_node.evaluate();

    if (data_node.empty()) {
        return {};
    }
    const auto & data = data_node.get_impl()->get_data();
    const auto & shape = data_node.get_impl()->get_shape();
    const auto sz = data.size();

    if (m_device.get_type() == Device::NOT_CL_CPU) {
        std::vector<float> res(sz);
        for (size_t i = 0; i < sz; ++i) {
            res[i] = std::sqrt(data[i]);
        }
        return Data(std::move(res), shape);
    } else {
//        m_device.get_impl()->get_kernel(ABS);
        auto kernel = m_device.get_impl()->get_kernel(SQRT);
        Data result;
        result.get_impl()->resize(data.size());
        auto res_cl = result.get_impl()->get_cl_data(m_device);
        auto op = data_node.get_impl()->get_cl_data(m_device);
        cl_int err;
        err = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *) &res_cl.mem);
        err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *) &op.mem);
        size_t local_work_size[2], global_work_size[2];
        local_work_size[0] = 1;
        local_work_size[1] = 1;
        global_work_size[0] = sz;
        global_work_size[1] = 1;
        err |= clEnqueueNDRangeKernel(
            m_device.get_impl()->get_queue(),
            kernel,
            1,
            nullptr,
            global_work_size,
            local_work_size,
            0,
            nullptr,
            nullptr);
        if (err == CL_SUCCESS) {
            result.get_impl()->set_shape(shape);
            return result;
        }
    }
    return {};
}

}