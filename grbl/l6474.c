/******************************************************//**
 * @file    l6474.cpp 
 * @version V1.0
 * @date    March 3, 2014
 * @brief   L6474 library for arduino 
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 **********************************************************/ 

#include "grbl.h"
#include "l6474_profile.h"




volatile uint8_t numberOfShields;

uint8_t spiTxBursts[L6474_CMD_ARG_MAX_NB_BYTES][MAX_NUMBER_OF_SHIELDS];
uint8_t spiRxBursts[L6474_CMD_ARG_MAX_NB_BYTES][MAX_NUMBER_OF_SHIELDS];

static volatile bool isrFlag;
static volatile bool spiPreemtionByIsr;
volatile uint8_t numberOfShields;

uint8_t spiTxBursts[L6474_CMD_ARG_MAX_NB_BYTES][MAX_NUMBER_OF_SHIELDS];
uint8_t spiRxBursts[L6474_CMD_ARG_MAX_NB_BYTES][MAX_NUMBER_OF_SHIELDS];



/******************************************************//**
 * @brief Starts the L6474 library
 * @param[in] nbShields Number of L6474 shields to use (from 1 to 3)
 * @retval None
 **********************************************************/
void L6474_init(uint8_t nbShields)
{
  numberOfShields = nbShields;  
  uint8_t i = 0;

  
  /* Set all registers and context variables to the predefined values from l6474_target_config.h */
  for (i = 0; i < nbShields; i++)
  {
    L6474_SetRegisterToPredefinedValues(i);
  } 
  
  /* Disable L6474 powerstage */
  
  for (i = 0; i < nbShields; i++)
  {
    L6474_CmdDisable(i);
    /* Get Status to clear flags after start up */
    L6474_CmdGetStatus(i);
  }
}




/******************************************************//**
 * @brief  Issue the Disable command to the L6474 of the specified shield
 * @param[in] shieldId (from 0 to 2)
 * @retval None
 **********************************************************/
void L6474_CmdDisable(uint8_t shieldId)
{
  L6474_SendCommand(shieldId, L6474_DISABLE);
}

/******************************************************//**
 * @brief  Issues the Enable command to the L6474 of the specified shield
 * @param[in] shieldId (from 0 to 2)
 * @retval None
 **********************************************************/
void L6474_CmdEnable(uint8_t shieldId)
{
  L6474_SendCommand(shieldId, L6474_ENABLE);
}

/******************************************************//**
 * @brief  Issues the GetParam command to the L6474 of the specified shield
 * @param[in] shieldId (from 0 to 2)
 * @param[in] param Register adress (L6474_ABS_POS, L6474_MARK,...)
 * @retval Register value
 **********************************************************/
uint32_t L6474_CmdGetParam(uint8_t shieldId, L6474_Registers_t param)
{
  uint32_t i;
  uint32_t spiRxData;
  uint8_t maxArgumentNbBytes = 0;
  uint8_t spiIndex = numberOfShields - shieldId - 1;

  
      
    for (i = 0; i < numberOfShields; i++)
    {
      spiTxBursts[0][i] = L6474_NOP;
      spiTxBursts[1][i] = L6474_NOP;
      spiTxBursts[2][i] = L6474_NOP;
      spiTxBursts[3][i] = L6474_NOP;
      spiRxBursts[1][i] = 0;
      spiRxBursts[2][i] = 0;
      spiRxBursts[3][i] = 0;    
    }
    switch (param)
    {
      case L6474_ABS_POS: ;
      case L6474_MARK:
        spiTxBursts[0][spiIndex] = ((uint8_t)L6474_GET_PARAM )| (param);
        maxArgumentNbBytes = 3;
        break;
      case L6474_EL_POS: ;
      case L6474_CONFIG: ;
      case L6474_STATUS:
        spiTxBursts[1][spiIndex] = ((uint8_t)L6474_GET_PARAM )| (param);
        maxArgumentNbBytes = 2;
        break;
      default:
        spiTxBursts[2][spiIndex] = ((uint8_t)L6474_GET_PARAM )| (param);
        maxArgumentNbBytes = 1;
    }
    

    
  for (i = L6474_CMD_ARG_MAX_NB_BYTES-1-maxArgumentNbBytes;
       i < L6474_CMD_ARG_MAX_NB_BYTES;
       i++)
  {
     L6474_WriteBytes(&spiTxBursts[i][0],
                          &spiRxBursts[i][0]);
  }
  
  spiRxData = ((uint32_t)spiRxBursts[1][spiIndex] << 16)|
              (spiRxBursts[2][spiIndex] << 8) |
              (spiRxBursts[3][spiIndex]);
      
  return (spiRxData);
}

/******************************************************//**
 * @brief  Issues the GetStatus command to the L6474 of the specified shield
 * @param[in] shieldId (from 0 to 2)
 * @retval Status Register value
 * @note Once the GetStatus command is performed, the flags of the status register
 * are reset. This is not the case when the status register is read with the
 * GetParam command (via the functions ReadStatusRegister or CmdGetParam).
 **********************************************************/
uint16_t L6474_CmdGetStatus(uint8_t shieldId)
{
  uint32_t i;
  uint16_t status;
  uint8_t spiIndex = numberOfShields - shieldId - 1;

  

    for (i = 0; i < numberOfShields; i++)
    {
       spiTxBursts[0][i] = L6474_NOP;
       spiTxBursts[1][i] = L6474_NOP;
       spiTxBursts[2][i] = L6474_NOP;
       spiRxBursts[1][i] = 0;
       spiRxBursts[2][i] = 0;
    }
    spiTxBursts[0][spiIndex] = L6474_GET_STATUS;


  for (i = 0; i < L6474_CMD_ARG_NB_BYTES_GET_STATUS + L6474_RSP_NB_BYTES_GET_STATUS; i++)
  {
     L6474_WriteBytes(&spiTxBursts[i][0], &spiRxBursts[i][0]);
  }
  status = (spiRxBursts[1][spiIndex] << 8) | (spiRxBursts[2][spiIndex]);
  
  return (status);
}

/******************************************************//**
 * @brief  Issues the Nop command to the L6474 of the specified shield
 * @param[in] shieldId (from 0 to 2)
 * @retval None
 **********************************************************/
void L6474_CmdNop(uint8_t shieldId)
{
  L6474_SendCommand(shieldId, L6474_NOP);
}

/******************************************************//**
 * @brief  Issues the SetParam command to the L6474 of the specified shield
 * @param[in] shieldId (from 0 to 2)
 * @param[in] param Register adress (L6474_ABS_POS, L6474_MARK,...)
 * @param[in] value Value to set in the register
 * @retval None
 **********************************************************/
void L6474_CmdSetParam(uint8_t shieldId,
                        L6474_Registers_t param,
                        uint32_t value)
{
  uint32_t i;
  uint8_t maxArgumentNbBytes = 0;
  uint8_t spiIndex = numberOfShields - shieldId - 1;

    for (i = 0; i < numberOfShields; i++)
    {
      spiTxBursts[0][i] = L6474_NOP;
      spiTxBursts[1][i] = L6474_NOP;
      spiTxBursts[2][i] = L6474_NOP;
      spiTxBursts[3][i] = L6474_NOP;
    }
    switch (param)
  {
    case L6474_ABS_POS: ;
    case L6474_MARK:
        spiTxBursts[0][spiIndex] = param;
        spiTxBursts[1][spiIndex] = (uint8_t)(value >> 16);
        spiTxBursts[2][spiIndex] = (uint8_t)(value >> 8);
        maxArgumentNbBytes = 3;
        break;
    case L6474_EL_POS: ;
    case L6474_CONFIG:
        spiTxBursts[1][spiIndex] = param;
        spiTxBursts[2][spiIndex] = (uint8_t)(value >> 8);
        maxArgumentNbBytes = 2;
        break;
    default:
        spiTxBursts[2][spiIndex] = param;
        maxArgumentNbBytes = 1;
    }
    spiTxBursts[3][spiIndex] = (uint8_t)(value);
    

 
  /* SPI transfer */
  for (i = L6474_CMD_ARG_MAX_NB_BYTES-1-maxArgumentNbBytes;
       i < L6474_CMD_ARG_MAX_NB_BYTES;
       i++)
  {
     L6474_WriteBytes(&spiTxBursts[i][0],&spiRxBursts[i][0]);
  }

}

/******************************************************//**
 * @brief  Reads the Status Register value
 * @param[in] shieldId (from 0 to 2)
 * @retval Status register valued
 * @note The status register flags are not cleared 
 * at the difference with CmdGetStatus()
 **********************************************************/
uint16_t L6474_ReadStatusRegister(uint8_t shieldId)
{
  return (L6474_CmdGetParam(shieldId,L6474_STATUS));
}

/******************************************************//**
 * @brief  Set the stepping mode 
 * @param[in] shieldId (from 0 to 2)
 * @param[in] stepMod from full step to 1/16 microstep as specified in enum L6474_STEP_SEL_t
 * @retval None
 **********************************************************/
void L6474_SelectStepMode(uint8_t shieldId, L6474_STEP_SEL_t stepMod)
{
  uint8_t stepModeRegister;
  
  /* Disable power stage */
   L6474_CmdDisable(shieldId);

  
  /* Read Step mode register and clear STEP_SEL field */
  stepModeRegister = (uint8_t)(0xF8 & L6474_CmdGetParam(shieldId,L6474_STEP_MODE)) ;
  
  /* Apply new step mode */
  L6474_CmdSetParam(shieldId, L6474_STEP_MODE, stepModeRegister | (uint8_t)stepMod);

}



/******************************************************//**
 * @brief  Sends a command without arguments to the L6474 via the SPI
 * @param[in] shieldId (from 0 to 2)
 * @param[in] param Command to send 
 * @retval None
 **********************************************************/
void L6474_SendCommand(uint8_t shieldId, uint8_t param)
{
  uint8_t spiIndex = numberOfShields - shieldId - 1;

  uint32_t i = 0;
    for (i = 0; i < numberOfShields; i++)
    {
      spiTxBursts[3][i] = L6474_NOP;     
    }
    spiTxBursts[3][spiIndex] = param;
    

  L6474_WriteBytes(&spiTxBursts[3][0], &spiRxBursts[3][0]); 
  
}

/******************************************************//**
 * @brief  Sets the registers of the L6474 to their predefined values 
 * from l6474_target_config.h
 * @param[in] shieldId (from 0 to 2)
 * @retval None
 **********************************************************/
void L6474_SetRegisterToPredefinedValues(uint8_t shieldId)
{
  L6474_CmdSetParam(shieldId,
                    L6474_ABS_POS,
                    0);
  L6474_CmdSetParam(shieldId,
                    L6474_EL_POS,
                    0);
  L6474_CmdSetParam(shieldId,
                    L6474_MARK,
                    0);
  switch (shieldId)
  {
    case 0:
      L6474_CmdSetParam(shieldId,
                        L6474_TVAL,
                        L6474_Tval_Current_to_Par(L6474_CONF_PARAM_TVAL_SHIELD_0));
      L6474_CmdSetParam(shieldId,
                        L6474_T_FAST,
                        (uint8_t)L6474_CONF_PARAM_TOFF_FAST_SHIELD_0 |
                        (uint8_t)L6474_CONF_PARAM_FAST_STEP_SHIELD_0);
      L6474_CmdSetParam(shieldId,
                        L6474_TON_MIN,
                        L6474_Tmin_Time_to_Par(L6474_CONF_PARAM_TON_MIN_SHIELD_0));
      L6474_CmdSetParam(shieldId,
                        L6474_TOFF_MIN,
                        L6474_Tmin_Time_to_Par(L6474_CONF_PARAM_TOFF_MIN_SHIELD_0));
      L6474_CmdSetParam(shieldId,
                        L6474_OCD_TH,
                        L6474_CONF_PARAM_OCD_TH_SHIELD_0);
      L6474_CmdSetParam(shieldId,
                        L6474_STEP_MODE,
                        (uint8_t)L6474_CONF_PARAM_STEP_SEL_SHIELD_0 |
                        (uint8_t)L6474_CONF_PARAM_SYNC_SEL_SHIELD_0);
      L6474_CmdSetParam(shieldId,
                        L6474_ALARM_EN,
                        L6474_CONF_PARAM_ALARM_EN_SHIELD_0);
      L6474_CmdSetParam(shieldId,
                        L6474_CONFIG,
                        (uint16_t)L6474_CONF_PARAM_CLOCK_SETTING_SHIELD_0 |
                        (uint16_t)L6474_CONF_PARAM_TQ_REG_SHIELD_0 |
                        (uint16_t)L6474_CONF_PARAM_OC_SD_SHIELD_0 |
                        (uint16_t)L6474_CONF_PARAM_SR_SHIELD_0 |
                        (uint16_t)L6474_CONF_PARAM_TOFF_SHIELD_0);
      break;
    case 1:
      L6474_CmdSetParam(shieldId,
                        L6474_TVAL,
                        L6474_Tval_Current_to_Par(L6474_CONF_PARAM_TVAL_SHIELD_1));
      L6474_CmdSetParam(shieldId,
                        L6474_T_FAST,
                        (uint8_t)L6474_CONF_PARAM_TOFF_FAST_SHIELD_1 |
                        (uint8_t)L6474_CONF_PARAM_FAST_STEP_SHIELD_1);
      L6474_CmdSetParam(shieldId,
                        L6474_TON_MIN,
                        L6474_Tmin_Time_to_Par(L6474_CONF_PARAM_TON_MIN_SHIELD_1));
      L6474_CmdSetParam(shieldId,
                        L6474_TOFF_MIN,
                        L6474_Tmin_Time_to_Par(L6474_CONF_PARAM_TOFF_MIN_SHIELD_1));
      L6474_CmdSetParam(shieldId,
                        L6474_OCD_TH,
                        L6474_CONF_PARAM_OCD_TH_SHIELD_1);
      L6474_CmdSetParam(shieldId,
                        L6474_STEP_MODE,
                        (uint8_t)L6474_CONF_PARAM_STEP_SEL_SHIELD_1 |
                        (uint8_t)L6474_CONF_PARAM_SYNC_SEL_SHIELD_1);
      L6474_CmdSetParam(shieldId,
                        L6474_ALARM_EN,
                        L6474_CONF_PARAM_ALARM_EN_SHIELD_1);
      L6474_CmdSetParam(shieldId,
                        L6474_CONFIG,
                        (uint16_t)L6474_CONF_PARAM_CLOCK_SETTING_SHIELD_1 |
                        (uint16_t)L6474_CONF_PARAM_TQ_REG_SHIELD_1 |
                        (uint16_t)L6474_CONF_PARAM_OC_SD_SHIELD_1 |
                        (uint16_t)L6474_CONF_PARAM_SR_SHIELD_1 |
                        (uint16_t)L6474_CONF_PARAM_TOFF_SHIELD_1);
      break;
    case 2:
      L6474_CmdSetParam(shieldId,
                        L6474_TVAL,
                        L6474_Tval_Current_to_Par(L6474_CONF_PARAM_TVAL_SHIELD_2));
      L6474_CmdSetParam(shieldId,
                        L6474_T_FAST,
                        (uint8_t)L6474_CONF_PARAM_TOFF_FAST_SHIELD_2 |
                        (uint8_t)L6474_CONF_PARAM_FAST_STEP_SHIELD_2);
      L6474_CmdSetParam(shieldId,
                        L6474_TON_MIN,
                        L6474_Tmin_Time_to_Par(L6474_CONF_PARAM_TON_MIN_SHIELD_2));
      L6474_CmdSetParam(shieldId,
                        L6474_TOFF_MIN,
                        L6474_Tmin_Time_to_Par(L6474_CONF_PARAM_TOFF_MIN_SHIELD_2));
      L6474_CmdSetParam(shieldId,
                        L6474_OCD_TH,
                        L6474_CONF_PARAM_OCD_TH_SHIELD_2);
      L6474_CmdSetParam(shieldId,
                        L6474_STEP_MODE,
                        (uint8_t)L6474_CONF_PARAM_STEP_SEL_SHIELD_2 |
                        (uint8_t)L6474_CONF_PARAM_SYNC_SEL_SHIELD_2);
      L6474_CmdSetParam(shieldId,
                        L6474_ALARM_EN,
                        L6474_CONF_PARAM_ALARM_EN_SHIELD_2);
      L6474_CmdSetParam(shieldId,
                        L6474_CONFIG,
                        (uint16_t)L6474_CONF_PARAM_CLOCK_SETTING_SHIELD_2 |
                        (uint16_t)L6474_CONF_PARAM_TQ_REG_SHIELD_2 |
                        (uint16_t)L6474_CONF_PARAM_OC_SD_SHIELD_2 |
                        (uint16_t)L6474_CONF_PARAM_SR_SHIELD_2 |
                        (uint16_t)L6474_CONF_PARAM_TOFF_SHIELD_2);
      break;
    default: ;
  }
}

/******************************************************//**
 * @brief  Sets the registers of the L6474 to their predefined values 
 * from l6474_target_config.h
 * @param[in] shieldId (from 0 to 2)
 * @retval None
 **********************************************************/
void L6474_WriteBytes(uint8_t *pByteToTransmit, uint8_t *pReceivedByte)
{
  spi_enable();
  uint32_t i = 0;
  for (i = 0; i < numberOfShields; i++)
  {
    *pReceivedByte = spi_transfer(*pByteToTransmit);
    pByteToTransmit++;
    pReceivedByte++;
  }
  spi_disable();
}




/******************************************************//**
 * @brief Converts mA in compatible values for TVAL register 
 * @param[in] Tval
 * @retval TVAL values
 **********************************************************/
inline uint8_t L6474_Tval_Current_to_Par(double Tval)
{
  return ((uint8_t)(((Tval - 31.25)/31.25)+0.5));
}

/******************************************************//**
 * @brief Convert time in us in compatible values 
 * for TON_MIN register
 * @param[in] Tmin
 * @retval TON_MIN values
 **********************************************************/
inline uint8_t L6474_Tmin_Time_to_Par(double Tmin)
{
  return ((uint8_t)(((Tmin - 0.5)*2)+0.5));
}
                   

