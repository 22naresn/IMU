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
