#include "NodeMul.h"

namespace cl_graph {

NodeMul::NodeMul(Node left, Node right, const Device & device)
    : m_left(std::move(left)),
      m_right(std::move(right)),
      m_device(device)
{

}

Data NodeMul::evaluate()
{
    Data left_data = m_left.evaluate();
    Data right_data = m_right.evaluate();
    if (m_device.get_type() == Device::NOT_CL_CPU) {

    } else {

    }
    return {};
}


}