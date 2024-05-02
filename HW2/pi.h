#ifndef _CONSTANT_H_
#define _CONSTANT_H_
int N = 6;

// Given baseline counters in Question 1
int add_cnt = 0;
int sub_cnt = 0;
int mul_cnt = 0;
int div_cnt = 0;
int lw_cnt = 0;
int sw_cnt = 0;
int others_cnt = 0;

// Given baseline CPI
const int add_CPI = 3;
const int sub_CPI = 3;
const int mul_CPI = 4;
const int div_CPI = 4;
const int lw_CPI = 20;
const int sw_CPI = 15;
const int others_CPI = 3;

// Cycle count
float pi_cycle_count = 0.0;

// ratio
float pi_ratio = 0.0;

// Given cycle time
const int cycle_time = 384; // us

// CPU time
float pi_cpu_time = 0.0;

#endif
