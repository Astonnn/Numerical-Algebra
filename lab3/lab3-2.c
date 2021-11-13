#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void DoolittleSolve(double *A, double *b, double *x, unsigned n) {
    printf("A:\n");
    Print(A, n);

    double *L = (double *)malloc(n * n * sizeof(double)),
           *U = (double *)malloc(n * n * sizeof(double));
    memset(L, 0, n * n * sizeof(double));
    memset(U, 0, n * n * sizeof(double));
    Doolittle(A, L, U, n);
    printf("L:\n");
    Print(L, n);
    printf("U:\n");
    Print(U, n);
    for (unsigned i = 0; i < n; i++) {
        x[i] = b[i];
        for (unsigned j = 0; j < i; j++)
            x[i] -= L[i * n + j] * x[j];
        x[i] /= L[i * n + i];
    }
    for (int i = n - 1; i >= 0; i--) {
        for (unsigned j = i + 1; j < n; j++)
            x[i] -= U[i * n + j] * x[j];
        x[i] /= U[i * n + i];
    }
}

void CholeskySolve(double *A, double *b, double *x, unsigned n) {
    printf("A:\n");
    Print(A, n);

    double *L = (double *)malloc(n * n * sizeof(double));
    memset(L, 0, n * n * sizeof(double));
    Cholesky(A, L, n);
    printf("L:\n");
    Print(L, n);
    for (unsigned i = 0; i < n; i++) {
        x[i] = b[i];
        for (unsigned j = 0; j < i; j++)
            x[i] -= L[i * n + j] * x[j];
        x[i] /= L[i * n + i];
    }
    for (int i = n - 1; i >= 0; i--) {
        for (unsigned j = i + 1; j < n; j++)
            x[i] -= L[j * n + i] * x[j];
        x[i] /= L[i * n + i];
    }
}

int main(int argc, char **argv) {
    unsigned n = 4;
    double A[] = {0.05, 0.07, 0.06, 0.05, 0.07, 0.10, 0.08, 0.07,
                  0.06, 0.08, 0.10, 0.09, 0.05, 0.07, 0.09, 0.10};
    double b[] = {0.23, 0.32, 0.33, 0.31};

    double *x = (double *)malloc(n * sizeof(double));
    DoolittleSolve(A, b, x, n);
    printf("x:\n");
    for (unsigned i = 0; i < n; i++) {
        printf("%f\t", x[i]);
    }
    printf("\n");

    CholeskySolve(A, b, x, n);
    printf("x:\n");
    for (unsigned i = 0; i < n; i++) {
        printf("%f\t", x[i]);
    }
    printf("\n");
    return 0;
}