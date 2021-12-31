#include "LU.h"
#include <stdio.h>
#include <time.h>

void Print(double *matrix, unsigned n) {
    putchar('(');
    for (unsigned i = 0; i + 1 < n; i++) {
        printf("%f, ", matrix[i]);
    }
    printf("%f)^T", matrix[n - 1]);
}

double *Product(double *A, double *x, unsigned n) {
    double *result = (double *)malloc(n * sizeof(double));
    for (unsigned i = 0; i < n; i++) {
        result[i] = 0.;
        for (unsigned j = 0; j < n; j++) {
            result[i] += A[i * n + j] * x[j];
        }
    }
    return result;
}

double Distance(double *x, double *y, unsigned n) {
    // if (!n)
    //     return 0.;
    double rst = fabs(x[0] - y[0]);
    for (unsigned i = 1; i < n; i++) {
        if (fabs(x[i] - y[i]) > rst)
            rst = fabs(x[i] - y[i]);
    }
    return rst;
}

double *Divide(double *x, double divisor, unsigned n) {
    for (unsigned i = 0; i < n; i++) {
        x[i] /= divisor;
    }
    return x;
}

double Norm(double *x, unsigned n) {
    // if (!n)
    //     return 0.;
    double rst = fabs(x[0]);
    for (unsigned i = 1; i < n; i++) {
        if (fabs(x[i]) > rst)
            rst = fabs(x[i]);
    }
    return rst;
}

double PowerMethod(double *A, double **x, double phi(double *, unsigned),
                   unsigned n, double *r) {
    double *y = Product(A, *x, n);
    *r = phi(y, n) / phi(*x, n);
    Divide(y, Norm(y, n), n);
    double d = Distance(*x, y, n);
    free(*x);
    *x = y;
    return d;
}

double InversePowerMethodDoolittle(double *L, double *U, double **x,
                                   double phi(double *, unsigned), unsigned n,
                                   double *r) {
    double *y = DoolittleSolve_(L, U, *x, n);
    *r = phi(y, n) / phi(*x, n);
    Divide(y, Norm(y, n), n);
    double d = Distance(*x, y, n);
    free(*x);
    *x = y;
    return d;
}

double Band(double *M, unsigned n, unsigned x, unsigned y, double value) {
    for (unsigned i = x, j = y; i < n && j < n; i++, j++) {
        M[i * n + j] = value;
    }
}

double Phi(double *x, unsigned n) { return x[1]; }

double Psi(double *x, unsigned n) { return x[0]; }

double Phi_(double *x, unsigned n) { return x[n - 1]; }

int main(int argc, char **argv) {
    // 例1
    unsigned n = 3;
    double AA[] = {6, 5, -5, 2, 6, -2, 2, 5, -1};
    double *A = (double *)AA, *x = (double *)malloc(n * sizeof(double));
    x[0] = -1, x[1] = 1, x[2] = 1;
    printf("k=0\tx^{0}=");
    Print(x, n);
    putchar('\n');
    unsigned count = 0;
    double r;
    while (PowerMethod(A, &x, Phi, n, &r) > 1e-5) {
        count++;
        printf("k=%u\tx^{%u}=", count, count);
        Print(x, n);
        printf("\tr_{%d}=%f\n", count - 1, r);
    }
    free(x);
    // 例2
    x = (double *)malloc(n * sizeof(double));
    x[0] = 3, x[1] = 7, x[2] = -13;
    printf("k=0\tx^{0}=");
    Print(x, n);
    putchar('\n');
    count = 0;
    double *L = (double *)malloc(n * n * sizeof(double)),
           *U = (double *)malloc(n * n * sizeof(double));
    Doolittle(A, L, U, n);
    while (InversePowerMethodDoolittle(L, U, &x, Psi, n, &r) > 0 &&
           count <= 10) {
        count++;
        printf("k=%u\tx^{%u}=", count, count);
        Print(x, n);
        printf("\tr_{%d}=%f\n", count - 1, r);
    }
    free(x);
    free(L);
    free(U);
    // PowerMethod
    clock_t t_start, t_end;
    n = 15;
    double delta = 1e-10;
    A = (double *)malloc(n * n * sizeof(double));
    memset(A, 0, n * n * sizeof(double));
    A[0] = 4.14;
    Band(A, n, 1, 1, 2.);
    Band(A, n, 0, 1, -1.);
    Band(A, n, 1, 0, -1.);
    x = (double *)malloc(n * sizeof(double));
    for (unsigned i = 0; i < n; i++) {
        x[i] = 1.;
    }
    printf("k=0\tx^{0}=");
    Print(x, n);
    putchar('\n');
    count = 0;
    t_start = clock();
    while (PowerMethod(A, &x, Phi_, n, &r) > delta) {
        count++;
        printf("k=%u\tx^{%u}=", count, count);
        Print(x, n);
        printf("\tr_{%d}=%f\n", count - 1, r);
    }
    t_end = clock();
    printf("time: %ld\n", t_end - t_start);
    // InversePowerMethod
    for (unsigned i = 0; i < n; i++) {
        x[i] = 1.;
    }
    printf("k=0\tx^{0}=");
    Print(x, n);
    putchar('\n');
    count = 0;
    L = (double *)malloc(n * n * sizeof(double)),
    U = (double *)malloc(n * n * sizeof(double));
    Doolittle(A, L, U, n);
    t_start = clock();
    while (InversePowerMethodDoolittle(L, U, &x, Phi_, n, &r) > delta) {
        count++;
        printf("k=%u\tx^{%u}=", count, count);
        Print(x, n);
        printf("\tr_{%d}=%f\n", count - 1, r);
    }
    t_end = clock();
    printf("time: %ld\n", t_end - t_start);
    free(x);
    free(L);
    free(U);
    free(A);
    return 0;
}