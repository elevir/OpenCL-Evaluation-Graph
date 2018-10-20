#pragma once

#include "Data.h"
#include "Device.h"

namespace cl_graph {

class INode;

class Node
{
    Node(INode * impl);
public:
    Node() = default;
    Node(Node &);
    Node(Node &&) = default;
    Node(Data &);
    ~Node() = default;

    Data evaluate();

    // static interface for node creation:
    static Node add_node(Node & left, Node & right, const Device & device = Device::get_default());
    static Node mul_node(Node & left, Node & right, const Device & device = Device::get_default());
    static Node element_wise_mul_node(const Node & left, const Node & right, const Device & device = Device::get_default());
    static Node abs_node(const Node & op, const Device & device = Device::get_default());
    static Node sqrt_node(const Node & op, const Device & device = Device::get_default());

private:
    std::shared_ptr<INode> m_impl;
};

};