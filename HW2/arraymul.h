#ifndef _CONSTANT_H_
#define _CONSTANT_H_
int arr_size = 16;
static short int student_id = 10;//student_id = your_studnet_id % 100
static short int *h;
static short int *x;
static short int *y;

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
float arraymul_baseline_cycle_count = 0.0;
float improved_version1_cycle_count = 0.0;
float improved_version2_cycle_count = 0.0;

// ratio
float arraymul_baseline_ratio = 0.0;

// Given cycle time
const int cycle_time = 384; // us

// CPU time
float arraymul_baseline_cpu_time = 0.0;
float improved_version1_cpu_time = 0.0;
float improved_version2_cpu_time = 0.0;

void init();
void arraymul_baseline();
void improved_version1();
void improved_version2();
void input();

#endif
