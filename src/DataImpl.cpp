#include "DataImpl.h"

namespace cl_graph {

bool DataImpl::download(std::vector<float> & data, std::vector<size_t> & shape) const {
    data = m_data;
    shape = m_shape;
    return true;
}

bool DataImpl::upload(std::vector<float> data, std::vector<size_t> shape) {
    m_data = std::move(data);
    m_shape = std::move(shape);
    return true;
}


}