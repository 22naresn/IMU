/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
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
* File Name    : r_cg_port.c
* Version      : CodeGenerator for RL78/F14 V2.03.06.01 [25 Nov 2020]
* Device(s)    : R5F10PPJ
* Tool-Chain   : CCRL
* Description  : This file implements device driver for PORT module.
* Creation Date: 15/12/2025
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_port.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_PORT_Create
* Description  : This function initializes the Port I/O.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PORT_Create(void)
{
    P0 = _00_Pn3_OUTPUT_0;
    P3 = _00_Pn0_OUTPUT_0 | _00_Pn2_OUTPUT_0;
    P14 = _00_Pn0_OUTPUT_0;
    P15 = _00_Pn7_OUTPUT_0;
    PMC7 = _00_PMCn0_DI_ON | _02_PMCn1_NOT_USE | _04_PMCn2_NOT_USE | _08_PMCn3_NOT_USE | _10_PMCn4_NOT_USE |
           _E0_PMC7_DEFAULT;
    PMC12 = _00_PMCn0_DI_ON | _00_PMCn5_DI_ON | _DE_PMC12_DEFAULT;
    PSRSEL = _00_PSR140_NORMAL | _00_PSR120_NORMAL | _00_PSR30_NORMAL;
    PM0 = _01_PMn0_NOT_USE | _02_PMn1_NOT_USE | _04_PMn2_NOT_USE | _00_PMn3_MODE_OUTPUT | _F0_PM0_DEFAULT;
    PM3 = _00_PMn0_MODE_OUTPUT | _02_PMn1_NOT_USE | _00_PMn2_MODE_OUTPUT | _08_PMn3_NOT_USE | _10_PMn4_NOT_USE |
          _E0_PM3_DEFAULT;
    PM7 = _01_PMn0_MODE_INPUT | _02_PMn1_NOT_USE | _04_PMn2_NOT_USE | _08_PMn3_NOT_USE | _10_PMn4_NOT_USE |
          _20_PMn5_NOT_USE | _40_PMn6_NOT_USE | _80_PMn7_MODE_INPUT;
    PM12 = _01_PMn0_MODE_INPUT | _20_PMn5_MODE_INPUT | _40_PMn6_NOT_USE | _80_PMn7_NOT_USE | _1E_PM12_DEFAULT;
    PM14 = _00_PMn0_MODE_OUTPUT | _FE_PM14_DEFAULT;
    PM15 = _01_PMn0_NOT_USE | _02_PMn1_NOT_USE | _04_PMn2_NOT_USE | _08_PMn3_NOT_USE | _10_PMn4_NOT_USE |
           _20_PMn5_MODE_INPUT | _40_PMn6_NOT_USE | _00_PMn7_MODE_OUTPUT;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
