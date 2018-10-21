#include "NodeMul.h"

namespace cl_graph {

OPENCL_EVAL_G_API NodeMul::NodeMul(Node & left, Node & right, const Device & device)
    : m_left(left),
      m_right(right),
      m_device(device)
{

}

OPENCL_EVAL_G_API Data NodeMul::evaluate()
{
    Data left_data = m_left.evaluate();
    Data right_data = m_right.evaluate();
    if (m_device.get_type() == Device::NOT_CL_CPU) {
        // TODO: implement

    }
    return {};
}


}