#pragma once

#include "dll_macros.h"
#include <atomic>
#include <cstddef>
#include "Data.h"

namespace cl_graph {

class OPENCL_EVAL_G_API INode
{
public:
	virtual Data evaluate() = 0;
};

}