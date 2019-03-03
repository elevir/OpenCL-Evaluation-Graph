#include "cl_graph/Data.h"
#include "DataImpl.h"

#include <assert.h>
#include <ostream>
#include <cl_graph/Data.h>


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

Data::~Data() = default;

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

bool Data::reshape(std::vector<size_t> shape)
{
    if (m_impl) {
        return m_impl->set_shape(std::move(shape));
    }
    return false;
}

DataImpl * Data::get_impl()
{
    assert(m_impl && "DataImpl is nullptr");
    return m_impl.get();
}

bool Data::empty() const {
    return !m_impl || m_impl->empty();
}

OPENCL_EVAL_G_API  std::ostream & operator<<(std::ostream & strm, const Data & data)
{
    if (data.m_impl) {
        data.m_impl->print(strm);
    } else {
        strm << "<empty>";
    }
    return strm;
}

}