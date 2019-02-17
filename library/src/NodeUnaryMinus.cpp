//
// Created by pav on 2019-02-17.
//

#include "NodeUnaryMinus.h"

#include "DataImpl.h"
#include "DeviceImpl.h"

#include "helpers/ClKernelsDefinitions.h"

#include <cmath>

namespace cl_graph {

NodeUnaryMinus::NodeUnaryMinus(Node op, const Device & device)
    : NodeUnaryOp(std::move(op), device)
{}

Data NodeUnaryMinus::evaluate()
{
    if (m_device.get_type() == Device::NOT_CL_CPU) {
        Data data_node = m_node.evaluate();

        if (data_node.empty()) {
            return {};
        }
        const auto & data = data_node.get_impl()->get_data();
        const auto & shape = data_node.get_impl()->get_shape();
        const auto sz = data.size();

        std::vector<float> res(sz);
        for (size_t i = 0; i < sz; ++i) {
            res[i] = -data[i];
        }
        return Data(std::move(res), shape);
    }
    return perform_opencl_operation(UNARY_MINUS);
}


}