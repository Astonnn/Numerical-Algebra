#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// HilbertMatrix
void HilbertMatrix(double *matrix, unsigned n) {
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < n; j++) {
            matrix[i * n + j] = 1 / (i + j + 1.);
        }
    }
}

void Print(double *matrix, unsigned n) {
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < n; j++) {
            printf("%f\t", matrix[i * n + j]);
        }
        printf("\n");
    }
}

void Doolittle(double *matrix, double *L, double *U, unsigned n) {
    for (unsigned i = 0; i < n; i++) {
        L[i * n + i] = 1.;
        for (unsigned j = i; j < n; j++) {
            U[i * n + j] = matrix[i * n + j];
            for (unsigned k = 0; k < i; k++) {
                U[i * n + j] -= L[i * n + k] * U[k * n + j];
            }
        }
        for (unsigned j = i + 1; j < n; j++) {
            L[j * n + i] = matrix[j * n + i];
            for (unsigned k = 0; k < i; k++) {
                L[j * n + i] -= L[j * n + k] * U[k * n + i];
            }
            L[j * n + i] /= U[i * n + i];
        }
    }
}

void Cholesky(double *matrix, double *L, unsigned n) {
    for (unsigned i = 0; i < n; i++) {
        L[i * n + i] = matrix[i * n + i];
        for (unsigned k = 0; k < i; k++) {
            L[i * n + i] -= L[i * n + k] * L[i * n + k];
        }
        L[i * n + i] = sqrt(L[i * n + i]);
        for (unsigned j = i + 1; j < n; j++) {
            L[j * n + i] = matrix[j * n + i];
            for (unsigned k = 0; k < i; k++) {
                L[j * n + i] -= L[j * n + k] * L[i * n + k];
            }
            L[j * n + i] /= L[i * n + i];
        }
    }
}

void Product(double *A, double *B, unsigned n) {
    double *result = (double *)malloc(n * n * sizeof(double));
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < n; j++) {
            result[i * n + j] = 0.;
            for (unsigned k = 0; k < n; k++) {
                result[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
    memcpy(A, result, n * n * sizeof(double));
}

void Transpose(double *A, double *AT, unsigned n) {
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < n; j++) {
            AT[i * n + j] = A[j * n + i];
        }
    }
}

int main(int argc, char **argv) {
    unsigned n = 7;
    double *H = (double *)malloc(n * n * sizeof(double));
    HilbertMatrix(H, n);
    printf("HilbertMatrix:\n");
    Print(H, n);

    double *L = (double *)malloc(n * n * sizeof(double)),
           *U = (double *)malloc(n * n * sizeof(double));
    Doolittle(H, L, U, n);
    printf("L:\n");
    Print(L, n);
    printf("U:\n");
    Print(U, n);
    Product(L, U, n);
    printf("L.U:\n");
    Print(L, n);

    memset(L, 0, n * n * sizeof(double));
    Cholesky(H, L, n);
    printf("L:\n");
    Print(L, n);
    Transpose(L, U, n);
    printf("L^T:\n");
    Print(U, n);
    Product(L, U, n);
    printf("L.L^T:\n");
    Print(L, n);

    return 0;
}