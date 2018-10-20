#include "NodeData.h"

namespace cl_graph {

NodeData::NodeData(Data & data)
    : m_data(data)
{ }


Data NodeData::evaluate()
{
    return m_data;
}

}