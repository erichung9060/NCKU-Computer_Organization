"loop:\n"
    "lh t0, 0(%[h])\n" // t0 = p_h[i]
    "lh t1, 0(%[x])\n" // t1 = p_x[i]
    "addi %[lw_cnt], %[lw_cnt], 2\n"
    
    "mul t0, t0, t1\n" // t0 = p_h[i] * p_x[i]
    "addi %[mul_cnt], %[mul_cnt], 1\n"
    "add t0, t0, %[id]\n" // t0 = p_h[i] * p_x[i] + id
    "addi %[add_cnt], %[add_cnt], 1\n"

    "sh t0, 0(%[y])\n" // p_c[i] = t0
    "addi %[sw_cnt], %[sw_cnt], 1\n"

    "addi %[h], %[h], 2\n" // p_h ++
    "addi %[x], %[x], 2\n" // p_x ++
    "addi %[y], %[y], 2\n" // p_y ++
    "addi %[add_cnt], %[add_cnt], 3\n"

    "addi %[arr_size], %[arr_size], -1\n" // arr_size --
    "addi %[add_cnt], %[add_cnt], 1\n"

"addi %[others_cnt], %[others_cnt], 1\n"
"bgt %[arr_size], zero, loop\n" // if arr_size > 0
