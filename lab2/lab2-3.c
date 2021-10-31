/*3.2.3*/
#include <math.h>
#include <stdio.h>
#define delta (1e-15)
#define epsilon (1e-15)

double f(double x) { return tan(x) / (x * x); }

// f'
double f1(double x) {
    return 1 / (x * x * cos(x) * cos(x)) - 2 * sin(x) / (x * x * x * cos(x));
}

// f''
double f2(double x) {
    return 2 *
           ((3 * tan(x) / x - 2 / (cos(x) * cos(x))) / x +
            sin(x) / (cos(x) * cos(x) * cos(x))) /
           (x * x);
}

double newton(double f(double), double f1(double), double x) {
    double fx = f(x), y = x - fx / f1(x);
    printf("%f\t%+e\t%f\t%f\n", x, fx, f1(x), y);
    if ((x - y < delta && x - y > -delta) || (fx > -epsilon && fx < epsilon)) {
        return y;
    }
    return newton(f, f1, y);
}

int main(int argc, char **argv) {
    double x = newton(f1, f2, 1.0);
    printf("x=%.20f\nf(x)=%.20f\n", x, f(x));
    return 0;
}