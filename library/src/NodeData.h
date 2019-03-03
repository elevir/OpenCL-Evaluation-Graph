#pragma once

#include "cl_graph/Definitions.h"
#include "cl_graph/Data.h"
#include "INode.h"

namespace cl_graph {

class NodeData : public INode {

public:
    NodeData(const Data & data);

    Data evaluate() final;

private:
    Data m_data;
};

}
