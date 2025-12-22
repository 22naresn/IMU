/*===========================================================================*/
/* PROJECT = RSCAN Type RSCAN_LITE                                           */
/*****************************************************************************/
/*                                  COPYRIGHT                                */
/*===========================================================================*/
/* Copyright (c) 2017 by Renesas Electronics Europe GmbH,                    */
/*               a company of the Renesas Electronics Corporation            */
/*===========================================================================*/
/*===========================================================================*/
/* In case of any question please do not hesitate to contact:                */
/*                                                                           */
/*        ABG.Support                                                        */
/*                                                                           */
/*        Renesas Electronics Europe GmbH                                    */
/*        Arcadiastrasse 10                                                  */
/*        D-40472 Duesseldorf, Germany                                       */
/*                                                                           */
/*        e-mail: device_support.rl78-eu@lm.renesas.com                      */
/*        FAX:   +49 - (0)211 / 65 03 - 12 79                                */
/*                                                                           */
/*===========================================================================*/
/* Warranty Disclaimer                                                       */
/*                                                                           */
/* Because the Product(s) is licensed free of charge, there is no warranty   */
/* of any kind whatsoever and expressly disclaimed and excluded by Renesas,  */
/* either expressed or implied, including but not limited to those for       */
/* non-infringement of intellectual property, merchantability and/or         */
/* fitness for the particular purpose.                                       */
/* Renesas shall not have any obligation to maintain, service or provide bug */
/* fixes for the supplied Product(s) and/or the Application.                 */
/*                                                                           */
/* Each User is solely responsible for determining the appropriateness of    */
/* using the Product(s) and assumes all risks associated with its exercise   */
/* of rights under this Agreement, including, but not limited to the risks   */
/* and costs of program errors, compliance with applicable laws, damage to   */
/* or loss of data, programs or equipment, and unavailability or             */
/* interruption of operations.                                               */
/*                                                                           */
/* Limitation of Liability                                                   */
/*                                                                           */
/* In no event shall Renesas be liable to the User for any incidental,       */
/* consequential, indirect, or punitive damage (including but not limited    */
/* to lost profits) regardless of whether such liability is based on breach  */
/* of contract, tort, strict liability, breach of warranties, failure of     */
/* essential purpose or otherwise and even if advised of the possibility of  */
/* such damages. Renesas shall not be liable for any services or products    */
/* provided by third party vendors, developers or consultants identified or  */
/* referred to the User by Renesas in connection with the Product(s) and/or  */
/* the Application.                                                          */
/*                                                                           */
/*===========================================================================*/

#ifndef _RSCAN_A_H
#define _RSCAN_A_H

#include "iodefine.h"
#include "r_cg_macrodriver.h"

extern uint8_t EE_RSCAN_BasicTest( uint8_t Unit1_uint8_t,
                               uint8_t Unit2_uint8_t,
                               uint8_t Channel1_uint8_t,
                               uint8_t Channel2_uint8_t );
                        
extern uint8_t EE_RSCAN_BasicSelfTest( uint8_t Unit1_uint8_t,
                                   uint8_t Channel1_uint8_t,
                                   uint8_t Channel2_uint8_t );
                            
extern uint8_t EE_RSCAN_BasicIntSelfTest( uint8_t Unit_uint8_t,
                                      uint8_t Channel_uint8_t );

extern uint8_t EE_RSCAN_BasicTest_Tx( uint8_t Unit1_uint8_t,
                                  uint8_t Channel1_uint8_t );

extern uint8_t EE_RSCAN_BasicTest_Rx( uint8_t Unit1_uint8_t,
                                  uint8_t Channel1_uint8_t );
                             
extern uint8_t EE_RSCAN_RAMTestApp( uint8_t Unit_uint8_t );

#endif
