.DEFAULT_GOAL: check
.PHONY: check
check: checkq1 checkq2

.PHONY: checkq1
checkq1:
	@printf "=============== Q1 ===============\n"
	@python3 testq1.py

.PHONY: checkq2
checkq2:
	@printf "=============== Q2 ===============\n"
	@python3 testq2.py

.PHONY: diffq1
diffq1:
	@git diff --color-words --no-index -U0 -G. Q1/ans.output Q1/stu.output

.PHONY: diffq2
diffq2:
	@git diff --color-words --no-index -U0 -G. Q2/ans.output Q2/stu.output

.PHONY: clean
clean:
	$(RM) Q1/*.out* Q2/*.out*
