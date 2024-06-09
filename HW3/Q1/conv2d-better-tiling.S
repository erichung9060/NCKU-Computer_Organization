# -----------------------------------
# Improved ratio:  1.5217037880019508
# -----------------------------------

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

	li  t0, 0 # block_i
	5:
		li  t1, 0 # block_j
		6:
			add  t2, t0, 0 # i
			1:
				add  t3, t1, 0 # j
				2:
					li  t4, 0 # sum = 0

					li  t5, 0 # n = 0
					3:
						li  t6, 0 # m = 0
						4:
							# a6, a7
							add a6, t2, t5 # (i+n)
							mul a6, a6, a2 # (i+n)*w
							add a6, a6, t3 # (i+n)*w + j
							add a6, a6, t6 # (i+n)*w + j+m
							slli a6, a6, 2
							add a6, a6, a0 # address of input[]
							lw  a6, 0(a6) # input[]
						
							mul a7, t5, a4 # n * ksize
							add a7, a7, t6 # n * ksize + m
							slli a7, a7, 2
							add a7, a7, a1 # address of kernel[]
							lw  a7, 0(a7) # kernel[]
						
							mul a6, a7, a6 # input[] * kernel[]
							add t4, t4, a6 # sum += input * kernel

						add t6, t6, 1
						blt t6, a4, 4b # if n < ksize then goto tag 4

					add t5, t5, 1
					blt t5, a4, 3b # if m < ksize then goto tag 3

					mul a6, t2, a2 # i*w
					add a6, a6, t3 # i*w + j
					slli a6, a6, 2
					add a6, a0, a6
					sw  t4, 0(a6) # input[i*w + j] = sum

				addi t3, t3, 1

				# check j < block_j + 55 && j <= w - ksize
				if1_j:
					addi a6, t1, 55
					blt t3, a6, if2_j 
					j endif_j

				if2_j:
					sub a6, a2, a4
					ble t3, a6, 2b

				endif_j:

			addi t2, t2, 1

			# check i < block_i + 55 && i <= h - ksize
			if1_i:
				addi a6, t0, 55
				blt t2, a6, if2_i
				j endif_i

			if2_i:
				sub a6, a3, a4
				ble t2, a6, 1b

			endif_i:
		
		addi t1, t1, 55
		blt t1, a2, 6b

	addi t0, t0, 55
	blt t0, a3, 5b

# end of your implementation

# epilogue
	# lw a0, 0(sp)
	# addi sp, sp, 4
	ret