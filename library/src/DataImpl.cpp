#include "DataImpl.h"

#include "DeviceImpl.h"

#include <ostream>

namespace cl_graph {

bool DataImpl::download(std::vector<float> & data, std::vector<size_t> & shape) const
{
    if (m_cl_mem.mem != nullptr) {
        clEnqueueReadBuffer(m_cl_mem.queue, m_cl_mem.mem, CL_TRUE, 0, m_data.size() * sizeof(float), (void*)m_data.data(), 0, nullptr, nullptr);
    }
    data = m_data;
    shape = m_shape;
    return true;
}

bool DataImpl::upload(std::vector<float> data, std::vector<size_t> shape)
{
    m_data = std::move(data);
    m_shape = std::move(shape);
    // TODO: resend or cleanup cl device memory
    return true;
}

ClMem DataImpl::get_cl_data(const Device & device, size_t broadcast_size)
{
    if (m_cl_mem.mem == nullptr) {
        m_cl_mem.device = device.get_impl()->get_device_id();
        m_cl_mem.queue = device.get_impl()->get_queue();
        if (!(m_shape.size() == 1 && m_shape[0] == 1)) {
            broadcast_size = 0;
        }
        std::vector<float> data;
        if (broadcast_size) {
            data = std::vector<float> (broadcast_size, m_data[0]);
        }
        auto _data = broadcast_size ? data.data() : m_data.data();
        auto _sz = broadcast_size ? data.size() : m_data.size();

        cl_int err;
        m_cl_mem.mem = clCreateBuffer(device.get_impl()->get_context(),
            CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
            _sz * sizeof(float),
            _data,
            &err);
        if (err != CL_SUCCESS) {
            return ClMem();
        }

    } else if (m_cl_mem.device != device.get_impl()->get_device_id()) {
        // TODO: relocate to other device memory
    }
    return m_cl_mem;
}

void DataImpl::resize(size_t sz)
{
    if (m_data.size() < sz) {
        if (m_cl_mem.mem != nullptr) {
            // TODO: copy data before allocating new
        } else {
            m_data.resize(sz);
        }
    }
}

void DataImpl::print(std::ostream & strm) const
{
    if (m_cl_mem.mem != nullptr) {
        clEnqueueReadBuffer(m_cl_mem.queue, m_cl_mem.mem, CL_TRUE, 0, m_data.size() * sizeof(float), (void*)m_data.data(), 0, nullptr, nullptr);
    }
    if (m_shape.empty() || m_data.empty()) {
        strm << "<empty>";
    }
    if (m_shape.size() > 2) {
        strm << "[tensor] " << m_shape[0];
        for (size_t d = 1; d < m_shape.size(); d++) {
            strm << "x" << m_shape[d];
        }
        strm << "[data]";
        for (const auto & el : m_data) {
            strm << " " << el;
        }
    }
    if (m_shape.size() == 2) {
        strm << "[matrix]:\n";
        for (size_t i = 0; i < m_shape[0]; ++i) {
            size_t j = 0;
            for (; j < m_shape[1] - 1; ++j) {
                strm << m_data[i * m_shape[1] + j] << " ";
            }
            strm << m_data[i * m_shape[1] + j];
            if (i + 1 != m_shape[0]) {
                strm << std::endl;
            }
        }
    }
    if (m_shape.size() == 1)  {
        if (m_shape[0] == 1) {
            strm << "[scalar] " << m_data[0];
        } else {
            strm << "[vector]";
            for (const auto & el : m_data) {
                strm << " " << el;
            }
        }
    }
}

}