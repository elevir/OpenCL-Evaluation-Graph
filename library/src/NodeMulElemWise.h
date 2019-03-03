//
// Created by pav on 2019-02-17.
//

#pragma once

#include "cl_graph/Definitions.h"

#include "NodeTwoOp.h"

namespace cl_graph{

class NodeMulElemWise :
    public NodeTwoOp
{
public:
    NodeMulElemWise(Node left, Node right, const Device & device);

    Data evaluate() final;

};

}