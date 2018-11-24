#pragma once
#include "NodeAddCL.h"
#include "helpers/opencl.h"

namespace cl_graph {

	NodeAddCL::NodeAddCL(Node & left, Node & right, const Device & device) :
		m_device(device), m_left(left), m_right(right) {}

	Data NodeAddCL::evaluate()
	{
		return Data();
	}
}
