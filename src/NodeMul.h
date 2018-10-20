#pragma once

#include <Node.h>
#include "NodeImpl.h"

namespace cl_graph {

class NodeMul : public NodeImpl {
public:
    NodeMul(Node & left, Node & right, const Device & device);

    Data evaluate() final;

private:
    Node m_left;
    Node m_right;

    Device m_device;
};

}
