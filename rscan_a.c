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

#include "addl_types.h"
#include "r_cg_macrodriver.h"
#include <stdbool.h>
#include "map_rscan.h"

#define  DRIVER_LOCAL
#define  APPLICATION_INTERFACE

#include "rscan_p.h"
#include "rscan_s.h"

#include <stddef.h>
#include <stdio.h>

//#include <varargs.h>

/*
 * Global Settings
 */

#ifndef EE_RSCAN_A_TIMEOUT_LIMIT
    #define EE_RSCAN_A_TIMEOUT_LIMIT ( 100000000L )
#endif

#ifdef  EE_RSCAN_VERBOSE
#if( EE_RSCAN_VERBOSE == 1 )
#define printf( String ) \
              ( ASMN_UARTSENDSTRING( ASMN_MENUCOM, String, ASMN_UARTMODECRLF ) )
#endif

#if( EE_RSCAN_VERBOSE == 2 )
#endif

#if( EE_RSCAN_VERBOSE == 0 )
#define printf( String ) ( RSCAN_A_DoNothing( String ) )
#endif

#else
#define printf( String ) ( RSCAN_A_DoNothing( String ) )
#endif

/*
 * Global Variables
 */

static uint8_t EE_RSCAN_A_IRQ_REC_0  = 0;
static uint8_t EE_RSCAN_A_IRQ_REC_1  = 0;
static uint8_t EE_RSCAN_A_IRQ_TRX_0  = 0;

static uint8_t PNWUnit_u08           = 0;
static uint8_t PNWChannel_u08        = 0;

/*
 * Local Support Functions
 */

void RSCAN_A_DoNothing( char *String )  /* Suppress printing action */
{
}

void RSCAN_A_UnitChannel1ReceiveIRQ( void )  /* Receive Interrupt 1st Unit/Channel */
{
  EE_RSCAN_A_IRQ_REC_0++;
  return;
}

void RSCAN_A_UnitChannel2ReceiveIRQ( void )  /* Receive Interrupt 1st Unit/Channel */
{
  EE_RSCAN_A_IRQ_REC_1++;
  return;
}

void RSCAN_A_UnitChannel1TransmitIRQ( void )  /* Receive Interrupt 1st Unit/Channel */
{
  EE_RSCAN_A_IRQ_TRX_0++;
  return;
}

uint8_t EE_RSCAN_Shutdown( uint8_t Unit_u08 )
{
  uint8_t EE_RSCAN_Status_bit   = EE_RSCAN_OK;

  EE_RSCAN_Status_bit &= EE_RSCAN_Stop( Unit_u08,
                                        EE_RSCAN_GLOBAL,
                                        EE_RSCAN_OPMODE_RESET );
  return( EE_RSCAN_Status_bit );
}

void RSCAN_A_PNWGlobalErrorIRQ( void )     /* Global Error Interrupt for PNW */
{
  uint8_t FIFOErrStatus_u08;

  /* Check for any FIFO overflow - to be fail safe in case of unexpected stops */
  
  EE_RSCAN_GetFIFOStatus( PNWUnit_u08,
                          EE_RSCAN_GLOBAL,
                          0,
                          EE_RSCAN_FIFO_STATUS_LOST,
                          &FIFOErrStatus_u08 );
                                             
  if( FIFOErrStatus_u08 == EE_RSCAN_SET )  /* Clear RXFIFO 0 */
  {
    EE_RSCAN_EnableRXFIFO( PNWUnit_u08, 0, EE_RSCAN_CLEAR );
    EE_RSCAN_EnableRXFIFO( PNWUnit_u08, 0, EE_RSCAN_SET );
  }
  
  EE_RSCAN_GetFIFOStatus( PNWUnit_u08,
                          EE_RSCAN_GLOBAL,
                          1,
                          EE_RSCAN_FIFO_STATUS_LOST,
                          &FIFOErrStatus_u08 );

  if( FIFOErrStatus_u08 == EE_RSCAN_SET )  /* Clear RXFIFO 1 */
  {
    EE_RSCAN_EnableRXFIFO( PNWUnit_u08, 1, EE_RSCAN_CLEAR );
    EE_RSCAN_EnableRXFIFO( PNWUnit_u08, 1, EE_RSCAN_SET );
  }
  return;
}

/*
 * Application Test Functions
 */

//=============================================================================
// FunctionName: EE_RSCAN_BasicTest
// IN  :         Unit Numbers, Channel Numbers
// OUT :         Success Status
// Description : Performs elementary sending and receiving of one standard 
//               message with default settings between two channels
// 
//=============================================================================

uint8_t EE_RSCAN_BasicTest( uint8_t Unit1_u08,           /* runs with default configuration */
                        uint8_t Unit2_u08,
                        uint8_t Channel1_u08,
                        uint8_t Channel2_u08 )
{
  uint8_t EE_RSCAN_Status_bit   = EE_RSCAN_OK;
  uint8_t DataCounter_u08;
  uint8_t SendStatus_u08;
  uint8_t ReceiveStatus_u08;
  uint32_t TimeoutLimit_u32;
  
  struct ee_rscan_message SendMessage;
  struct ee_rscan_message ReceiveMessage;
  struct ee_rscan_a_afl   *FilterEntry = &EE_RSCAN_A_AFL_RXBOX_ANY;
  
  /* Message Set Up */
  
  SendMessage.hdr.id     = 0x5AA;
  SendMessage.hdr.thlen  = EE_RSCAN_CLEAR;        /* No entry in THL */
  SendMessage.hdr.rtr    = 0;                     /* Data Frame */
  SendMessage.hdr.ide    = 0;                     /* Standard Frame */
  SendMessage.flag.ptr   = 0x23;                  /* HTH value */
  SendMessage.flag.dlc   = 8;
  SendMessage.path       = EE_RSCAN_PATH_MSGBOX;  /* Send via Message Box */
  SendMessage.pathdetail = EE_RSCAN_PATHDETAIL_ANY;  /* use any box... */
  
  for( DataCounter_u08 = 0;
       DataCounter_u08 < SendMessage.flag.dlc;
       DataCounter_u08++ )
  {
    SendMessage.data[ DataCounter_u08 ] = DataCounter_u08 + 1;
  }

  ReceiveMessage.path       = EE_RSCAN_PATH_MSGBOX; /* Receive in msg box */
  ReceiveMessage.pathdetail = 0;                    /* Check in box #0 */
  FilterEntry->ptr0.rmdp    = 0;                    /* Receive in box #0 */
  FilterEntry->ptr0.ptr     = 0x23;                 /* HRH equal to HTH */
  
  /* Port activation */
  
  EE_RSCAN_Status_bit =  EE_RSCAN_PortEnable( Unit1_u08,
                                              Channel1_u08 );
  if( EE_RSCAN_Status_bit == EE_RSCAN_ERROR ) return( EE_RSCAN_ERROR );
  EE_RSCAN_Status_bit =  EE_RSCAN_PortEnable( Unit2_u08,
                                              Channel2_u08 );
  if( EE_RSCAN_Status_bit == EE_RSCAN_ERROR ) return( EE_RSCAN_ERROR );
    
  /* Configuration */
  
  EE_RSCAN_Status_bit &= EE_RSCAN_SetGlobalConfiguration( Unit1_u08,
                                                          &EE_RSCAN_A_GCFG_BASIC );
  EE_RSCAN_Status_bit &= EE_RSCAN_SetGlobalConfiguration( Unit2_u08,
                                                          &EE_RSCAN_A_GCFG_BASIC );
                                                          
	EE_RSCAN_Status_bit &= EE_RSCAN_Start( Unit1_u08, /* Perform global activation */
			                                   Channel1_u08,
																				 EE_RSCAN_OPMODE_RESET, /* Channel Reset */
																				 EE_RSCAN_CLEAR,
																				 EE_RSCAN_CLEAR );

	EE_RSCAN_Status_bit &= EE_RSCAN_Start( Unit2_u08, /* Perform global activation */
			                                   Channel2_u08,
																				 EE_RSCAN_OPMODE_RESET, /* Channel Reset */
																				 EE_RSCAN_CLEAR,
																				 EE_RSCAN_CLEAR );

	EE_RSCAN_Status_bit &= EE_RSCAN_SetChannelConfiguration( Unit1_u08,
                                                           Channel1_u08,
                                                           &EE_RSCAN_A_CHCFG_BASIC );
  EE_RSCAN_Status_bit &= EE_RSCAN_SetChannelConfiguration( Unit2_u08,
                                                           Channel2_u08,
                                                           &EE_RSCAN_A_CHCFG_BASIC );

  EE_RSCAN_Status_bit &= EE_RSCAN_CreateInterrupt( Unit1_u08,
                                                   Channel1_u08,
                                                   EE_RSCAN_INT_TX,
                                                   EE_RSCAN_INTENABLEDEFAULT,
                                                   RSCAN_A_UnitChannel1TransmitIRQ );
  
  EE_RSCAN_Status_bit &= EE_RSCAN_SetAFLEntry( Unit2_u08,
                                               Channel2_u08,
																							 0,
                                               FilterEntry );
  
  if( EE_RSCAN_Status_bit == EE_RSCAN_ERROR ) return( EE_RSCAN_ERROR );
    
  /* Activate Units and Channels */

  EE_RSCAN_Status_bit &= EE_RSCAN_Start( Unit1_u08,
                                         Channel1_u08,
                                         EE_RSCAN_OPMODE_OPER,   /* operation mode */
                                         EE_RSCAN_SET,           /* error clearing */
                                         EE_RSCAN_SET );         /* timestamp reset */

  EE_RSCAN_Status_bit &= EE_RSCAN_Start( Unit2_u08,
                                         Channel2_u08,
                                         EE_RSCAN_OPMODE_OPER,   /* operation mode */
                                         EE_RSCAN_SET,           /* error clearing */
                                         EE_RSCAN_SET );         /* timestamp reset */

  EE_RSCAN_A_IRQ_TRX_0 = 0;
  
  /* Send Message to be received by other unit/channel */
  
  EE_RSCAN_Status_bit &= EE_RSCAN_SendMessage( Unit1_u08,
                                               Channel1_u08,
                                               &SendStatus_u08,
                                               &SendMessage );

  if( EE_RSCAN_Status_bit == EE_RSCAN_ERROR ) return( EE_RSCAN_ERROR );
    
  TimeoutLimit_u32 = EE_RSCAN_A_TIMEOUT_LIMIT;
  while( ( --TimeoutLimit_u32 > 0 ) && ( EE_RSCAN_A_IRQ_TRX_0 == 0 ) );
  if( EE_RSCAN_A_IRQ_TRX_0 == 0 ) return( EE_RSCAN_ERROR );
  
  /* Receive the message */

  TimeoutLimit_u32 = EE_RSCAN_A_TIMEOUT_LIMIT;

  do
  {  
    EE_RSCAN_Status_bit &= EE_RSCAN_ReceiveMessage( Unit2_u08,
                                                    &ReceiveStatus_u08,
                                                    &ReceiveMessage );
    if( EE_RSCAN_Status_bit == EE_RSCAN_ERROR ) return( EE_RSCAN_ERROR );
  
  } while( ( ReceiveStatus_u08 == EE_RSCAN_FAULT_NODATA ) &&
           ( --TimeoutLimit_u32 > 0 ) );
           
  if( TimeoutLimit_u32 == 0L ) EE_RSCAN_Status_bit = EE_RSCAN_ERROR;
                                                  
  /* Verify the message */
  
  EE_RSCAN_Status_bit &= ( ReceiveMessage.hdr.id   == SendMessage.hdr.id );
  EE_RSCAN_Status_bit &= ( ReceiveMessage.hdr.rtr  == SendMessage.hdr.rtr );
  EE_RSCAN_Status_bit &= ( ReceiveMessage.hdr.ide  == SendMessage.hdr.ide );
  EE_RSCAN_Status_bit &= ( ReceiveMessage.flag.ptr == SendMessage.flag.ptr );
  EE_RSCAN_Status_bit &= ( ReceiveMessage.flag.dlc == SendMessage.flag.dlc );

  for( DataCounter_u08 = 0;
       DataCounter_u08 < SendMessage.flag.dlc;
       DataCounter_u08++ )
  {
    EE_RSCAN_Status_bit &= ( ReceiveMessage.data[ DataCounter_u08 ] == 
                             SendMessage.data[ DataCounter_u08 ] );
  } 
  
  /* Shutdown */
  
  EE_RSCAN_Status_bit &= EE_RSCAN_Stop( Unit1_u08,
                                        EE_RSCAN_GLOBAL,
                                        EE_RSCAN_OPMODE_RESET );
  EE_RSCAN_Status_bit &= EE_RSCAN_Stop( Unit2_u08,
                                        EE_RSCAN_GLOBAL,
                                        EE_RSCAN_OPMODE_RESET );
   
  return( EE_RSCAN_Status_bit );
}

//=============================================================================
// FunctionName: EE_RSCAN_BasicSelfTest
// IN  :         Unit Number, Channel Numbers
// OUT :         Success Status
// Description : Performs elementary sending and receiving of one standard 
//               message with default settings between two channels internally
// 
//=============================================================================

uint8_t EE_RSCAN_BasicSelfTest( uint8_t Unit1_u08,   /* runs with default configuration */
                            uint8_t Channel1_u08,
                            uint8_t Channel2_u08 )
{
  uint8_t EE_RSCAN_Status_bit   = EE_RSCAN_OK;
  uint8_t DataCounter_u08;
  uint8_t SendStatus_u08;
  uint8_t ReceiveStatus_u08;
  uint32_t TimeoutLimit_u32;
  
  struct ee_rscan_message SendMessage;
  struct ee_rscan_message ReceiveMessage;
  struct ee_rscan_a_afl   *FilterEntry = &EE_RSCAN_A_AFL_RXBOX_ANY;
  
  /* Message Set Up */
  
  SendMessage.hdr.id     = 0x5AA;
  SendMessage.hdr.thlen  = EE_RSCAN_CLEAR;        /* No entry in THL */
  SendMessage.hdr.rtr    = 0;                     /* Data Frame */
  SendMessage.hdr.ide    = 0;                     /* Standard Frame */
  SendMessage.flag.ptr   = 0x23;                  /* HTH value */
  SendMessage.flag.dlc   = 8;
  SendMessage.path       = EE_RSCAN_PATH_MSGBOX;  /* Send via Message Box */
  SendMessage.pathdetail = EE_RSCAN_PATHDETAIL_ANY;  /* use any box... */
  
  for( DataCounter_u08 = 0;
       DataCounter_u08 < SendMessage.flag.dlc;
       DataCounter_u08++ )
  {
    SendMessage.data[ DataCounter_u08 ] = DataCounter_u08 + 1;
  }

  ReceiveMessage.path       = EE_RSCAN_PATH_MSGBOX; /* Receive in msg box */
  ReceiveMessage.pathdetail = 0;                    /* Check in box #0 */
  FilterEntry->ptr0.rmdp    = 0;                    /* Receive in box #0 */
  FilterEntry->ptr0.ptr     = 0x23;                 /* HRH equal to HTH */
  
  /* Configuration */
  
  EE_RSCAN_Status_bit &= EE_RSCAN_SetGlobalConfiguration( Unit1_u08,
                                                          &EE_RSCAN_A_GCFG_BASIC );
                                                          
	EE_RSCAN_Status_bit &= EE_RSCAN_Start( Unit1_u08, /* Perform global activation */
			                                   Channel1_u08,
																				 EE_RSCAN_OPMODE_RESET, /* Channel Reset */
																				 EE_RSCAN_CLEAR,
																				 EE_RSCAN_CLEAR );

	EE_RSCAN_Status_bit &= EE_RSCAN_Start( Unit1_u08, /* Perform global activation */
			                                   Channel2_u08,
																				 EE_RSCAN_OPMODE_RESET, /* Channel Reset */
																				 EE_RSCAN_CLEAR,
																				 EE_RSCAN_CLEAR );

	EE_RSCAN_Status_bit &= EE_RSCAN_SetChannelConfiguration( Unit1_u08,
                                                           Channel1_u08,
                                                           &EE_RSCAN_A_CHCFG_BASIC );
  EE_RSCAN_Status_bit &= EE_RSCAN_SetChannelConfiguration( Unit1_u08,
                                                           Channel2_u08,
                                                           &EE_RSCAN_A_CHCFG_BASIC );

  EE_RSCAN_Status_bit &= EE_RSCAN_CreateInterrupt( Unit1_u08,
                                                   Channel1_u08,
                                                   EE_RSCAN_INT_TX,
                                                   EE_RSCAN_INTENABLEDEFAULT,
                                                   RSCAN_A_UnitChannel1TransmitIRQ );
  
  EE_RSCAN_Status_bit &= EE_RSCAN_SetAFLEntry( Unit1_u08,
                                               Channel2_u08,
																							 0,
                                               FilterEntry );
  
  if( EE_RSCAN_Status_bit == EE_RSCAN_ERROR ) return( EE_RSCAN_ERROR );
    
  /* Activate internal communication test mode */

  EE_RSCAN_Status_bit &= EE_RSCAN_Stop( Unit1_u08,
                                        EE_RSCAN_GLOBAL,
                                        EE_RSCAN_OPMODE_HALT );

  EE_RSCAN_Status_bit &= EE_RSCAN_IntCANBusActivate( Unit1_u08 );

  /* Activate Units and Channels */
  
  EE_RSCAN_Status_bit &= EE_RSCAN_Start( Unit1_u08,
                                         Channel1_u08,
                                         EE_RSCAN_OPMODE_OPER,   /* operation mode */
                                         EE_RSCAN_SET,           /* error clearing */
                                         EE_RSCAN_SET );         /* timestamp reset */

  EE_RSCAN_Status_bit &= EE_RSCAN_Start( Unit1_u08,
                                         Channel2_u08,
                                         EE_RSCAN_OPMODE_OPER,   /* operation mode */
                                         EE_RSCAN_SET,           /* error clearing */
                                         EE_RSCAN_SET );         /* timestamp reset */

  EE_RSCAN_A_IRQ_TRX_0 = 0;
  
  /* Send Message to be received by other unit/channel */
  
  EE_RSCAN_Status_bit &= EE_RSCAN_SendMessage( Unit1_u08,
                                               Channel1_u08,
                                               &SendStatus_u08,
                                               &SendMessage );

  if( EE_RSCAN_Status_bit == EE_RSCAN_ERROR ) return( EE_RSCAN_ERROR );
    
  TimeoutLimit_u32 = EE_RSCAN_A_TIMEOUT_LIMIT;
  while( ( --TimeoutLimit_u32 > 0 ) && ( EE_RSCAN_A_IRQ_TRX_0 == 0 ) );
  if( EE_RSCAN_A_IRQ_TRX_0 == 0 ) return( EE_RSCAN_ERROR );
  
  /* Receive the message */

  TimeoutLimit_u32 = EE_RSCAN_A_TIMEOUT_LIMIT;

  do
  {  
    EE_RSCAN_Status_bit &= EE_RSCAN_ReceiveMessage( Unit1_u08,
                                                    &ReceiveStatus_u08,
                                                    &ReceiveMessage );
    if( EE_RSCAN_Status_bit == EE_RSCAN_ERROR ) return( EE_RSCAN_ERROR );
  
  } while( ( ReceiveStatus_u08 == EE_RSCAN_FAULT_NODATA ) &&
           ( --TimeoutLimit_u32 > 0 ) );
           
  if( TimeoutLimit_u32 == 0L ) EE_RSCAN_Status_bit = EE_RSCAN_ERROR;
                                                  
  /* Verify the message */
  
  EE_RSCAN_Status_bit &= ( ReceiveMessage.hdr.id   == SendMessage.hdr.id );
  EE_RSCAN_Status_bit &= ( ReceiveMessage.hdr.rtr  == SendMessage.hdr.rtr );
  EE_RSCAN_Status_bit &= ( ReceiveMessage.hdr.ide  == SendMessage.hdr.ide );
  EE_RSCAN_Status_bit &= ( ReceiveMessage.flag.ptr == SendMessage.flag.ptr );
  EE_RSCAN_Status_bit &= ( ReceiveMessage.flag.dlc == SendMessage.flag.dlc );

  for( DataCounter_u08 = 0;
       DataCounter_u08 < SendMessage.flag.dlc;
       DataCounter_u08++ )
  {
    EE_RSCAN_Status_bit &= ( ReceiveMessage.data[ DataCounter_u08 ] == 
                             SendMessage.data[ DataCounter_u08 ] );
  } 
  
  /* Shutdown */
  
  EE_RSCAN_Status_bit &= EE_RSCAN_Stop( Unit1_u08,
                                        EE_RSCAN_GLOBAL,
                                        EE_RSCAN_OPMODE_RESET );
   
  return( EE_RSCAN_Status_bit );
}

//=============================================================================
// FunctionName: EE_RSCAN_BasicIntSelfTest
// IN  :         Unit Number, Channel Number
// OUT :         Success Status
// Description : Performs elementary sending of one standard 
//               message with default settings to the channel itself internally
// 
//=============================================================================

uint8_t EE_RSCAN_BasicIntSelfTest( uint8_t Unit_u08,           /* runs with default configuration */
                               uint8_t Channel_u08 )
{
  uint8_t EE_RSCAN_Status_bit   = EE_RSCAN_OK;
  uint8_t DataCounter_u08;
  uint8_t SendStatus_u08;
  uint8_t ReceiveStatus_u08;
  uint32_t TimeoutLimit_u32;

  struct ee_rscan_message SendMessage;
  struct ee_rscan_message ReceiveMessage;
  struct ee_rscan_a_afl   *FilterEntry = &EE_RSCAN_A_AFL_RXBOX_ANY;
  
  /* Message Set Up */
  
  SendMessage.hdr.id     = 0x5AA;
  SendMessage.hdr.thlen  = EE_RSCAN_CLEAR;        /* No entry in THL */
  SendMessage.hdr.rtr    = 0;                     /* Data Frame */
  SendMessage.hdr.ide    = 0;                     /* Standard Frame */
  SendMessage.flag.ptr   = 0x23;                  /* HTH value */
  SendMessage.flag.dlc   = 8;
  SendMessage.path       = EE_RSCAN_PATH_MSGBOX;  /* Send via Message Box */
  SendMessage.pathdetail = EE_RSCAN_PATHDETAIL_ANY;  /* use any box... */
  
  ReceiveMessage.path       = EE_RSCAN_PATH_MSGBOX;  /* RX to a Message Box */
  ReceiveMessage.pathdetail = EE_RSCAN_PATHDETAIL_ANY; 

  for( DataCounter_u08 = 0;
       DataCounter_u08 < SendMessage.flag.dlc;
       DataCounter_u08++ )
  {
    SendMessage.data[ DataCounter_u08 ] = DataCounter_u08 + 1;
  }

  /* Configuration */
  
  EE_RSCAN_Status_bit &= EE_RSCAN_SetGlobalConfiguration( Unit_u08,
                                                          &EE_RSCAN_A_GCFG_BASIC );
                                                          
  EE_RSCAN_Status_bit &= EE_RSCAN_Start( Unit_u08, /* Perform global activation */
                                         Channel_u08,
                                         EE_RSCAN_OPMODE_RESET, /* Channel Reset */
                                         EE_RSCAN_SET,         /* error clearing */
                                         EE_RSCAN_SET );      /* timestamp reset */

  EE_RSCAN_Status_bit &= EE_RSCAN_SetChannelConfiguration( Unit_u08,
                                                           Channel_u08,
                                                           &EE_RSCAN_A_CHCFG_BASIC );

  EE_RSCAN_Status_bit &= EE_RSCAN_CreateInterrupt( Unit_u08,
                                                   Channel_u08,
                                                   EE_RSCAN_INT_TX,
                                                   0,
                                                   RSCAN_A_UnitChannel1TransmitIRQ );
  
  EE_RSCAN_Status_bit &= EE_RSCAN_SetAFLEntry( Unit_u08,
                                               Channel_u08,
                                               0,
                                               FilterEntry );
  
  if( EE_RSCAN_Status_bit == EE_RSCAN_ERROR )
  {
    EE_RSCAN_Status_bit &= EE_RSCAN_Shutdown( Unit_u08 );
    return( EE_RSCAN_ERROR );
  }
  
  /* Activate Units and Channels */

  EE_RSCAN_Status_bit &= EE_RSCAN_Stop( Unit_u08,
                                        EE_RSCAN_GLOBAL,
                                        EE_RSCAN_OPMODE_HALT );

  EE_RSCAN_Status_bit &= EE_RSCAN_Start( Unit_u08,
                                         Channel_u08,
                                         EE_RSCAN_OPMODE_STEST,  /* self test mode */
                                         EE_RSCAN_CLEAR,           
                                         EE_RSCAN_CLEAR );         

  EE_RSCAN_A_IRQ_TRX_0 = 0;
  
  /* Send Message to own channel to receive */
  
  EE_RSCAN_Status_bit &= EE_RSCAN_SendMessage( Unit_u08,
                                               Channel_u08,
                                               &SendStatus_u08,
                                               &SendMessage );

  if( EE_RSCAN_Status_bit == EE_RSCAN_ERROR )
  {
    EE_RSCAN_Status_bit &= EE_RSCAN_Shutdown( Unit_u08 );
    return( EE_RSCAN_ERROR );
  }
    
  TimeoutLimit_u32 = EE_RSCAN_A_TIMEOUT_LIMIT;
  while( ( --TimeoutLimit_u32 > 0 ) && ( EE_RSCAN_A_IRQ_TRX_0 == 0 ) );
  if( EE_RSCAN_A_IRQ_TRX_0 == 0 ) 
  {
    EE_RSCAN_Status_bit &= EE_RSCAN_Shutdown( Unit_u08 );
    return( EE_RSCAN_ERROR );
  }
  if( TimeoutLimit_u32 == 0L ) EE_RSCAN_Status_bit = EE_RSCAN_ERROR;
                                                  
  /* Receive a message */

  TimeoutLimit_u32 = EE_RSCAN_A_TIMEOUT_LIMIT;

  do
  {  
    EE_RSCAN_Status_bit &= EE_RSCAN_ReceiveMessage( Unit_u08,
                                                    &ReceiveStatus_u08,
                                                    &ReceiveMessage );
    if( EE_RSCAN_Status_bit == EE_RSCAN_ERROR ) 
    {
      EE_RSCAN_Status_bit &= EE_RSCAN_Shutdown( Unit_u08 );
      return( EE_RSCAN_ERROR );
    }
  } while( ( ReceiveStatus_u08 == EE_RSCAN_FAULT_NODATA ) &&
           ( --TimeoutLimit_u32 > 0 ) );
           
  if( TimeoutLimit_u32 == 0L ) EE_RSCAN_Status_bit = EE_RSCAN_ERROR;

  /* Shutdown */
  
  EE_RSCAN_Status_bit &= EE_RSCAN_Shutdown( Unit_u08 );
  
  return( EE_RSCAN_Status_bit );
}

//=============================================================================
// FunctionName: EE_RSCAN_BasicTest_Tx
// IN  :         Unit Number, Channel Number
// OUT :         Success Status
// Description : Performs elementary sending of one standard 
//               message with default settings
// 
//=============================================================================

uint8_t EE_RSCAN_BasicTest_Tx( uint8_t Unit1_u08,           /* runs with default configuration */
                           uint8_t Channel1_u08 )
{
  uint8_t EE_RSCAN_Status_bit   = EE_RSCAN_OK;
  uint8_t DataCounter_u08;
  uint8_t SendStatus_u08;
  uint32_t TimeoutLimit_u32;
  
  struct ee_rscan_message SendMessage;
  
  /* Message Set Up */
  
  SendMessage.hdr.id     = 0x5AA;
  SendMessage.hdr.thlen  = EE_RSCAN_CLEAR;        /* No entry in THL */
  SendMessage.hdr.rtr    = 0;                     /* Data Frame */
  SendMessage.hdr.ide    = 0;                     /* Standard Frame */
  SendMessage.flag.ptr   = 0x23;                  /* HTH value */
  SendMessage.flag.dlc   = 8;
  SendMessage.path       = EE_RSCAN_PATH_MSGBOX;  /* Send via Message Box */
  SendMessage.pathdetail = EE_RSCAN_PATHDETAIL_ANY;  /* use any box... */
  
  for( DataCounter_u08 = 0;
       DataCounter_u08 < SendMessage.flag.dlc;
       DataCounter_u08++ )
  {
    SendMessage.data[ DataCounter_u08 ] = DataCounter_u08 + 1;
  }

  /* Port activation */
  
  EE_RSCAN_Status_bit =  EE_RSCAN_PortEnable( Unit1_u08,
                                              Channel1_u08 );
  if( EE_RSCAN_Status_bit == EE_RSCAN_ERROR ) return( EE_RSCAN_ERROR );

  /* Configuration */
  
  EE_RSCAN_Status_bit &= EE_RSCAN_SetGlobalConfiguration( Unit1_u08,
                                                          &EE_RSCAN_A_GCFG_BASIC );
                                                          
	EE_RSCAN_Status_bit &= EE_RSCAN_Start( Unit1_u08, /* Perform global activation */
			                                   Channel1_u08,
																				 EE_RSCAN_OPMODE_RESET, /* Channel Reset */
																				 EE_RSCAN_CLEAR,
																				 EE_RSCAN_CLEAR );

	EE_RSCAN_Status_bit &= EE_RSCAN_SetChannelConfiguration( Unit1_u08,
                                                           Channel1_u08,
                                                           &EE_RSCAN_A_CHCFG_BASIC );

  EE_RSCAN_Status_bit &= EE_RSCAN_CreateInterrupt( Unit1_u08,
                                                   Channel1_u08,  
                                                   EE_RSCAN_INT_TX,
                                                   0,
                                                   RSCAN_A_UnitChannel1TransmitIRQ );
  
  if( EE_RSCAN_Status_bit == EE_RSCAN_ERROR ) return( EE_RSCAN_ERROR );
    
  /* Activate Units and Channels */

  EE_RSCAN_Status_bit &= EE_RSCAN_Start( Unit1_u08,
                                         Channel1_u08,
                                         EE_RSCAN_OPMODE_OPER,   /* operation mode */
                                         EE_RSCAN_SET,           /* error clearing */
                                         EE_RSCAN_SET );         /* timestamp reset */

  EE_RSCAN_A_IRQ_TRX_0 = 0;
  
  /* Send Message to be received by external toolset */
  
  EE_RSCAN_Status_bit &= EE_RSCAN_SendMessage( Unit1_u08,
                                               Channel1_u08,
                                               &SendStatus_u08,
                                               &SendMessage );

  if( EE_RSCAN_Status_bit == EE_RSCAN_ERROR ) return( EE_RSCAN_ERROR );
    
  TimeoutLimit_u32 = EE_RSCAN_A_TIMEOUT_LIMIT;
  while( ( --TimeoutLimit_u32 > 0 ) && ( EE_RSCAN_A_IRQ_TRX_0 == 0 ) );
  
  if( TimeoutLimit_u32 == 0L ) EE_RSCAN_Status_bit = EE_RSCAN_ERROR;
                                                  
  /* Shutdown */
  
  EE_RSCAN_Status_bit &= EE_RSCAN_Stop( Unit1_u08,
                                        EE_RSCAN_GLOBAL,
                                        EE_RSCAN_OPMODE_RESET );

  return( EE_RSCAN_Status_bit );
}

//=============================================================================
// FunctionName: EE_RSCAN_BasicTest_Rx
// IN  :         Unit Number, Channel Number
// OUT :         Success Status
// Description : Performs elementary receiving of one standard 
//               message with default settings
// 
//=============================================================================

uint8_t EE_RSCAN_BasicTest_Rx( uint8_t Unit1_u08,           /* runs with default configuration */
                           uint8_t Channel1_u08 )
{
  uint8_t EE_RSCAN_Status_bit   = EE_RSCAN_OK;
  uint8_t ReceiveStatus_u08;
  uint32_t TimeoutLimit_u32;
  
  struct ee_rscan_message ReceiveMessage;
  struct ee_rscan_a_afl   *FilterEntry = &EE_RSCAN_A_AFL_RXBOX_ANY;
  
  /* Message Set Up */
  
  ReceiveMessage.path       = EE_RSCAN_PATH_MSGBOX; /* Receive in msg box */
  ReceiveMessage.pathdetail = 0;                    /* Check in box #0 */
  FilterEntry->ptr0.rmdp    = 0;                    /* Receive in box #0 */
  FilterEntry->ptr0.ptr     = 0x23;                 /* HRH equal to HTH */
  
  /* Port activation */
  
  EE_RSCAN_Status_bit =  EE_RSCAN_PortEnable( Unit1_u08,
                                              Channel1_u08 );
  if( EE_RSCAN_Status_bit == EE_RSCAN_ERROR ) return( EE_RSCAN_ERROR );
    
  /* Configuration */
  
  EE_RSCAN_Status_bit &= EE_RSCAN_SetGlobalConfiguration( Unit1_u08,
                                                          &EE_RSCAN_A_GCFG_BASIC );
                                                          
	EE_RSCAN_Status_bit &= EE_RSCAN_Start( Unit1_u08, /* Perform global activation */
			                                   Channel1_u08,
																				 EE_RSCAN_OPMODE_RESET, /* Channel Reset */
																				 EE_RSCAN_CLEAR,
																				 EE_RSCAN_CLEAR );

	EE_RSCAN_Status_bit &= EE_RSCAN_SetChannelConfiguration( Unit1_u08,
                                                           Channel1_u08,
                                                           &EE_RSCAN_A_CHCFG_BASIC );

  EE_RSCAN_Status_bit &= EE_RSCAN_SetAFLEntry( Unit1_u08,
                                               Channel1_u08,
																							 0,
                                               FilterEntry );
  
  if( EE_RSCAN_Status_bit == EE_RSCAN_ERROR ) return( EE_RSCAN_ERROR );
    
  /* Activate Units and Channels */

  EE_RSCAN_Status_bit &= EE_RSCAN_Start( Unit1_u08,
                                         Channel1_u08,
                                         EE_RSCAN_OPMODE_OPER,   /* operation mode */
                                         EE_RSCAN_SET,           /* error clearing */
                                         EE_RSCAN_SET );         /* timestamp reset */

  /* Receive a message */

  TimeoutLimit_u32 = EE_RSCAN_A_TIMEOUT_LIMIT;

  do
  {  
    EE_RSCAN_Status_bit &= EE_RSCAN_ReceiveMessage( Unit1_u08,
                                                    &ReceiveStatus_u08,
                                                    &ReceiveMessage );
    if( EE_RSCAN_Status_bit == EE_RSCAN_ERROR ) return( EE_RSCAN_ERROR );
  
  } while( ( ReceiveStatus_u08 == EE_RSCAN_FAULT_NODATA ) &&
           ( --TimeoutLimit_u32 > 0 ) );
           
  if( TimeoutLimit_u32 == 0L ) EE_RSCAN_Status_bit = EE_RSCAN_ERROR;
                                                  
  /* Shutdown */
  
  EE_RSCAN_Status_bit &= EE_RSCAN_Stop( Unit1_u08,
                                        EE_RSCAN_GLOBAL,
                                        EE_RSCAN_OPMODE_RESET );

  return( EE_RSCAN_Status_bit );
}

//=============================================================================
// FunctionName: EE_RSCAN_CANFD_PNW_Test
// IN  :         Unit Number, Channel Number
// OUT :         Success Status
// Description : Performs elementary sending of one standard 
//               message with default settings
// 
//=============================================================================

#define EE_RSCAN_PNW_CONNECTED     ( true )
#define EE_RSCAN_PNW_DISCONNECTED  ( false )
#define EE_RSCAN_PNW_CONNECTDATA   ( 0 )
#define EE_RSCAN_PNW_CONNECTFILTER ( 0x01 )
#define EE_RSCAN_PNW_EXITDATA      ( 1 )
#define EE_RSCAN_PNW_EXITFILTER    ( 0x01 )
#define EE_RSCAN_PNW_MINDLC        ( 2 )

uint8_t EE_RSCAN_CANFD_PNW_Test( uint8_t Unit1_u08,
                             uint8_t Channel1_u08 )
{
  uint8_t EE_RSCAN_Status_bit   = EE_RSCAN_OK;
  uint8_t ExitFlag_bit          = false;
  uint8_t PNW_ConnectedState    = EE_RSCAN_PNW_CONNECTED;
  uint8_t RXStatus_u08;
  uint8_t TXStatus_u08;
  
  struct ee_rscan_message MyMessage;
  
  PNWUnit_u08    = Unit1_u08;     /* update globals for Error IRQ handling */
  PNWChannel_u08 = Channel1_u08;
  
  /* Port activation */
  
  EE_RSCAN_Status_bit =  EE_RSCAN_PortEnable( Unit1_u08,
                                              Channel1_u08 );
  if( EE_RSCAN_Status_bit == EE_RSCAN_ERROR ) return( EE_RSCAN_ERROR );

  /* Configuration */
  
  EE_RSCAN_Status_bit &= EE_RSCAN_SetGlobalConfiguration( Unit1_u08,
                                                          &EE_RSCAN_A_GCFG_FDPNW );
                                                          
	EE_RSCAN_Status_bit &= EE_RSCAN_Start( Unit1_u08, /* Perform global activation */
			                                   Channel1_u08,
																				 EE_RSCAN_OPMODE_RESET, /* Channel Reset */
																				 EE_RSCAN_CLEAR,
																				 EE_RSCAN_CLEAR );

	EE_RSCAN_Status_bit &= EE_RSCAN_SetChannelConfiguration( Unit1_u08,
                                                           Channel1_u08,
                                                           &EE_RSCAN_A_CHCFG_FDPNW );

  EE_RSCAN_Status_bit &= EE_RSCAN_SetAFLEntry( Unit1_u08,
                                               Channel1_u08,
																							 0,
                                               &EE_RSCAN_A_AFL_RXFIFO_FDPNW_SWITCH );
  EE_RSCAN_Status_bit &= EE_RSCAN_SetAFLEntry( Unit1_u08,
                                               Channel1_u08,
																							 1,
                                               &EE_RSCAN_A_AFL_RXFIFO_FDPNW_ANY );
  /* Interrupt Activation */

  EE_RSCAN_Status_bit &= EE_RSCAN_CreateInterrupt( Unit1_u08,
                                                   Channel1_u08,
                                                   EE_RSCAN_INT_TX,
                                                   1,
                                                   RSCAN_A_UnitChannel1TransmitIRQ );
  EE_RSCAN_Status_bit &= EE_RSCAN_CreateInterrupt( Unit1_u08,
                                                   EE_RSCAN_GLOBAL,
                                                   EE_RSCAN_INT_RXF0,
                                                   1,
                                                   RSCAN_A_UnitChannel1ReceiveIRQ );
  EE_RSCAN_Status_bit &= EE_RSCAN_CreateInterrupt( Unit1_u08,
                                                   EE_RSCAN_GLOBAL,
                                                   EE_RSCAN_INT_RXF1,
                                                   1,
                                                   RSCAN_A_UnitChannel2ReceiveIRQ );
  EE_RSCAN_Status_bit &= EE_RSCAN_CreateInterrupt( Unit1_u08,
                                                   EE_RSCAN_GLOBAL,
                                                   EE_RSCAN_INT_GERR,
                                                   0,   /* error with higher priority */
                                                   RSCAN_A_PNWGlobalErrorIRQ );
  
  if( EE_RSCAN_Status_bit == EE_RSCAN_ERROR ) return( EE_RSCAN_ERROR );
    
  EE_RSCAN_A_IRQ_TRX_0 = 0;
  EE_RSCAN_A_IRQ_REC_0 = 0;
  EE_RSCAN_A_IRQ_REC_1 = 0;

  /* Activate Units and Channels */

  EE_RSCAN_Status_bit &= EE_RSCAN_Start( Unit1_u08,
                                         Channel1_u08,
                                         EE_RSCAN_OPMODE_OPER,   /* operation mode */
                                         EE_RSCAN_SET,           /* error clearing */
                                         EE_RSCAN_SET );         /* timestamp reset */

  
  /* Wait for a Message Reception or Transmission Completion */
  
  while( !ExitFlag_bit && ( EE_RSCAN_Status_bit == EE_RSCAN_OK ) )
  {
    if( EE_RSCAN_A_IRQ_REC_1 > 0 )
    {
      EE_RSCAN_A_IRQ_REC_1 = 0;
      
      do
      {
        /* processing of FD switching messages */
        
        MyMessage.path       = EE_RSCAN_PATH_RXFIFO;   /* use RX FIFO 1 */
        MyMessage.pathdetail = 1;
        
        EE_RSCAN_Status_bit &= EE_RSCAN_ReceiveMessage( Unit1_u08, 
                          			                  	    &RXStatus_u08, 
  				                                              &MyMessage );

        if( RXStatus_u08 == EE_RSCAN_FAULT_NONE )
        {
          if( MyMessage.flag.dlc >= EE_RSCAN_PNW_MINDLC )
          {
            if( MyMessage.data[ EE_RSCAN_PNW_CONNECTDATA ] & EE_RSCAN_PNW_CONNECTFILTER )
            {
              PNW_ConnectedState = EE_RSCAN_PNW_CONNECTED;
              
              EE_RSCAN_Status_bit &= EE_RSCAN_Stop( Unit1_u08,
                                                    Channel1_u08,
                                                    EE_RSCAN_OPMODE_RESET );
              EE_RSCAN_Status_bit &= EE_RSCAN_Start( Unit1_u08,
                                                     Channel1_u08,
                                                     EE_RSCAN_OPMODE_OPER,   /* Operation mode */
                                                     EE_RSCAN_SET,           /* error clearing */
                                                     EE_RSCAN_SET );        /* timestamp reset */
            }
            else
            {
              PNW_ConnectedState = EE_RSCAN_PNW_DISCONNECTED;
              
              MyMessage.path       = EE_RSCAN_PATH_MSGBOX;              /* stop all pending TX */
              MyMessage.pathdetail = EE_RSCAN_PATHDETAIL_ANY;
              
              EE_RSCAN_Status_bit &= EE_RSCAN_TxAbort( Unit1_u08,
                                                       Channel1_u08,
                                                       &MyMessage );
              
              EE_RSCAN_Status_bit &= EE_RSCAN_Stop( Unit1_u08,         /* then stop controller */
                                                    Channel1_u08,
                                                    EE_RSCAN_OPMODE_HALT );
              EE_RSCAN_Status_bit &= EE_RSCAN_Start( Unit1_u08,
                                                     Channel1_u08,
                                                     EE_RSCAN_OPMODE_RECONLY,  /* RX-Only mode */
                                                     EE_RSCAN_SET,           /* error clearing */
                                                     EE_RSCAN_SET );        /* timestamp reset */
            }
            if( MyMessage.data[ EE_RSCAN_PNW_EXITDATA ] & EE_RSCAN_PNW_EXITFILTER )
            {
              ExitFlag_bit = true;
            }
          }
        }
          
      } while( ( RXStatus_u08 == EE_RSCAN_FAULT_NONE ) &&
               ( EE_RSCAN_Status_bit == EE_RSCAN_OK ) );
    }
    if( ( EE_RSCAN_A_IRQ_REC_0 > 0 ) && ( EE_RSCAN_A_IRQ_REC_1 == 0 ) )
    {
      /* processing of other messages (just copy and send back with modified ID) */
      /* these FIFO reads are not processed in a loop to avoid locking here:
         at heavy bus load still the switching messages must be detectable */

      EE_RSCAN_A_IRQ_REC_0 = 0;
      
      /* processing of FD switching messages */
      
      MyMessage.path       = EE_RSCAN_PATH_RXFIFO;   /* use RX FIFO 0 */
      MyMessage.pathdetail = 0;
      
      EE_RSCAN_Status_bit &= EE_RSCAN_ReceiveMessage( Unit1_u08, 
                        			                  	    &RXStatus_u08, 
				                                              &MyMessage );

      if( RXStatus_u08 == EE_RSCAN_FAULT_NONE )
      {
        if( PNW_ConnectedState == EE_RSCAN_PNW_CONNECTED )
        {
          /* send back received message with ID0 uint8_t set (odd) */
          
          MyMessage.hdr.id    |= 0x00000001;
          MyMessage.path       = EE_RSCAN_PATH_MSGBOX;
          MyMessage.pathdetail = EE_RSCAN_PATHDETAIL_ANY;
          
          do
          {
            EE_RSCAN_Status_bit &= EE_RSCAN_SendMessage( Unit1_u08,
                                                         Channel1_u08,
                                                        &TXStatus_u08,
                                                        &MyMessage );
                                                        
          } while( ( TXStatus_u08 == EE_RSCAN_FAULT_BUSY ) &&
                   ( EE_RSCAN_Status_bit == EE_RSCAN_OK ) );
        }
      }
    }
  }
                                                  
  /* Shutdown */
  
  EE_RSCAN_Status_bit &= EE_RSCAN_Stop( Unit1_u08,
                                        EE_RSCAN_GLOBAL,
                                        EE_RSCAN_OPMODE_RESET );

  return( EE_RSCAN_Status_bit );
}

//=============================================================================
// FunctionName: EE_RSCAN_RAMTestApp
// IN  :         Unit Number
// OUT :         Success Status
// Description : Executes RAM Test after stopping RSCAN
// 
//=============================================================================

uint8_t EE_RSCAN_RAMTestApp( uint8_t Unit_u08 )
{
  uint8_t EE_RSCAN_Status_bit = EE_RSCAN_OK;
  
  EE_RSCAN_Status_bit &= EE_RSCAN_Start( Unit_u08,
                                         EE_RSCAN_GLOBAL,
                                         EE_RSCAN_OPMODE_HALT,   /* operation mode */
                                         EE_RSCAN_SET,           /* error clearing */
                                         EE_RSCAN_SET );         /* timestamp reset */
  
  EE_RSCAN_Status_bit &= EE_RSCAN_Stop( Unit_u08,
                                        EE_RSCAN_GLOBAL,
                                        EE_RSCAN_OPMODE_HALT );
    
  EE_RSCAN_Status_bit &= EE_RSCAN_RAMTest( Unit_u08 );
  
  return( EE_RSCAN_Status_bit );
}
