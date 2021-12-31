#pragma once
#include <math.h>
#include <stdlib.h>
#include <string.h>

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

double *DoolittleSolve_(double *L, double *U, double *b, unsigned n) {
    double *x = (double *)malloc(n * sizeof(double));
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
    return x;
}

double *DoolittleSolve(double *A, double *b, unsigned n) {
    double *L = (double *)malloc(n * n * sizeof(double)),
           *U = (double *)malloc(n * n * sizeof(double));
    Doolittle(A, L, U, n);
    double *x = DoolittleSolve_(L, U, b, n);
    free(L);
    free(U);
    return x;
}

double *CholeskySolve_(double *L, double *b, unsigned n) {
    double *x = (double *)malloc(n * sizeof(double));
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
    return x;
}

double *CholeskySolve(double *A, double *b, unsigned n) {
    double *L = (double *)malloc(n * n * sizeof(double));
    Cholesky(A, L, n);
    double *x = CholeskySolve_(L, b, n);
    free(L);
    return x;
}