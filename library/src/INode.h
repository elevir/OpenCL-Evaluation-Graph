#pragma once

#include "Definitions.h"

#include "Data.h"

namespace cl_graph {

class OPENCL_EVAL_G_API INode
{
public:
	virtual Data evaluate() = 0;
	virtual ~INode() = default;
};

}