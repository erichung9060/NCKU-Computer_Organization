void matrix_multiplication(int *a, int *b, int *output, int i,
                           int k, int j) {
    for (int x = 0; x < i; x++) {
        for (int y = 0; y < j; y++) {
            int sum = 0;
            for (int z = 0; z < k; z++) {
                sum += a[x * k + z] * b[z * j + y];
            }
            output[x * j + y] = sum;
        }
    }
    return;
}