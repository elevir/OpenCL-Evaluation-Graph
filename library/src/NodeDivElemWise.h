//
// Created by pav on 2019-02-17.
//

#pragma once

#include "Definitions.h"

#include "Device.h"
#include "Node.h"
#include "INode.h"

namespace cl_graph {

class NodeDivElemWise  :
    public INode
{
public:
    NodeDivElemWise (Node left, Node right, const Device & device);

    Data evaluate() final;

private:
    Node m_left;
    Node m_right;

    Device m_device;
};

}
