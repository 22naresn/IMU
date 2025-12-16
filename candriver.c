/***********************************************************************************************************************
* File Name    : candriver.c
* Version      : 1.0
* Device(s)    : R5F10PPJ
* Description  : Ground up CAN Driver for the Renesas R5F10PPJ microcontroller.
***********************************************************************************************************************

#include <stdbool.h>
#include <stddef.h>
#include "r_cg_macrodriver.h"
#include "addl_types.h"
#include "iodefine.h"
#include "map_rscan.h"
#include "rscan.h"
#include "rscan_p.h"
#include "rscan_a.h"
#include "standardports.h"


//=============================================================================
// FunctionName: RSCAN_PortEnable
// IN  : UnitNumber: Selected Macro
//       ChannelNumber: Selected Channel
// OUT : Error Flag
// Description : 
// Enable I/O ports
//=============================================================================
uint8_t EE_RSCAN_PortEnable( uint8_t UnitNumber_u08,
                         uint8_t ChannelNumber_u08 )
{
  uint8_t ChannelCount_u08;

  if( UnitNumber_u08 >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
  if( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) 
    return( EE_RSCAN_ERROR );

  switch( UnitNumber_u08 ) 
  {
    case EE_RSCAN_0:
    {
      switch( ChannelNumber_u08 )
      {

#ifdef EE_RSCAN_PORT_M0RX0
        case EE_RSCAN_CHANNEL0:
          PORT_Enable( EE_RSCAN_PORT_M0RX0, EE_RSCAN_PORT_BIT_M0RX0,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       EE_RSCAN_PORT_FUNC_M0RX0 );
          PORT_Enable( EE_RSCAN_PORT_M0TX0, EE_RSCAN_PORT_BIT_M0TX0,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       EE_RSCAN_PORT_FUNC_M0TX0 );
          break;
#endif

#ifdef EE_RSCAN_PORT_M0RX1
        case EE_RSCAN_CHANNEL1:
          PORT_Enable( EE_RSCAN_PORT_M0RX1, EE_RSCAN_PORT_BIT_M0RX1,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       EE_RSCAN_PORT_FUNC_M0RX1 );
          PORT_Enable( EE_RSCAN_PORT_M0TX1, EE_RSCAN_PORT_BIT_M0TX1,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       EE_RSCAN_PORT_FUNC_M0TX1 );
          break;
#endif

        case EE_RSCAN_GLOBAL:
          for( ChannelCount_u08 = 0; 
               ChannelCount_u08 < ee_rscan_channels[ UnitNumber_u08 ];
               ChannelCount_u08++ )
            {
              EE_RSCAN_PortEnable( UnitNumber_u08, ChannelCount_u08 );
            }
          break;
            
        default:
          return( EE_RSCAN_ERROR );
      }
    } // switch ChannelNumber_u08
    break;
      
    case EE_RSCAN_1:
    {
      switch( ChannelNumber_u08 )
      {

#ifdef EE_RSCAN_PORT_M1RX0
        case EE_RSCAN_CHANNEL0:
          PORT_Enable( EE_RSCAN_PORT_M1RX0, EE_RSCAN_PORT_BIT_M1RX0,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       EE_RSCAN_PORT_FUNC_M1RX0 );
          PORT_Enable( EE_RSCAN_PORT_M1TX0, EE_RSCAN_PORT_BIT_M1TX0,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       EE_RSCAN_PORT_FUNC_M1TX0 );
          break;
#endif

#ifdef EE_RSCAN_PORT_M1RX1
        case EE_RSCAN_CHANNEL1:
          PORT_Enable( EE_RSCAN_PORT_M1RX1, EE_RSCAN_PORT_BIT_M1RX1,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       EE_RSCAN_PORT_FUNC_M1RX1 );
          PORT_Enable( EE_RSCAN_PORT_M1TX1, EE_RSCAN_PORT_BIT_M1TX1,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       EE_RSCAN_PORT_FUNC_M1TX1 );
          break;
#endif

        case EE_RSCAN_GLOBAL:
          for( ChannelCount_u08 = 0; 
               ChannelCount_u08 < ee_rscan_channels[ UnitNumber_u08 ];
               ChannelCount_u08++ )
            {
              EE_RSCAN_PortEnable( UnitNumber_u08, ChannelCount_u08 );
            }
          break;
            
        default:
          return( EE_RSCAN_ERROR );
      }
    } // switch ChannelNumber_u08
    break;

    default: 
      return( EE_RSCAN_ERROR );

  } // switch( UnitNumber )

  return( EE_RSCAN_OK );
}
    

//=============================================================================
// FunctionName: EE_RSCAN_SetGlobalConfiguration
// IN  :         UnitNumber, Global configuration set
// Description : Performs Global Configurations
// 
//=============================================================================

uint8_t EE_RSCAN_SetGlobalConfiguration( uint8_t UnitNumber_u08,
                                     const struct ee_rscan_cfg_global *Config )
{    
  if( UnitNumber_u08 >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );

  /* Must be in global reset to set the global configuration! *
  
  while( ee_rscan_common_p[ UnitNumber_u08 ]->gsts.rsts );

  if( ee_rscan_common_p[ UnitNumber_u08 ]->gsts.mds != EE_RSCAN_OPMODE_RESET )
    return( EE_RSCAN_ERROR );

  ee_rscan_common_p[ UnitNumber_u08 ]->gctrl.gslpr  = Config->gctrl.gslpr;
  while( ee_rscan_common_p[ UnitNumber_u08 ]->gsts.slps );

  ee_rscan_common_p[ UnitNumber_u08 ]->grwcr.rpage  = EE_RSCAN_SET;

  ee_rscan_common_p[ UnitNumber_u08 ]->gcfgl.tpri   = Config->gcfgl.tpri;
  ee_rscan_common_p[ UnitNumber_u08 ]->gcfgl.dce    = Config->gcfgl.dce;
  ee_rscan_common_p[ UnitNumber_u08 ]->gcfgl.dre    = Config->gcfgl.dre;
  ee_rscan_common_p[ UnitNumber_u08 ]->gcfgl.mme    = Config->gcfgl.mme;
  ee_rscan_common_p[ UnitNumber_u08 ]->gcfgl.dcs    = Config->gcfgl.dcs;
  ee_rscan_common_p[ UnitNumber_u08 ]->gcfgl.tsp    = Config->gcfgl.tsp;
  ee_rscan_common_p[ UnitNumber_u08 ]->gcfgl.tsss   = Config->gcfgl.tsss;
  ee_rscan_common_p[ UnitNumber_u08 ]->gcfgh.itrcp  = Config->gcfgh.itrcp;

  ee_rscan_common_p[ UnitNumber_u08 ]->gctrl.gmdc   = Config->gctrl.gmdc;
  ee_rscan_common_p[ UnitNumber_u08 ]->gctrl.ie     = Config->gctrl.ie;
  ee_rscan_common_p[ UnitNumber_u08 ]->gctrh.tsrst  = Config->gctrh.tsrst;

  ee_rscan_common_p[ UnitNumber_u08 ]->rmnb         = Config->rmnb;

  ee_rscan_common_p[ UnitNumber_u08 ]->gaflcfg.rnc0 = Config->rnc[ 0 ];
  ee_rscan_common_p[ UnitNumber_u08 ]->gaflcfg.rnc1 = Config->rnc[ 1 ];

  return( EE_RSCAN_OK );
}    

//=============================================================================
// FunctionName: EE_RSCAN_SetChannelConfiguration
// IN  :         UnitNumber, Channel Number, Config Set
// OUT :         Success Status
// Description : Performs Channel Configurations
// 
//=============================================================================

uint8_t EE_RSCAN_SetChannelConfiguration( uint8_t UnitNumber_u08,
                                      uint8_t ChannelNumber_u08,
                                      const struct ee_rscan_cfg_channel *Config )
{  
  uint32_t ClockFrequency_u32;
  uint16_t BRPSetting_u16;
  uint8_t TSEG1Setting_u08;
  uint8_t TSEG2Setting_u08;
  uint8_t SJWSetting_u08;
  uint8_t TXCounter_u08;
  uint8_t Status_bit;
    
  if( UnitNumber_u08 >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
  if( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) 
    return( EE_RSCAN_ERROR );
  if( ee_rscan_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].stsl.mds != EE_RSCAN_OPMODE_RESET )
    return( EE_RSCAN_ERROR );

  /* first, clear any sleep mode *
  ee_rscan_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ctrl.cslpr = Config->ctrl.cslpr;

  if( ee_rscan_common_p[ UnitNumber_u08 ]->gcfgl.dcs == EE_RSCAN_CLOCK_SYS )
  {
    ClockFrequency_u32 = ( uint32_t )( OSCILLATOR_FREQUENCY * EE_RSCAN_FREQFACTOR );
    if( Config->bitrate > EE_RSCAN_MAXBAUDRATE ) return( EE_RSCAN_ERROR );
  }
  else
  {
    ClockFrequency_u32 = ( uint32_t )( OSCILLATOR_FREQUENCY * EE_RSCAN_FREQFACTORPLLBP );
    if( Config->bitrate > EE_RSCAN_MAXBAUDRATEPLLBP ) return( EE_RSCAN_ERROR );
  }
      
  Status_bit = EE_RSCAN_SetBittiming( UnitNumber_u08,
                                      ClockFrequency_u32,
                                      Config->bitrate,
                                      Config->tq_perbit,
                                      Config->syncjumpwidth,
                                      &BRPSetting_u16,
                                      &TSEG1Setting_u08,
                                      &TSEG2Setting_u08,
                                      &SJWSetting_u08,
                                      Config->samplingpointpos );
  if( Status_bit != EE_RSCAN_OK ) return( EE_RSCAN_ERROR );
    
  ee_rscan_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].cfgl.brp = 
    ( uint16_t )BRPSetting_u16;
  ee_rscan_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].cfgh.tseg1 = 
    ( uint16_t )TSEG1Setting_u08;
  ee_rscan_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].cfgh.tseg2 = 
    ( uint16_t )TSEG2Setting_u08;
  ee_rscan_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].cfgh.sjw = 
    ( uint16_t )SJWSetting_u08;

  ee_rscan_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ctrl.chmdc = Config->ctrl.chmdc;
  ee_rscan_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ctrl.rtbo  = Config->ctrl.rtbo;
  ee_rscan_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ctrl.iel   = Config->ctrl.iel;
  ee_rscan_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ctrh.ieh   = Config->ctrh.ieh;
  ee_rscan_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ctrh.bom   = Config->ctrh.bom;
  ee_rscan_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ctrh.errd  = Config->ctrh.errd;
  ee_rscan_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ctrh.ctme  = Config->ctrh.ctme;
  ee_rscan_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ctrh.ctms  = Config->ctrh.ctms;
  
  for( TXCounter_u08 = 0;
       TXCounter_u08 < EE_RSCAN_MAXTXBUFFERS;
       TXCounter_u08++ )
  {
    if( ( Config->tmiec >> TXCounter_u08 ) & 0x01 )
    {
      ee_rscan_common_p[ UnitNumber_u08 ]->
        tmiec[ EE_RSCAN_COMTXREG( ChannelNumber_u08 ) ] |= 
        ( 1 << ( TXCounter_u08 + 
               ( ChannelNumber_u08 * ( EE_RSCAN_MAXTXBUFFERS + EE_RSCAN_COMSPAREBITS ) ) -
               ( EE_RSCAN_COMREGSBITS * EE_RSCAN_COMTXREG( ChannelNumber_u08 ) ) ) );
    }
    else
    {
      ee_rscan_common_p[ UnitNumber_u08 ]->
        tmiec[ EE_RSCAN_COMTXREG( ChannelNumber_u08 ) ] &= 
        ~( 1 << ( TXCounter_u08 + 
                ( ChannelNumber_u08 * ( EE_RSCAN_MAXTXBUFFERS + EE_RSCAN_COMSPAREBITS ) ) -
                ( EE_RSCAN_COMREGSBITS * EE_RSCAN_COMTXREG( ChannelNumber_u08 ) ) ) );
    }
  }

	/* Set Channel to HALT mode, in order to configure lists *

	ee_rscan_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ctrl.chmdc =
		EE_RSCAN_OPMODE_HALT;
	while( ee_rscan_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].stsl.mds
			   != EE_RSCAN_OPMODE_HALT );
	
  ee_rscan_common_p[ UnitNumber_u08 ]->thlcc[ ChannelNumber_u08 ].thle = Config->thlcc.thle;
  ee_rscan_common_p[ UnitNumber_u08 ]->thlcc[ ChannelNumber_u08 ].ie   = Config->thlcc.ie;
  ee_rscan_common_p[ UnitNumber_u08 ]->thlcc[ ChannelNumber_u08 ].im   = Config->thlcc.im;
  ee_rscan_common_p[ UnitNumber_u08 ]->thlcc[ ChannelNumber_u08 ].dte  = Config->thlcc.dte;
  
	return( EE_RSCAN_OK );
}


//=============================================================================
// FunctionName: EE_RSCAN_Start
// IN  :         UnitNumber, Channel Number, Operation Mode
// OUT :         Success Status
// Description : Activates CAN Unit from any stop/sleep mode
// 
//=============================================================================
uint8_t EE_RSCAN_Start( uint8_t UnitNumber_u08,
                    uint8_t ChannelNumber_u08,
                    uint8_t OperationMode_u08,
                    uint8_t ClearErrorCounter_u08,
                    uint16_t TimeStampSetting_u16 )
{
  uint32_t AccessTimeout_u32 = EE_RSCAN_SHUTDOWNTIMEOUT; 
  uint8_t ChannelIndex_u08;

  if( UnitNumber_u08 >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
    
  while( ee_rscan_common_p[ UnitNumber_u08 ]->gsts.rsts );
    
  if( ee_rscan_common_p[ UnitNumber_u08 ]->gsts.slps )  /* activate the unit *
  {
    ee_rscan_common_p[ UnitNumber_u08 ]->gctrl.gslpr = EE_RSCAN_SLEEP_DISABLE;
  }

  /* go globally to OPERATION *

  if( ee_rscan_common_p[ UnitNumber_u08 ]->gsts.mds != EE_RSCAN_RSTATUS_OPERATION )
  {                                               
  	ee_rscan_common_p[ UnitNumber_u08 ]->gctrl.gmdc = EE_RSCAN_OPMODE_OPER;
    while( ( ee_rscan_common_p[ UnitNumber_u08 ]->gsts.mds != EE_RSCAN_RSTATUS_OPERATION )
             && ( --AccessTimeout_u32 > 0 ) );
    if( AccessTimeout_u32 == 0L ) return( EE_RSCAN_ERROR );
  }
   
  if( TimeStampSetting_u16 )
  {
  	ee_rscan_common_p[ UnitNumber_u08 ]->gctrh.tsrst = EE_RSCAN_SET;
  }
  
  if( ChannelNumber_u08 == EE_RSCAN_GLOBAL )
  {
    for( ChannelIndex_u08 = 0;
         ChannelIndex_u08 < ee_rscan_channels[ UnitNumber_u08 ];
         ChannelIndex_u08++ )
    {
      EE_RSCAN_Start( UnitNumber_u08,
                      ChannelIndex_u08,
                      OperationMode_u08,
                      ClearErrorCounter_u08,
                      TimeStampSetting_u16 );
    }
  }
  else
  {  
    if( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) 
      return( EE_RSCAN_ERROR );
      
    /* channels: cancel any sleep states *
    
    ee_rscan_common_p[ UnitNumber_u08 ]->ch
                     [ ChannelNumber_u08 ].ctrl.cslpr = EE_RSCAN_CLEAR;
    AccessTimeout_u32 = EE_RSCAN_SHUTDOWNTIMEOUT;
    while( ( ee_rscan_common_p[ UnitNumber_u08 ]->ch
                              [ ChannelNumber_u08 ].stsl.slps != EE_RSCAN_CLEAR )
             && ( --AccessTimeout_u32 > 0 ) );
    if( AccessTimeout_u32 == 0L ) return( EE_RSCAN_ERROR );
      
    if( ClearErrorCounter_u08 )
    {
      EE_RSCAN_Start( UnitNumber_u08,
                      ChannelNumber_u08,
                      EE_RSCAN_OPMODE_RESET,
                      0,
                      0 );
    }
    
    switch( OperationMode_u08 )
    {
      case EE_RSCAN_OPMODE_RESET:
        ee_rscan_common_p[ UnitNumber_u08 ]->ch
                         [ ChannelNumber_u08 ].ctrl.chmdc = EE_RSCAN_OPMODE_RESET;
        break;
        
      case EE_RSCAN_OPMODE_HALT:
        ee_rscan_common_p[ UnitNumber_u08 ]->ch
                         [ ChannelNumber_u08 ].ctrl.chmdc = EE_RSCAN_OPMODE_HALT;
        ee_rscan_common_p[ UnitNumber_u08 ]->ch
                         [ ChannelNumber_u08 ].ctrh.ctme = EE_RSCAN_CLEAR;
        break;
  
      case EE_RSCAN_OPMODE_OPER:
        ee_rscan_common_p[ UnitNumber_u08 ]->ch
                         [ ChannelNumber_u08 ].ctrl.chmdc = EE_RSCAN_OPMODE_OPER;
        break;
  
      case EE_RSCAN_OPMODE_RECONLY:
        ee_rscan_common_p[ UnitNumber_u08 ]->ch
                         [ ChannelNumber_u08 ].ctrh.ctms = EE_RSCAN_TEST_RXONLY;
        ee_rscan_common_p[ UnitNumber_u08 ]->ch
                         [ ChannelNumber_u08 ].ctrh.ctme = EE_RSCAN_SET;
        ee_rscan_common_p[ UnitNumber_u08 ]->ch
                         [ ChannelNumber_u08 ].ctrl.chmdc = EE_RSCAN_OPMODE_OPER;
        OperationMode_u08 = EE_RSCAN_OPMODE_OPER;
        break;
  
      case EE_RSCAN_OPMODE_STEST:
        ee_rscan_common_p[ UnitNumber_u08 ]->ch
                         [ ChannelNumber_u08 ].ctrh.ctms = EE_RSCAN_TEST_INTLOOP;
        ee_rscan_common_p[ UnitNumber_u08 ]->ch
                         [ ChannelNumber_u08 ].ctrh.ctme = EE_RSCAN_SET;
        ee_rscan_common_p[ UnitNumber_u08 ]->ch
                         [ ChannelNumber_u08 ].ctrl.chmdc = EE_RSCAN_OPMODE_OPER;
        OperationMode_u08 = EE_RSCAN_OPMODE_OPER;
        break;
        
      default: return( EE_RSCAN_ERROR );
  
    } // switch( OperationMode_u08 )
  
    AccessTimeout_u32 = EE_RSCAN_SHUTDOWNTIMEOUT;
    while( ( ee_rscan_common_p[ UnitNumber_u08 ]->ch
                              [ ChannelNumber_u08 ].stsl.mds != ( uint32_t )OperationMode_u08 )
           && ( --AccessTimeout_u32 > 0 ) );
    if( AccessTimeout_u32 == 0L ) return( EE_RSCAN_ERROR );
      
    if( OperationMode_u08 == EE_RSCAN_OPMODE_OPER )    /* verify communication ready state *
    {
      AccessTimeout_u32 = EE_RSCAN_SHUTDOWNTIMEOUT;
      while( ( ee_rscan_common_p[ UnitNumber_u08 ]->ch
                                [ ChannelNumber_u08 ].stsl.coms != EE_RSCAN_SET )
             && ( --AccessTimeout_u32 > 0 ) );
      if( AccessTimeout_u32 == 0L ) return( EE_RSCAN_ERROR );      
    }
      
  }  
  return( EE_RSCAN_OK );    
}


//=============================================================================
// FunctionName: EE_RSCAN_Stop
// IN  :         UnitNumber, Channel Number, Stop Mode
// OUT :         Success Status
// Description : Sets CAN Channel into any init/stop/sleep mode
// 
//=============================================================================
uint8_t EE_RSCAN_Stop( uint8_t UnitNumber_u08,
                   uint8_t ChannelNumber_u08,
                   uint8_t StopMode_u08 )
{
  uint32_t AccessTimeout_u32 = EE_RSCAN_SHUTDOWNTIMEOUT; 

  if( UnitNumber_u08 >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
  if( ( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) &&
      ( ChannelNumber_u08 != EE_RSCAN_GLOBAL ) ) return( EE_RSCAN_ERROR );

  if( ChannelNumber_u08 == EE_RSCAN_GLOBAL )
    {
      switch( StopMode_u08 )
        {
        case EE_RSCAN_OPMODE_SLEEP:
          if( ee_rscan_common_p[ UnitNumber_u08 ]->gsts.mds != EE_RSCAN_OPMODE_RESET )
            return( EE_RSCAN_ERROR );
          ee_rscan_common_p[ UnitNumber_u08 ]->gctrl.gslpr = EE_RSCAN_SET;
          while( ( ee_rscan_common_p[ UnitNumber_u08 ]->gsts.slps != EE_RSCAN_SET )
                 && ( --AccessTimeout_u32 > 0 ) );
          ee_rscan_common_p[ UnitNumber_u08 ]->gtstcfg.icbce = EE_RSCAN_COMTEST_OFF;  
          ee_rscan_common_p[ UnitNumber_u08 ]->gtstctr = EE_RSCAN_COMTEST_OFF;
          while( ee_rscan_common_p[ UnitNumber_u08 ]->gtstctr != EE_RSCAN_COMTEST_OFF );
          break;
          
        default:
          ee_rscan_common_p[ UnitNumber_u08 ]->gctrl.gmdc = ( uint32_t )StopMode_u08;
          while( ( ee_rscan_common_p[ UnitNumber_u08 ]->gsts.mds != ( uint32_t )StopMode_u08 )
                 && ( --AccessTimeout_u32 > 0 ) );
          break;
        }
    }
  else
    {
      switch( StopMode_u08 )
        {
        case EE_RSCAN_OPMODE_SLEEP:
          if( ee_rscan_common_p[ UnitNumber_u08 ]->ch
                               [ ChannelNumber_u08 ].stsl.mds != EE_RSCAN_OPMODE_RESET )
            return( EE_RSCAN_ERROR );
          ee_rscan_common_p[ UnitNumber_u08 ]->ch
                           [ ChannelNumber_u08 ].ctrl.cslpr = EE_RSCAN_SET;
          while( ( ee_rscan_common_p[ UnitNumber_u08 ]->ch
                                    [ ChannelNumber_u08 ].stsl.slps != EE_RSCAN_SET )
                 && ( --AccessTimeout_u32 > 0 ) );
          break;

        default:
          ee_rscan_common_p[ UnitNumber_u08 ]->ch
                           [ ChannelNumber_u08 ].ctrl.chmdc = ( uint32_t )StopMode_u08;
          ee_rscan_common_p[ UnitNumber_u08 ]->ch
                           [ ChannelNumber_u08 ].ctrh.ctme = EE_RSCAN_CLEAR;
          while( ( ee_rscan_common_p[ UnitNumber_u08 ]->ch
                                    [ ChannelNumber_u08 ].stsl.mds != ( uint32_t )StopMode_u08 )
                 && ( --AccessTimeout_u32 > 0 ) );
          break;
        }
    }

  if( AccessTimeout_u32 == 0L ) return( EE_RSCAN_ERROR );
  else return( EE_RSCAN_OK );
}    
  


//=============================================================================
// FunctionName: EE_RSCAN_SendMessage
// IN  :         UnitNumber, Channel Number, Message
// OUT :         Success Status
// Description : Performs Message Sending
//=============================================================================
uint8_t EE_RSCAN_SendMessage( uint8_t  UnitNumber_u08,
                          uint8_t  ChannelNumber_u08,
                          puint8_t Status_pu08,
                          struct ee_rscan_message *Message )
{
  uint8_t SendBox_u08;
  uint8_t FirstBox_u08;
  uint8_t LastBox_u08;
  uint8_t SendBoxOccupied_u08 = EE_RSCAN_CLEAR;
  uint8_t FIFONumber_u08;
  
  *Status_pu08 = EE_RSCAN_FAULT_PARAMETER;
  
  if( UnitNumber_u08 >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
  if( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) 
    return( EE_RSCAN_ERROR );
  if( ee_rscan_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].stsl.mds != EE_RSCAN_OPMODE_OPER )
    return( EE_RSCAN_ERROR );
    
  *Status_pu08 = EE_RSCAN_FAULT_NONE;

  switch( Message->path )
  {
    case EE_RSCAN_PATH_MSGBOX:      /* search a free SendBox, if required *
    {
      if( Message->pathdetail != EE_RSCAN_PATHDETAIL_ANY )
      {
        FirstBox_u08 = Message->pathdetail;
        LastBox_u08  = FirstBox_u08;
        if( FirstBox_u08 >= EE_RSCAN_MAXTXBUFFERS )
        {
          *Status_pu08 = EE_RSCAN_FAULT_PARAMETER;
          return( EE_RSCAN_ERROR );
        }
      }
      else
      {
        FirstBox_u08 = 0;
        LastBox_u08  = ( EE_RSCAN_MAXTXBUFFERS - 1 );
      }
      
      for( SendBox_u08 =  FirstBox_u08;
           SendBox_u08 <= LastBox_u08;
           SendBox_u08++ )
      {
        if( ( ( ( ee_rscan_common_p[ UnitNumber_u08 ]->tmsts
                  [ ( EE_RSCAN_MAXTXBUFFERS * ChannelNumber_u08 + 
                      SendBox_u08 ) ] ) )
                & EE_RSCAN_TMSTS_STSMSK ) == 
                EE_RSCAN_TMSTS_CLEAR )    /* check pending TRQ *
        {
          for( FIFONumber_u08 = 0;
               FIFONumber_u08 < EE_RSCAN_MAXCOMFIFOS;
               FIFONumber_u08++ )   /* check any COM FIFO assignment *
          
          {
            if( ( ( uint8_t )( ee_rscan_common_p[ UnitNumber_u08 ]->cfcc
                                            [ EE_RSCAN_MAXCOMFIFOS * 
                                            ChannelNumber_u08 ].h.cftml ) 
                                            == SendBox_u08 ) &&
                         ( ee_rscan_common_p[ UnitNumber_u08 ]->cfcc
                                            [ EE_RSCAN_MAXCOMFIFOS * 
                                            ChannelNumber_u08 ].l.cfe ) )
            {
              SendBoxOccupied_u08 = EE_RSCAN_SET;
              break;
            }
          }
        }
        else
        {
          SendBoxOccupied_u08 = EE_RSCAN_SET;
        }

        if( SendBoxOccupied_u08 == EE_RSCAN_CLEAR )
        {
          /* Initiate Sending with this box and exit the box searching *
          
          EE_RSCAN_SetIDData( &ee_rscan_txmsg_p[ UnitNumber_u08 ]
                                               [ ChannelNumber_u08 ]->
                                            buf[ SendBox_u08 ],
                              Message );
                         
          ee_rscan_common_p[ UnitNumber_u08 ]->tmsts
                           [ ( EE_RSCAN_MAXTXBUFFERS * ChannelNumber_u08 + 
                             SendBox_u08 ) ] &= ( uint8_t )
                             ( ~( EE_RSCAN_TMSTS_RFMSK ) );

          ee_rscan_common_p[ UnitNumber_u08 ]->tmc
                           [ ( EE_RSCAN_MAXTXBUFFERS * ChannelNumber_u08 + 
                             SendBox_u08 ) ] |= ( uint8_t )
                             ( EE_RSCAN_TMC_SET_TR );
          break;
        }
        else
        {
          SendBoxOccupied_u08 = EE_RSCAN_CLEAR;   /* test next SendBox *
        }
      }
      
      if( SendBox_u08 >= EE_RSCAN_MAXTXBUFFERS )
      {
        *Status_pu08 = EE_RSCAN_FAULT_BUSY;
        return( EE_RSCAN_OK );
      }
      break;
    }
    
    case EE_RSCAN_PATH_COMFIFO:                    /* use dedicated FIFO *
    {
      if( Message->pathdetail != EE_RSCAN_PATHDETAIL_ANY )
      {
        SendBox_u08 = Message->pathdetail;
        if( SendBox_u08 >= EE_RSCAN_MAXCOMFIFOS )
        {
          *Status_pu08 = EE_RSCAN_FAULT_PARAMETER;
          return( EE_RSCAN_ERROR );
        }
        else
        {
          SendBox_u08 = ( EE_RSCAN_MAXCOMFIFOS * ChannelNumber_u08 ) + 
                        Message->pathdetail;
          if( ee_rscan_common_p[ UnitNumber_u08 ]->cfsts[ SendBox_u08 ].cffll )
          {
            *Status_pu08 = EE_RSCAN_FAULT_BUSY;
            return( EE_RSCAN_OK );                    
          }
        }
      }
      else                                  /* search enabled, non-full FIFO *
      {
        SendBox_u08 = EE_RSCAN_FIFO_NEXTELEMENT;
        
        for( FIFONumber_u08 = ( EE_RSCAN_MAXCOMFIFOS * ChannelNumber_u08 );
             FIFONumber_u08 < ( EE_RSCAN_MAXCOMFIFOS * ( ChannelNumber_u08 + 1 ) );
             FIFONumber_u08++ )
        {
          if( ee_rscan_common_p[ UnitNumber_u08 ]->cfcc[ FIFONumber_u08 ].l.cfe )
          {
            if( !ee_rscan_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cffll )
            {
              SendBox_u08 = FIFONumber_u08;
              if( ee_rscan_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cfemp )
              {
                break;             /* an empty FIFO can be used immediately *
              }
            }
          }
        }
      }
      
      if( SendBox_u08 != EE_RSCAN_FIFO_NEXTELEMENT ) /* feed message into FIFO *
      {
        SendBox_u08 %= EE_RSCAN_MAXCOMFIFOS;
        
        EE_RSCAN_SetIDDataCFIFO( &ee_rscan_comfifo_p[ UnitNumber_u08 ]
                                                    [ ChannelNumber_u08 ]->
                                                 buf[ SendBox_u08 ],
                                 Message );
                       
        ee_rscan_common_p[ UnitNumber_u08 ]->cfpctr
                         [ EE_RSCAN_MAXCOMFIFOS * ChannelNumber_u08 + 
                           SendBox_u08 ].fpc = EE_RSCAN_FIFO_NEXTELEMENT;      
      }
      else                  /* free and enabled FIFO was not found *
      {
        *Status_pu08 = EE_RSCAN_FAULT_BUSY;
        return( EE_RSCAN_OK );        
      }
      break;
    }
      
    default:
      *Status_pu08 = EE_RSCAN_FAULT_PARAMETER;
      return( EE_RSCAN_ERROR );
  }
     
  return( EE_RSCAN_OK );
}

//=============================================================================
// FunctionName: EE_RSCAN_ReceiveMessage
// IN  :         UnitNumber, (preferred) Reception path within message
// OUT :         Success Status
//               Message with content and information
// Description : Performs Message Reception
// 
//=============================================================================
uint8_t EE_RSCAN_ReceiveMessage( uint8_t                      UnitNumber_u08,
                             puint8_t                     Status_pu08,
                             struct ee_rscan_message *Message )
{
  uint8_t ReceiveBox_u08;
  uint8_t SearchBegin_u08;
  uint8_t SearchEnd_u08;
  
  *Status_pu08 = EE_RSCAN_FAULT_PARAMETER;
  
  if( UnitNumber_u08 >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
  if( ee_rscan_common_p[ UnitNumber_u08 ]->gsts.mds != EE_RSCAN_OPMODE_OPER )
    return( EE_RSCAN_ERROR );
    
  *Status_pu08 = EE_RSCAN_FAULT_NODATA;
  
  if( ( Message->path == EE_RSCAN_PATH_MSGBOX ) ||
      ( Message->path == EE_RSCAN_PATH_ANY ) ) /* check within message boxes *
  {
    if( Message->pathdetail == EE_RSCAN_GLOBAL )    /* read first filled box *
    {
      SearchBegin_u08 = 0;
      SearchEnd_u08   = EE_RSCAN_MAXRXBUFFERS - 1;
    }
    else                             /* read dedicated box (typical polling) *
    {
      SearchBegin_u08 = Message->pathdetail;
      SearchEnd_u08   = Message->pathdetail;
      
      if( SearchBegin_u08 >= EE_RSCAN_MAXRXBUFFERS )
      {
        *Status_pu08 = EE_RSCAN_FAULT_PARAMETER;
        return( EE_RSCAN_ERROR );
      }
    }
    
    for( ReceiveBox_u08 =  SearchBegin_u08;
         ReceiveBox_u08 <= SearchEnd_u08;
         ReceiveBox_u08++ )
    {
      while( ee_rscan_common_p[ UnitNumber_u08 ]->rmnd
                              [ EE_RSCAN_COMRXREG( ReceiveBox_u08 ) ] >> 
                                EE_RSCAN_COMRXBIT( ReceiveBox_u08 ) & 
                                EE_RSCAN_SET )
      {
        *Status_pu08 = EE_RSCAN_FAULT_NONE;
                                                      /* Clear new data flag *
        ee_rscan_common_p[ UnitNumber_u08 ]->rmnd
                         [ EE_RSCAN_COMRXREG( ReceiveBox_u08 ) ] = ( uint32_t ) 
                         ( ~( 1 << EE_RSCAN_COMRXBIT( ReceiveBox_u08 ) ) );
        
        EE_RSCAN_GetMessage( &ee_rscan_rxmsg_p[ UnitNumber_u08 ]->
                                           buf[ ReceiveBox_u08 ],
                             Message );
      }
      if( *Status_pu08 != EE_RSCAN_FAULT_NODATA ) break;
    }
  }

  if( ( Message->path == EE_RSCAN_PATH_RXFIFO ) ||
      ( ( Message->path == EE_RSCAN_PATH_ANY ) &&
        ( *Status_pu08 == EE_RSCAN_FAULT_NODATA ) ) ) /* check within RX FIFO *
  {
    if( Message->pathdetail == EE_RSCAN_GLOBAL )    /* read first filled FIFO *
    {
      SearchBegin_u08 = 0;
      SearchEnd_u08   = EE_RSCAN_MAXRXFIFOS - 1;
    }
    else                                               /* read dedicated FIFO *
    {
      SearchBegin_u08 = Message->pathdetail;
      SearchEnd_u08   = Message->pathdetail;
 
      if( SearchBegin_u08 >= EE_RSCAN_MAXRXFIFOS )
      {
        *Status_pu08 = EE_RSCAN_FAULT_PARAMETER;
        return( EE_RSCAN_ERROR );
      }
    }
    
    for( ReceiveBox_u08 =  SearchBegin_u08;
         ReceiveBox_u08 <= SearchEnd_u08;
         ReceiveBox_u08++ )
    {
      if( !ee_rscan_common_p[ UnitNumber_u08 ]->rfsts[ ReceiveBox_u08 ].rfemp )
      {
        *Status_pu08 = EE_RSCAN_FAULT_NONE;
        
        EE_RSCAN_GetMessage( &ee_rscan_rxfifo_p[ UnitNumber_u08 ]->
                                            buf[ ReceiveBox_u08 ],
                             Message );
        
        ee_rscan_common_p[ UnitNumber_u08 ]->rfpctr[ ReceiveBox_u08 ].fpc = 
          EE_RSCAN_FIFO_NEXTELEMENT;
        
        break;
      }
    }    
  }

  if( ( Message->path == EE_RSCAN_PATH_COMFIFO ) ||
      ( ( Message->path == EE_RSCAN_PATH_ANY ) &&
        ( *Status_pu08 == EE_RSCAN_FAULT_NODATA ) ) ) /* check within COMFIFO *
  {
    if( Message->pathdetail == EE_RSCAN_GLOBAL )    /* read first filled FIFO *
    {
      SearchBegin_u08 = 0;
      SearchEnd_u08   = EE_RSCAN_MAXCOMFIFOS * ee_rscan_channels[ UnitNumber_u08 ] - 1;
    }
    else                                               /* read dedicated FIFO *
    {
      SearchBegin_u08 = Message->pathdetail;
      SearchEnd_u08   = Message->pathdetail;
 
      if( SearchBegin_u08 >= ( EE_RSCAN_MAXCOMFIFOS * ee_rscan_channels[ UnitNumber_u08 ] ) )
      {
        *Status_pu08 = EE_RSCAN_FAULT_PARAMETER;
        return( EE_RSCAN_ERROR );
      }
    }
    
    for( ReceiveBox_u08 =  SearchBegin_u08;
         ReceiveBox_u08 <= SearchEnd_u08;
         ReceiveBox_u08++ )
    {
      if( !ee_rscan_common_p[ UnitNumber_u08 ]->cfsts[ ReceiveBox_u08 ].cfemp )
      {
        *Status_pu08 = EE_RSCAN_FAULT_NONE;
        
        EE_RSCAN_GetMessageCF( &ee_rscan_comfifo_p[ UnitNumber_u08 ]
		                                              [ ReceiveBox_u08 /
					                                     EE_RSCAN_MAXCOMFIFOS ]->
                                               buf[ ReceiveBox_u08 ],
                               Message );
        
        ee_rscan_common_p[ UnitNumber_u08 ]->cfpctr[ ReceiveBox_u08 ].fpc = 
          EE_RSCAN_FIFO_NEXTELEMENT;
        
        break;
      }
    }    
  }

  return( EE_RSCAN_OK );
}


//=============================================================================
// FunctionName: EE_RSCAN_PortDisable
// IN  : UnitNumber: Selected Macro
//       ChannelNumber: Selected Channel
// OUT : Error Flag
// Description : 
// Release I/O ports to normal port function
//=============================================================================
uint8_t EE_RSCAN_PortDisable( uint8_t UnitNumber_u08,
                          uint8_t ChannelNumber_u08 )
{
  uint8_t ChannelCount_u08;

  if( UnitNumber_u08 >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
  if( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) 
    return( EE_RSCAN_ERROR );

  switch( UnitNumber_u08 ) 
  {
    case EE_RSCAN_0:
    {
      switch( ChannelNumber_u08 )
      {
          
#ifdef EE_RSCAN_PORT_M0RX0
        case EE_RSCAN_CHANNEL0:
          PORT_Disable( EE_RSCAN_PORT_M0RX0, EE_RSCAN_PORT_BIT_M0RX0 );
          PORT_Disable( EE_RSCAN_PORT_M0TX0, EE_RSCAN_PORT_BIT_M0TX0 );
          break;
#endif

#ifdef EE_RSCAN_PORT_M0RX1
        case EE_RSCAN_CHANNEL1:
          PORT_Disable( EE_RSCAN_PORT_M0RX1, EE_RSCAN_PORT_BIT_M0RX1 );
          PORT_Disable( EE_RSCAN_PORT_M0TX1, EE_RSCAN_PORT_BIT_M0TX1 );
          break;
#endif

        case EE_RSCAN_GLOBAL:
          for( ChannelCount_u08 = 0; 
               ChannelCount_u08 < ee_rscan_channels[ UnitNumber_u08 ];
               ChannelCount_u08++ )
          {
            EE_RSCAN_PortDisable( UnitNumber_u08, ChannelCount_u08 );
          }
          break;

        default:
          return( EE_RSCAN_ERROR );
      } // switch ChannelNumber_u08
      break;
    }
    
    case EE_RSCAN_1:
    {
      switch( ChannelNumber_u08 )
      {
          
#ifdef EE_RSCAN_PORT_M1RX0
        case EE_RSCAN_CHANNEL0:
          PORT_Disable( EE_RSCAN_PORT_M1RX0, EE_RSCAN_PORT_BIT_M1RX0 );
          PORT_Disable( EE_RSCAN_PORT_M1TX0, EE_RSCAN_PORT_BIT_M1TX0 );
          break;
#endif

#ifdef EE_RSCAN_PORT_M1RX1
        case EE_RSCAN_CHANNEL1:
          PORT_Disable( EE_RSCAN_PORT_M1RX1, EE_RSCAN_PORT_BIT_M1RX1 );
          PORT_Disable( EE_RSCAN_PORT_M1TX1, EE_RSCAN_PORT_BIT_M1TX1 );
          break;
#endif

        case EE_RSCAN_GLOBAL:
          for( ChannelCount_u08 = 0; 
               ChannelCount_u08 < ee_rscan_channels[ UnitNumber_u08 ];
               ChannelCount_u08++ )
          {
            EE_RSCAN_PortDisable( UnitNumber_u08, ChannelCount_u08 );
          }
          break;

        default:
          return( EE_RSCAN_ERROR );
      } // switch ChannelNumber_u08
      break;
    }

    default: 
      return( EE_RSCAN_ERROR );

  } // switch( UnitNumber )
  
  return( EE_RSCAN_OK );*/
}