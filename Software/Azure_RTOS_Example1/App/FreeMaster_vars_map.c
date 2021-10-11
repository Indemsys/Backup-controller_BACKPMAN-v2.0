#include "App.h"
#include "freemaster_cfg.h"
#include "freemaster.h"
#include "freemaster_tsa.h"


FMSTR_TSA_TABLE_BEGIN(app_vars)


FMSTR_TSA_RW_VAR( g_cpu_usage                            ,FMSTR_TSA_UINT32     )
FMSTR_TSA_RW_VAR( g_cpu_usage_fp                         ,FMSTR_TSA_FLOAT      )
// FMSTR_TSA_RW_VAR( DCDC_DAC_comm_errors                ,FMSTR_TSA_UINT32     )
//
// FMSTR_TSA_RW_VAR( sig_oledv                           ,FMSTR_TSA_SINT32     )
// FMSTR_TSA_RW_VAR( sig_oled_cs                         ,FMSTR_TSA_SINT32     )
// FMSTR_TSA_RW_VAR( sig_oled_res                        ,FMSTR_TSA_SINT32     )
// FMSTR_TSA_RW_VAR( sig_oled_dc                         ,FMSTR_TSA_SINT32     )
// FMSTR_TSA_RW_VAR( sig_led_gr                          ,FMSTR_TSA_SINT32     )
// FMSTR_TSA_RW_VAR( sig_led_rd                          ,FMSTR_TSA_SINT32     )
// FMSTR_TSA_RW_VAR( sig_out1                            ,FMSTR_TSA_SINT32     )
// FMSTR_TSA_RW_VAR( sig_out2                            ,FMSTR_TSA_SINT32     )
// FMSTR_TSA_RW_VAR( sig_invsw_on                        ,FMSTR_TSA_SINT32     )
// FMSTR_TSA_RW_VAR( sig_pids_shdn                       ,FMSTR_TSA_SINT32     )
// FMSTR_TSA_RW_VAR( sig_aids_shdn                       ,FMSTR_TSA_SINT32     )
// FMSTR_TSA_RW_VAR( sig_aids_fbc                        ,FMSTR_TSA_SINT32     )
// FMSTR_TSA_RW_VAR( sig_en_DCDC                         ,FMSTR_TSA_SINT32     )
// FMSTR_TSA_RW_VAR( sig_dcdc_mode                       ,FMSTR_TSA_SINT32     )
// FMSTR_TSA_RW_VAR( sig_sw_inv_path                     ,FMSTR_TSA_SINT32     )
// FMSTR_TSA_RW_VAR( sig_sw_mains_path                   ,FMSTR_TSA_SINT32     )
//
// FMSTR_TSA_RW_VAR( sys.accum_id_i                      ,FMSTR_TSA_FLOAT      )
// FMSTR_TSA_RW_VAR( sys.accum_i                         ,FMSTR_TSA_FLOAT      )
// FMSTR_TSA_RW_VAR( sys.accum_sum_i                     ,FMSTR_TSA_FLOAT      )
// FMSTR_TSA_RW_VAR( sys.psrc_i                          ,FMSTR_TSA_FLOAT      )
// FMSTR_TSA_RW_VAR( sys.invert_i                        ,FMSTR_TSA_FLOAT      )
// FMSTR_TSA_RW_VAR( sys.invert_v                        ,FMSTR_TSA_FLOAT      )
// FMSTR_TSA_RW_VAR( sys.sys_v                           ,FMSTR_TSA_FLOAT      )
// FMSTR_TSA_RW_VAR( sys.mains_path_state                ,FMSTR_TSA_UINT8      )
// FMSTR_TSA_RW_VAR( sys.inv_path_state                  ,FMSTR_TSA_UINT8      )
// FMSTR_TSA_RW_VAR( sys.psrc_v                          ,FMSTR_TSA_FLOAT      )
// FMSTR_TSA_RW_VAR( sys.accum_v                         ,FMSTR_TSA_FLOAT      )
// FMSTR_TSA_RW_VAR( sys.accum_charge_power              ,FMSTR_TSA_FLOAT      )
// FMSTR_TSA_RW_VAR( sys.accum_discharge_power           ,FMSTR_TSA_FLOAT      )
// FMSTR_TSA_RW_VAR( sys.pwr_src_power                   ,FMSTR_TSA_FLOAT      )
// FMSTR_TSA_RW_VAR( sys.chaging_pwr_loss                ,FMSTR_TSA_FLOAT      )
// FMSTR_TSA_RW_VAR( sys.charging_efficiency             ,FMSTR_TSA_FLOAT      )
// FMSTR_TSA_RW_VAR( sys.accum_charge                    ,FMSTR_TSA_FLOAT      )
// FMSTR_TSA_RW_VAR( sys.cpu_temper                      ,FMSTR_TSA_FLOAT      )
//
// FMSTR_TSA_RW_VAR( sys.DCDC_DAC_code                   ,FMSTR_TSA_UINT16     )
// FMSTR_TSA_RW_VAR( sys.dcdc_dac_error_flag             ,FMSTR_TSA_UINT8      )
//
// FMSTR_TSA_RW_VAR( sys.fp_smpl_accum_id_i              ,FMSTR_TSA_FLOAT      )
// FMSTR_TSA_RW_VAR( sys.fp_smpl_accum_i                 ,FMSTR_TSA_FLOAT      )
// FMSTR_TSA_RW_VAR( sys.fp_smpl_psrc_i                  ,FMSTR_TSA_FLOAT      )
// FMSTR_TSA_RW_VAR( sys.fp_smpl_invert_i                ,FMSTR_TSA_FLOAT      )
// FMSTR_TSA_RW_VAR( sys.fp_smpl_invert_v                ,FMSTR_TSA_FLOAT      )
// FMSTR_TSA_RW_VAR( sys.fp_smpl_sys_v                   ,FMSTR_TSA_FLOAT      )
// FMSTR_TSA_RW_VAR( sys.fp_smpl_psrc_v                  ,FMSTR_TSA_FLOAT      )
// FMSTR_TSA_RW_VAR( sys.fp_smpl_accum_v                 ,FMSTR_TSA_FLOAT      )
// FMSTR_TSA_RW_VAR( sys.fp_smpl_cpu_temper              ,FMSTR_TSA_FLOAT      )
//
// FMSTR_TSA_RW_VAR( g_ADC_results.smpl_ACCUM_ID_I       ,FMSTR_TSA_UINT16     )
// FMSTR_TSA_RW_VAR( g_ADC_results.smpl_ACCUM_I          ,FMSTR_TSA_UINT16     )
// FMSTR_TSA_RW_VAR( g_ADC_results.smpl_PSRC_I           ,FMSTR_TSA_UINT16     )
// FMSTR_TSA_RW_VAR( g_ADC_results.smpl_INVERT_I         ,FMSTR_TSA_UINT16     )
// FMSTR_TSA_RW_VAR( g_ADC_results.smpl_INVERT_V         ,FMSTR_TSA_UINT16     )
// FMSTR_TSA_RW_VAR( g_ADC_results.smpl_PWR24_V          ,FMSTR_TSA_UINT16     )
// FMSTR_TSA_RW_VAR( g_ADC_results.smpl_MAINS_PATH_STATE ,FMSTR_TSA_UINT16     )
// FMSTR_TSA_RW_VAR( g_ADC_results.smpl_INV_PATH_STATE   ,FMSTR_TSA_UINT16     )
// FMSTR_TSA_RW_VAR( g_ADC_results.smpl_PSRC_V           ,FMSTR_TSA_UINT16     )
// FMSTR_TSA_RW_VAR( g_ADC_results.smpl_ACCUM_V          ,FMSTR_TSA_UINT16     )
//
// FMSTR_TSA_RW_VAR( g_ADC_raw_results.smpl_ACCUM_ID_I       ,FMSTR_TSA_UINT16 )
// FMSTR_TSA_RW_VAR( g_ADC_raw_results.smpl_ACCUM_I          ,FMSTR_TSA_UINT16 )
// FMSTR_TSA_RW_VAR( g_ADC_raw_results.smpl_PSRC_I           ,FMSTR_TSA_UINT16 )
// FMSTR_TSA_RW_VAR( g_ADC_raw_results.smpl_INVERT_I         ,FMSTR_TSA_UINT16 )
// FMSTR_TSA_RW_VAR( g_ADC_raw_results.smpl_INVERT_V         ,FMSTR_TSA_UINT16 )
// FMSTR_TSA_RW_VAR( g_ADC_raw_results.smpl_PWR24_V          ,FMSTR_TSA_UINT16 )
// FMSTR_TSA_RW_VAR( g_ADC_raw_results.smpl_MAINS_PATH_STATE ,FMSTR_TSA_UINT16 )
// FMSTR_TSA_RW_VAR( g_ADC_raw_results.smpl_INV_PATH_STATE   ,FMSTR_TSA_UINT16 )
// FMSTR_TSA_RW_VAR( g_ADC_raw_results.smpl_PSRC_V           ,FMSTR_TSA_UINT16 )
// FMSTR_TSA_RW_VAR( g_ADC_raw_results.smpl_ACCUM_V          ,FMSTR_TSA_UINT16 )
// FMSTR_TSA_RW_VAR( g_ADC_raw_results.smpl_VREF_1_65V       ,FMSTR_TSA_UINT16 )
//
//
// FMSTR_TSA_RW_VAR( s_VREF_1_65V                        ,FMSTR_TSA_UINT16     )
// FMSTR_TSA_RW_VAR( s_ACCUM_ID_I                        ,FMSTR_TSA_SINT16     )
// FMSTR_TSA_RW_VAR( s_ACCUM_I                           ,FMSTR_TSA_SINT16     )
// FMSTR_TSA_RW_VAR( s_PSRC_I                            ,FMSTR_TSA_SINT16     )
// FMSTR_TSA_RW_VAR( s_INVERT_I                          ,FMSTR_TSA_SINT16     )

FMSTR_TSA_TABLE_END();

