#pragma once

#include "dll_macros.h"
#include <atomic>
#include <cstddef>
#include "Data.h"

namespace cl_graph {

class INode
{
public:
	OPENCL_EVAL_G_API virtual Data evaluate() = 0;
};

}