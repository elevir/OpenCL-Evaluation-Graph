#pragma once

#include "dll_macros.h"
#include "Device.h"
#include "Node.h"
#include "INode.h"

namespace cl_graph {

	class OPENCL_EVAL_G_API NodeAddCL : public INode {
	public:
		NodeAddCL(Node & left, Node & right, const Device & device);
		Data evaluate() final;

	private:
		Node m_left;
		Node m_right;

		Device m_device;
	};

}
