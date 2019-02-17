R"(

__kernel void sqrt_func(__global float* C /* out */, __global float* A)
{
    int x = get_global_id(0);
    C[x] = sqrt(A[x]);
}

)"