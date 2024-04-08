// Matrix Multiply Without For Loop
#include <stdio.h>

int main() {
    int i = 0;
    int h[9] = {0}, x[6] = {0}, y[6] = {0};
    FILE *input = fopen("../input/4.txt", "r");
    for (i = 0; i < 9; i++) fscanf(input, "%d", &h[i]);
    for (i = 0; i < 6; i++) fscanf(input, "%d", &x[i]);
    for (i = 0; i < 6; i++) fscanf(input, "%d", &y[i]);
    fclose(input);

    int *p_x = &x[0];
    int *p_h = &h[0];
    int *p_y = &y[0];
    /* Original C code segment
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 2; j++) {
                for (int f = 0; f < 3; f++){
                    y[2*i+j] += h[3*i+f] * x[2*f+j];
                }
            }
        }
    */
    asm volatile(
        "li t0, 0\n\t"               // (t0)i = 0
        "i_loop:\n\t"

            "li t1, 0\n\t"               // (t1)j = 0
            "j_loop:\n\t"

                "li t2, 0\n\t"               // (t2)f = 0
                "f_loop:\n\t"                     

                    "slli t3, t0, 1\n\t"          // t3 = 2i
                    "add t3, t3, t0\n\t"          // t3 = 3i
                    "add t3, t3, t2\n\t"          // t3 = 3i+f
                    "slli t3, t3, 2\n\t"          // t3 = (3i+f) * 4(byte)
                    "add t3, t3, %[p_h]\n\t"      // t3 = h[3i+f]
                    "lw t5, 0(t3)\n\t"            // Load h[3i+f] into t5

                    "slli t3, t2, 1\n\t"          // t3 = 2f
                    "add t3, t3, t1\n\t"          // t3 = 2f+j
                    "slli t3, t3, 2\n\t"          // t3 = (3i+f) * 4(byte)
                    "add t3, t3, %[p_x]\n\t"      // t3 = x[2f+j]
                    "lw t6, 0(t3)\n\t"            // Load x[2f+j] into t6

                    "slli t3, t0, 1\n\t"          // t3 = 2i
                    "add t3, t3, t1\n\t"          // t3 = 2i+j
                    "slli t3, t3, 2\n\t"          // t3 = (3i+f) * 4(byte)
                    "add t3, t3, %[p_y]\n\t"      // t3 = y[2i+j]
                    "lw t4, 0(t3)\n\t"            // Load y[2i+j] into t4

                    "mul t5, t5, t6\n\t"          // t5 =  h[3i+f] * x[2f+j]
                    "add t4, t4, t5\n\t"          // t4 =  y[2i+j] + h[3i+f] * x[2f+j]
                    "sw t4, 0(t3)\n\t"            // Store t4 into y[2i+j]

                "addi t2, t2, 1\n\t"          // f++
                "li t3, 3\n\t"                // t3 = 3 
                "blt t2, t3, f_loop\n\t"      // if f < 3 

            "addi t1, t1, 1\n\t"          // j++
            "li t3, 2\n\t"                // t3 = 2
            "blt t1, t3, j_loop\n\t"      // if j < 2 

        "addi t0, t0, 1\n\t"          // i++
        "li t3, 3\n\t"                // t3 = 3
        "blt t0, t3, i_loop\n\t"      // if i < 3
        :                             // No outputs, directly modifying memory
        : [p_y] "r" (p_y), [p_h] "r" (p_h), [p_x] "r" (p_x)  // Inputs
    );

    p_y = &y[0];
    for (i = 0; i < 6; i++) printf("%d ", *p_y++);
    printf("\n");
    return 0;
}
