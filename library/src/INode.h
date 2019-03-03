#pragma once

#include "cl_graph/Definitions.h"

#include "cl_graph/Data.h"

namespace cl_graph {

class OPENCL_EVAL_G_API INode
{
public:
	virtual Data evaluate() = 0;
	virtual ~INode() = default;
};

}