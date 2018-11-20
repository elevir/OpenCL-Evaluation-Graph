#pragma once

#include "dll_macros.h"
#include "Data.h"
#include "INode.h"

namespace cl_graph {

class NodeData : public INode {

public:
    OPENCL_EVAL_G_API NodeData(const Data & data);

	OPENCL_EVAL_G_API Data evaluate() final;

private:
    Data m_data;
};

}
