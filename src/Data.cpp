#include "Data.h"
#include "DataImpl.h"

namespace cl_graph {

Data::Data(std::vector<float> container, std::vector<size_t> shape)
    : m_impl(new DataImpl(std::move(container),
                          std::move(shape))) {

}

bool Data::download(std::vector<float> & data, std::vector<size_t> & shape) {
    if (m_impl) {
        data = m_impl->get_data();
        shape = m_impl->get_shape();
        return true;
    }
    return false;
}

const DataImpl * Data::get_impl() const
{
    assert(m_impl && "DataImpl is nullptr");
    return m_impl;
}

bool Data::empty() const {
    return !m_impl;
}

}