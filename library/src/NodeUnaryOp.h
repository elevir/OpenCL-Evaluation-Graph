//
// Created by pav on 2019-02-17.
//

#pragma once

#include "Device.h"
#include "INode.h"
#include "Node.h"

namespace cl_graph {

class NodeUnaryOp :
    public INode
{
public:
    NodeUnaryOp(Node node, const Device & device);

    Data perform_opencl_operation(const std::pair<const char *, const char *> & op);

protected:
    Node m_node;

    Device m_device;
};

}