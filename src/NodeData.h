#pragma once

#include "Data.h"
#include "NodeImpl.h"

namespace cl_graph {

class NodeData : public NodeImpl {

public:
    NodeData(Data & data);

    Data evaluate() final;

private:
    Data m_data;
};

}
