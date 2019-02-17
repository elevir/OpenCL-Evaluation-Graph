//
// Created by pav on 2019-02-17.
//

#pragma once

#include "INode.h"
#include "Node.h"

namespace cl_graph {

class NodeAbs :
    public INode
{
public:
    NodeAbs(Node op, const Device & device);

    Data evaluate() final;

private:
    Node m_node;

    Device m_device;
};

}
