#pragma once

#include "dll_macros.h"
#include <cstddef>
#include <vector>

namespace cl_graph {

class DataImpl {
public:
    OPENCL_EVAL_G_API DataImpl() = default;
	OPENCL_EVAL_G_API DataImpl(const DataImpl &) = delete;

	OPENCL_EVAL_G_API bool download(std::vector<float> & data, std::vector<size_t> & shape) const;
	OPENCL_EVAL_G_API bool upload(std::vector<float> data, std::vector<size_t> shape);

	OPENCL_EVAL_G_API const std::vector<float> & get_data() const { return m_data; }
	OPENCL_EVAL_G_API const std::vector<size_t> & get_shape() const { return m_shape; }

private:
    std::vector<float> m_data;
    std::vector<size_t> m_shape;
};

}