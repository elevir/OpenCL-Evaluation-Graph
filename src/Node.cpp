#include "Data.h"
#include "Device.h"
#include "NodeImpl.h"
#include "Node.h"
#include "NodeAdd.h"
#include "NodeMul.h"
#include "NodeData.h"


namespace cl_graph {

Node::Node(NodeImpl * impl)
    : m_impl(impl)
{ }

Node::Node(Data & data)
    : m_impl(new NodeData(data))
{ }

Node::Node(Node & node) : m_impl(node.m_impl)
{
    if (m_impl) {
        m_impl->retain();
    }
}

Node Node::add_node(Node & left, Node & right, const Device & device) {
    return new NodeAdd(left, right, device);
}

Node Node::mul_node(Node & left, Node & right, const Device & device) {
    return new NodeMul(left, right, device);
}

Node Node::element_wise_mul_node(const Node & left, const Node & right, const Device & device) {
    return nullptr;
}

Node Node::abs_node(const Node & op, const Device & device) {
    return nullptr;
}

Node Node::sqrt_node(const Node & op, const Device & device) {
    return nullptr;
}

Node::~Node() {
    if (m_impl) {
        m_impl->release();
    }
}

Data Node::evaluate() {
    return m_impl ? m_impl->evaluate() : Data();
}

}
