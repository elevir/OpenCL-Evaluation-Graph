#pragma once

#include <atomic>
#include <cstddef>
#include "Data.h"

namespace cl_graph {

class NodeImpl
{
public:
    virtual Data evaluate() = 0;

    void retain();
    void release();

private:
    std::atomic<size_t> m_ref_counter {1};
};

}