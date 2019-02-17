R"(

__kernel void add(__global float* C /* out */, __global float* A, __global float* B, float sign_a, float sign_b)
{
    int x = get_global_id(0);
    C[x] = sign_a * A[x] + sign_b * B[x];
}

)"