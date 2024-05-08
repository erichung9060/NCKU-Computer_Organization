//----------------------------------3-1--------------------------------------
#define macro_pi_cycle_count pi_cycle_count = \
    add_cnt * add_CPI + sub_cnt * sub_CPI + mul_cnt * mul_CPI + div_cnt * div_CPI + \
    lw_cnt * lw_CPI + sw_cnt * sw_CPI + others_cnt * others_CPI;

#define macro_pi_cpu_time pi_cpu_time = \
    pi_cycle_count * cycle_time;

#define macro_calc_pi_ratio pi_ratio = \
    (add_cnt * add_CPI + sub_cnt * sub_CPI + mul_cnt * mul_CPI + div_cnt * div_CPI \
    + others_cnt * others_CPI) / pi_cycle_count ;
//----------------------------------3-2--------------------------------------
#define macro_arraymul_baseline_cycle_count arraymul_baseline_cycle_count = \
    add_cnt * add_CPI + sub_cnt * sub_CPI + mul_cnt * mul_CPI + div_cnt * div_CPI + \
    lw_cnt * lw_CPI + sw_cnt * sw_CPI + others_cnt * others_CPI;

#define macro_arraymul_baseline_cpu_time arraymul_baseline_cpu_time = \
    arraymul_baseline_cycle_count * cycle_time;

#define macro_calc_arraymul_baseline_ratio arraymul_baseline_ratio = \
    (add_cnt * add_CPI + sub_cnt * sub_CPI + mul_cnt * mul_CPI + div_cnt * div_CPI \
    + others_cnt * others_CPI) / arraymul_baseline_cycle_count ;
//----------------------------------3-3--------------------------------------
#define macro_improved_version1_cycle_count improved_version1_cycle_count = \
    add_cnt * add_CPI + sub_cnt * sub_CPI + mul_cnt * mul_CPI + div_cnt * div_CPI + \
    lw_cnt * lw_CPI + sw_cnt * sw_CPI + others_cnt * others_CPI;

#define macro_improved_version1_cpu_time improved_version1_cpu_time = \
    improved_version1_cycle_count * cycle_time;
//----------------------------------3-4--------------------------------------
#define macro_improved_version2_cycle_count improved_version2_cycle_count = \
    add_cnt * add_CPI + sub_cnt * sub_CPI + mul_cnt * mul_CPI + div_cnt * div_CPI + \
    lw_cnt * lw_CPI + sw_cnt * sw_CPI + others_cnt * others_CPI;

#define macro_improved_version2_cpu_time improved_version2_cpu_time = \
    improved_version2_cycle_count * cycle_time;
