#pragma once

#include "dll_macros.h"
#include <cstddef>
#include <iterator>
#include <vector>

namespace cl_graph {

class DataImpl;

class OPENCL_EVAL_G_API Data
{
public:
    Data();
    Data(const Data &) = default;
	Data(Data &&) = default;
	Data(std::vector<float> container, std::vector<size_t> shape);

	Data & operator=(const Data &) = delete;

	bool download(std::vector<float> & data, std::vector<size_t> & shape) const;
	bool upload(std::vector<float> data, std::vector<size_t> shape);

	bool empty() const;

	const DataImpl * get_impl() const;
private:
    std::shared_ptr<DataImpl> m_impl;
};


}
