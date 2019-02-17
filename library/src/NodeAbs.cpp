//
// Created by pav on 2019-02-17.
//

#include "NodeAbs.h"

#include "DataImpl.h"
#include "DeviceImpl.h"

#include "helpers/ClKernelsDefinitions.h"

#include <cmath>

namespace cl_graph {

NodeAbs::NodeAbs(Node op, const Device & device)
    : NodeUnaryOp(std::move(op), device)
{ }

Data NodeAbs::evaluate() {
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
            res[i] = std::abs(data[i]);
        }
        return Data(std::move(res), shape);
    }
    return perform_opencl_operation(ABS);
}


}