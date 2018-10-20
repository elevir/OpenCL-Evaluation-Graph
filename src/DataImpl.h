#pragma once

#include <cstddef>
#include <vector>

namespace cl_graph {

class DataImpl {
public:
    DataImpl() = default;
    DataImpl(const DataImpl &) = delete;

    bool download(std::vector<float> & data, std::vector<size_t> & shape) const;
    bool upload(std::vector<float> data, std::vector<size_t> shape);

    const std::vector<float> & get_data() const { return m_data; }
    const std::vector<size_t> & get_shape() const { return m_shape; }

private:
    std::vector<float> m_data;
    std::vector<size_t> m_shape;
};

}