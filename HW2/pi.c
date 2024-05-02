"li t4, -1\n" // t4 = -1
"addi %[lw_cnt], %[lw_cnt], 1\n"
"li t2, 1\n" // t2 = 1
"addi %[lw_cnt], %[lw_cnt], 1\n"
"fcvt.d.w f1, t2\n" // use f1 as sign
"addi %[others_cnt], %[others_cnt], 1\n"
"li t1, 0\n" // i = 0
"addi %[lw_cnt], %[lw_cnt], 1\n"

"loop:\n"
    "li t2, 2\n" // t2 = 2
    "addi %[lw_cnt], %[lw_cnt], 1\n"
    "mul t2, t1, t2\n" // t2 = i * 2
    "addi %[mul_cnt], %[mul_cnt], 1\n"
    "addi t2, t2, 1\n" // t2 = i * 2 + 1
    "addi %[add_cnt], %[add_cnt], 1\n"
    "fcvt.d.w f2, t2\n" // convert t2 to f2
    "addi %[others_cnt], %[others_cnt], 1\n"
    "fdiv.d f2, f1, f2\n" // f2 = sign / (i * 2 + 1)
    "addi %[div_cnt], %[div_cnt], 1\n"

    "fadd.d %[pi], %[pi], f2\n" // pi += sign / (i * 2 + 1)
    "addi %[add_cnt], %[add_cnt], 1\n"

    "fcvt.d.w f2, t4\n" // f2 = -1
    "addi %[others_cnt], %[others_cnt], 1\n"
    "fmul.d f1, f1, f2\n" // f1 *= -1
    "addi %[mul_cnt], %[mul_cnt], 1\n"
    "addi t1, t1, 1\n" // i++
    "addi %[add_cnt], %[add_cnt], 1\n"

"addi %[others_cnt], %[others_cnt], 1\n" // calculate before jump
"blt t1, %[N], loop\n"