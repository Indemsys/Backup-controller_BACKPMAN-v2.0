#ifndef APP_UTILS_H
  #define APP_UTILS_H

void     Reset_system(void);
uint64_t Measure_reference_time_interval(uint32_t time_delay_ms);
float    Get_float_val(volatile float *p_val);
void     Set_float_val(volatile float *p_val, float val);

#endif // APP_UTILS_H



