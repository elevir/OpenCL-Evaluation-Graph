R"(
/*
 * Naive implementation of matrix multiplication
 * @param M - height of matrix A
 * @param N - width of matrix B
 * @param K - width of matrix A and height of matrix B
 * @param A - matrix A
 * @param B - matrix B
 * @param C - result
 */

__kernel void matrix_mul(const int M, const int N, const int K,
                         __global const float  * A,
                         __global const float  * B,
                         __global float   * C)
{
    const int m = get_global_id(0);
    const int n = get_global_id(1);

    float acc = 0.0f;
    for (int k=0; k<K; k++) {
        acc += A[m * K + k] * B[k * N + n];
    }

    C[m * N + n] = acc;
}

)"