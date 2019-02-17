R"(

__kernel void abs_func(__global float* C /* out */, __global float* A)
{
    int x = get_global_id(0);
    C[x] = (A[x] > 0 ? A[x] : -A[x]);
}

)"