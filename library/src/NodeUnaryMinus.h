//
// Created by pav on 2019-02-17.
//

#pragma once

#include "cl_graph/Device.h"
#include "NodeUnaryOp.h"

namespace cl_graph {

class NodeUnaryMinus  :
    public NodeUnaryOp
{
public:
    NodeUnaryMinus(Node op, const Device & device);

    Data evaluate() final;

};

}
