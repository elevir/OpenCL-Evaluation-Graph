//
// Created by pav on 2019-02-17.
//

#include "NodeDivElemWise.h"

#include "DataImpl.h"
#include "DeviceImpl.h"

#include "helpers/ClKernelsDefinitions.h"

#include <assert.h>

namespace cl_graph {


NodeDivElemWise::NodeDivElemWise(Node left, Node right, const Device & device)
    : NodeTwoOp(std::move(left), std::move(right), device)
{ }

Data NodeDivElemWise::evaluate()
{
    if (m_device.get_type() == Device::NOT_CL_CPU) {
        Data left_data = m_left.evaluate();
        Data right_data = m_right.evaluate();

        if (left_data.empty() || right_data.empty()) {
            return {};
        }
        const auto & data_left = left_data.get_impl()->get_data();
        const auto & data_right = right_data.get_impl()->get_data();
        const auto & left_shape = left_data.get_impl()->get_shape();
        const auto & right_shape = right_data.get_impl()->get_shape();
        assert((data_left.size() == data_right.size() || data_left.size() == 1 || data_right.size() == 1) && "matrixes are not of equal size and not a scalar");
        assert(((left_shape == right_shape) || (left_shape.size() == 1 && left_shape[0] == 1) || (right_shape.size() == 1 && right_shape[0] == 1)) && "shapes are missmatch and not a one is  scalar");

        const auto sz = data_left.size();
        std::vector<float> res(sz);
        for (size_t i = 0; i < sz; ++i) {
            res[i] = data_left[i] / data_right[i];
        }
        return Data(std::move(res), left_data.get_impl()->get_shape());
    }
    return perform_opencl_operation(ELEM_WISE_DIV);
}


}