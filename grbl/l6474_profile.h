
/******************************************************//**
 * @file    l6474_target_config.h
 * @version V1.0
 * @date    March 3, 2014
 * @brief   Predefines values for the L6474 registers
 * and for the shields parameters
  *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 **********************************************************/

#ifndef __L6474_TARGET_CONFIG_H
#define __L6474_TARGET_CONFIG_H

/// The maximum number of shields in the daisy chain
#define MAX_NUMBER_OF_SHIELDS                 (4)



/************************ Phase Current Control *******************************/

// Current value that is assigned to the torque regulation DAC
/// TVAL register value for shield 0 (range 31.25mA to 4000mA)
#define L6474_CONF_PARAM_TVAL_SHIELD_0  (250)
/// TVAL register value for shield 1 (range 31.25mA to 4000mA)
#define L6474_CONF_PARAM_TVAL_SHIELD_1  (250)
/// TVAL register value for shield 2 (range 31.25mA to 4000mA)
#define L6474_CONF_PARAM_TVAL_SHIELD_2  (250)
/// TVAL register value for shield 3 (range 31.25mA to 4000mA)
#define L6474_CONF_PARAM_TVAL_SHIELD_3  (250)


/// Fall time value (T_FAST field of T_FAST register) for shield 0 (range 2us to 32us)
#define L6474_CONF_PARAM_FAST_STEP_SHIELD_0  (L6474_FAST_STEP_16us)
/// Fall time value (T_FAST field of T_FAST register) for shield 1 (range 2us to 32us)
#define L6474_CONF_PARAM_FAST_STEP_SHIELD_1  (L6474_FAST_STEP_16us)
/// Fall time value (T_FAST field of T_FAST register) for shield 2 (range 2us to 32us)
#define L6474_CONF_PARAM_FAST_STEP_SHIELD_2  (L6474_FAST_STEP_16us)
/// Fall time value (T_FAST field of T_FAST register) for shield 3 (range 2us to 32us)
#define L6474_CONF_PARAM_FAST_STEP_SHIELD_3  (L6474_FAST_STEP_16us)


/// Maximum fast decay time (T_OFF field of T_FAST register) for shield 0 (range 2us to 32us)
#define L6474_CONF_PARAM_TOFF_FAST_SHIELD_0  (L6474_TOFF_FAST_10us)
/// Maximum fast decay time (T_OFF field of T_FAST register) for shield 1 (range 2us to 32us)
#define L6474_CONF_PARAM_TOFF_FAST_SHIELD_1  (L6474_TOFF_FAST_10us)
/// Maximum fast decay time (T_OFF field of T_FAST register) for shield 2 (range 2us to 32us)
#define L6474_CONF_PARAM_TOFF_FAST_SHIELD_2  (L6474_TOFF_FAST_10us)
/// Maximum fast decay time (T_OFF field of T_FAST register) for shield 3 (range 2us to 32us)
#define L6474_CONF_PARAM_TOFF_FAST_SHIELD_3  (L6474_TOFF_FAST_10us)


/// Minimum ON time (TON_MIN register) for shield 0 (range 0.5us to 64us)
#define L6474_CONF_PARAM_TON_MIN_SHIELD_0 (4)
/// Minimum ON time (TON_MIN register) for shield 1 (range 0.5us to 64us)
#define L6474_CONF_PARAM_TON_MIN_SHIELD_1 (4)
/// Minimum ON time (TON_MIN register) for shield 2 (range 0.5us to 64us)
#define L6474_CONF_PARAM_TON_MIN_SHIELD_2 (4)
/// Minimum ON time (TON_MIN register) for shield 3 (range 0.5us to 64us)
#define L6474_CONF_PARAM_TON_MIN_SHIELD_3 (4)


/// Minimum OFF time (TOFF_MIN register) for shield 0 (range 0.5us to 64us)
#define L6474_CONF_PARAM_TOFF_MIN_SHIELD_0 (21)
/// Minimum OFF time (TOFF_MIN register) for shield 1 (range 0.5us to 64us)
#define L6474_CONF_PARAM_TOFF_MIN_SHIELD_1 (21)
/// Minimum OFF time (TOFF_MIN register) for shield 2 (range 0.5us to 64us)
#define L6474_CONF_PARAM_TOFF_MIN_SHIELD_2 (21)
/// Minimum OFF time (TOFF_MIN register) for shield 3 (range 0.5us to 64us)
#define L6474_CONF_PARAM_TOFF_MIN_SHIELD_3 (21)


/******************************* Others ***************************************/

/// Overcurrent threshold settings for shield 0 (OCD_TH register)
#define L6474_CONF_PARAM_OCD_TH_SHIELD_0  (L6474_OCD_TH_750mA)
/// Overcurrent threshold settings for shield 1 (OCD_TH register)
#define L6474_CONF_PARAM_OCD_TH_SHIELD_1  (L6474_OCD_TH_750mA)
/// Overcurrent threshold settings for shield 2 (OCD_TH register)
#define L6474_CONF_PARAM_OCD_TH_SHIELD_2  (L6474_OCD_TH_750mA)
/// Overcurrent threshold settings for shield 3 (OCD_TH register)
#define L6474_CONF_PARAM_OCD_TH_SHIELD_3  (L6474_OCD_TH_750mA)


/// Alarm settings for shield 0 (ALARM_EN register)
#define L6474_CONF_PARAM_ALARM_EN_SHIELD_0  (	L6474_ALARM_EN_OVERCURRENT |\
                                                L6474_ALARM_EN_THERMAL_SHUTDOWN |\
                                                L6474_ALARM_EN_THERMAL_WARNING |\
                                                L6474_ALARM_EN_UNDERVOLTAGE |\
                                                L6474_ALARM_EN_SW_TURN_ON |\
                                                L6474_ALARM_EN_WRONG_NPERF_CMD)

///Alarm settings for shield 1 (ALARM_EN register)
#define L6474_CONF_PARAM_ALARM_EN_SHIELD_1  (	L6474_ALARM_EN_OVERCURRENT |\
                                                L6474_ALARM_EN_THERMAL_SHUTDOWN |\
                                                L6474_ALARM_EN_THERMAL_WARNING |\
                                                L6474_ALARM_EN_UNDERVOLTAGE |\
                                                L6474_ALARM_EN_SW_TURN_ON |\
                                                L6474_ALARM_EN_WRONG_NPERF_CMD)

/// Alarm settings for shield 2 (ALARM_EN register)
#define L6474_CONF_PARAM_ALARM_EN_SHIELD_2  (	L6474_ALARM_EN_OVERCURRENT |\
                                                L6474_ALARM_EN_THERMAL_SHUTDOWN |\
                                                L6474_ALARM_EN_THERMAL_WARNING |\
                                                L6474_ALARM_EN_UNDERVOLTAGE |\
                                                L6474_ALARM_EN_SW_TURN_ON |\
                                                L6474_ALARM_EN_WRONG_NPERF_CMD)
                                                
/// Alarm settings for shield 3 (ALARM_EN register)
#define L6474_CONF_PARAM_ALARM_EN_SHIELD_3  (	L6474_ALARM_EN_OVERCURRENT |\
												L6474_ALARM_EN_THERMAL_SHUTDOWN |\
												L6474_ALARM_EN_THERMAL_WARNING |\
												L6474_ALARM_EN_UNDERVOLTAGE |\
												L6474_ALARM_EN_SW_TURN_ON |\
												L6474_ALARM_EN_WRONG_NPERF_CMD)
													

/// Step selection settings for shield 0 (STEP_SEL field of STEP_MODE register)
#define L6474_CONF_PARAM_STEP_SEL_SHIELD_0  (L6474_STEP_SEL_1_16)
/// Step selection settings for shield 1 (STEP_SEL field of STEP_MODE register)
#define L6474_CONF_PARAM_STEP_SEL_SHIELD_1  (L6474_STEP_SEL_1_16)
/// Step selection settings for shield 2 (STEP_SEL field of STEP_MODE register)
#define L6474_CONF_PARAM_STEP_SEL_SHIELD_2  (L6474_STEP_SEL_1_16)
/// Step selection settings for shield 3 (STEP_SEL field of STEP_MODE register)
#define L6474_CONF_PARAM_STEP_SEL_SHIELD_3  (L6474_STEP_SEL_1_16)


/// Synch. selection settings for shield 0 (SYNC_SEL field of STEP_MODE register)
#define L6474_CONF_PARAM_SYNC_SEL_SHIELD_0  (L6474_SYNC_SEL_1_2)
/// Synch. selection settings for shield 1 (SYNC_SEL field of STEP_MODE register)
#define L6474_CONF_PARAM_SYNC_SEL_SHIELD_1  (L6474_SYNC_SEL_1_2)
/// Synch. selection settings for shield 2 (SYNC_SEL field of STEP_MODE register)
#define L6474_CONF_PARAM_SYNC_SEL_SHIELD_2  (L6474_SYNC_SEL_1_2)
/// Synch. selection settings for shield 3 (SYNC_SEL field of STEP_MODE register)
#define L6474_CONF_PARAM_SYNC_SEL_SHIELD_3  (L6474_SYNC_SEL_1_2)


/// Target Swicthing Period for shield 0 (field TOFF of CONFIG register)
#define L6474_CONF_PARAM_TOFF_SHIELD_0  (L6474_CONFIG_TOFF_044us)
/// Target Swicthing Period for shield 1 (field TOFF of CONFIG register)
#define L6474_CONF_PARAM_TOFF_SHIELD_1  (L6474_CONFIG_TOFF_044us)
/// Target Swicthing Period for shield 2 (field TOFF of CONFIG register)
#define L6474_CONF_PARAM_TOFF_SHIELD_2  (L6474_CONFIG_TOFF_044us)
/// Target Swicthing Period for shield 3 (field TOFF of CONFIG register)
#define L6474_CONF_PARAM_TOFF_SHIELD_3  (L6474_CONFIG_TOFF_044us)


/// Slew rate for shield 0 (POW_SR field of CONFIG register)
#define L6474_CONF_PARAM_SR_SHIELD_0  (L6474_CONFIG_SR_320V_us)
/// Slew rate for shield 1 (POW_SR field of CONFIG register)
#define L6474_CONF_PARAM_SR_SHIELD_1  (L6474_CONFIG_SR_320V_us)
/// Slew rate for shield 2 (POW_SR field of CONFIG register)
#define L6474_CONF_PARAM_SR_SHIELD_2  (L6474_CONFIG_SR_320V_us)
/// Slew rate for shield 3 (POW_SR field of CONFIG register)
#define L6474_CONF_PARAM_SR_SHIELD_3  (L6474_CONFIG_SR_320V_us)


/// Over current shutwdown enabling for shield 0 (OC_SD field of CONFIG register)
#define L6474_CONF_PARAM_OC_SD_SHIELD_0  (L6474_CONFIG_OC_SD_ENABLE)
/// Over current shutwdown enabling for shield 1 (OC_SD field of CONFIG register)
#define L6474_CONF_PARAM_OC_SD_SHIELD_1  (L6474_CONFIG_OC_SD_ENABLE)
/// Over current shutwdown enabling for shield 2 (OC_SD field of CONFIG register)
#define L6474_CONF_PARAM_OC_SD_SHIELD_2  (L6474_CONFIG_OC_SD_ENABLE)
/// Over current shutwdown enabling for shield 3 (OC_SD field of CONFIG register)
#define L6474_CONF_PARAM_OC_SD_SHIELD_3  (L6474_CONFIG_OC_SD_ENABLE)


/// Torque regulation method for shield 0 (EN_TQREG field of CONFIG register)
#define L6474_CONF_PARAM_TQ_REG_SHIELD_0  (L6474_CONFIG_EN_TQREG_TVAL_USED)
///Torque regulation method for shield 1 (EN_TQREG field of CONFIG register)
#define L6474_CONF_PARAM_TQ_REG_SHIELD_1  (L6474_CONFIG_EN_TQREG_TVAL_USED)
/// Torque regulation method for shield 2 (EN_TQREG field of CONFIG register)
#define L6474_CONF_PARAM_TQ_REG_SHIELD_2  (L6474_CONFIG_EN_TQREG_TVAL_USED)
/// Torque regulation method for shield 3 (EN_TQREG field of CONFIG register)
#define L6474_CONF_PARAM_TQ_REG_SHIELD_3  (L6474_CONFIG_EN_TQREG_TVAL_USED)


/// Clock setting for shield 0 (OSC_CLK_SEL field of CONFIG register)
#define L6474_CONF_PARAM_CLOCK_SETTING_SHIELD_0  (L6474_CONFIG_INT_16MHZ)
/// Clock setting for shield 1 (OSC_CLK_SEL field of CONFIG register)
#define L6474_CONF_PARAM_CLOCK_SETTING_SHIELD_1  (L6474_CONFIG_INT_16MHZ)
/// Clock setting for shield 2 (OSC_CLK_SEL field of CONFIG register)
#define L6474_CONF_PARAM_CLOCK_SETTING_SHIELD_2  (L6474_CONFIG_INT_16MHZ)
/// Clock setting for shield 3 (OSC_CLK_SEL field of CONFIG register)
#define L6474_CONF_PARAM_CLOCK_SETTING_SHIELD_3  (L6474_CONFIG_INT_16MHZ)


#endif /* __L6474_TARGET_CONFIG_H */

