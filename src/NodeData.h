#pragma once

#include "Data.h"
#include "INode.h"

namespace cl_graph {

class NodeData : public INode {

public:
    NodeData(Data & data);

    Data evaluate() final;

private:
    Data m_data;
};

}
