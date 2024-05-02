// exercise2_1.c

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "answer.h"
#include "arraymul.h"

int main(int argc, char *argv[]) {
    init();
    input();
    improved_version1();
    return 0;
}

void improved_version1() {
    short int *p_h = h;
    short int *p_x = x;
    short int *p_y = y;
    short int id = student_id;  // id = your_student_id % 100;
    /* original C code
    for (int i = 0; i < arr_size; i++){
        p_y[i] = p_h[i] * p_x[i] + id;
    }
    */

    asm volatile(
        #include "arraymul_improved_version1.c"

        : [h] "+r"(p_h), [x] "+r"(p_x), [y] "+r"(p_y), [add_cnt] "+r"(add_cnt), [sub_cnt] "+r"(sub_cnt), [mul_cnt] "+r"(mul_cnt), [div_cnt] "+r"(div_cnt), [lw_cnt] "+r"(lw_cnt), [sw_cnt] "+r"(sw_cnt), [others_cnt] "+r"(others_cnt)
        : [id] "r"(id), [arr_size] "r"(arr_size)
        : "t0", "v0", "v1", "v2");

    printf("\n===== Question 2-1 =====\n");
    printf("output: ");
    for (int i = 0; i < arr_size; i++) {
        printf(" %d ", y[i]);
    }

    printf("\n");

    printf("add counter used: %d\n", add_cnt);
    printf("sub counter used: %d\n", sub_cnt);
    printf("mul counter used: %d\n", mul_cnt);
    printf("div counter used: %d\n", div_cnt);
    printf("lw counter used: %d\n", lw_cnt);
    printf("sw counter used: %d\n", sw_cnt);
    printf("others counter used: %d\n", others_cnt);
    macro_improved_version1_cycle_count
        printf("The total cycle count in this program: %.0f\n", improved_version1_cycle_count);

    macro_improved_version1_cpu_time
        printf("CPU time = %f us\n", improved_version1_cpu_time);
        
    FILE *fp_1;
    fp_1 = fopen("improved_version1_cpu_time.txt", "w");
    fprintf(fp_1, "%f", improved_version1_cpu_time);
    fclose(fp_1);

    float speedup = 0.0;

    FILE *fp_2;
    fp_2 = fopen("arraymul_baseline_cpu_time.txt", "r");
    fscanf(fp_2, "%f", &speedup);
    fclose(fp_2);
    speedup = speedup / improved_version1_cpu_time;
    printf("V extension ISA faster %f times than baseline ISA\n", speedup);
}
void init() {
    add_cnt = 0;
    sub_cnt = 0;
    mul_cnt = 0;
    div_cnt = 0;
    lw_cnt = 0;
    sw_cnt = 0;
    others_cnt = 0;

    float temp = arr_size;
    while (temp != 1 && temp > 1) {
        temp = temp / 2;
    }
    if (temp != 1) {
        printf("log2(arr_size) must be an integer !!!\n");
        exit(0);
    }

    printf("array size = %d\n", arr_size);
    printf("student id = %d\n", student_id);
    h = calloc(arr_size, sizeof(short));
    x = calloc(arr_size, sizeof(short));
    y = calloc(arr_size, sizeof(short));
}

void input() {
    int fd;
    char *buf = (char *)calloc(3000, sizeof(char));

    fd = open("./arraymul_input.txt", O_RDONLY);
    if (fd < 0)
        exit(EXIT_FAILURE);
    if (read(fd, buf, 3000) < 0)
        exit(EXIT_FAILURE);

    char *token;
    token = strtok(buf, " ");
    int count = 0;

    for (int i = 0; i < arr_size * 2; ++i) {
        if (i < arr_size)
            h[i] = atoi(token);
        else
            x[i - arr_size] = atoi(token);

        token = strtok(NULL, " ");
    }
}
