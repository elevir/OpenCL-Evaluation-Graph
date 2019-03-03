#include "NodeMul.h"

#include "cl_graph/Data.h"
#include "DataImpl.h"
#include "DeviceImpl.h"

#include "helpers/opencl.h"
#include "helpers/ClKernelsDefinitions.h"

#include <assert.h>

namespace cl_graph {

NodeMul::NodeMul(Node left, Node right, const Device & device)
    : m_left(std::move(left)),
      m_right(std::move(right)),
      m_device(std::move(device))
{

}

namespace {

bool is_scalar(const std::vector<size_t> & shape)
{
    return (shape.size() == 1) && (shape[0] == 1);
}

bool is_vector(const std::vector<size_t> & shape)
{
    return (shape.size() == 1) && (shape[0] != 1);
}

}

Data NodeMul::evaluate_scalar(const std::vector<float> & op, const std::vector<size_t> & shape, float scalar)
{
    std::vector<float> res;
    res.reserve(op.size());
    for (auto & el : op) {
        res.push_back(el * scalar);
    }
    return { std::move(res), shape };
}

Data NodeMul::matrix_x_matrix(const std::vector<float> & left,
                              const std::vector<size_t> & left_shape,
                              const std::vector<float> & right,
                              const std::vector<size_t> & right_shape)
{
    const size_t M = left_shape[0];
    const size_t K = left_shape[1];
    const size_t N = right_shape[1];
    assert((K == right_shape[0]) && "dims mismatch");
    if (m_device.get_type() == Device::NOT_CL_CPU) {
        std::vector<float> res(M * N);
        for (size_t m = 0; m < M; ++m) {
            for (size_t n = 0; n < N; ++n) {
                float acc = 0.0f;
                for (size_t k = 0; k < K; ++k) {
                    acc += left[m * K + k] * right[k * N + n];
                }
                res[m * N + n] = acc;
            }
        }
        return {std::move(res), {M, N}};
    } else {
        auto kernel = m_device.get_impl()->get_kernel(MATRIX_MUL);
        Data result;
        result.get_impl()->resize(M * N);
        auto res_cl = result.get_impl()->get_cl_data(m_device);
        auto a = m_left_data.get_impl()->get_cl_data(m_device);
        auto b = m_right_data.get_impl()->get_cl_data(m_device);
        cl_int err;
        int M2 = M;
        int N2 = N;
        int K2 = K;
        err = clSetKernelArg(kernel, 0, sizeof(int), (void *)&M2);
        err |= clSetKernelArg(kernel, 1, sizeof(int), (void *)&N2);
        err |= clSetKernelArg(kernel, 2, sizeof(int), (void *)&K2);
        err |= clSetKernelArg(kernel, 3, sizeof(cl_mem), (void *)&a.mem);
        err |= clSetKernelArg(kernel, 4, sizeof(cl_mem), (void *)&b.mem);
        err |= clSetKernelArg(kernel, 5, sizeof(cl_mem), (void *)&res_cl.mem);
        size_t local_work_size[2], global_work_size[2];

        local_work_size[0] = 1;
        local_work_size[1] = 1;
        global_work_size[0] = M;
        global_work_size[1] = N;
        err |= clEnqueueNDRangeKernel(
            m_device.get_impl()->get_queue(),
            kernel,
            2,
            nullptr,
            global_work_size,
            local_work_size,
            0,
            nullptr,
            nullptr);
        if (err == CL_SUCCESS) {
            result.get_impl()->set_shape({M, N});
            return result;
        }
        return {};
    }
}

Data NodeMul::tensor_x_vector(const std::vector<float> & tensor,
                              const std::vector<size_t> & shape_tensor,
                              const std::vector<float> & vector,
                              std::vector<size_t> shape_vector)
{
    if (shape_tensor.size() > 2) {
        return {}; // Not a 2d matrix
    }
    size_t K = shape_tensor[1];
    size_t K2 = shape_vector[0];
    if (K != K2) {
        return {};
    }
    shape_vector.push_back(1); // make matrix (K, 1)
    auto res = matrix_x_matrix(tensor, shape_tensor, vector, shape_vector);
    res.get_impl()->squeeze();
    return res;
}

Data NodeMul::vector_x_tensor(const std::vector<float> & vector,
                              std::vector<size_t> shape_vector,
                              const std::vector<float> & tensor,
                              const std::vector<size_t> & shape_tensor)
{
    if (shape_tensor.size() > 2) {
        return {}; // Not a 2d matrix
    }
    size_t K = shape_tensor[0];
    size_t K2 = shape_vector[0];
    if (K != K2) {
        return {};
    }
    shape_vector.push_back(1); // make matrix (K, 1)
    std::swap(shape_vector[0], shape_vector[1]);
    auto res = matrix_x_matrix(vector, shape_vector, tensor, shape_tensor);
    res.get_impl()->squeeze();
    return res;
}

Data NodeMul::evaluate_tensor_x_scalar_or_vector(const std::vector<float> & tensor,
                                                 const std::vector<size_t> & tensor_shape,
                                                 const std::vector<float> & vector_or_scalar,
                                                 const std::vector<size_t> & vector_or_scalar_shape)
{
    if (is_scalar(vector_or_scalar_shape)) {
        return evaluate_scalar(tensor, tensor_shape, vector_or_scalar[0]);
    }
    if (is_vector(vector_or_scalar_shape)) {
        return tensor_x_vector(tensor, tensor_shape, vector_or_scalar, vector_or_scalar_shape);
    }
    return {}; // FIXME: exception "internal error?" must never happen
}

Data NodeMul::evaluate_scalar_or_vector_x_tensor(const std::vector<float> & vector_or_scalar,
                                                 const std::vector<size_t> & vector_or_scalar_shape,
                                                 const std::vector<float> & tensor,
                                                 const std::vector<size_t> & tensor_shape)
{
    if (is_scalar(vector_or_scalar_shape)) {
        return evaluate_scalar(tensor, tensor_shape, vector_or_scalar[0]);
    }
    if (is_vector(vector_or_scalar_shape)) {
        return vector_x_tensor(vector_or_scalar, vector_or_scalar_shape, tensor, tensor_shape);
    }
    return {}; // FIXME: exception "internal error?" must never happen
}

Data NodeMul::evaluate()
{
//    if (m_device.get_type() == Device::NOT_CL_CPU) {
    m_left_data = m_left.evaluate();
    m_right_data = m_right.evaluate();
    const auto & left_shape = m_left_data.get_impl()->get_shape();
    const auto & right_shape = m_right_data.get_impl()->get_shape();
    const auto & left = m_left_data.get_impl()->get_data();
    const auto & right = m_right_data.get_impl()->get_data();
    const auto rss = right_shape.size();
    switch (left_shape.size()) {
    case 0: return {}; // FIXME: empty return (exception?)
    case 1: // scalar or vector
        return evaluate_scalar_or_vector_x_tensor(left, left_shape, right, right_shape);
    case 2:
        switch (rss) {
        case 0: return {}; // FIXME: empty return (exception?)
        case 1: return evaluate_tensor_x_scalar_or_vector(left, left_shape, right, right_shape);
        case 2: return matrix_x_matrix(left, left_shape, right, right_shape);
        default: return {};
        }
    default:
        switch (rss) {
        case 0: return {}; // FIXME: empty return (exception?)
        case 1: return evaluate_tensor_x_scalar_or_vector(left, left_shape, right, right_shape);
        default: return {}; // FIXME: exception?
        }
    }
//    } else {
//
//    }
    return {};
}


}