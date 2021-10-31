#include <math.h>
#include <stdio.h>

float f(float x) { return sqrtf(x * x + 1.f) - 1.f; }
float g(float x) { return x * x / (sqrtf(x * x + 1.f) + 1.f); }

int main(int argc, char **argv) {
    for (int i = 1; i <= 10; i++) {
        printf("4^-%d\t%.12e\t%.12e\n", i, f(1.f / (1 << (i << 1))),
               g(1.f / (1 << (i << 1))));
    }
}