#include "NodeImpl.h"

namespace cl_graph {

void NodeImpl::retain()
{
    ++m_ref_counter;
}

void NodeImpl::release()
{
    --m_ref_counter;
}

}