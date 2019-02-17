R"(

__kernel void unary_minus(__global float* C /* out */, __global float* A)
{
    int x = get_global_id(0);
    C[x] = -A[x];
}

)"