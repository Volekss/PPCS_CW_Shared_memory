
#ifndef PPCS_CW_FUNCTIONS_H
#define PPCS_CW_FUNCTIONS_H

void printMatrix(int *A, int n);

void printVector(int *A, int n);

void fillMatrix(int num, int *A, int n);

void fillVector(int num, int *A, int n);

int matrixMin(int *A, int from, int to, int n);

int vectorMax(int *A, int from, int to, int n);

void vectorMatrixMultiplication(const int *A, const int *B, int *C, int from, int to, int n);

void merge(int *A, int leftIndex, int rightIndex, int leftSize, int rightSize, int n);

void vectorSort(int *A, int from, int to);

void F(int *MA, int m, int *MK, int e, int *MS, int *MF, int l, int from, int to, int n);

#endif //PPCS_CW_FUNCTIONS_H