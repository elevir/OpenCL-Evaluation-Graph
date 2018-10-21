#include "dll_macros.h"
#include "Data.h"
#include "Device.h"
#include "INode.h"
#include "Node.h"
#include "NodeAdd.h"
#include "NodeMul.h"
#include "NodeData.h"


namespace cl_graph {

OPENCL_EVAL_G_API Node::Node(INode * impl)
    : m_impl(impl)
{ }

OPENCL_EVAL_G_API Node::Node(Data & data)
    : m_impl(new NodeData(data))
{ }

OPENCL_EVAL_G_API Node::Node(Node & node) : m_impl(node.m_impl)
{ }

OPENCL_EVAL_G_API Node Node::add_node(Node & left, Node & right, const Device & device) {
    return new NodeAdd(left, right, device);
}

OPENCL_EVAL_G_API Node Node::mul_node(Node & left, Node & right, const Device & device) {
    return new NodeMul(left, right, device);
}

OPENCL_EVAL_G_API Node Node::element_wise_mul_node(const Node & left, const Node & right, const Device & device) {
    return nullptr;
}

OPENCL_EVAL_G_API Node Node::abs_node(const Node & op, const Device & device) {
    return nullptr;
}

OPENCL_EVAL_G_API Node Node::sqrt_node(const Node & op, const Device & device) {
    return nullptr;
}

OPENCL_EVAL_G_API Data Node::evaluate() {
    return m_impl ? m_impl->evaluate() : Data();
}

}
