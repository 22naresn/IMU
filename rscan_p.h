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
