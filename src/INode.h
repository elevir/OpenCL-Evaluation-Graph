#pragma once

#include <atomic>
#include <cstddef>
#include "Data.h"

namespace cl_graph {

class INode
{
public:
    virtual Data evaluate() = 0;
};

}