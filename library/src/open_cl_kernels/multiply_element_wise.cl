R"(

__kernel void multiply_element_wise(__global float* C /* out */, __global float* A, __global float* B)
{
    int x = get_global_id(0);
    C[x] = A[x] * B[x];
}

)"