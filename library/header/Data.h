#pragma once

#include "Definitions.h"

#include "Node.h"

#include <cstddef>
#include <iterator>
#include <vector>

namespace cl_graph {

class OPENCL_EVAL_G_API Data {
public:
    Data();
    Data(const Data &) = default;
    Data(Data &&) = default;
    Data(std::vector<float> container, std::vector<size_t> shape);
    template<class ...T>
    Data(const T & ... data);
    template<class ...T>
    Data(std::initializer_list<T> && ... data);
    template<class ...T>
    Data(std::initializer_list<std::initializer_list<T>> && ... data);

    Data & operator=(const Data &) = delete;

    template<class T>
    bool get_shaped_data(T & shaped_data);
    template<class ...T>
    bool set_shaped_data(const T & ... shaped_data);

    template<class ...T, void * = nullptr>
    bool set_shaped_data(std::initializer_list<T> && ... data);
    template<class ...T>
    bool set_shaped_data(std::initializer_list<std::initializer_list<T>> && ... data);

    bool download(std::vector<float> & data, std::vector<size_t> & shape) const;
    bool upload(std::vector<float> data, std::vector<size_t> shape);

    bool empty() const;

    DataImpl * get_impl();

    friend std::ostream & operator<<(std::ostream & strm, const Data & data);

private:
    std::shared_ptr<DataImpl> m_impl;
};

}

#include "Data.inl"
