// Matrix Multiply
#include <stdio.h>

/*
 *|h11 h12 h13| |x1 x2| |y1 y2| | h11*x1+h12*x3+h13*x5 h11*x2+h12*x4+h13*x6|
 *|h21 h22 h23|*|x3 x4|=|y3 y4|=| h21*x1+h22*x3+h23*x5 h21*x2+h22*x4+h23*x6|
 *|h31 h32 h33| |x5 x6| |y5 y6| | h31*x1+h32*x5+h33*x5 h31*x2+h32*x4+h33*x6|
 *
 * Element are to store in following order:
 *
 * matrix h[9]={h11,h12,h13, h21,h22,h23, h31,h32,h33}
 * vector x[6]={x1,x2, x3,x4, x5,x6}
 * vector y[6]={y1,y2, y3,y4, y5,y6}
 */

int main() {
    int f, i, j;
    int h[9] = {0}, x[6] = {0}, y[6] = {0};
    FILE *input = fopen("../input/3.txt", "r");
    for (i = 0; i < 9; i++) fscanf(input, "%d", &h[i]);
    for (i = 0; i < 6; i++) fscanf(input, "%d", &x[i]);
    for (i = 0; i < 6; i++) fscanf(input, "%d", &y[i]);
    fclose(input);

    int *p_x = &x[0];
    int *p_h = &h[0];
    int *p_y = &y[0];

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 2; j++) {
            for (f = 0; f < 3; f++){
                /* Original C code segment
                    y[2*i+j] += h[3*i+f] * x[2*f+j];
                */
                asm volatile(
                    "lw t0, 0(%0)\n\t"            // Load y[2i+j] into t0
                    "lw t1, 0(%1)\n\t"            // Load h[3i+f] into t1
                    "lw t2, 0(%2)\n\t"            // Load x[2f+j] into t2
                    "mul t3, t1, t2\n\t"          // t3 =  h[3i+f] * x[2f+j]
                    "add t0, t0, t3\n\t"          // y[2i+j] += t3
                    "sw t0, 0(%0)\n\t"            // Store t0 into y[2i+j]
                    :                             // No outputs, directly modifying memory
                    : "r" (p_y + 2*i+j), "r" (p_h + 3*i+f), "r" (p_x + 2*f+j)  // Inputs
                );
            }
        }
    }

    p_y = &y[0];
    for (i = 0; i < 6; i++) printf("%d ", *p_y++);
    printf("\n");
    return 0;
}
