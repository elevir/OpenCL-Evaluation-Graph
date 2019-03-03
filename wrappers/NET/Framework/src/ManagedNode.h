#pragma once

#include "cl_graph/Node.h"
#include "Utilities.hpp"
#include "ManagedData.h"
#include "ManagedDevice.h"

namespace CLGraph {

	typedef cl_graph::Node NativeNode;

	public ref class Node sealed
	{
	public:
		!Node();
		Node(Node^ node);
		Node(Data^ data);
		Data^ Evaluate();
		// static interface for node creation:

		static operator Node^(Data^);

		static Node^ AddNode(Node^ left, Node^ right, Device^ device);
		static Node^ MulNode(Node^ left, Node^ right, Device^ device);
		static Node^ ElementWiseMulNode(Node^ left, Node^ right, Device^ device);
		static Node^ AbsNode(Node^ op, Device^ device);
		static Node^ SqrtNode(Node^ op, Device^ device);

	internal:
		Node(NativeNode& node);
		NativeNode& GetNativeNode();

	private:
		NativeNode* m_node;
	};

}