#pragma once

#include "dll_macros.h"
#include "Device.h"
#include "Node.h"
#include "INode.h"

namespace cl_graph {

class NodeAdd : public INode {
public:
    OPENCL_EVAL_G_API NodeAdd(Node & left, Node & right, const Device & device);

	OPENCL_EVAL_G_API Data evaluate() final;

private:
    Node m_left;
    Node m_right;

    Device m_device;
};

}
