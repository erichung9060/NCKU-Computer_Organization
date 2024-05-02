// exercise1_1.c
/*
 * description: Gregory-Leibniz series
 *
 *    we use Leibniz formula to approximate Pi
 *
 *    pi/4 = (1 - 1/3 + 1/5 - 1/7 + 1/9 - ...)
 *    pi   = 4(1 - 1/3 + 1/5 - 1/7 + 1/9 - ...)
 *
 */

#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "answer.h"
#include "pi.h"

int main() {
    double pi = 0.0;
    printf("Number of iterations: %d\n", N);

    /* original code
    for (int i = 0, sign = 1; i < N; i++, sign *= -1) {
        double term = sign / double(2 * i + 1);
        pi += term;
    }
    */
    asm volatile(
        #include "pi.c"

        : [add_cnt] "+r"(add_cnt), [sub_cnt] "+r"(sub_cnt), [mul_cnt] "+r"(mul_cnt), [div_cnt] "+r"(div_cnt), [lw_cnt] "+r"(lw_cnt), [sw_cnt] "+r"(sw_cnt), [others_cnt] "+r"(others_cnt), [pi] "+f"(pi)
        : [N] "r"(N)
        : "f1", "f2", "t1", "t2", "t3", "t4");

    pi = 4 * pi;

    printf("===== Question 1-1 =====\n");
    printf("PI = %.9lf\n", pi);

    printf("add counter used: %d\n", add_cnt);
    printf("sub counter used: %d\n", sub_cnt);
    printf("mul counter used: %d\n", mul_cnt);
    printf("div counter used: %d\n", div_cnt);
    printf("lw counter used: %d\n", lw_cnt);
    printf("sw counter used: %d\n", sw_cnt);
    printf("others counter used: %d\n", others_cnt);

    macro_pi_cycle_count
        printf("The total cycle count in this program: %.0f\n", pi_cycle_count);

    macro_pi_cpu_time
        printf("CPU time = %f us\n", pi_cpu_time);

    macro_calc_pi_ratio
        if (pi_ratio > 0.5) {
            printf("This program is a CPU bound task.\n");
        }
        else {
            printf("This program is a Memory bound task.\n");
        }
    return (0);
}
