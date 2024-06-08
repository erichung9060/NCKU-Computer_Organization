.global conv2d
conv2d:
# a0: address of input
# a1: address of kernel
# a2: w
# a3: h
# a4: ksize
# a5: s

# prologue
	# addi sp, sp, -4
	# sw a0, 0(sp)

# content
	sub t0, a2, a4 # h - ksize
	sub t1, a3, a4 # w - ksize
	li  t2, 0 # j = 0
1:
	li  t3, 0 # i = 0
2:
	li  t4, 0 # sum = 0
	li  t5, 0 # n = 0
3:
	li  t6, 0 # m = 0
4:
	# a6, a7
	add a6, t3, t6 # (i+m)
	mul a6, a6, a2 # (i+m)*w
	add a6, a6, t2 # (i+m)*w + j
	add a6, a6, t5 # (i+m)*w + j+n
	slli a6, a6, 2
	add a6, a6, a0 # address of input[]
	lw  a6, 0(a6) # input[]

	mul a7, a4, t6 # m*ksize
	add a7, a7, t5 # m*ksize + n
	slli a7, a7, 2
	add a7, a7, a1 # address of kernel[]
	lw  a7, 0(a7) # kernel[]

	mul a6, a7, a6 # input[] * kernel[]
	add t4, t4, a6 # sum += input * kernel

	add t6, t6, a5
	blt t6, a4, 4b # if n < ksize then goto tag 4
	add t5, t5, a5
	blt t5, a4, 3b # if m < ksize then goto tag 3

	mul a6, t3, a2 # i*w
	add a6, a6, t2 # i*w + j
	slli a6, a6, 2
	add a6, a0, a6 
	sw  t4, 0(a6) # input[i*w + j] = sum

	addi t3, t3, 1
	ble t3, t0, 2b # if i < w-ksize then goto tag 2

	addi t2, t2, 1
	ble t2, t1, 1b # if j < h-ksize then goto tag 1

# epilogue
	# lw a0, 0(sp)
	# addi sp, sp, 4
	ret