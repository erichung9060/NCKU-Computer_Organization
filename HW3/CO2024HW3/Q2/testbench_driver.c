
#define I 70
#define K 70
#define J 70

#include <stdio.h>
#include <string.h>

#define GOLDEN_RATIO_32 0x61C88647
static inline int hash_32(int val) {
    return (val * GOLDEN_RATIO_32) >> 22;
}

extern void matrix_multiplication(int (*a)[K], int (*b)[J],
                                  int (*output)[J], int i, int k,
                                  int j);

int main(int argc, char *argv[]) {
    int a[I][K] __attribute__((aligned(4096)));
    int b[K][J] __attribute__((aligned(4096)));
    int output[I][J] __attribute__((aligned(4096)));

    int seed = 0;

    memset(output, 0, I * J * sizeof(int));
    for (int i = 0; i < I; i++) {
        for (int j = 0; j < K; j++)
            a[i][j] = hash_32(i * K + j);
    }

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < J; j++)
            b[i][j] = hash_32(i * J + j);
    }

    matrix_multiplication(a, b, output, I, K, J);

    if (argc == 2) {
        FILE *f = fopen(argv[1], "w");
        for (int i = 0; i < I; i++) {
            for (int j = 0; j < J; j++) {
                fprintf(f, "%d ", output[i][j]);
            }
            fprintf(f, "\n");
        }
        fclose(f);
    }

    return 0;
}
