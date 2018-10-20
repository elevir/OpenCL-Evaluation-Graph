#include "Data.h"
#include "DataImpl.h"

namespace cl_graph {

Data::Data(std::vector<float> container, std::vector<size_t> shape)
{
    m_impl = std::make_shared<DataImpl>();
    upload(std::move(container), std::move(shape));
}

Data::Data()
{
    m_impl = std::make_shared<DataImpl>();
}

bool Data::download(std::vector<float> & data, std::vector<size_t> & shape) const
{
    if (m_impl) {
        return m_impl->download(data, shape);
    }
    return false;
}

bool Data::upload(std::vector<float> data, std::vector<size_t> shape) {
    if (m_impl) {
        return m_impl->upload(std::move(data), std::move(shape));
    }
    return false;
}

const DataImpl * Data::get_impl() const
{
    assert(m_impl && "DataImpl is nullptr");
    return m_impl.get();
}

bool Data::empty() const {
    return !m_impl;
}

}