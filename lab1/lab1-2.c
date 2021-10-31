#include <stdio.h>

int main(int argc, char **argv) {

    float xFloat[] = {2.718281828f, -3.141592654f, 1.414213562f, 0.5772156649f,
                      0.3010299957f};
    double xDouble[] = {2.718281828, -3.141592654, 1.414213562, 0.5772156649,
                        0.3010299957};
    float yFloat[] = {1486.2497f, 878366.9879f, -22.37492f, 4773714.647f,
                      0.000185049f};
    double yDouble[] = {1486.2497, 878366.9879, -22.37492, 4773714.647,
                        0.000185049};
    float xyFloat[5];
    double xyDouble[5];
    for (int i = 0; i < 5; i++) {
        xyFloat[i] = xFloat[i] * yFloat[i];
        xyDouble[i] = xDouble[i] * yDouble[i];
    }

    // Forward order
    float resultFloat = 0.0f;
    // xyFloat[0] + xyFloat[1] + xyFloat[2] + xyFloat[3] + xyFloat[4];
    double resultDouble = 0.0;
    // xyDouble[0] + xyDouble[1] + xyDouble[2] + xyDouble[3] + xyDouble[4];
    for (int i = 0; i < 5; i++) {
        resultFloat += xyFloat[i];
        resultDouble += xyDouble[i];
    }
    printf("Forward order:\t\t\t\t%+.6e\t%+.6e\n", resultFloat, resultDouble);

    // Reverse order
    resultFloat = 0.0f;
    // xyFloat[4] + xyFloat[3] + xyFloat[2] + xyFloat[1] + xyFloat[0];
    resultDouble = 0.0;
    // xyDouble[4] + xyDouble[3] + xyDouble[2] + xyDouble[1] + xyDouble[0];
    for (int i = 4; i >= 0; i--) {
        resultFloat += xyFloat[i];
        resultDouble += xyDouble[i];
    }
    printf("Reverse order:\t\t\t\t%+.6e\t%+.6e\n", resultFloat, resultDouble);

    unsigned Porder[] = {3, 0, 4};
    unsigned Norder[] = {1, 2};

    // Largest-to-smallest order
    resultFloat = 0.0f;
    // (xyFloat[3] + xyFloat[0] + xyFloat[4]) + (xyFloat[1] + xyFloat[2]);
    resultDouble = 0.0;
    // (xyDouble[3] + xyDouble[0] + xyDouble[4]) + (xyDouble[1] + xyDouble[2]);
    float pFloat = 0.0f, nFloat = 0.0f;
    double pDouble = 0.0, nDouble = 0.0;
    for (int i = 0; i < 3; i++) {
        pFloat += xyFloat[Porder[i]];
        pDouble += xyDouble[Porder[i]];
    }
    for (int i = 0; i < 2; i++) {
        nFloat += xyFloat[Norder[i]];
        nDouble += xyDouble[Norder[i]];
    }
    resultFloat = pFloat + nFloat;
    resultDouble = pDouble + nDouble;
    printf("Largest-to-smallest order:\t%+.6e\t%+.6e\n", resultFloat,
           resultDouble);

    // Smallest-to-largest order
    resultFloat = 0.0f;
    // (xyFloat[4] + xyFloat[0] + xyFloat[3]) + (xyFloat[2] + xyFloat[1]);
    resultDouble = 0.0;
    // (xyDouble[4] + xyDouble[0] + xyDouble[3]) + (xyDouble[2] + xyDouble[1]);
    pFloat = 0.0f, nFloat = 0.0f;
    pDouble = 0.0, nDouble = 0.0;
    for (int i = 2; i >= 0; i--) {
        pFloat += xyFloat[Porder[i]];
        pDouble += xyDouble[Porder[i]];
    }
    for (int i = 1; i >= 0; i--) {
        nFloat += xyFloat[Norder[i]];
        nDouble += xyDouble[Norder[i]];
    }
    resultFloat = pFloat + nFloat;
    resultDouble = pDouble + nDouble;
    printf("Smallest-to-largest order:\t%+.6e\t%+.6e\n", resultFloat,
           resultDouble);
}