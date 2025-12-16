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

#ifndef _RSCAN_P_H
#define _RSCAN_P_H

#include "r_cg_macrodriver.h"
#include "addl_types.h"

#define OSCILLATOR_FREQUENCY     ( ( float )( 64.0E6 ) )

extern uint8_t EE_RSCAN_PortEnable(  uint8_t UnitNumber_u08,
                                 uint8_t ChannelNumber_u08 );

extern uint8_t EE_RSCAN_PortDisable( uint8_t UnitNumber_u08,
                                 uint8_t ChannelNumber_u08 );
								
extern uint8_t EE_RSCAN_CreateInterrupt( uint8_t  Unit_u08,
                                     uint8_t  Channel_u08,
                                     uint8_t  IntNumber_u08,
                                     uint16_t  SetIntLevel_u08,
                                     void ( *FunctionVector )( ) );
									 
extern uint8_t EE_RSCAN_SetInterrupt( uint8_t Unit_u08,
                                  uint8_t Channel_u08,
                                  uint8_t InterruptSelection_u08,
                                  uint16_t InterruptSubSelection_u16 );
								  
extern uint8_t EE_RSCAN_GetStatus( 	uint8_t  Unit_u08,
                								uint8_t  Channel_u08,
                								uint8_t  StatusNumber_u08,
                								puint8_t StatusValue_u08 );								  
                                  
extern uint8_t EE_RSCAN_GetFIFOStatus( uint8_t  UnitNumber_u08,
                                   uint8_t  ChannelNumber_u08,
                                   uint8_t  FIFONumber_u08,
                                   uint8_t  StatusType_u08,
                                   puint8_t StatusValue_pu08 );

extern uint8_t EE_RSCAN_GetError( uint8_t  Unit_u08,
                              uint8_t  Channel_u08,
                              puint16_t InterruptErrorFlag_pu16,
                              puint16_t LastErrorFlag_pu16 );
                             
extern uint8_t EE_RSCAN_Start( uint8_t UnitNumber_u08,
                           uint8_t ChannelNumber_u08,
                           uint8_t OperationMode_u08,
                           uint8_t ClearErrorCounter_u08,
                           uint16_t TimeStampSetting_u16 );
                           
extern uint8_t EE_RSCAN_Stop( uint8_t UnitNumber_u08,
                          uint8_t ChannelNumber_u08,
                          uint8_t StopMode_u08 );

extern uint8_t EE_RSCAN_SetGlobalConfiguration( uint8_t Unit_u08,
                                            const struct ee_rscan_cfg_global *Config );

extern uint8_t EE_RSCAN_SetChannelConfiguration( uint8_t Unit_u08,
                                             uint8_t Channel_u08,
                                             const struct ee_rscan_cfg_channel *Config );

extern uint8_t EE_RSCAN_SetCOMFIFOConfiguration( uint8_t UnitNumber_u08,
                                             uint8_t ChannelNumber_u08,
                                             const struct ee_rscan_cfg_channel *Config );

extern uint8_t EE_RSCAN_SendMessage( uint8_t  UnitNumber_u08,
                                 uint8_t  ChannelNumber_u08,
                                 puint8_t Status_pu08,
                                 struct ee_rscan_message *Message );

extern uint8_t EE_RSCAN_TxAbort( uint8_t  Unit_u08,
                             uint8_t  Channel_u08,
                             struct ee_rscan_message *Message );
  
extern uint8_t EE_RSCAN_ReceiveMessage( uint8_t  Unit_u08, 
                        				    puint8_t Status_pu08, 
				                            struct ee_rscan_message *Message );

extern uint8_t EE_RSCAN_SetAFLEntry( uint8_t  Unit_u08,
                                 uint8_t  Channel_u08,
								                 uint16_t  RuleNumber_u16,																 
                                 struct ee_rscan_a_afl *AFLEntry );

extern uint8_t EE_RSCAN_EnableRXFIFO( uint8_t UnitNumber_u08,
                                  uint8_t FIFONumber_u08,
                                  uint8_t EnableFlag_u08 );

extern uint8_t EE_RSCAN_EnableCOMFIFO( uint8_t UnitNumber_u08,
                                   uint8_t ChannelNumber_u08,
                                   uint8_t FIFONumber_u08,
                                   uint8_t EnableFlag_u08 );

extern uint8_t EE_RSCAN_GetTimeStampCounter( uint8_t  UnitNumber_u08,
                                         puint32_t TimeStampValue_pu32 );

extern uint8_t EE_RSCAN_IntCANBusActivate( uint8_t UnitNumber_u08 );

extern uint8_t EE_RSCAN_RAMTest( uint8_t Unit_u08 );

#endif
