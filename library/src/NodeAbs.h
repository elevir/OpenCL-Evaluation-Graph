//
// Created by pav on 2019-02-17.
//

#pragma once

#include "INode.h"
#include "NodeUnaryOp.h"

namespace cl_graph {

class NodeAbs :
    public NodeUnaryOp
{
public:
    NodeAbs(Node op, const Device & device);

    Data evaluate() final;

};

}
