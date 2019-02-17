R"(

__kernel void multiply_element_wise(__global float* C /* out */, __global float* A, __global float* B, float sign)
{
    int x = get_global_id(0);
    C[x] = sign * A[x] * B[x];
}

)"