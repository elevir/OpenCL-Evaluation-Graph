#pragma once

#include "dll_macros.h"
#include "Data.h"
#include "Device.h"

namespace cl_graph {

class INode;

class Node
{
    Node(INode * impl);
public:
	OPENCL_EVAL_G_API Node() = default;
	OPENCL_EVAL_G_API Node(Node &);
	OPENCL_EVAL_G_API Node(Node &&) = default;
	OPENCL_EVAL_G_API Node(const Data &);
	OPENCL_EVAL_G_API ~Node() = default;

	OPENCL_EVAL_G_API Data evaluate();

    // static interface for node creation:
	OPENCL_EVAL_G_API static Node add_node(Node & left, Node & right, const Device & device = Device::get_default());
	OPENCL_EVAL_G_API static Node mul_node(Node & left, Node & right, const Device & device = Device::get_default());
	OPENCL_EVAL_G_API static Node element_wise_mul_node(const Node & left, const Node & right, const Device & device = Device::get_default());
	OPENCL_EVAL_G_API static Node abs_node(const Node & op, const Device & device = Device::get_default());
	OPENCL_EVAL_G_API static Node sqrt_node(const Node & op, const Device & device = Device::get_default());

private:
    std::shared_ptr<INode> m_impl;
};

};