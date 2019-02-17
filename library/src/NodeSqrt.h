//
// Created by pav on 2019-02-17.
//

#pragma once

#include "Device.h"
#include "Node.h"
#include "INode.h"

namespace cl_graph {

class NodeSqrt :
    public INode
{
public:
    NodeSqrt(Node op, const Device & device);

    Data evaluate() final;

private:
    Node m_node;

    Device m_device;
};

}
