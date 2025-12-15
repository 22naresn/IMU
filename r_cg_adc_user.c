/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIuint8_tED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2012, 2020 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_adc_user.c
* Version      : CodeGenerator for RL78/F14 V2.03.06.01 [25 Nov 2020]
* Device(s)    : R5F10PPJ
* Tool-Chain   : CCRL
* Description  : This file implements device driver for ADC module.
* Creation Date: 13/12/2025
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_adc.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt r_adc_interrupt(vect=INTAD)
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */

// READS POSITIVE ISOLATION VALUE

uint16_t ADC_Read_ISO_POS(void)
{
    uint16_t adc_result;

    /* Select ANI0 (ISO_POS) */
    ADS = _00_AD_INPUT_CHANNEL_0_3;

    /* Start conversion */
    R_ADC_Start();

    /* Wait until conversion completes */
    while (ADIF == 0U)
    {
        ;
    }

    /* Stop ADC to be clean */
    R_ADC_Stop();

    /* Read result */
    R_ADC_Get_Result(&adc_result);

    return adc_result;
}

//READS NEGATIVE ISOLATION VALUE

uint16_t ADC_Read_ISO_NEG(void)
{
    uint16_t adc_result;

    /* Select ANI1 (ISO_NEG) */
    ADS = _04_AD_INPUT_CHANNEL_4_7;

    /* Start conversion */
    R_ADC_Start();

    /* Wait until conversion completes */
    while (ADIF == 0U)
    {
        ;
    }

    /* Stop ADC */
    R_ADC_Stop();

    /* Read result */
    R_ADC_Get_Result(&adc_result);

    return adc_result;
}


// READS V_BATT ADC VALUE AND MULTIPLIES WITH CONSTANT TO RETURN THE VOLTAGE OF THE BATTERY (PENDING)!!

uint16_t ADC_Read_V_BATT(void)
{
    uint16_t adc_result;

    /* Select ANI2 (V_BATT) */
    ADS = _08_AD_INPUT_CHANNEL_8_11;

    /* Start conversion */
    R_ADC_Start();

    /* Wait until conversion completes */
    while (ADIF == 0U)
    {
        ;
    }

    /* Stop ADC */
    R_ADC_Stop();

    /* Read result */
    R_ADC_Get_Result(&adc_result);

    return adc_result;
}


/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_adc_interrupt
* Description  : This function is INTAD interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_adc_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
