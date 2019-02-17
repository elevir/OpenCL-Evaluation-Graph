#pragma once

#include "Definitions.h"
#include <Node.h>
#include "INode.h"

namespace cl_graph {

class NodeMul : public INode {
public:
    NodeMul(Node left, Node right, const Device & device);

	Data evaluate() final;

private:
    Node m_left;
    Node m_right;

    Device m_device;
};

}
