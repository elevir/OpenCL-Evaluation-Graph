//
// Created by pav on 2019-02-17.
//

#pragma once

#include "Device.h"
#include "INode.h"
#include "Node.h"

namespace cl_graph {

class NodeTwoOp :
    public INode
{
public:
    NodeTwoOp(Node left, Node right, const Device & device);

    Data perform_opencl_operation(const std::pair<const char *, const char *> & op);

protected:
    Node m_left;
    Node m_right;

    Device m_device;
};

}