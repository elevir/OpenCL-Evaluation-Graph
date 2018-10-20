#include "DataImpl.h"

namespace cl_graph {

DataImpl::DataImpl(std::vector<float> container, std::vector<size_t> shape)
    : m_data(std::move(container)),
      m_shape(std::move(shape))
{

}


}