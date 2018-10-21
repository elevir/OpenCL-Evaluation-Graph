#include "dll_macros.h"
#include "DataImpl.h"

namespace cl_graph {

OPENCL_EVAL_G_API bool DataImpl::download(std::vector<float> & data, std::vector<size_t> & shape) const {
    data = m_data;
    shape = m_shape;
    return true;
}

OPENCL_EVAL_G_API bool DataImpl::upload(std::vector<float> data, std::vector<size_t> shape) {
    m_data = std::move(data);
    m_shape = std::move(shape);
    return true;
}


}