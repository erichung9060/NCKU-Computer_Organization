"improved_loop:\n"
    "vsetivli t0, 8, e16\n"  // process up to 8 shorts at a time
    "addi %[others_cnt], %[others_cnt], 1\n"

    "vle16.v v0, (%[h])\n"  // v0 = h[i~i+8]
    "vle16.v v1, (%[x])\n"  // v1 = x[i~i+8]
    "addi %[lw_cnt], %[lw_cnt], 2\n"

    "vmul.vv v2, v0, v1\n"  // v2 = h * x
    "addi %[mul_cnt], %[mul_cnt], 1\n"
    "vadd.vx v2, v2, %[id]\n"  // v2 = h * x + id
    "addi %[add_cnt], %[add_cnt], 1\n"
    
    "vse16.v v2, (%[y])\n"  // y = h * x + id
    "addi %[sw_cnt], %[sw_cnt], 1\n"

    "addi %[y], %[y], 16\n"  // y[i] -> y[i+8]
    "addi %[h], %[h], 16\n"  // h[i] -> h[i+8]
    "addi %[x], %[x], 16\n"  // x[i] -> x[i+8]
    "addi %[add_cnt], %[add_cnt], 3\n"

    "sub %[arr_size], %[arr_size], t0\n"  // arr_size -= (number of processed shorts)
    "addi %[sub_cnt], %[sub_cnt], 1\n"

    "addi %[others_cnt], %[others_cnt], 1\n"
    "bgt %[arr_size], zero, improved_loop\n"  // if arr_size > 0