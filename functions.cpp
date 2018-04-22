#include <cstdio>
#include <cstdlib>

#include "functions.h"



void printMatrix(int *A, int n){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", A[i * n + j]);
        }
        printf("\n");
    }
}


void fillMatrix(int num, int *A, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i * n + j] = num;
}

/**
 * Multiplication matrix A and B
 * @param A - matrix
 * @param B - matrix
 * @param C=A*B - matrix
 */
void matrixMultiplication(const int *A, const int *B, int *C, int from, int to, int n) {
    int buf;
    for (int i = 0; i < n; i++) {
        for (int j = from; j < to; j++) {
            buf = 0;
            for (int k = 0; k < n; k++) {
                buf += A[i * n + k] * B[k * n + j];
            }
            C[i * n + j] = buf;
        }
    }
}



/**
* Searching min of matrix from to
*/
int matrixMin(int *A, int from, int to, int n) {
    int min = INT_MAX;


    for (int i = 0; i < n; i++) {
        for (int j = from; j < to; j++) {
            if ((A[i * n + j]) < min) {
                min = A[i * n + j];
            }
        }
    }
    return min;
}



/**
 *  MA = min(MO) * MK + e * ( MS * MF) * min(MR)
 *
 */
void F(int *MA, int m, int *MK, int e, int *MS, int *MF, int l, int from, int to, int n) {


    auto MBuf = (int *) malloc((size_t) (n * n * 4));

    for (int j = 0; j < n; j++) {

        for (int i = from; i < to; i++) {
            MK[j*n + i] = MK[j*n + i] * m;
        }

        for (int i = from; i < to; i++) {
            MF[j*n + i] = MF[j*n + i] * l;
        }
    }


    matrixMultiplication(MS, MF, MBuf, from, to, n);

    for (int k = 0; k < n; ++k) {
        for (int i = from; i < to; i++) {
            MA[k*n + i] =  MK[k*n + i] + e *MBuf[k*n + i] *  l;
        }
    }

    free(MBuf);
}
