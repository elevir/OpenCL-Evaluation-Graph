#ifdef WIN32
#include <assert.h>
#endif

#include "dll_macros.h"
#include "Data.h"
#include "DataImpl.h"

namespace cl_graph {

OPENCL_EVAL_G_API Data::Data(std::vector<float> container, std::vector<size_t> shape)
{
    m_impl = std::make_shared<DataImpl>();
    upload(std::move(container), std::move(shape));
}

OPENCL_EVAL_G_API Data::Data()
{
    m_impl = std::make_shared<DataImpl>();
}

OPENCL_EVAL_G_API bool Data::download(std::vector<float> & data, std::vector<size_t> & shape) const
{
    if (m_impl) {
        return m_impl->download(data, shape);
    }
    return false;
}

OPENCL_EVAL_G_API bool Data::upload(std::vector<float> data, std::vector<size_t> shape) {
    if (m_impl) {
        return m_impl->upload(std::move(data), std::move(shape));
    }
    return false;
}

OPENCL_EVAL_G_API const DataImpl * Data::get_impl() const
{
    assert(m_impl && "DataImpl is nullptr");
    return m_impl.get();
}

OPENCL_EVAL_G_API bool Data::empty() const {
    return !m_impl;
}

}