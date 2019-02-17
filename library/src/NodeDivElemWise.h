//
// Created by pav on 2019-02-17.
//

#pragma once

#include "NodeTwoOp.h"

namespace cl_graph {

class NodeDivElemWise  :
    public NodeTwoOp
{
public:
    NodeDivElemWise(Node left, Node right, const Device & device);

    Data evaluate() final;

};

}
