#ifdef WIN32
#include <assert.h>
#endif

#include "NodeAdd.h"
#include "DataImpl.h"


namespace cl_graph {

OPENCL_EVAL_G_API NodeAdd::NodeAdd(Node & left, Node & right, const Device & device)
    : m_left(left),
      m_right(right),
      m_device(device)
{ }

OPENCL_EVAL_G_API Data NodeAdd::evaluate()
{
    Data left_data = m_left.evaluate();
    Data right_data = m_right.evaluate();

    if (left_data.empty() || right_data.empty()) {
        return {};
    }

    if (m_device.get_type() == Device::NOT_CL_CPU) {
        const auto & data_left = left_data.get_impl()->get_data();
        const auto & data_right = right_data.get_impl()->get_data();
        assert(data_left.size() == data_right.size() && "matrixes are not of equal size");
        assert(left_data.get_impl()->get_shape() == right_data.get_impl()->get_shape() && "shapes are missmatched");
        const auto sz = data_left.size();
        std::vector<float> res(sz);
        for (size_t i = 0; i < sz; ++i) {
            res[i] = data_left[i] + data_right[i];
        }
        return Data(std::move(res), left_data.get_impl()->get_shape());
    }
    return {};
}

}
