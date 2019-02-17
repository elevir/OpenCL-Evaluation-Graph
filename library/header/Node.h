#pragma once

#include "Data.h"
#include "Device.h"
#include "Definitions.h"

namespace cl_graph {

class OPENCL_EVAL_G_API Node
{
    Node(INode * impl);
public:
	Node() = default;
	Node(Node &);
	Node(Node &&) = default;
	Node(const Data &);
	~Node();
	
	Data evaluate();

	Node operator-();

	Node operator+(Node other);
	Node operator-(Node other);
	Node operator*(Node other);
	Node operator/(Node other);

    // static interface for node creation:
	static Node add_node(Node left, Node right, const Device & device = Device::get_default());
    static Node sub_node(Node left, Node right, const Device & device = Device::get_default());
	static Node unary_minus_node(Node op, const Device & device = Device::get_default());
	static Node mul_node(Node left, Node right, const Device & device = Device::get_default());
	static Node div_node(Node left, Node right, const Device & device = Device::get_default());
	static Node element_wise_mul_node(Node left, Node right, const Device & device = Device::get_default());
    static Node element_wise_div_node(Node left, Node right, const Device & device = Device::get_default());
	static Node abs_node(Node op, const Device & device = Device::get_default());
	static Node sqrt_node(Node op, const Device & device = Device::get_default());

private:
    std::shared_ptr<INode> m_impl;
};

};