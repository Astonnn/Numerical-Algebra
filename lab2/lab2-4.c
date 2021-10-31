/*3.2.4*/
#include <math.h>
#include <stdio.h>

// 定义 f
double f(double x) { return x * (x * (x - 5) + 3) - 7; }

// 定义 f'
double f1(double x) { return x * (3 * x - 10) + 3; }

double newton(double f(double), double f1(double), double x, int times) {
    printf("%f\t%+e\t%f\n", x, f(x), f1(x));
    for (int i = 0; i < times; i++) {
        x -= f(x) / f1(x);
        printf("%f\t%+e\t%f\n", x, f(x), f1(x));
    }
    return x;
}

int main(int argc, char **argv) {
    double x = newton(f, f1, 5.0, 10);
    printf("%.20f\n", x);
    return 0;
}