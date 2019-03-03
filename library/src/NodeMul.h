#pragma once

#include "cl_graph/Definitions.h"
#include <cl_graph/Node.h>
#include "INode.h"

namespace cl_graph {

OPENCL_EVAL_G_API class NodeMul : public INode {
public:
    NodeMul(Node left, Node right, const Device & device);

	Data evaluate() final;

private:
	Data evaluate_scalar(const std::vector<float> & op, const std::vector<size_t> & shape, float scalar);
	Data matrix_x_matrix(const std::vector<float> & left,
                         const std::vector<size_t> & left_shape,
                         const std::vector<float> & right,
                         const std::vector<size_t> & right_shape);
	Data tensor_x_vector(const std::vector<float> & tensor,
						 const std::vector<size_t> & shape_tensor,
						 const std::vector<float> & vector,
						 std::vector<size_t> shape_vector);
	Data vector_x_tensor(const std::vector<float> & vector,
						 std::vector<size_t> shape_vector,
						 const std::vector<float> & tensor,
						 const std::vector<size_t> & shape_tensor);
	Data evaluate_tensor_x_scalar_or_vector(const std::vector<float> & tensor,
											const std::vector<size_t> & tensor_shape,
											const std::vector<float> & vector_or_scalar,
											const std::vector<size_t> & vector_or_scalar_shape);
	Data evaluate_scalar_or_vector_x_tensor(const std::vector<float> & vector_or_scalar,
											const std::vector<size_t> & vector_or_scalar_shape,
											const std::vector<float> & tensor,
											const std::vector<size_t> & tensor_shape);

private:
    Node m_left;
    Node m_right;

    Data m_left_data;
	Data m_right_data;

    Device m_device;
};

}
