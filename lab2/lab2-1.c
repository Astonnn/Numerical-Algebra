/*3.1.1(d)*/
#include <math.h>
#include <stdio.h>
#define delta (1e-10)
#define epsilon (1e-10)

// 定义 f
double f(double x) {
    return (x * (x * (x + 4) + 3) + 5) / (x * (x * (x * 2 - 9) + 18) - 2);
}

double bisection(double f(double), double l, double r) {
    double m = (l + r) / 2, fm = f(m);
    printf("|%.10f|%+e|%e|\n", m, fm, fabs(r - l));
    // printf("%.10f\t%+e\t%e\n", m, fm, fabs(r - l));
    if (fabs(r - l) < delta || fabs(fm) < epsilon) {
        return m;
    }
    if (fm > 0) {
        return bisection(f, l, m);
    } else if (fm < 0) {
        return bisection(f, m, r);
    }
}

int main(int argc, char **argv) {
    double fa = f(0.), fb = f(4.);
    printf("%f\t%f\n", fa, fb);
    double x = bisection(f, 0., 4.);
    printf("%f\t%f\n", x, f(x));
    return 0;
}