#include "Data.h"

namespace cl_graph {

namespace detail {

inline bool parse_shape_data(const float & data, std::vector<size_t> & shape, size_t i, std::vector<float> & final_data)
{
    final_data.emplace_back(data);
    return true;
}

template <class T>
inline bool parse_shape_data(const std::vector<T> & data, std::vector<size_t> & shape, size_t i, std::vector<float> & final_data)
{
    if (i < shape.size()) {
        if (shape[i] != data.size()) {
            return false;
        }
    } else {
        shape.emplace_back(data.size());
    }
    for (const auto & entry : data) {
        parse_shape_data(entry, shape, i + 1, final_data);
    }
    return true;
}

inline bool ensure_shape_and_fill(const std::vector<float> & data, size_t & j, const std::vector<size_t> & shape, const size_t i, std::vector<float> & shaped_data)
{
    if (i >= shape.size() || i + 1 < shape.size()) {
        return false;
    }
    if (shaped_data.size() != shape[i]) {
        shaped_data.resize(shape[i]);
    }
    if (j + shaped_data.size() > data.size()) {
        return false;
    }
    for (auto & val : shaped_data) {
        val = data[j++];
    }
    return true;
}

template <class T>
bool ensure_shape_and_fill(const std::vector<float> & data, size_t & j, const std::vector<size_t> & shape, const size_t i, std::vector<T> & shaped_data)
{
    if (i >= shape.size()) {
        return false;
    }
    if (shaped_data.size() != shape[i]) {
        shaped_data.resize(shape[i]);
    }
    for (auto & dim : shaped_data) {
        if (!ensure_shape_and_fill(data, j, shape, i + 1, dim)) {
            return false;
        }
    }
    return true;
}

}

template <class T>
bool Data::set_shaped_data(const std::vector<T> & shaped_data)
{
    std::vector<float> final_data;
    std::vector<size_t> shape;
    if (detail::parse_shape_data(shaped_data, shape, 0, final_data)) {
        upload(final_data, shape);
        return true;
    }
    return false;
}

template <class T>
Data::Data(const std::vector<T> & data) : Data()
{
    set_shaped_data(data);
}

template <class T>
bool Data::get_shaped_data(std::vector<T> & shaped_data)
{
    std::vector<size_t> shape;
    std::vector<float> data;
    if (!download(data, shape)) {
        return false;
    }
    size_t j = 0;
    return detail::ensure_shape_and_fill(data, j, shape, 0, shaped_data);
}

}