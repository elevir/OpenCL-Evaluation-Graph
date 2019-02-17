#pragma once

#include "Definitions.h"

#include <cstddef>
#include <iterator>
#include <vector>

namespace cl_graph {

class OPENCL_EVAL_G_API Data
{
public:
    Data();
    Data(const Data &) = default;
	Data(Data &&) = default;
	Data(float scalar);
	Data(std::vector<float> container, std::vector<size_t> shape);

	Data & operator=(const Data &) = delete;

	bool download(std::vector<float> & data, std::vector<size_t> & shape) const;
	bool upload(std::vector<float> data, std::vector<size_t> shape);

	bool empty() const;

	DataImpl * get_impl();

	friend std::ostream & operator<<(std::ostream & strm, const Data & data);

private:
    std::shared_ptr<DataImpl> m_impl;
};


}
