#include "Data.h"

namespace cl_graph {

namespace detail {

template <class Cont>
class has_size
{
    template <typename C> static std::true_type test(decltype(&C::size));
    template <typename C> static std::false_type test(...);
public:
    typedef decltype(test<Cont>(nullptr)) type;
    static constexpr bool value = std::is_same<std::true_type, decltype(test<Cont>(0))>::value;
};

template <typename T, typename... Args>
class has_resize
{
    template <typename C, typename = decltype( std::declval<C>().resize(std::declval<Args>()...) )> static std::true_type test(int);
    template <typename C> static std::false_type test(...);

public:
    static constexpr bool value = std::is_same<std::true_type, decltype(test<T>(0))>::value;
};

template <class T, typename std::enable_if_t<!has_size<T>::value && !std::is_array<T>::value> * = nullptr>
inline bool parse_shape_data(std::vector<size_t> & shape, size_t i, std::vector<float> & final_data, const T & data)
{
    if (shape.empty()) {
        shape.emplace_back(1);
    }
    final_data.emplace_back(data);
    return true;
}

template <class T, typename std::enable_if_t<has_size<T>::value || std::is_array<T>::value> * = nullptr>
inline bool parse_shape_data(std::vector<size_t> & shape, size_t i, std::vector<float> & final_data, const T & data)
{
    if (i < shape.size()) {
        if (shape[i] != std::size(data)) {
            return false;
        }
    } else {
        shape.emplace_back(std::size(data));
    }
    for (const auto & entry : data) {
        parse_shape_data(shape, i + 1, final_data, entry);
    }
    return true;
}

template <class C, class ...T>
inline bool parse_variadic_shape_data(std::vector<size_t> & shape, size_t i, std::vector<float> & final_data, const C & data)
{
    return parse_shape_data(shape, i + 1, final_data, data);
}

template <class C, class ...T>
inline bool parse_variadic_shape_data(std::vector<size_t> & shape, size_t i, std::vector<float> & final_data, const C & data, T... lists)
{
    if (!parse_shape_data(shape, i + 1, final_data, data)) {
        return false;
    }
    return parse_variadic_shape_data(shape, i, final_data, lists...);
}

template <class ...T>
inline bool parse_variadic_shape_data(std::vector<size_t> & shape, size_t i, std::vector<float> & final_data, T... lists)
{
    if (i < shape.size()) {
        if (shape[i] != sizeof...(lists)) {
            return false;
        }
    } else {
        shape.emplace_back(sizeof...(lists));
    }
    return parse_shape_data(shape, i, final_data, lists...);
}


template <class T, typename std::enable_if_t<std::is_arithmetic<T>::value> * = nullptr>
inline bool ensure_shape_and_fill(const std::vector<float> & data, size_t & j, const std::vector<size_t> & shape, const size_t i, T & shaped_data)
{
    if (i < shape.size()) {
        return false;
    }
    shaped_data = data[j++];
    return true;
}

template <class T, typename std::enable_if_t<(has_size<T>::value && has_resize<T, size_t>::value) && !std::is_arithmetic<T>::value> * = nullptr>
bool ensure_shape_and_fill(const std::vector<float> & data, size_t & j, const std::vector<size_t> & shape, const size_t i, T & shaped_data)
{
    if (i >= shape.size()) {
        return false;
    }
    if (std::size(shaped_data) != shape[i]) {
        shaped_data.resize(shape[i]);
    }
    for (auto & dim : shaped_data) {
        if (!ensure_shape_and_fill(data, j, shape, i + 1, dim)) {
            return false;
        }
    }
    return true;
}

template <class T, typename std::enable_if_t<!(has_size<T>::value && has_resize<T, size_t>::value) && !std::is_arithmetic<T>::value> * = nullptr>
bool ensure_shape_and_fill(const std::vector<float> & data, size_t & j, const std::vector<size_t> & shape, const size_t i, T & shaped_data)
{
    if (i >= shape.size()) {
        return false;
    }
    if (std::size(shaped_data) != shape[i]) {
        return false;
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
bool Data::set_shaped_data(const T & shaped_data)
{
    std::vector<float> final_data;
    std::vector<size_t> shape;
    if (detail::parse_shape_data(shape, 0, final_data, shaped_data)) {
        upload(final_data, shape);
        return true;
    }
    return false;
}

template <class T>
Data::Data(const T & data) : Data()
{
    set_shaped_data(data);
}

template <class ...T>
bool Data::set_shaped_data(T... shaped_data)
{
    std::vector<float> final_data;
    std::vector<size_t> shape;
    if (detail::parse_variadic_shape_data(shape, 0, final_data, shaped_data...)) {
        upload(final_data, shape);
        return true;
    }
    return false;
}

template <class ...T>
Data::Data(std::initializer_list<T> && ... data) : Data()
{
    set_shaped_data(data...);
}

template <class ...T>
Data::Data(std::initializer_list<std::initializer_list<T>> && ... data) : Data()
{
    set_shaped_data(data...);
}

template <class T>
bool Data::get_shaped_data(T & shaped_data)
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