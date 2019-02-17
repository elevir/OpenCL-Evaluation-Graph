R"(

__kernel void add(__global float* C /* out */, __global float* A, __global float* B)
{
    int x = get_global_id(0);
    C[x] = A[x] + B[x];
}

)"