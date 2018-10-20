#pragma once

#include "Device.h"
#include "Node.h"
#include "NodeImpl.h"

namespace cl_graph {

class NodeAdd : public NodeImpl {
public:
    NodeAdd(Node & left, Node & right, const Device & device);

    Data evaluate() final;

private:
    Node m_left;
    Node m_right;

    Device m_device;
};

}
