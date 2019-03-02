#include "ManagedNode.h"

using namespace CLGraph;

Node::Node(NativeNode& node) : m_node(new NativeNode(node))
{}

CLGraph::Node::!Node()
{
	delete m_node;
}

Node::Node(Node^ node) : m_node(node->m_node)
{}

Node::Node(Data^ data) : m_node(new NativeNode(*data->GetNativeData()))
{}

Data^ Node::Evaluate()
{
	return gcnew Data(new NativeData(m_node->evaluate()));
}

CLGraph::Node::operator Node^(Data^ data)
{
	return gcnew Node(NativeNode(*data->GetNativeData()));
}

Node^ Node::AddNode(Node^ left, Node^ right, Device^ device)
{
	return gcnew Node(NativeNode::add_node(*left->m_node, *right->m_node, device->GetNativeDevice()));
}

Node^ Node::MulNode(Node^ left, Node^ right, Device^ device)
{
	return gcnew Node(NativeNode::mul_node(*left->m_node, *right->m_node, device->GetNativeDevice()));
}

Node^ Node::ElementWiseMulNode(Node^ left, Node^ right, Device^ device)
{
	return gcnew Node(NativeNode::element_wise_mul_node(*left->m_node, *right->m_node, device->GetNativeDevice()));
}

Node^ Node::AbsNode(Node^ op, Device^ device)
{
	return gcnew Node(NativeNode::abs_node(*op->m_node, device->GetNativeDevice()));
}

Node^ Node::SqrtNode(Node^ op, Device^ device)
{
	return gcnew Node(NativeNode::sqrt_node(*op->m_node, device->GetNativeDevice()));
}

NativeNode& CLGraph::Node::GetNativeNode()
{
	return *m_node;
}
