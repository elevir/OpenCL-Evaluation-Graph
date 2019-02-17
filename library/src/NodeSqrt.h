//
// Created by pav on 2019-02-17.
//

#pragma once

#include "Device.h"
#include "NodeUnaryOp.h"

namespace cl_graph {

class NodeSqrt :
    public NodeUnaryOp
{
public:
    NodeSqrt(Node op, const Device & device);

    Data evaluate() final;
};

}
