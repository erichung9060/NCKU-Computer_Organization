// Subtract Array
#include <stdio.h>

int main() {
    int a[10] = {0}, b[10] = {0}, c[10] = {0};
    int i, arr_size = 10;
    FILE *input = fopen("../input/2.txt", "r");
    for (i = 0; i < arr_size; i++) fscanf(input, "%d", &a[i]);
    for (i = 0; i < arr_size; i++) fscanf(input, "%d", &b[i]);
    for (i = 0; i < arr_size; i++) fscanf(input, "%d", &c[i]);
    fclose(input);
    
    int *p_a = &a[0];
    int *p_b = &b[0];
    int *p_c = &c[0];

    for (int i = 0; i < arr_size; i++) {
        /* Original C code segment
            *p_c++ = *p_a++ - *p_b++;
        */
        asm volatile(
            "lw t0, 0(%0)\n\t"                 // Load *p_a into t0
            "lw t1, 0(%1)\n\t"                 // Load *p_b into t1
            "sub t2, t0, t1\n\t"               // t2 = t0 - t1
            "sw t2, 0(%2)\n\t"                 // Store t2 into *p_c
            "addi %0, %0, 4\n\t"               // p_a ++
            "addi %1, %1, 4\n\t"               // p_b ++
            "addi %2, %2, 4\n\t"               // p_c ++
            : "+r"(p_a), "+r"(p_b), "+r"(p_c)  // Outputs and inputs
            :                                  // No inputs only
        );
    }

    p_c = &c[0];
    for (int i = 0; i < arr_size; i++) printf("%d ", *p_c++);
    printf("\n");
    return 0;
}
