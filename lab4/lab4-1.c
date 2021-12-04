#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double Jacobi(double *A, double *x, double *b, unsigned n) {
    double *rst = (double *)malloc(n * sizeof(double));
    double max = 0.;
    for (unsigned i = 0; i < n; i++) {
        rst[i] = .0;
        for (unsigned j = 0; j < n; j++) {
            if (i == j) {
                rst[i] += b[i];
            } else {
                rst[i] -= A[i * n + j] * x[j];
            }
        }
        rst[i] /= A[i * n + i];
        fabs(rst[i] - x[i]) > max && (max = fabs(rst[i] - x[i]));
    }
    memmove(x, rst, n * sizeof(double));
    return max;
}

double Gauss_Seidel(double *A, double *x, double *b, unsigned n) {
    double max = 0.;
    for (unsigned i = 0; i < n; i++) {
        double xi = x[i];
        x[i] = .0;
        for (unsigned j = 0; j < n; j++) {
            if (i == j) {
                x[i] += b[i];
            } else {
                x[i] -= A[i * n + j] * x[j];
            }
        }
        x[i] /= A[i * n + i];
        fabs(xi - x[i]) > max && (max = fabs(xi - x[i]));
    }
    return max;
}

void Print(double *X, unsigned n) {
    for (unsigned i = 0; i < n; i++) {
        printf("%f ", X[i]);
    }
    putchar('\n');
}

double Band(double *M, unsigned n, unsigned x, unsigned y, double value) {
    for (unsigned i = x, j = y; i < n && j < n; i++, j++) {
        M[i * n + j] = value;
    }
}

int main(int argc, char **argv) {
    unsigned n = 30;
    double delta = 1e-5;
    double *A = (double *)malloc(n * n * sizeof(double));
    memset(A, 0, n * n * sizeof(double));
    Band(A, n, 0, 0, 2.8);
    Band(A, n, 0, 1, -1.);
    Band(A, n, 1, 0, -1.);
    double *b = (double *)malloc(n * sizeof(double));
    for (unsigned i = 0; i < n; i++) {
        b[i] = 2.;
    }
    double *x = (double *)malloc(n * sizeof(double));
    memset(x, 0, n * sizeof(double));
    unsigned count = 0;
    while (Jacobi(A, x, b, n) > delta) {
        printf("x_{%d}:\n", ++count);
        Print(x, n);
    }

    putchar('\n');
    memset(x, 0, n * sizeof(double));
    count = 0;
    while (Gauss_Seidel(A, x, b, n) > delta) {
        printf("x_{%d}:\n", ++count);
        Print(x, n);
    }
    return 0;
}