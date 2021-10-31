/*3.1.4*/
#include <math.h>
#include <stdio.h>
#define sign(x) (((x) > 0) ? 1 : (((x) < 0) ? -1 : 0))
#define delta (1e-10)
#define epsilon (1e-10)

double f(double x) {
    return x * (x * (x * (x * (x * (x * (x * (x - 36) + 546) - 4536) + 22449) -
                          67284) +
                     118124) -
                109584) +
           40320;
}

//  -36 改为 -36.001
double g(double x) {
    return x * (x * (x * (x * (x * (x * (x * (x - 36.001) + 546) - 4536) +
                               22449) -
                          67284) +
                     118124) -
                109584) +
           40320;
}

double bisection(double f(double), double l, double r) {
    double sfl = sign(f(l)), sfr = sign(f(r));
    printf("%f\t%f\n", f(l), f(r));
    if (!sfl)
        return l;
    if (!sfr)
        return r;
    if (sfl != sfr) {
        double m = (l + r) / 2, fm = f(m);
        printf("m=%f\t%f\n", m, fm);
        if (fabs(r - l) < delta || fabs(fm) < epsilon) {
            return m;
        }
        if (sign(fm) != sfl) {
            return bisection(f, l, m);
        } else if (sign(fm) != sfr) {
            return bisection(f, m, r);
        }
    }
    return (l + r) / 2;
}

int main(int argc, char **argv) {
    double x = bisection(f, 5.5, 6.5);
    printf("x=%f\tf(x)=%f\n", x, f(x));
    x = bisection(g, 5.5, 6.5);
    printf("x=%f\tg(x)=%f\n", x, g(x));
    return 0;
}