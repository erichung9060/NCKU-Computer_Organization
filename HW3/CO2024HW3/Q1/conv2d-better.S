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

# start of your implementation

# end of your implementation

# epilogue
	# lw a0, 0(sp)
	# addi sp, sp, 4
	ret
