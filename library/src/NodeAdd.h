#pragma once

#include "NodeTwoOp.h"

namespace cl_graph {

class NodeAdd
	: public NodeTwoOp {
public:
    NodeAdd(Node left, Node right, const Device & device);

	Data evaluate() final;

};

}
