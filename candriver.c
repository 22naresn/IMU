/***********************************************************************************************************************
* File Name    : candriver.c
* Version      : 1.0
* Device(s)    : R5F10PPJ
* Description  : Ground up CAN Driver for the Renesas R5F10PPJ microcontroller.
***********************************************************************************************************************/

// GLOBAL VARIABLES HERE IF NEEDED???
// TF GLOBAL VARIABLES DOES THIS NEED??

#include <stdbool.h>
#include <stddef.h>
#include "r_cg_macrodriver.h"
#include "iodefine.h"
#include "r_cg_userdefine.h"
#include "map_rscan.h"
#include "rscan.h"
#include "rscan_p.h"
#include "rscan_a.h"
#include "addl_types.h"


/* *******************************************************************************************************************
// RSCAN_PortEnable(unit, channel)
// - inputs: unit number, channel number
// - returns: EE_RSCAN_OK or EE_RSCAN_ERROR
// MUX's the GPIOs for CAN (sets RX as input, TX as output).
***********************************************************************************************************************/

uint8_t EE_RSCAN_PortEnable( uint8_t UnitNumber_uint8_t,
                         uint8_t ChannelNumber_uint8_t )
{
  uint8_t ChannelCount_uint8_t;

  if( UnitNumber_uint8_t >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
  if( ChannelNumber_uint8_t >= ee_rscan_channels[ UnitNumber_uint8_t ] ) 
    return( EE_RSCAN_ERROR );

  switch( UnitNumber_uint8_t ) 
  {
    case EE_RSCAN_0:
    {
      switch( ChannelNumber_uint8_t )
      {

#ifdef EE_RSCAN_PORT_M0RX0
        case EE_RSCAN_CHANNEL0:
          PORT_Enable( EE_RSCAN_PORT_M0RX0, EE_RSCAN_PORT_uint8_t_M0RX0,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       EE_RSCAN_PORT_FUNC_M0RX0 );
          PORT_Enable( EE_RSCAN_PORT_M0TX0, EE_RSCAN_PORT_uint8_t_M0TX0,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       EE_RSCAN_PORT_FUNC_M0TX0 );
          break;
#endif

#ifdef EE_RSCAN_PORT_M0RX1
        case EE_RSCAN_CHANNEL1:
          PORT_Enable( EE_RSCAN_PORT_M0RX1, EE_RSCAN_PORT_uint8_t_M0RX1,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       EE_RSCAN_PORT_FUNC_M0RX1 );
          PORT_Enable( EE_RSCAN_PORT_M0TX1, EE_RSCAN_PORT_uint8_t_M0TX1,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       EE_RSCAN_PORT_FUNC_M0TX1 );
          break;
#endif

        case EE_RSCAN_GLOBAL:
          for( ChannelCount_uint8_t = 0; 
               ChannelCount_uint8_t < ee_rscan_channels[ UnitNumber_uint8_t ];
               ChannelCount_uint8_t++ )
            {
              EE_RSCAN_PortEnable( UnitNumber_uint8_t, ChannelCount_uint8_t );
            }
          break;
            
        default:
          return( EE_RSCAN_ERROR );
      }
    } // switch ChannelNumber_uint8_t
    break;
      
    case EE_RSCAN_1:
    {
      switch( ChannelNumber_uint8_t )
      {

#ifdef EE_RSCAN_PORT_M1RX0
        case EE_RSCAN_CHANNEL0:
          PORT_Enable( EE_RSCAN_PORT_M1RX0, EE_RSCAN_PORT_uint8_t_M1RX0,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       EE_RSCAN_PORT_FUNC_M1RX0 );
          PORT_Enable( EE_RSCAN_PORT_M1TX0, EE_RSCAN_PORT_uint8_t_M1TX0,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       EE_RSCAN_PORT_FUNC_M1TX0 );
          break;
#endif

#ifdef EE_RSCAN_PORT_M1RX1
        case EE_RSCAN_CHANNEL1:
          PORT_Enable( EE_RSCAN_PORT_M1RX1, EE_RSCAN_PORT_uint8_t_M1RX1,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       EE_RSCAN_PORT_FUNC_M1RX1 );
          PORT_Enable( EE_RSCAN_PORT_M1TX1, EE_RSCAN_PORT_uint8_t_M1TX1,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       EE_RSCAN_PORT_FUNC_M1TX1 );
          break;
#endif

        case EE_RSCAN_GLOBAL:
          for( ChannelCount_uint8_t = 0; 
               ChannelCount_uint8_t < ee_rscan_channels[ UnitNumber_uint8_t ];
               ChannelCount_uint8_t++ )
            {
              EE_RSCAN_PortEnable( UnitNumber_uint8_t, ChannelCount_uint8_t );
            }
          break;
            
        default:
          return( EE_RSCAN_ERROR );
      }
    } // switch ChannelNumber_uint8_t
    break;

    default: 
      return( EE_RSCAN_ERROR );

  } // switch( UnitNumber )

  return( EE_RSCAN_OK );
}
    

// *******************************************************************************************************************
// EE_RSCAN_SetGlobalConfiguration(unit, cfg)
// - inputs: which CAN unit, pointer to global config struct
// - returns: EE_RSCAN_OK / EE_RSCAN_ERROR
// Applies global settings. Must be called while the unit is in RESET.
// waits for reset/sleep flags internally — caller doesn't need to.
// *******************************************************************************************************************


uint8_t EE_RSCAN_SetGlobalConfiguration( uint8_t UnitNumber_uint8_t,
                                     const struct ee_rscan_cfg_global *Config )
{    
  if( UnitNumber_uint8_t >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );

  /* Must be in global reset to set the global configuration! */
  
  while( ee_rscan_common_p[ UnitNumber_uint8_t ]->gsts.rsts );

  if( ee_rscan_common_p[ UnitNumber_uint8_t ]->gsts.mds != EE_RSCAN_OPMODE_RESET )
    return( EE_RSCAN_ERROR );

  ee_rscan_common_p[ UnitNumber_uint8_t ]->gctrl.gslpr  = Config->gctrl.gslpr;
  while( ee_rscan_common_p[ UnitNumber_uint8_t ]->gsts.slps );

  ee_rscan_common_p[ UnitNumber_uint8_t ]->grwcr.rpage  = EE_RSCAN_SET;

  ee_rscan_common_p[ UnitNumber_uint8_t ]->gcfgl.tpri   = Config->gcfgl.tpri;
  ee_rscan_common_p[ UnitNumber_uint8_t ]->gcfgl.dce    = Config->gcfgl.dce;
  ee_rscan_common_p[ UnitNumber_uint8_t ]->gcfgl.dre    = Config->gcfgl.dre;
  ee_rscan_common_p[ UnitNumber_uint8_t ]->gcfgl.mme    = Config->gcfgl.mme;
  ee_rscan_common_p[ UnitNumber_uint8_t ]->gcfgl.dcs    = Config->gcfgl.dcs;
  ee_rscan_common_p[ UnitNumber_uint8_t ]->gcfgl.tsp    = Config->gcfgl.tsp;
  ee_rscan_common_p[ UnitNumber_uint8_t ]->gcfgl.tsss   = Config->gcfgl.tsss;
  ee_rscan_common_p[ UnitNumber_uint8_t ]->gcfgh.itrcp  = Config->gcfgh.itrcp;

  ee_rscan_common_p[ UnitNumber_uint8_t ]->gctrl.gmdc   = Config->gctrl.gmdc;
  ee_rscan_common_p[ UnitNumber_uint8_t ]->gctrl.ie     = Config->gctrl.ie;
  ee_rscan_common_p[ UnitNumber_uint8_t ]->gctrh.tsrst  = Config->gctrh.tsrst;

  ee_rscan_common_p[ UnitNumber_uint8_t ]->rmnb         = Config->rmnb;

  ee_rscan_common_p[ UnitNumber_uint8_t ]->gaflcfg.rnc0 = Config->rnc[ 0 ];
  ee_rscan_common_p[ UnitNumber_uint8_t ]->gaflcfg.rnc1 = Config->rnc[ 1 ];

  return( EE_RSCAN_OK );
}    


// *******************************************************************************************************************
// EE_RSCAN_Start(unit, channel, mode, clearErrs, ts)
// - starts a channel (or all channels if channel==GLOBAL) into mode.
// - clearErrs: non-zero resets error counters
// - ts: if non-zero, resets timestamp counter
// Brings the unit to OPERATION if needed, then sets channel mode.
// Returns EE_RSCAN_OK or EE_RSCAN_ERROR on timeout/invalid args.
// *******************************************************************************************************************

uint8_t EE_RSCAN_SetChannelConfiguration( uint8_t UnitNumber_uint8_t,
                                      uint8_t ChannelNumber_uint8_t,
                                      const struct ee_rscan_cfg_channel *Config )
{  
  int32_t ClockFrequency_int32_t;
  uint16_t BRPSetting_uint16_t;
  uint8_t TSEG1Setting_uint8_t;
  uint8_t TSEG2Setting_uint8_t;
  uint8_t SJWSetting_uint8_t;
  uint8_t TXCounter_uint8_t;
  uint8_t Status_uint8_t;
    
  if( UnitNumber_uint8_t >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
  if( ChannelNumber_uint8_t >= ee_rscan_channels[ UnitNumber_uint8_t ] ) 
    return( EE_RSCAN_ERROR );
  if( ee_rscan_common_p[ UnitNumber_uint8_t ]->ch[ ChannelNumber_uint8_t ].stsl.mds != EE_RSCAN_OPMODE_RESET )
    return( EE_RSCAN_ERROR );

  /* first, clear any sleep mode */
  ee_rscan_common_p[ UnitNumber_uint8_t ]->ch[ ChannelNumber_uint8_t ].ctrl.cslpr = Config->ctrl.cslpr;

  if( ee_rscan_common_p[ UnitNumber_uint8_t ]->gcfgl.dcs == EE_RSCAN_CLOCK_SYS )
  {
    ClockFrequency_int32_t = ( int32_t )( OSCILLATOR_FREQUENCY * EE_RSCAN_FREQFACTOR );
    if( Config->uint8_trate > EE_RSCAN_MAXBAUDRATE ) return( EE_RSCAN_ERROR );
  }
  else
  {
    ClockFrequency_int32_t = ( int32_t )( OSCILLATOR_FREQUENCY * EE_RSCAN_FREQFACTORPLLBP );
    if( Config->uint8_trate > EE_RSCAN_MAXBAUDRATEPLLBP ) return( EE_RSCAN_ERROR );
  }
      
  Status_uint8_t = EE_RSCAN_Setuint8_ttiming( UnitNumber_uint8_t,
                                      ClockFrequency_int32_t,
                                      Config->uint8_trate,
                                      Config->tq_peruint8_t,
                                      Config->syncjumpwidth,
                                      &BRPSetting_uint16_t,
                                      &TSEG1Setting_uint8_t,
                                      &TSEG2Setting_uint8_t,
                                      &SJWSetting_uint8_t,
                                      Config->samplingpointpos );
  if( Status_uint8_t != EE_RSCAN_OK ) return( EE_RSCAN_ERROR );
    
  ee_rscan_common_p[ UnitNumber_uint8_t ]->ch[ ChannelNumber_uint8_t ].cfgl.brp = 
    ( uint16_t )BRPSetting_uint16_t;
  ee_rscan_common_p[ UnitNumber_uint8_t ]->ch[ ChannelNumber_uint8_t ].cfgh.tseg1 = 
    ( uint16_t )TSEG1Setting_uint8_t;
  ee_rscan_common_p[ UnitNumber_uint8_t ]->ch[ ChannelNumber_uint8_t ].cfgh.tseg2 = 
    ( uint16_t )TSEG2Setting_uint8_t;
  ee_rscan_common_p[ UnitNumber_uint8_t ]->ch[ ChannelNumber_uint8_t ].cfgh.sjw = 
    ( uint16_t )SJWSetting_uint8_t;

  ee_rscan_common_p[ UnitNumber_uint8_t ]->ch[ ChannelNumber_uint8_t ].ctrl.chmdc = Config->ctrl.chmdc;
  ee_rscan_common_p[ UnitNumber_uint8_t ]->ch[ ChannelNumber_uint8_t ].ctrl.rtbo  = Config->ctrl.rtbo;
  ee_rscan_common_p[ UnitNumber_uint8_t ]->ch[ ChannelNumber_uint8_t ].ctrl.iel   = Config->ctrl.iel;
  ee_rscan_common_p[ UnitNumber_uint8_t ]->ch[ ChannelNumber_uint8_t ].ctrh.ieh   = Config->ctrh.ieh;
  ee_rscan_common_p[ UnitNumber_uint8_t ]->ch[ ChannelNumber_uint8_t ].ctrh.bom   = Config->ctrh.bom;
  ee_rscan_common_p[ UnitNumber_uint8_t ]->ch[ ChannelNumber_uint8_t ].ctrh.errd  = Config->ctrh.errd;
  ee_rscan_common_p[ UnitNumber_uint8_t ]->ch[ ChannelNumber_uint8_t ].ctrh.ctme  = Config->ctrh.ctme;
  ee_rscan_common_p[ UnitNumber_uint8_t ]->ch[ ChannelNumber_uint8_t ].ctrh.ctms  = Config->ctrh.ctms;
  
  for( TXCounter_uint8_t = 0;
       TXCounter_uint8_t < EE_RSCAN_MAXTXBUFFERS;
       TXCounter_uint8_t++ )
  {
    if( ( Config->tmiec >> TXCounter_uint8_t ) & 0x01 )
    {
      ee_rscan_common_p[ UnitNumber_uint8_t ]->
        tmiec[ EE_RSCAN_COMTXREG( ChannelNumber_uint8_t ) ] |= 
        ( 1 << ( TXCounter_uint8_t + 
               ( ChannelNumber_uint8_t * ( EE_RSCAN_MAXTXBUFFERS + EE_RSCAN_COMSPAREuint8_tS ) ) -
               ( EE_RSCAN_COMREGSuint8_tS * EE_RSCAN_COMTXREG( ChannelNumber_uint8_t ) ) ) );
    }
    else
    {
      ee_rscan_common_p[ UnitNumber_uint8_t ]->
        tmiec[ EE_RSCAN_COMTXREG( ChannelNumber_uint8_t ) ] &= 
        ~( 1 << ( TXCounter_uint8_t + 
                ( ChannelNumber_uint8_t * ( EE_RSCAN_MAXTXBUFFERS + EE_RSCAN_COMSPAREuint8_tS ) ) -
                ( EE_RSCAN_COMREGSuint8_tS * EE_RSCAN_COMTXREG( ChannelNumber_uint8_t ) ) ) );
    }
  }

	/* Set Channel to HALT mode, in order to configure lists */

	ee_rscan_common_p[ UnitNumber_uint8_t ]->ch[ ChannelNumber_uint8_t ].ctrl.chmdc =
		EE_RSCAN_OPMODE_HALT;
	while( ee_rscan_common_p[ UnitNumber_uint8_t ]->ch[ ChannelNumber_uint8_t ].stsl.mds
			   != EE_RSCAN_OPMODE_HALT );
	
  ee_rscan_common_p[ UnitNumber_uint8_t ]->thlcc[ ChannelNumber_uint8_t ].thle = Config->thlcc.thle;
  ee_rscan_common_p[ UnitNumber_uint8_t ]->thlcc[ ChannelNumber_uint8_t ].ie   = Config->thlcc.ie;
  ee_rscan_common_p[ UnitNumber_uint8_t ]->thlcc[ ChannelNumber_uint8_t ].im   = Config->thlcc.im;
  ee_rscan_common_p[ UnitNumber_uint8_t ]->thlcc[ ChannelNumber_uint8_t ].dte  = Config->thlcc.dte;
  
	return( EE_RSCAN_OK );
}


// *******************************************************************************************************************
// EE_RSCAN_Start(unit, channel, mode, clearErrs, ts)
// - starts a channel (or all channels if channel==GLOBAL) into mode.
// - clearErrs: non-zero resets error counters
// - ts: if non-zero, resets timestamp counter
// Brings the unit to OPERATION if needed, then sets channel mode.
// Returns EE_RSCAN_OK or EE_RSCAN_ERROR on timeout/invalid args
// *******************************************************************************************************************


uint8_t EE_RSCAN_Start( uint8_t UnitNumber_uint8_t,
                    uint8_t ChannelNumber_uint8_t,
                    uint8_t OperationMode_uint8_t,
                    uint8_t ClearErrorCounter_uint8_t,
                    uint16_t TimeStampSetting_uint16_t )
{
  int32_t AccessTimeout_int32_t = EE_RSCAN_SHUTDOWNTIMEOUT; 
  uint8_t ChannelIndex_uint8_t;

  if( UnitNumber_uint8_t >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
    
  while( ee_rscan_common_p[ UnitNumber_uint8_t ]->gsts.rsts );
    
  if( ee_rscan_common_p[ UnitNumber_uint8_t ]->gsts.slps )  /* activate the unit */
  {
    ee_rscan_common_p[ UnitNumber_uint8_t ]->gctrl.gslpr = EE_RSCAN_SLEEP_DISABLE;
  }

  /* go globally to OPERATION */

  if( ee_rscan_common_p[ UnitNumber_uint8_t ]->gsts.mds != EE_RSCAN_RSTATUS_OPERATION )
  {                                               
  	ee_rscan_common_p[ UnitNumber_uint8_t ]->gctrl.gmdc = EE_RSCAN_OPMODE_OPER;
    while( ( ee_rscan_common_p[ UnitNumber_uint8_t ]->gsts.mds != EE_RSCAN_RSTATUS_OPERATION )
             && ( --AccessTimeout_int32_t > 0 ) );
    if( AccessTimeout_int32_t == 0L ) return( EE_RSCAN_ERROR );
  }
   
  if( TimeStampSetting_uint16_t )
  {
  	ee_rscan_common_p[ UnitNumber_uint8_t ]->gctrh.tsrst = EE_RSCAN_SET;
  }
  
  if( ChannelNumber_uint8_t == EE_RSCAN_GLOBAL )
  {
    for( ChannelIndex_uint8_t = 0;
         ChannelIndex_uint8_t < ee_rscan_channels[ UnitNumber_uint8_t ];
         ChannelIndex_uint8_t++ )
    {
      EE_RSCAN_Start( UnitNumber_uint8_t,
                      ChannelIndex_uint8_t,
                      OperationMode_uint8_t,
                      ClearErrorCounter_uint8_t,
                      TimeStampSetting_uint16_t );
    }
  }
  else
  {  
    if( ChannelNumber_uint8_t >= ee_rscan_channels[ UnitNumber_uint8_t ] ) 
      return( EE_RSCAN_ERROR );
      
    /* channels: cancel any sleep states */
    
    ee_rscan_common_p[ UnitNumber_uint8_t ]->ch
                     [ ChannelNumber_uint8_t ].ctrl.cslpr = EE_RSCAN_CLEAR;
    AccessTimeout_int32_t = EE_RSCAN_SHUTDOWNTIMEOUT;
    while( ( ee_rscan_common_p[ UnitNumber_uint8_t ]->ch
                              [ ChannelNumber_uint8_t ].stsl.slps != EE_RSCAN_CLEAR )
             && ( --AccessTimeout_int32_t > 0 ) );
    if( AccessTimeout_int32_t == 0L ) return( EE_RSCAN_ERROR );
      
    if( ClearErrorCounter_uint8_t )
    {
      EE_RSCAN_Start( UnitNumber_uint8_t,
                      ChannelNumber_uint8_t,
                      EE_RSCAN_OPMODE_RESET,
                      0,
                      0 );
    }
    
    switch( OperationMode_uint8_t )
    {
      case EE_RSCAN_OPMODE_RESET:
        ee_rscan_common_p[ UnitNumber_uint8_t ]->ch
                         [ ChannelNumber_uint8_t ].ctrl.chmdc = EE_RSCAN_OPMODE_RESET;
        break;
        
      case EE_RSCAN_OPMODE_HALT:
        ee_rscan_common_p[ UnitNumber_uint8_t ]->ch
                         [ ChannelNumber_uint8_t ].ctrl.chmdc = EE_RSCAN_OPMODE_HALT;
        ee_rscan_common_p[ UnitNumber_uint8_t ]->ch
                         [ ChannelNumber_uint8_t ].ctrh.ctme = EE_RSCAN_CLEAR;
        break;
  
      case EE_RSCAN_OPMODE_OPER:
        ee_rscan_common_p[ UnitNumber_uint8_t ]->ch
                         [ ChannelNumber_uint8_t ].ctrl.chmdc = EE_RSCAN_OPMODE_OPER;
        break;
  
      case EE_RSCAN_OPMODE_RECONLY:
        ee_rscan_common_p[ UnitNumber_uint8_t ]->ch
                         [ ChannelNumber_uint8_t ].ctrh.ctms = EE_RSCAN_TEST_RXONLY;
        ee_rscan_common_p[ UnitNumber_uint8_t ]->ch
                         [ ChannelNumber_uint8_t ].ctrh.ctme = EE_RSCAN_SET;
        ee_rscan_common_p[ UnitNumber_uint8_t ]->ch
                         [ ChannelNumber_uint8_t ].ctrl.chmdc = EE_RSCAN_OPMODE_OPER;
        OperationMode_uint8_t = EE_RSCAN_OPMODE_OPER;
        break;
  
      case EE_RSCAN_OPMODE_STEST:
        ee_rscan_common_p[ UnitNumber_uint8_t ]->ch
                         [ ChannelNumber_uint8_t ].ctrh.ctms = EE_RSCAN_TEST_INTLOOP;
        ee_rscan_common_p[ UnitNumber_uint8_t ]->ch
                         [ ChannelNumber_uint8_t ].ctrh.ctme = EE_RSCAN_SET;
        ee_rscan_common_p[ UnitNumber_uint8_t ]->ch
                         [ ChannelNumber_uint8_t ].ctrl.chmdc = EE_RSCAN_OPMODE_OPER;
        OperationMode_uint8_t = EE_RSCAN_OPMODE_OPER;
        break;
        
      default: return( EE_RSCAN_ERROR );
  
    } // switch( OperationMode_uint8_t )
  
    AccessTimeout_int32_t = EE_RSCAN_SHUTDOWNTIMEOUT;
    while( ( ee_rscan_common_p[ UnitNumber_uint8_t ]->ch
                              [ ChannelNumber_uint8_t ].stsl.mds != ( int32_t )OperationMode_uint8_t )
           && ( --AccessTimeout_int32_t > 0 ) );
    if( AccessTimeout_int32_t == 0L ) return( EE_RSCAN_ERROR );
      
    if( OperationMode_uint8_t == EE_RSCAN_OPMODE_OPER )    /* verify communication ready state */
    {
      AccessTimeout_int32_t = EE_RSCAN_SHUTDOWNTIMEOUT;
      while( ( ee_rscan_common_p[ UnitNumber_uint8_t ]->ch
                                [ ChannelNumber_uint8_t ].stsl.coms != EE_RSCAN_SET )
             && ( --AccessTimeout_int32_t > 0 ) );
      if( AccessTimeout_int32_t == 0L ) return( EE_RSCAN_ERROR );      
    }
      
  }  
  return( EE_RSCAN_OK );    
}

// *******************************************************************************************************************
// EE_RSCAN_Stop(unit, channel, stopMode)
// - inputs: unit, channel (or EE_RSCAN_GLOBAL), stopMode
// - returns: EE_RSCAN_OK or EE_RSCAN_ERROR
// What it does: Puts a channel (or the whole unit) into RESET/HALT/SLEEP.
// Notes: Waits for hardware status uint8_ts and times out on failure.
// *******************************************************************************************************************


uint8_t EE_RSCAN_Stop( uint8_t UnitNumber_uint8_t,
                   uint8_t ChannelNumber_uint8_t,
                   uint8_t StopMode_uint8_t )
{
  int32_t AccessTimeout_int32_t = EE_RSCAN_SHUTDOWNTIMEOUT; 

  if( UnitNumber_uint8_t >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
  if( ( ChannelNumber_uint8_t >= ee_rscan_channels[ UnitNumber_uint8_t ] ) &&
      ( ChannelNumber_uint8_t != EE_RSCAN_GLOBAL ) ) return( EE_RSCAN_ERROR );

  if( ChannelNumber_uint8_t == EE_RSCAN_GLOBAL )
    {
      switch( StopMode_uint8_t )
        {
        case EE_RSCAN_OPMODE_SLEEP:
          if( ee_rscan_common_p[ UnitNumber_uint8_t ]->gsts.mds != EE_RSCAN_OPMODE_RESET )
            return( EE_RSCAN_ERROR );
          ee_rscan_common_p[ UnitNumber_uint8_t ]->gctrl.gslpr = EE_RSCAN_SET;
          while( ( ee_rscan_common_p[ UnitNumber_uint8_t ]->gsts.slps != EE_RSCAN_SET )
                 && ( --AccessTimeout_int32_t > 0 ) );
          ee_rscan_common_p[ UnitNumber_uint8_t ]->gtstcfg.icbce = EE_RSCAN_COMTEST_OFF;  
          ee_rscan_common_p[ UnitNumber_uint8_t ]->gtstctr = EE_RSCAN_COMTEST_OFF;
          while( ee_rscan_common_p[ UnitNumber_uint8_t ]->gtstctr != EE_RSCAN_COMTEST_OFF );
          break;
          
        default:
          ee_rscan_common_p[ UnitNumber_uint8_t ]->gctrl.gmdc = ( int32_t )StopMode_uint8_t;
          while( ( ee_rscan_common_p[ UnitNumber_uint8_t ]->gsts.mds != ( int32_t )StopMode_uint8_t )
                 && ( --AccessTimeout_int32_t > 0 ) );
          break;
        }
    }
  else
    {
      switch( StopMode_uint8_t )
        {
        case EE_RSCAN_OPMODE_SLEEP:
          if( ee_rscan_common_p[ UnitNumber_uint8_t ]->ch
                               [ ChannelNumber_uint8_t ].stsl.mds != EE_RSCAN_OPMODE_RESET )
            return( EE_RSCAN_ERROR );
          ee_rscan_common_p[ UnitNumber_uint8_t ]->ch
                           [ ChannelNumber_uint8_t ].ctrl.cslpr = EE_RSCAN_SET;
          while( ( ee_rscan_common_p[ UnitNumber_uint8_t ]->ch
                                    [ ChannelNumber_uint8_t ].stsl.slps != EE_RSCAN_SET )
                 && ( --AccessTimeout_int32_t > 0 ) );
          break;

        default:
          ee_rscan_common_p[ UnitNumber_uint8_t ]->ch
                           [ ChannelNumber_uint8_t ].ctrl.chmdc = ( int32_t )StopMode_uint8_t;
          ee_rscan_common_p[ UnitNumber_uint8_t ]->ch
                           [ ChannelNumber_uint8_t ].ctrh.ctme = EE_RSCAN_CLEAR;
          while( ( ee_rscan_common_p[ UnitNumber_uint8_t ]->ch
                                    [ ChannelNumber_uint8_t ].stsl.mds != ( int32_t )StopMode_uint8_t )
                 && ( --AccessTimeout_int32_t > 0 ) );
          break;
        }
    }

  if( AccessTimeout_int32_t == 0L ) return( EE_RSCAN_ERROR );
  else return( EE_RSCAN_OK );
}    


// *******************************************************************************************************************
// EE_RSCAN_SendMessage(unit, ch, status_out, *msg)
// - sends msg via either message box or FIFO (based on msg->path)
// - status_out: set to FAULT_NONE / FAULT_BUSY / FAULT_PARAMETER etc.
// If all TX boxes/FIFOs are busy, returns OK with status=FAULT_BUSY.
// *******************************************************************************************************************


uint8_t EE_RSCAN_SendMessage( uint8_t  UnitNumber_uint8_t,
                          uint8_t  ChannelNumber_uint8_t,
                          puint8_t Status_puint8_t,
                          struct ee_rscan_message *Message )
{
  uint8_t SendBox_uint8_t;
  uint8_t FirstBox_uint8_t;
  uint8_t LastBox_uint8_t;
  uint8_t SendBoxOccupied_uint8_t = EE_RSCAN_CLEAR;
  uint8_t FIFONumber_uint8_t;
  
  *Status_puint8_t = EE_RSCAN_FAULT_PARAMETER;
  
  if( UnitNumber_uint8_t >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
  if( ChannelNumber_uint8_t >= ee_rscan_channels[ UnitNumber_uint8_t ] ) 
    return( EE_RSCAN_ERROR );
  if( ee_rscan_common_p[ UnitNumber_uint8_t ]->ch[ ChannelNumber_uint8_t ].stsl.mds != EE_RSCAN_OPMODE_OPER )
    return( EE_RSCAN_ERROR );
    
  *Status_puint8_t = EE_RSCAN_FAULT_NONE;

  switch( Message->path )
  {
    case EE_RSCAN_PATH_MSGBOX:      /* search a free SendBox, if required */
    {
      if( Message->pathdetail != EE_RSCAN_PATHDETAIL_ANY )
      {
        FirstBox_uint8_t = Message->pathdetail;
        LastBox_uint8_t  = FirstBox_uint8_t;
        if( FirstBox_uint8_t >= EE_RSCAN_MAXTXBUFFERS )
        {
          *Status_puint8_t = EE_RSCAN_FAULT_PARAMETER;
          return( EE_RSCAN_ERROR );
        }
      }
      else
      {
        FirstBox_uint8_t = 0;
        LastBox_uint8_t  = ( EE_RSCAN_MAXTXBUFFERS - 1 );
      }
      
      for( SendBox_uint8_t =  FirstBox_uint8_t;
           SendBox_uint8_t <= LastBox_uint8_t;
           SendBox_uint8_t++ )
      {
        if( ( ( ( ee_rscan_common_p[ UnitNumber_uint8_t ]->tmsts
                  [ ( EE_RSCAN_MAXTXBUFFERS * ChannelNumber_uint8_t + 
                      SendBox_uint8_t ) ] ) )
                & EE_RSCAN_TMSTS_STSMSK ) == 
                EE_RSCAN_TMSTS_CLEAR )    /* check pending TRQ */
        {
          for( FIFONumber_uint8_t = 0;
               FIFONumber_uint8_t < EE_RSCAN_MAXCOMFIFOS;
               FIFONumber_uint8_t++ )   /* check any COM FIFO assignment */
          
          {
            if( ( ( uint8_t )( ee_rscan_common_p[ UnitNumber_uint8_t ]->cfcc
                                            [ EE_RSCAN_MAXCOMFIFOS * 
                                            ChannelNumber_uint8_t ].h.cftml ) 
                                            == SendBox_uint8_t ) &&
                         ( ee_rscan_common_p[ UnitNumber_uint8_t ]->cfcc
                                            [ EE_RSCAN_MAXCOMFIFOS * 
                                            ChannelNumber_uint8_t ].l.cfe ) )
            {
              SendBoxOccupied_uint8_t = EE_RSCAN_SET;
              break;
            }
          }
        }
        else
        {
          SendBoxOccupied_uint8_t = EE_RSCAN_SET;
        }

        if( SendBoxOccupied_uint8_t == EE_RSCAN_CLEAR )
        {
          /* Initiate Sending with this box and exit the box searching */
          
          EE_RSCAN_SetIDData( &ee_rscan_txmsg_p[ UnitNumber_uint8_t ]
                                               [ ChannelNumber_uint8_t ]->
                                            buf[ SendBox_uint8_t ],
                              Message );
                         
          ee_rscan_common_p[ UnitNumber_uint8_t ]->tmsts
                           [ ( EE_RSCAN_MAXTXBUFFERS * ChannelNumber_uint8_t + 
                             SendBox_uint8_t ) ] &= ( uint8_t )
                             ( ~( EE_RSCAN_TMSTS_RFMSK ) );

          ee_rscan_common_p[ UnitNumber_uint8_t ]->tmc
                           [ ( EE_RSCAN_MAXTXBUFFERS * ChannelNumber_uint8_t + 
                             SendBox_uint8_t ) ] |= ( uint8_t )
                             ( EE_RSCAN_TMC_SET_TR );
          break;
        }
        else
        {
          SendBoxOccupied_uint8_t = EE_RSCAN_CLEAR;   /* test next SendBox */
        }
      }
      
      if( SendBox_uint8_t >= EE_RSCAN_MAXTXBUFFERS )
      {
        *Status_puint8_t = EE_RSCAN_FAULT_BUSY;
        return( EE_RSCAN_OK );
      }
      break;
    }
    
    case EE_RSCAN_PATH_COMFIFO:                    /* use dedicated FIFO */
    {
      if( Message->pathdetail != EE_RSCAN_PATHDETAIL_ANY )
      {
        SendBox_uint8_t = Message->pathdetail;
        if( SendBox_uint8_t >= EE_RSCAN_MAXCOMFIFOS )
        {
          *Status_puint8_t = EE_RSCAN_FAULT_PARAMETER;
          return( EE_RSCAN_ERROR );
        }
        else
        {
          SendBox_uint8_t = ( EE_RSCAN_MAXCOMFIFOS * ChannelNumber_uint8_t ) + 
                        Message->pathdetail;
          if( ee_rscan_common_p[ UnitNumber_uint8_t ]->cfsts[ SendBox_uint8_t ].cffll )
          {
            *Status_puint8_t = EE_RSCAN_FAULT_BUSY;
            return( EE_RSCAN_OK );                    
          }
        }
      }
      else                                  /* search enabled, non-full FIFO */
      {
        SendBox_uint8_t = EE_RSCAN_FIFO_NEXTELEMENT;
        
        for( FIFONumber_uint8_t = ( EE_RSCAN_MAXCOMFIFOS * ChannelNumber_uint8_t );
             FIFONumber_uint8_t < ( EE_RSCAN_MAXCOMFIFOS * ( ChannelNumber_uint8_t + 1 ) );
             FIFONumber_uint8_t++ )
        {
          if( ee_rscan_common_p[ UnitNumber_uint8_t ]->cfcc[ FIFONumber_uint8_t ].l.cfe )
          {
            if( !ee_rscan_common_p[ UnitNumber_uint8_t ]->cfsts[ FIFONumber_uint8_t ].cffll )
            {
              SendBox_uint8_t = FIFONumber_uint8_t;
              if( ee_rscan_common_p[ UnitNumber_uint8_t ]->cfsts[ FIFONumber_uint8_t ].cfemp )
              {
                break;             /* an empty FIFO can be used immediately */
              }
            }
          }
        }
      }
      
      if( SendBox_uint8_t != EE_RSCAN_FIFO_NEXTELEMENT ) /* feed message into FIFO */
      {
        SendBox_uint8_t %= EE_RSCAN_MAXCOMFIFOS;
        
        EE_RSCAN_SetIDDataCFIFO( &ee_rscan_comfifo_p[ UnitNumber_uint8_t ]
                                                    [ ChannelNumber_uint8_t ]->
                                                 buf[ SendBox_uint8_t ],
                                 Message );
                       
        ee_rscan_common_p[ UnitNumber_uint8_t ]->cfpctr
                         [ EE_RSCAN_MAXCOMFIFOS * ChannelNumber_uint8_t + 
                           SendBox_uint8_t ].fpc = EE_RSCAN_FIFO_NEXTELEMENT;      
      }
      else                  /* free and enabled FIFO was not found */
      {
        *Status_puint8_t = EE_RSCAN_FAULT_BUSY;
        return( EE_RSCAN_OK );        
      }
      break;
    }
      
    default:
      *Status_puint8_t = EE_RSCAN_FAULT_PARAMETER;
      return( EE_RSCAN_ERROR );
  }
     
  return( EE_RSCAN_OK );
}

// *******************************************************************************************************************
// EE_RSCAN_ReceiveMessage(unit, status_out, *msg)
// - tries msg boxes, RX FIFOs, then COM FIFOs (depending on msg->path)
// - fills msg and sets status_out to FAULT_NONE if something was read
// Clears new-data flags for message boxes; advances FIFO pointers.
// *******************************************************************************************************************

uint8_t EE_RSCAN_ReceiveMessage( uint8_t                      UnitNumber_uint8_t,
                             puint8_t                     Status_puint8_t,
                             struct ee_rscan_message *Message )
{
  uint8_t ReceiveBox_uint8_t;
  uint8_t SearchBegin_uint8_t;
  uint8_t SearchEnd_uint8_t;
  
  *Status_puint8_t = EE_RSCAN_FAULT_PARAMETER;
  
  if( UnitNumber_uint8_t >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
  if( ee_rscan_common_p[ UnitNumber_uint8_t ]->gsts.mds != EE_RSCAN_OPMODE_OPER )
    return( EE_RSCAN_ERROR );
    
  *Status_puint8_t = EE_RSCAN_FAULT_NODATA;
  
  if( ( Message->path == EE_RSCAN_PATH_MSGBOX ) ||
      ( Message->path == EE_RSCAN_PATH_ANY ) ) /* check within message boxes */
  {
    if( Message->pathdetail == EE_RSCAN_GLOBAL )    /* read first filled box */
    {
      SearchBegin_uint8_t = 0;
      SearchEnd_uint8_t   = EE_RSCAN_MAXRXBUFFERS - 1;
    }
    else                             /* read dedicated box (typical polling) */
    {
      SearchBegin_uint8_t = Message->pathdetail;
      SearchEnd_uint8_t   = Message->pathdetail;
      
      if( SearchBegin_uint8_t >= EE_RSCAN_MAXRXBUFFERS )
      {
        *Status_puint8_t = EE_RSCAN_FAULT_PARAMETER;
        return( EE_RSCAN_ERROR );
      }
    }
    
    for( ReceiveBox_uint8_t =  SearchBegin_uint8_t;
         ReceiveBox_uint8_t <= SearchEnd_uint8_t;
         ReceiveBox_uint8_t++ )
    {
      while( ee_rscan_common_p[ UnitNumber_uint8_t ]->rmnd
                              [ EE_RSCAN_COMRXREG( ReceiveBox_uint8_t ) ] >> 
                                EE_RSCAN_COMRXuint8_t( ReceiveBox_uint8_t ) & 
                                EE_RSCAN_SET )
      {
        *Status_puint8_t = EE_RSCAN_FAULT_NONE;
                                                      /* Clear new data flag */
        ee_rscan_common_p[ UnitNumber_uint8_t ]->rmnd
                         [ EE_RSCAN_COMRXREG( ReceiveBox_uint8_t ) ] = ( int32_t ) 
                         ( ~( 1 << EE_RSCAN_COMRXuint8_t( ReceiveBox_uint8_t ) ) );
        
        EE_RSCAN_GetMessage( &ee_rscan_rxmsg_p[ UnitNumber_uint8_t ]->
                                           buf[ ReceiveBox_uint8_t ],
                             Message );
      }
      if( *Status_puint8_t != EE_RSCAN_FAULT_NODATA ) break;
    }
  }

  if( ( Message->path == EE_RSCAN_PATH_RXFIFO ) ||
      ( ( Message->path == EE_RSCAN_PATH_ANY ) &&
        ( *Status_puint8_t == EE_RSCAN_FAULT_NODATA ) ) ) /* check within RX FIFO */
  {
    if( Message->pathdetail == EE_RSCAN_GLOBAL )    /* read first filled FIFO */
    {
      SearchBegin_uint8_t = 0;
      SearchEnd_uint8_t   = EE_RSCAN_MAXRXFIFOS - 1;
    }
    else                                               /* read dedicated FIFO */
    {
      SearchBegin_uint8_t = Message->pathdetail;
      SearchEnd_uint8_t   = Message->pathdetail;
 
      if( SearchBegin_uint8_t >= EE_RSCAN_MAXRXFIFOS )
      {
        *Status_puint8_t = EE_RSCAN_FAULT_PARAMETER;
        return( EE_RSCAN_ERROR );
      }
    }
    
    for( ReceiveBox_uint8_t =  SearchBegin_uint8_t;
         ReceiveBox_uint8_t <= SearchEnd_uint8_t;
         ReceiveBox_uint8_t++ )
    {
      if( !ee_rscan_common_p[ UnitNumber_uint8_t ]->rfsts[ ReceiveBox_uint8_t ].rfemp )
      {
        *Status_puint8_t = EE_RSCAN_FAULT_NONE;
        
        EE_RSCAN_GetMessage( &ee_rscan_rxfifo_p[ UnitNumber_uint8_t ]->
                                            buf[ ReceiveBox_uint8_t ],
                             Message );
        
        ee_rscan_common_p[ UnitNumber_uint8_t ]->rfpctr[ ReceiveBox_uint8_t ].fpc = 
          EE_RSCAN_FIFO_NEXTELEMENT;
        
        break;
      }
    }    
  }

  if( ( Message->path == EE_RSCAN_PATH_COMFIFO ) ||
      ( ( Message->path == EE_RSCAN_PATH_ANY ) &&
        ( *Status_puint8_t == EE_RSCAN_FAULT_NODATA ) ) ) /* check within COMFIFO */
  {
    if( Message->pathdetail == EE_RSCAN_GLOBAL )    /* read first filled FIFO */
    {
      SearchBegin_uint8_t = 0;
      SearchEnd_uint8_t   = EE_RSCAN_MAXCOMFIFOS * ee_rscan_channels[ UnitNumber_uint8_t ] - 1;
    }
    else                                               /* read dedicated FIFO */
    {
      SearchBegin_uint8_t = Message->pathdetail;
      SearchEnd_uint8_t   = Message->pathdetail;
 
      if( SearchBegin_uint8_t >= ( EE_RSCAN_MAXCOMFIFOS * ee_rscan_channels[ UnitNumber_uint8_t ] ) )
      {
        *Status_puint8_t = EE_RSCAN_FAULT_PARAMETER;
        return( EE_RSCAN_ERROR );
      }
    }
    
    for( ReceiveBox_uint8_t =  SearchBegin_uint8_t;
         ReceiveBox_uint8_t <= SearchEnd_uint8_t;
         ReceiveBox_uint8_t++ )
    {
      if( !ee_rscan_common_p[ UnitNumber_uint8_t ]->cfsts[ ReceiveBox_uint8_t ].cfemp )
      {
        *Status_puint8_t = EE_RSCAN_FAULT_NONE;
        
        EE_RSCAN_GetMessageCF( &ee_rscan_comfifo_p[ UnitNumber_uint8_t ]
		                                              [ ReceiveBox_uint8_t /
					                                     EE_RSCAN_MAXCOMFIFOS ]->
                                               buf[ ReceiveBox_uint8_t ],
                               Message );
        
        ee_rscan_common_p[ UnitNumber_uint8_t ]->cfpctr[ ReceiveBox_uint8_t ].fpc = 
          EE_RSCAN_FIFO_NEXTELEMENT;
        
        break;
      }
    }    
  }

  return( EE_RSCAN_OK );
}


// *******************************************************************************************************************
// EE_RSCAN_PortDisable(unit, channel)
// - inputs: unit, channel (or EE_RSCAN_GLOBAL)
// - returns: EE_RSCAN_OK or EE_RSCAN_ERROR
// Releases the CAN pins back to normal GPIO (disables peripheral mode).
// *******************************************************************************************************************


uint8_t EE_RSCAN_PortDisable( uint8_t UnitNumber_uint8_t,
                          uint8_t ChannelNumber_uint8_t )
{
  uint8_t ChannelCount_uint8_t;

  if( UnitNumber_uint8_t >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
  if( ChannelNumber_uint8_t >= ee_rscan_channels[ UnitNumber_uint8_t ] ) 
    return( EE_RSCAN_ERROR );

  switch( UnitNumber_uint8_t ) 
  {
    case EE_RSCAN_0:
    {
      switch( ChannelNumber_uint8_t )
      {
          
#ifdef EE_RSCAN_PORT_M0RX0
        case EE_RSCAN_CHANNEL0:
          PORT_Disable( EE_RSCAN_PORT_M0RX0, EE_RSCAN_PORT_uint8_t_M0RX0 );
          PORT_Disable( EE_RSCAN_PORT_M0TX0, EE_RSCAN_PORT_uint8_t_M0TX0 );
          break;
#endif

#ifdef EE_RSCAN_PORT_M0RX1
        case EE_RSCAN_CHANNEL1:
          PORT_Disable( EE_RSCAN_PORT_M0RX1, EE_RSCAN_PORT_uint8_t_M0RX1 );
          PORT_Disable( EE_RSCAN_PORT_M0TX1, EE_RSCAN_PORT_uint8_t_M0TX1 );
          break;
#endif

        case EE_RSCAN_GLOBAL:
          for( ChannelCount_uint8_t = 0; 
               ChannelCount_uint8_t < ee_rscan_channels[ UnitNumber_uint8_t ];
               ChannelCount_uint8_t++ )
          {
            EE_RSCAN_PortDisable( UnitNumber_uint8_t, ChannelCount_uint8_t );
          }
          break;

        default:
          return( EE_RSCAN_ERROR );
      } // switch ChannelNumber_uint8_t
      break;
    }
    
    case EE_RSCAN_1:
    {
      switch( ChannelNumber_uint8_t )
      {
          
#ifdef EE_RSCAN_PORT_M1RX0
        case EE_RSCAN_CHANNEL0:
          PORT_Disable( EE_RSCAN_PORT_M1RX0, EE_RSCAN_PORT_uint8_t_M1RX0 );
          PORT_Disable( EE_RSCAN_PORT_M1TX0, EE_RSCAN_PORT_uint8_t_M1TX0 );
          break;
#endif

#ifdef EE_RSCAN_PORT_M1RX1
        case EE_RSCAN_CHANNEL1:
          PORT_Disable( EE_RSCAN_PORT_M1RX1, EE_RSCAN_PORT_uint8_t_M1RX1 );
          PORT_Disable( EE_RSCAN_PORT_M1TX1, EE_RSCAN_PORT_uint8_t_M1TX1 );
          break;
#endif

        case EE_RSCAN_GLOBAL:
          for( ChannelCount_uint8_t = 0; 
               ChannelCount_uint8_t < ee_rscan_channels[ UnitNumber_uint8_t ];
               ChannelCount_uint8_t++ )
          {
            EE_RSCAN_PortDisable( UnitNumber_uint8_t, ChannelCount_uint8_t );
          }
          break;

        default:
          return( EE_RSCAN_ERROR );
      } // switch ChannelNumber_uint8_t
      break;
    }

    default: 
      return( EE_RSCAN_ERROR );

  } // switch( UnitNumber )
  
  return( EE_RSCAN_OK );
}


