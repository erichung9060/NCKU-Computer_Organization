# -----------------------------------
# Improved ratio:  1.9164761225682745
# -----------------------------------

#define Block_Size 10

void matrix_multiplication(int *a, int *b, int *output, int i, int k, int j) {
    for (int bx = 0; bx < i; bx += Block_Size) {
        for (int by = 0; by < j; by += Block_Size) {
            for (int bk = 0; bk < k; bk += Block_Size) {

                for (int x = bx; x < i && x < bx + Block_Size; x++) {
                    for (int y = by; y < j && y < by + Block_Size; y++) {
                        int sum = 0;
                        for (int z = bk; z < k && z < bk + Block_Size; z++) {
                            sum += a[x * k + z] * b[z * j + y];
                        }
                        output[x * j + y] += sum;
                    }
                }
            }
        }
    }
}