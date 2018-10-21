#pragma once

#include "dll_macros.h"
#include <cstddef>
#include <iterator>
#include <vector>

namespace cl_graph {

class DataImpl;

class Data
{
public:
    OPENCL_EVAL_G_API Data();
	OPENCL_EVAL_G_API Data(const Data &) = default;
	OPENCL_EVAL_G_API Data(Data &&) = default;
	OPENCL_EVAL_G_API Data(std::vector<float> container, std::vector<size_t> shape);

	OPENCL_EVAL_G_API Data & operator=(const Data &) = delete;

	OPENCL_EVAL_G_API bool download(std::vector<float> & data, std::vector<size_t> & shape) const;
	OPENCL_EVAL_G_API bool upload(std::vector<float> data, std::vector<size_t> shape);

	OPENCL_EVAL_G_API bool empty() const;

	OPENCL_EVAL_G_API const DataImpl * get_impl() const;
private:
    std::shared_ptr<DataImpl> m_impl;
};


}
