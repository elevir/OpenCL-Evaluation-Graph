R"(

__kernel void multiply_element_wise(__global float* C /* out */, __global float* A, __global float* B)
{
    int x = get_global_id(0);
    int y = get_global_id(1);
    C[x] = A[x] * B[x];
//    printf("%i %i: %f * %f = %f\n", x, y, A[x], B[x], C[x]);
}

)"