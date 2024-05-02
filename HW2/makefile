MAKEFLAGS += --no-print-directory

PK_PATH = /opt/riscv/riscv64-unknown-linux-gnu/bin/pk

judge_exercise1_1:
	@./test_exercise1_1
	
judge_exercise1_2:
	@./test_exercise1_2
	
judge_exercise2_1:
	@./test_exercise2_1

judge_exercise2_2:
	@./test_exercise2_2
	
run_exercise1_1: exercise1_1
	@spike --isa=RV64GCV $(PK_PATH) exercise1_1

run_exercise1_2: exercise1_2
	@spike --isa=RV64GCV $(PK_PATH) exercise1_2

run_exercise2_1: exercise2_1
	@spike --varch=vlen:128,elen:16 --isa=RV64GCV $(PK_PATH) exercise2_1

run_exercise2_2: exercise2_2
	@spike --varch=vlen:256,elen:16 --isa=RV64GCV $(PK_PATH) exercise2_2


exercise1_1: exercise1_1.c answer.h pi.h pi.c
	@riscv64-unknown-linux-gnu-gcc -march=rv64gcv -static -o exercise1_1 exercise1_1.c

exercise1_2: exercise1_2.c answer.h arraymul.h arraymul_baseline.c
	@riscv64-unknown-linux-gnu-gcc -march=rv64gcv -static -o exercise1_2 exercise1_2.c
	
exercise2_1: exercise2_1.c answer.h arraymul.h arraymul_improved_version1.c
	@riscv64-unknown-linux-gnu-gcc -march=rv64gcv -static -o exercise2_1 exercise2_1.c

exercise2_2: exercise2_2.c answer.h arraymul.h arraymul_improved_version2.c
	@riscv64-unknown-linux-gnu-gcc -march=rv64gcv -static -o exercise2_2 exercise2_2.c


clean:
	@rm -f exercise1_1 exercise1_2 exercise2_1 exercise2_2
