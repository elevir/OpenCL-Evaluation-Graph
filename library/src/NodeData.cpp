#include "NodeData.h"

namespace cl_graph {

OPENCL_EVAL_G_API NodeData::NodeData(const Data & data)
    : m_data(data)
{ }


OPENCL_EVAL_G_API Data NodeData::evaluate()
{
    return m_data;
}

}