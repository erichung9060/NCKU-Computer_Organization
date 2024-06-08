import subprocess
import os
import sys
import re

RISCV=os.environ.get("RISCV")
if not RISCV:
    print("Please set your RISCV variable before \"make check\"")
    sys.exit(1)

CACHE_MISS_PENALTY = 30
class testbench():
    def __init__(self, testbench:str, lib:str, execfile:str, outputfile:str):
        self.testbench = testbench
        self.lib = lib
        self.execfile = execfile
        self.outputfile = outputfile
        self.cycles = 0


    def compile(self):
        subprocess.run(["riscv64-unknown-linux-gnu-gcc", "-march=rv64gc", "-static", "-O0", self.testbench, self.lib, "-o", self.execfile])
    
    def run(self):
        self._exec = subprocess.run(["spike", "--isa=RV64GC", os.path.join(RISCV, "riscv64-unknown-linux-gnu/bin", "pk"), self.execfile, self.outputfile], capture_output=True, text=True)
        self.exec = subprocess.run(["spike", "--isa=RV64GC", "--dc=8:4:32", os.path.join(RISCV, "riscv64-unknown-linux-gnu/bin", "pk"), self.execfile], capture_output=True, text=True)
    
    def print(self):
        split = self.exec.stdout.split('\n')
        for s in split:
            if (re.search('Read Accesses', s)):
                self.Raccess = int(re.search('[0-9]+', s)[0])
            elif (re.search('Write Accesses', s)):
                self.Waccess = int(re.search('[0-9]+', s)[0])
            elif (re.search('Read Misses', s)):
                self.Rmiss = int(re.search('[0-9]+', s)[0])
            elif (re.search('Write Misses', s)):
                self.Wmiss = int(re.search('[0-9]+', s)[0])

        print(self.exec.stdout)
        self.cycles = self.Raccess - self.Rmiss + self.Waccess - self.Wmiss + CACHE_MISS_PENALTY * self.Rmiss + CACHE_MISS_PENALTY * self.Wmiss
        print("Memory access overhead = ", self.cycles, "(cpu cycle)")
        
print("Original version")
origin = testbench("Q2/testbench_driver.c", "Q2/mm.c", "Q2/a.out", "Q2/ans.output")
origin.compile()
origin.run()
origin.print()
print("-----------------------------------")

print("Improved version")
improve = testbench("Q2/testbench_driver.c", "Q2/mm-better.c", "Q2/a.out", "Q2/stu.output")
improve.compile()
improve.run()
improve.print()
print("-----------------------------------")

# compare two calculated result
correct_result = open("Q2/ans.output", 'r')
student_result = open("Q2/stu.output", 'r')

correct = True
print("Improved ratio: ", (origin.cycles/improve.cycles))
print("Output Correctness: ", "\x1b[32mPass\x1b[0m" if student_result.read() == correct_result.read() else "\x1b[31mFail\x1b[0m")
print("-----------------------------------")