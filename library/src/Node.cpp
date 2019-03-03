
#include <cl_graph/Node.h>

#include "cl_graph/Data.h"
#include "cl_graph/Device.h"
#include "INode.h"
#include "cl_graph/Node.h"

#include "NodeAbs.h"
#include "NodeAdd.h"
#include "NodeData.h"
#include "NodeDivElemWise.h"
#include "NodeMul.h"
#include "NodeMulElemWise.h"
#include "NodeSqrt.h"
#include "NodeUnaryMinus.h"

namespace cl_graph {

Node::Node(INode * impl)
    : m_impl(impl)
{ }

Node::Node(const Data & data)
    : m_impl(new NodeData(data))
{ }

Node::Node(const Node & node) : m_impl(node.m_impl)
{ }

Node::~Node() = default;

Node Node::add_node(Node left, Node right, const Device & device)
{
    return new NodeAdd(std::move(left), std::move(right), device);
}

Node Node::sub_node(Node left, Node right, const Device & device)
{
    return add_node(std::move(left), -right, device);
}

Node Node::unary_minus_node(Node op,const Device & device)
{
    return new NodeUnaryMinus(op, device);
}

Node Node::mul_node(Node left, Node right, const Device & device)
{
    return new NodeMul(std::move(left), std::move(right), device);
}

Node Node::div_node(Node left, Node right, const Device & device)
{
    return Node();
}

Node Node::element_wise_mul_node(Node left, Node right, const Device & device)
{
    return new NodeMulElemWise(std::move(left), std::move(right), device);
}

Node Node::element_wise_div_node(Node left, Node right, const Device & device)
{
    return new NodeDivElemWise(std::move(left), std::move(right), device);
}

Node Node::abs_node(Node op, const Device & device)
{
    return new NodeAbs(std::move(op), device);
}

Node Node::sqrt_node(Node op, const Device & device)
{
    return new NodeSqrt(std::move(op), device);
}

Data Node::evaluate()
{
    return m_impl ? m_impl->evaluate() : Data();
}

Node Node::operator+(Node other)
{
    return add_node(*this, std::move(other));
}

Node Node::operator-(Node other)
{
    return sub_node(*this, std::move(other));
}

Node Node::operator*(Node other)
{
    return mul_node(*this, std::move(other));
}

Node Node::operator/(Node other)
{
    return div_node(*this, std::move(other));
}

Node Node::operator-()
{
    return unary_minus_node(*this);
}

}
