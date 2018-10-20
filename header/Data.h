#pragma once

#include <cstddef>
#include <iterator>
#include <vector>

namespace cl_graph {

class DataImpl;

class Data
{
public:
    Data() = default;
    Data(std::vector<float> container, std::vector<size_t> shape);

    bool download(std::vector<float> & data, std::vector<size_t> & shape);

    bool empty() const;

    const DataImpl * get_impl() const;
private:
    DataImpl * m_impl = nullptr;
};


}
