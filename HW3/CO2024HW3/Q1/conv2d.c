/*
 * This file is just for illustrate the concept of the conv2d.S code.
 * There is no need to modify this file.
 */
void conv2d(int *input, int *kernel, int w, int h,
            int ksize, int s) {
    for (int j = 0; j <= w - ksize; j++) {
        for (int i = 0; i <= h - ksize; i++) {
            int sum = 0;
            for (int n = 0; n < ksize; n += s) {
                for (int m = 0; m < ksize; m += s) {
                    sum += input[(i + m) * w + j + n] * kernel[m * ksize + n];
                }
            }
            input[i * w + j] = sum;
        }
    }
}