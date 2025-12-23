#define DRIVER_LOCAL

#include <stddef.h>
#include <stdbool.h>
#include <stddef.h>
#include "r_cg_macrodriver.h"
#include "addl_types.h"
#include "iodefine.h"
#include "map_rscan.h"
#include "rscan.h"
#include "rscan_p.h"
#include "rscan_a.h"
#include "standard_ports.h"
#include "franken_functions.h"

#if( EE_RSCAN_MACROS > EE_RSCAN_MAXMACROS )
#error "NUMBER OF UNITS NOT SUPPORTED"
#endif

#ifdef EE_RSCAN_INT_BUNDLINGHOOK
extern void EE_RSCAN_INT_BUNDLINGHOOK( uint8_t,
                                       uint8_t *, uint8_t *, uint8_t * );
#endif

/*
 * CreateInterrupt() Jump Vector Table
 */
 
void EE_RSCAN_IRQDefault(void);

#if( EE_RSCAN_MACROS == 1 )

static void ( *EE_RSCAN_CIVector [ ( EE_RSCAN_MACROS * 
       			                       ( EE_RSCAN_INT_GLOBAL + 
            		                     EE_RSCAN_INT_CHANNEL * 
            		                     EE_RSCAN_MAXCHANNELS ) ) ] )( ) =
	{
		EE_RSCAN_IRQDefault,
		EE_RSCAN_IRQDefault, EE_RSCAN_IRQDefault, EE_RSCAN_IRQDefault, EE_RSCAN_IRQDefault,
		EE_RSCAN_IRQDefault, EE_RSCAN_IRQDefault, EE_RSCAN_IRQDefault, EE_RSCAN_IRQDefault,
		EE_RSCAN_IRQDefault, EE_RSCAN_IRQDefault
	};

#endif
		
#if( EE_RSCAN_MACROS == 2 )

static void ( *EE_RSCAN_CIVector [ ( EE_RSCAN_MACROS * 
       			                       ( EE_RSCAN_INT_GLOBAL + 
            		                     EE_RSCAN_INT_CHANNEL * 
            		                     EE_RSCAN_MAXCHANNELS ) ) ] )( ) =
	{
		EE_RSCAN_IRQDefault,
		EE_RSCAN_IRQDefault, EE_RSCAN_IRQDefault, EE_RSCAN_IRQDefault, EE_RSCAN_IRQDefault,
		EE_RSCAN_IRQDefault, EE_RSCAN_IRQDefault, EE_RSCAN_IRQDefault, EE_RSCAN_IRQDefault,
		EE_RSCAN_IRQDefault, EE_RSCAN_IRQDefault,
		EE_RSCAN_IRQDefault,
		EE_RSCAN_IRQDefault, EE_RSCAN_IRQDefault, EE_RSCAN_IRQDefault, EE_RSCAN_IRQDefault,
		EE_RSCAN_IRQDefault, EE_RSCAN_IRQDefault, EE_RSCAN_IRQDefault, EE_RSCAN_IRQDefault,
		EE_RSCAN_IRQDefault, EE_RSCAN_IRQDefault
	};

#endif

/*
 * Global Variables 
 */

/* Number of interrupt vector */

uint8_t EE_RSCAN_InterruptFlag_Unit_u08     = 0;

uint8_t EE_RSCAN_InterruptFlag_Global_u08   = EE_RSCAN_INT_NOINT;
uint8_t EE_RSCAN_InterruptFlag_Channel0_u08 = EE_RSCAN_INT_NOINT;
uint8_t EE_RSCAN_InterruptFlag_Channel1_u08 = EE_RSCAN_INT_NOINT;

uint8_t EE_RSCAN_LastErrorCode_Global_u08   = EE_RSCAN_GINT_NONE;
uint8_t EE_RSCAN_InterruptFlag_Channel_u08[ EE_RSCAN_MAXCHANNELS ] =
	{ EE_RSCAN_INT_NOINT, EE_RSCAN_INT_NOINT };
uint16_t EE_RSCAN_LastErrorCode_Channel_u16[ EE_RSCAN_MAXCHANNELS ] = 
	{ EE_RSCAN_ERROR_CLEARALL, EE_RSCAN_ERROR_CLEARALL };

uint8_t EE_RSCAN_LastTxObjectChannel0_u08   = EE_RSCAN_INT_NOINT;
uint8_t EE_RSCAN_LastTxObjectChannel1_u08   = EE_RSCAN_INT_NOINT;

/*
 * Internal Support Functions
 */
 
void EE_RSCAN_IRQDefault(void)
{
}

uint8_t EE_RSCAN_GetTxBuffer( uint16_t FlagRegister_u16 )
{
  uint8_t CurrentScan_u08;
  
  for( CurrentScan_u08 = 0; 
       CurrentScan_u08 < EE_RSCAN_MAXTXBUFFERS;
       CurrentScan_u08++ )
  {
    if( ( ( FlagRegister_u16 >> CurrentScan_u08 ) & 0x01 ) == 0x01 )
    {
      return( CurrentScan_u08 );
    }
  }
  return( EE_RSCAN_INT_NOINT );
}   

uint8_t EE_RSCAN_GetComFIFOIntStatus( uint8_t UnitNumber_u08,
                                  uint8_t ChannelNumber_u08,
                                  uint8_t InterruptType_u08 )
{
  uint8_t FlagSet_u16;
  //uint8_t FlagFirst_u08;
  
  switch( InterruptType_u08 )
  {
    case EE_RSCAN_INT_RXCF:
      FlagSet_u16 = ( uint16_t )( ee_rscan_common_p[ UnitNumber_u08 ]->cfists
                                              [ EE_RSCAN_COMCFINTREG( ChannelNumber_u08 ) ] );
      if( ( FlagSet_u16 >> ( EE_RSCAN_COMCFINTBIT( ChannelNumber_u08 ) ) )
                           & EE_RSCAN_COMCFINT_FLAG )
      return( 0 );
      break;

    case EE_RSCAN_INT_TXCF:
      FlagSet_u16 = ( uint16_t )( ee_rscan_common_p[ UnitNumber_u08 ]->gtintsts
                                              [ EE_RSCAN_COMGTINTREG( ChannelNumber_u08 ) ] );
      if( ( FlagSet_u16 >> ( EE_RSCAN_COMGTINTBIT( ChannelNumber_u08 ) ) )
                           & EE_RSCAN_GTINT_FIFO )
      return( 0 );
      break;
  }	
  return( EE_RSCAN_GLOBAL );
}

void EE_RSCAN_SetIDData( struct ee_rscan_t_msg   *Buffer,
                         struct ee_rscan_message *Message ) 
{
  uint8_t DataCount_u08;

  Buffer->idl.id    = ( uint16_t )( Message->hdr.id & EE_RSCAN_ID_MASK_LOW );
  Buffer->idh.id    = ( uint16_t )( ( Message->hdr.id >> EE_RSCAN_MAXREGWIDTH ) & EE_RSCAN_ID_MASK_HIGH );
  Buffer->idh.thlen = Message->hdr.thlen;
  Buffer->idh.rtr   = Message->hdr.rtr;
  Buffer->idh.ide   = Message->hdr.ide;
  Buffer->ptr.dlc   = Message->flag.dlc;
  
  Buffer->data[ 0 ] = 0;
  Buffer->data[ 1 ] = 0;
  Buffer->data[ 2 ] = 0;
  Buffer->data[ 3 ] = 0;
  
  for( DataCount_u08 = 0; DataCount_u08 < Message->flag.dlc; DataCount_u08++ ) 
  {
    if( DataCount_u08 < 2 ) 
    {
       Buffer->data[ 0 ] += ( Message->data[ DataCount_u08 ] << ( 8 * DataCount_u08 ) );
    } 
  	else if ( DataCount_u08 < 4 ) 
  	{
       Buffer->data[ 1 ] += ( Message->data[ DataCount_u08 ] << ( 8 * ( DataCount_u08 - 2 ) ) );
    }
  	else if ( DataCount_u08 < 6 ) 
  	{
       Buffer->data[ 2 ] += ( Message->data[ DataCount_u08 ] << ( 8 * ( DataCount_u08 - 4 ) ) );
    }
  	else if ( DataCount_u08 < 8 ) 
  	{
       Buffer->data[ 3 ] += ( Message->data[ DataCount_u08 ] << ( 8 * ( DataCount_u08 - 6 ) ) );
    }
  }
}

void EE_RSCAN_SetIDDataCFIFO( struct ee_rscan_r_cmsg  *Buffer,
                              struct ee_rscan_message *Message )
{
  uint8_t DataCount_u08;

  Buffer->idl.id    = ( uint16_t )( Message->hdr.id & EE_RSCAN_ID_MASK_LOW );
  Buffer->idh.id    = ( uint16_t )( ( Message->hdr.id >> EE_RSCAN_MAXREGWIDTH ) & EE_RSCAN_ID_MASK_HIGH );
  Buffer->idh.thlen = Message->hdr.thlen;
  Buffer->idh.rtr   = Message->hdr.rtr;
  Buffer->idh.ide   = Message->hdr.ide;
  Buffer->ptr.dlc   = Message->flag.dlc;

  for( DataCount_u08 = 0; DataCount_u08 < Message->flag.dlc; DataCount_u08++ ) 
  {
    if( DataCount_u08 < 2 ) 
    {
       Buffer->data[ 0 ] += ( Message->data[ DataCount_u08 ] << ( 8 * DataCount_u08 ) );
    } 
  	else if ( DataCount_u08 < 4 ) 
  	{
       Buffer->data[ 1 ] += ( Message->data[ DataCount_u08 ] << ( 8 * ( DataCount_u08 - 2 ) ) );
    }
  	else if ( DataCount_u08 < 6 ) 
  	{
       Buffer->data[ 2 ] += ( Message->data[ DataCount_u08 ] << ( 8 * ( DataCount_u08 - 4 ) ) );
    }
  	else if ( DataCount_u08 < 8 ) 
  	{
       Buffer->data[ 3 ] += ( Message->data[ DataCount_u08 ] << ( 8 * ( DataCount_u08 - 6 ) ) );
    }
  }
}

void EE_RSCAN_GetMessage( struct ee_rscan_r_rmsg  *Buffer, 
                          struct ee_rscan_message *Message ) 
{
  uint8_t DataCount_u08;
  
  Message->hdr.id  =  ( uint32_t )( Buffer->idl.id );
  Message->hdr.id  += ( ( uint32_t )( Buffer->idh.id ) << EE_RSCAN_MAXREGWIDTH );
  Message->hdr.rtr = Buffer->idh.rtr;
  Message->hdr.ide = Buffer->idh.ide;

  Message->flag.ts  = Buffer->ts;
  Message->flag.ptr = Buffer->ptr.ptr;
  Message->flag.dlc = Buffer->ptr.dlc;

  for( DataCount_u08 = 0; 
       DataCount_u08 < ( Message->flag.dlc );
       DataCount_u08++ ) 
  {
    if( DataCount_u08 < 2 ) 
  	{
      Message->data[ DataCount_u08 ] = ( uint8_t )( Buffer->data[ 0 ] >> ( 8 * DataCount_u08 ) );
    } 
    else if ( DataCount_u08 < 4 ) 
    {
      Message->data[ DataCount_u08 ] = ( uint8_t )( Buffer->data[ 1 ] >> ( 8 * ( DataCount_u08 - 2 ) ) );
    }
	  else if ( DataCount_u08 < 6 ) 
	  {
      Message->data[ DataCount_u08 ] = ( uint8_t )( Buffer->data[ 2 ] >> ( 8 * ( DataCount_u08 - 4 ) ) );
    }
	  else if ( DataCount_u08 < 8 ) 
	  {
      Message->data[ DataCount_u08 ] = ( uint8_t )( Buffer->data[ 3 ] >> ( 8 * ( DataCount_u08 - 6 ) ) );
    }
  }
}

void EE_RSCAN_GetMessageCF( struct ee_rscan_r_cmsg  *Buffer, 
                            struct ee_rscan_message *Message ) 
{
  uint8_t DataCount_u08;
  
  Message->hdr.id  =  ( uint32_t )( Buffer->idl.id );
  Message->hdr.id  += ( ( uint32_t )( Buffer->idh.id ) << EE_RSCAN_MAXREGWIDTH );
  Message->hdr.rtr = Buffer->idh.rtr;
  Message->hdr.ide = Buffer->idh.ide;

  Message->flag.ts  = Buffer->ts;
  Message->flag.ptr = Buffer->ptr.ptr;
  Message->flag.dlc = Buffer->ptr.dlc;

  for( DataCount_u08 = 0; 
       DataCount_u08 < ( Message->flag.dlc );
       DataCount_u08++ ) 
  {
    if( DataCount_u08 < 2 ) 
  	{
      Message->data[ DataCount_u08 ] = ( uint8_t )( Buffer->data[ 0 ] >> ( 8 * DataCount_u08 ) );
    } 
    else if ( DataCount_u08 < 4 ) 
    {
      Message->data[ DataCount_u08 ] = ( uint8_t )( Buffer->data[ 1 ] >> ( 8 * ( DataCount_u08 - 2 ) ) );
    }
	  else if ( DataCount_u08 < 6 ) 
	  {
      Message->data[ DataCount_u08 ] = ( uint8_t )( Buffer->data[ 2 ] >> ( 8 * ( DataCount_u08 - 4 ) ) );
    }
	  else if ( DataCount_u08 < 8 ) 
	  {
      Message->data[ DataCount_u08 ] = ( uint8_t )( Buffer->data[ 3 ] >> ( 8 * ( DataCount_u08 - 6 ) ) );
    }
  }
}

/*
 * The interrupt Functions
 */


//=============================================================================
// FunctionName: RSCAN_Interrupt
// IN  :         -
// OUT :         -
// Description : Central Interrupt Entry, clears pending bits and stores status
// 
//=============================================================================
void EE_RSCAN_Interrupt(void)
{     
	uint8_t FIFONumber_u08;
	uint8_t UnitNumber_u08;
	
	UnitNumber_u08 = EE_RSCAN_InterruptFlag_Unit_u08;

#ifdef EE_RSCAN_INT_BUNDLINGHOOK

    EE_RSCAN_INT_BUNDLINGHOOK( UnitNumber_u08,
                               &EE_RSCAN_InterruptFlag_Global_u08,
                               &EE_RSCAN_InterruptFlag_Channel0_u08,
                               &EE_RSCAN_InterruptFlag_Channel1_u08 );

#endif
	
  if( EE_RSCAN_InterruptFlag_Global_u08 != EE_RSCAN_INT_NOINT )
  {
    switch( EE_RSCAN_InterruptFlag_Global_u08 )
      {
      	case EE_RSCAN_INT_GERR:
        	EE_RSCAN_LastErrorCode_Global_u08 = ee_rscan_common_p[ UnitNumber_u08 ]->gerfl.err;
        	ee_rscan_common_p[ UnitNumber_u08 ]->gerfl.err = EE_RSCAN_GINT_NONE;
          for( FIFONumber_u08 = 0;
               FIFONumber_u08 < EE_RSCAN_MAXRXFIFOS;
               FIFONumber_u08++ )
          {
	        	if( ee_rscan_common_p[ UnitNumber_u08 ]->rfsts[ FIFONumber_u08 ].rfmlt )
        		{
        			EE_RSCAN_LastErrorCode_Global_u08 = EE_RSCAN_GINT_MSGLOST;
        			ee_rscan_common_p[ UnitNumber_u08 ]->rfsts[ FIFONumber_u08 ].rfmlt = 0;
        		}
        	}
          for( FIFONumber_u08 = 0;
               FIFONumber_u08 < ( EE_RSCAN_MAXCOMFIFOS * ee_rscan_channels[ UnitNumber_u08 ] );
               FIFONumber_u08++ )
          {
  	      	if( ee_rscan_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cfmlt )
	      		{
	      			EE_RSCAN_LastErrorCode_Global_u08 = EE_RSCAN_GINT_MSGLOST;
	      			ee_rscan_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cfmlt = 0;
	      		}
	      	}
        	EE_RSCAN_CIVector[ EE_RSCAN_INT_GERR ]( );
        	break;
      	case EE_RSCAN_INT_RXF0:
      	case EE_RSCAN_INT_RXF1:
      	case EE_RSCAN_INT_RXF2:
      	case EE_RSCAN_INT_RXF3:
        	FIFONumber_u08 = EE_RSCAN_InterruptFlag_Global_u08 - EE_RSCAN_INT_RXF0;
        		ee_rscan_common_p[ UnitNumber_u08 ]->rfsts[ FIFONumber_u08 ].rfif = 0;
        		EE_RSCAN_CIVector[ EE_RSCAN_INT_RXF0 + FIFONumber_u08 ]( );
          break;
        default:
        	break;
      }
    EE_RSCAN_InterruptFlag_Global_u08 = EE_RSCAN_INT_NOINT;
  }
  else if( EE_RSCAN_InterruptFlag_Channel0_u08 != EE_RSCAN_INT_NOINT )
  {
  	EE_RSCAN_InterruptFlag_Channel_u08[ EE_RSCAN_CHANNEL0 ] =
  		EE_RSCAN_InterruptFlag_Channel0_u08;
  		
  	switch( EE_RSCAN_InterruptFlag_Channel0_u08 )
  	{
  		case EE_RSCAN_INT_TX:
  			EE_RSCAN_LastTxObjectChannel0_u08 = 
  				EE_RSCAN_GetTxBuffer( ee_rscan_common_p[ UnitNumber_u08 ]->tmtcsts[ 0 ]);
  			if( EE_RSCAN_LastTxObjectChannel0_u08 != EE_RSCAN_INT_NOINT )
  			{
    			ee_rscan_common_p[ UnitNumber_u08 ]->tmsts[ EE_RSCAN_LastTxObjectChannel0_u08 ]
    			                      &= ( uint8_t )( ~( EE_RSCAN_TMSTS_RFMSK ) );
  				EE_RSCAN_CIVector[ EE_RSCAN_INT_GLOBAL + EE_RSCAN_INT_TX + 
  												 ( EE_RSCAN_INT_CHANNEL * EE_RSCAN_CHANNEL0 ) ]( );
  			}
  			break;
  		case EE_RSCAN_INT_TXA:
  			EE_RSCAN_LastTxObjectChannel0_u08 =
  				EE_RSCAN_GetTxBuffer( ee_rscan_common_p[ UnitNumber_u08 ]->tmtasts[ 0 ]);
  			if( EE_RSCAN_LastTxObjectChannel0_u08 != EE_RSCAN_INT_NOINT )
  			{
    			ee_rscan_common_p[ UnitNumber_u08 ]->tmsts[ EE_RSCAN_LastTxObjectChannel0_u08 ]
    			                      &= ( uint8_t )( ~( EE_RSCAN_TMSTS_RFMSK ) );
  				EE_RSCAN_CIVector[ EE_RSCAN_INT_GLOBAL + EE_RSCAN_INT_TXA + 
  												 ( EE_RSCAN_INT_CHANNEL * EE_RSCAN_CHANNEL0 ) ]( );
  			}
  			break;
			case EE_RSCAN_INT_CERR:
				EE_RSCAN_LastErrorCode_Channel_u16[ EE_RSCAN_CHANNEL0 ] = 
					( uint16_t )( ee_rscan_common_p[ UnitNumber_u08 ]->ch[ EE_RSCAN_CHANNEL0 ].erfll.err );
  			EE_RSCAN_CIVector[ EE_RSCAN_INT_GLOBAL + EE_RSCAN_INT_CERR + 
  												 ( EE_RSCAN_INT_CHANNEL * EE_RSCAN_CHANNEL0 ) ]( );
				ee_rscan_common_p[ UnitNumber_u08 ]->ch[ EE_RSCAN_CHANNEL0 ].erfll.err = EE_RSCAN_ERROR_CLEARALL;
				break;
			case EE_RSCAN_INT_TXHL:
				ee_rscan_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCAN_CHANNEL0 ].irq = 0;
				if( ee_rscan_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCAN_CHANNEL0 ].elt )
				{
					ee_rscan_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCAN_CHANNEL0 ].elt = 0;
					EE_RSCAN_LastErrorCode_Global_u08 = EE_RSCAN_GERROR_THLLOST;
					EE_RSCAN_CIVector[ EE_RSCAN_INT_GERR ]( );
				}
  			EE_RSCAN_CIVector[ EE_RSCAN_INT_GLOBAL + EE_RSCAN_INT_TXHL + 
  												 ( EE_RSCAN_INT_CHANNEL * EE_RSCAN_CHANNEL0 ) ]( );
				break;
			case EE_RSCAN_INT_RXCF:
      	FIFONumber_u08 = EE_RSCAN_GetComFIFOIntStatus( UnitNumber_u08, EE_RSCAN_CHANNEL0, EE_RSCAN_INT_RXCF );
      	if( FIFONumber_u08 == EE_RSCAN_GLOBAL ) break;
    		ee_rscan_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cfrxif = 0;
  			EE_RSCAN_CIVector[ EE_RSCAN_INT_GLOBAL + EE_RSCAN_INT_RXCF + 
  												 ( EE_RSCAN_INT_CHANNEL * EE_RSCAN_CHANNEL0 ) ]( );
				break;
			case EE_RSCAN_INT_TXCF:
      	FIFONumber_u08 = EE_RSCAN_GetComFIFOIntStatus( UnitNumber_u08, EE_RSCAN_CHANNEL0, EE_RSCAN_INT_TXCF );
      	if( FIFONumber_u08 == EE_RSCAN_GLOBAL ) break;
    		ee_rscan_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cftxif = 0;
  			EE_RSCAN_CIVector[ EE_RSCAN_INT_GLOBAL + EE_RSCAN_INT_TXCF + 
  												 ( EE_RSCAN_INT_CHANNEL * EE_RSCAN_CHANNEL0 ) ]( );
				break;
  	}
      EE_RSCAN_InterruptFlag_Channel0_u08 = EE_RSCAN_INT_NOINT;
  }
  else if( EE_RSCAN_InterruptFlag_Channel1_u08 != EE_RSCAN_INT_NOINT )
  {
  	EE_RSCAN_InterruptFlag_Channel_u08[ EE_RSCAN_CHANNEL1 ] =
  		EE_RSCAN_InterruptFlag_Channel1_u08;

  	switch( EE_RSCAN_InterruptFlag_Channel1_u08 )
  	{
  		case EE_RSCAN_INT_TX:
  			EE_RSCAN_LastTxObjectChannel1_u08 = 
  				EE_RSCAN_GetTxBuffer( ee_rscan_common_p[ UnitNumber_u08 ]->tmtcsts[ 0 ] >> ( EE_RSCAN_MAXTXBUFFERS + EE_RSCAN_COMSPAREBITS ));
  			if( EE_RSCAN_LastTxObjectChannel1_u08 != EE_RSCAN_INT_NOINT )
  			{
    			ee_rscan_common_p[ UnitNumber_u08 ]->tmsts[ EE_RSCAN_LastTxObjectChannel1_u08 
    			                              + EE_RSCAN_MAXTXBUFFERS ]
    			                      &= ( uint8_t )( ~( EE_RSCAN_TMSTS_RFMSK ) );
  				EE_RSCAN_CIVector[ EE_RSCAN_INT_GLOBAL + EE_RSCAN_INT_TX + 
  												 ( EE_RSCAN_INT_CHANNEL * EE_RSCAN_CHANNEL1 ) ]( );
  			}
  			break;
  		case EE_RSCAN_INT_TXA:
  			EE_RSCAN_LastTxObjectChannel1_u08 = 
  				EE_RSCAN_GetTxBuffer( ee_rscan_common_p[ UnitNumber_u08 ]->tmtasts[ 0 ] >> ( EE_RSCAN_MAXTXBUFFERS + EE_RSCAN_COMSPAREBITS ) );
  			if( EE_RSCAN_LastTxObjectChannel1_u08 != EE_RSCAN_INT_NOINT )
  			{
    			ee_rscan_common_p[ UnitNumber_u08 ]->tmsts[ EE_RSCAN_LastTxObjectChannel1_u08
    			                              + EE_RSCAN_MAXTXBUFFERS ]
    			                      &= ( uint8_t )( ~( EE_RSCAN_TMSTS_RFMSK ) );
  				EE_RSCAN_CIVector[ EE_RSCAN_INT_GLOBAL + EE_RSCAN_INT_TXA + 
  												 ( EE_RSCAN_INT_CHANNEL * EE_RSCAN_CHANNEL1 ) ]( );
  			}
  			break;
			case EE_RSCAN_INT_CERR:
				EE_RSCAN_LastErrorCode_Channel_u16[ EE_RSCAN_CHANNEL1 ] = 
					( uint16_t )( ee_rscan_common_p[ UnitNumber_u08 ]->ch[ EE_RSCAN_CHANNEL1 ].erfll.err );
  			EE_RSCAN_CIVector[ EE_RSCAN_INT_GLOBAL + EE_RSCAN_INT_CERR + 
  												 ( EE_RSCAN_INT_CHANNEL * EE_RSCAN_CHANNEL1 ) ]( );
				ee_rscan_common_p[ UnitNumber_u08 ]->ch[ EE_RSCAN_CHANNEL1 ].erfll.err = EE_RSCAN_ERROR_CLEARALL;
				break;
			case EE_RSCAN_INT_TXHL:
				ee_rscan_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCAN_CHANNEL1 ].irq = 0;
				if( ee_rscan_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCAN_CHANNEL1 ].elt )
				{
					ee_rscan_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCAN_CHANNEL1 ].elt = 0;
					EE_RSCAN_LastErrorCode_Global_u08 = EE_RSCAN_GERROR_THLLOST;
					EE_RSCAN_CIVector[ EE_RSCAN_INT_GERR ]( );
				}
  			EE_RSCAN_CIVector[ EE_RSCAN_INT_GLOBAL + EE_RSCAN_INT_TXHL + 
  												 ( EE_RSCAN_INT_CHANNEL * EE_RSCAN_CHANNEL1 ) ]( );
				break;
			case EE_RSCAN_INT_RXCF:
      	FIFONumber_u08 = EE_RSCAN_GetComFIFOIntStatus( UnitNumber_u08, EE_RSCAN_CHANNEL1, EE_RSCAN_INT_RXCF );
      	if( FIFONumber_u08 == EE_RSCAN_GLOBAL ) break;
    		ee_rscan_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cfrxif = 0;
  			EE_RSCAN_CIVector[ EE_RSCAN_INT_GLOBAL + EE_RSCAN_INT_RXCF + 
  												 ( EE_RSCAN_INT_CHANNEL * EE_RSCAN_CHANNEL1 ) ]( );
				break;
			case EE_RSCAN_INT_TXCF:
      	FIFONumber_u08 = EE_RSCAN_GetComFIFOIntStatus( UnitNumber_u08, EE_RSCAN_CHANNEL1, EE_RSCAN_INT_TXCF );
      	if( FIFONumber_u08 == EE_RSCAN_GLOBAL ) break;
    		ee_rscan_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cftxif = 0;
  			EE_RSCAN_CIVector[ EE_RSCAN_INT_GLOBAL + EE_RSCAN_INT_TXCF + 
  												 ( EE_RSCAN_INT_CHANNEL * EE_RSCAN_CHANNEL1 ) ]( );
				break;
  	}
      EE_RSCAN_InterruptFlag_Channel1_u08 = EE_RSCAN_INT_NOINT;
  }
}

/*
 * The peripheral Support Functions
 */

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
  
  return( EE_RSCAN_OK );
}

//=============================================================================
// FunctionName: EE_RSCAN_CreateInterrupt
// IN  :         Unit Number, Channel Number, Int Number, Int Level, 
//               Int Function Vector
// OUT :         Success Status
// Description : Enables and Sets Interrupt Vector to given Function
// 
//=============================================================================
uint8_t EE_RSCAN_CreateInterrupt( uint8_t  UnitNumber_u08,
                              uint8_t  ChannelNumber_u08,
                              uint8_t  IntNumber_u08,
                              uint16_t  SetIntLevel_u16,
                              void ( *FunctionVector )( ) )
{
  uint16_t IntLevel_u16 = SetIntLevel_u16;

  if( UnitNumber_u08 >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
  if( FunctionVector == NULL ) 
  {
    IntLevel_u16 = EE_RSCAN_INTCLEAR;
    FunctionVector = EE_RSCAN_IRQDefault;
  }

  if( ChannelNumber_u08 == EE_RSCAN_GLOBAL )
	{
      EE_RSCAN_CIVector[ UnitNumber_u08 * ( EE_RSCAN_CHANNELS * EE_RSCAN_INT_CHANNEL + 
                                            EE_RSCAN_INT_GLOBAL )
                                          + IntNumber_u08 ] = FunctionVector;
      
	  switch( UnitNumber_u08 )
        {
	  	case EE_RSCAN_0:
	    	switch( IntNumber_u08 ) 
	    	{
#if( defined( EE_RSCAN_INT_M0GERR ) )
            case EE_RSCAN_INT_GERR:
              EE_RSCAN_INT_M0GERR = IntLevel_u16;
              break;
#endif
#if( defined( EE_RSCAN_INT_M0RXF0 ) )
            case EE_RSCAN_INT_RXF0:
              EE_RSCAN_INT_M0RXF0 = IntLevel_u16;
              break;
#endif
#if( defined( EE_RSCAN_INT_M0RXF1 ) )
            case EE_RSCAN_INT_RXF1:
              EE_RSCAN_INT_M0RXF1 = IntLevel_u16;
              break;
#endif
#if( defined( EE_RSCAN_INT_M0RXF2 ) )
            case EE_RSCAN_INT_RXF2:
              EE_RSCAN_INT_M0RXF2 = IntLevel_u16;
              break;
#endif
#if( defined( EE_RSCAN_INT_M0RXF3 ) )
            case EE_RSCAN_INT_RXF3:
              EE_RSCAN_INT_M0RXF3 = IntLevel_u16;
              break;
#endif
	    	}
				break;

	  	case EE_RSCAN_1:
	    	switch( IntNumber_u08 ) 
	    	{
#if( defined( EE_RSCAN_INT_M1GERR ) )
            case EE_RSCAN_INT_GERR:
              EE_RSCAN_INT_M1GERR = IntLevel_u16;
              break;
#endif
#if( defined( EE_RSCAN_INT_M1RXF0 ) )
            case EE_RSCAN_INT_RXF0:
              EE_RSCAN_INT_M1RXF0 = IntLevel_u16;
              break;
#endif
#if( defined( EE_RSCAN_INT_M1RXF1 ) )
            case EE_RSCAN_INT_RXF1:
              EE_RSCAN_INT_M1RXF1 = IntLevel_u16;
              break;
#endif
#if( defined( EE_RSCAN_INT_M1RXF2 ) )
            case EE_RSCAN_INT_RXF2:
              EE_RSCAN_INT_M1RXF2 = IntLevel_u16;
              break;
#endif
#if( defined( EE_RSCAN_INT_M1RXF3 ) )
            case EE_RSCAN_INT_RXF3:
              EE_RSCAN_INT_M1RXF3 = IntLevel_u16;
              break;
#endif
	    	}

	    default:
		    return( EE_RSCAN_ERROR );
		}
	}
	else
	{
	  if( ChannelNumber_u08 >= EE_RSCAN_CHANNELS ) return( EE_RSCAN_ERROR );
	  
    EE_RSCAN_CIVector[ UnitNumber_u08 * ( EE_RSCAN_CHANNELS * EE_RSCAN_INT_CHANNEL + 
                                          EE_RSCAN_INT_GLOBAL )
                                        + ChannelNumber_u08 * EE_RSCAN_INT_CHANNEL
                                        + EE_RSCAN_INT_GLOBAL
										                    + IntNumber_u08 ] = FunctionVector;
	  switch( UnitNumber_u08 )
    {
	  	case EE_RSCAN_0:
        switch( ChannelNumber_u08 )
	  		{
          case EE_RSCAN_CHANNEL0:
            switch( IntNumber_u08 ) 
            {
#if( defined( EE_RSCAN_INT_M0TX0 ) )
              case EE_RSCAN_INT_TX:
                EE_RSCAN_INT_M0TX0 = IntLevel_u16;
               break;
#endif
#if( defined( EE_RSCAN_INT_M0TXA0 ) )
               case EE_RSCAN_INT_TXA:
                EE_RSCAN_INT_M0TXA0 = IntLevel_u16;
               break;
#endif
#if( defined( EE_RSCAN_INT_M0ERR0 ) )
               case EE_RSCAN_INT_CERR:
                EE_RSCAN_INT_M0ERR0 = IntLevel_u16;
               break;
#endif
#if( defined( EE_RSCAN_INT_M0THL0 ) )
               case EE_RSCAN_INT_TXHL:
                EE_RSCAN_INT_M0THL0 = IntLevel_u16;
			 break;
#endif
#if( defined( EE_RSCAN_INT_M0RXCF0 ) )
               case EE_RSCAN_INT_RXCF:
                EE_RSCAN_INT_M0RXCF0 = IntLevel_u16;
               break;
#endif
#if( defined( EE_RSCAN_INT_M0TXCF0 ) )
               case EE_RSCAN_INT_TXCF:
                EE_RSCAN_INT_M0TXCF0 = IntLevel_u16;
               break;
#endif
            }
            break;
              
          case EE_RSCAN_CHANNEL1:
            switch( IntNumber_u08 ) 
            {
#if( defined( EE_RSCAN_INT_M0TX1 ) )
              case EE_RSCAN_INT_TX:
                EE_RSCAN_INT_M0TX1 = IntLevel_u16;
               break;
#endif
#if( defined( EE_RSCAN_INT_M0TXA1 ) )
               case EE_RSCAN_INT_TXA:
                EE_RSCAN_INT_M0TXA1 = IntLevel_u16;
               break;
#endif
#if( defined( EE_RSCAN_INT_M0ERR1 ) )
               case EE_RSCAN_INT_CERR:
                EE_RSCAN_INT_M0ERR1 = IntLevel_u16;
               break;
#endif
#if( defined( EE_RSCAN_INT_M0THL1 ) )
               case EE_RSCAN_INT_TXHL:
                EE_RSCAN_INT_M0THL1 = IntLevel_u16;
               break;
#endif
#if( defined( EE_RSCAN_INT_M0RXCF1 ) )
			 case EE_RSCAN_INT_RXCF:
                EE_RSCAN_INT_M0RXCF1 = IntLevel_u16;
               break;
#endif
#if( defined( EE_RSCAN_INT_M0TXCF1 ) )
               case EE_RSCAN_INT_TXCF:
                EE_RSCAN_INT_M0TXCF1 = IntLevel_u16;
               break;
#endif
            }
            break;

	    default:
		    return( EE_RSCAN_ERROR );
		  }
		  break;
		
	  	case EE_RSCAN_1:
        switch( ChannelNumber_u08 )
	  		{
          case EE_RSCAN_CHANNEL0:
            switch( IntNumber_u08 ) 
              {
#if( defined( EE_RSCAN_INT_M1TX0 ) )
              case EE_RSCAN_INT_TX:
                EE_RSCAN_INT_M1TX0 = IntLevel_u16;
               break;
#endif
#if( defined( EE_RSCAN_INT_M1TXA0 ) )
               case EE_RSCAN_INT_TXA:
                EE_RSCAN_INT_M1TXA0 = IntLevel_u16;
               break;
#endif
#if( defined( EE_RSCAN_INT_M1ERR0 ) )
               case EE_RSCAN_INT_CERR:
                EE_RSCAN_INT_M1ERR0 = IntLevel_u16;
               break;
#endif
#if( defined( EE_RSCAN_INT_M1THL0 ) )
               case EE_RSCAN_INT_TXHL:
                EE_RSCAN_INT_M1THL0 = IntLevel_u16;
			         break;
#endif
#if( defined( EE_RSCAN_INT_M1RXCF0 ) )
               case EE_RSCAN_INT_RXCF:
                EE_RSCAN_INT_M1RXCF0 = IntLevel_u16;
               break;
#endif
#if( defined( EE_RSCAN_INT_M1TXCF0 ) )
               case EE_RSCAN_INT_TXCF:
                EE_RSCAN_INT_M1TXCF0 = IntLevel_u16;
               break;
#endif
            }
            break;

          case EE_RSCAN_CHANNEL1:
            switch( IntNumber_u08 ) 
            {
#if( defined( EE_RSCAN_INT_M1TX1 ) )
              case EE_RSCAN_INT_TX:
                EE_RSCAN_INT_M1TX1 = IntLevel_u16;
               break;
#endif
#if( defined( EE_RSCAN_INT_M1TXA1 ) )
               case EE_RSCAN_INT_TXA:
                EE_RSCAN_INT_M1TXA1 = IntLevel_u16;
               break;
#endif
#if( defined( EE_RSCAN_INT_M1ERR1 ) )
               case EE_RSCAN_INT_CERR:
                EE_RSCAN_INT_M1ERR1 = IntLevel_u16;
               break;
#endif
#if( defined( EE_RSCAN_INT_M1THL1 ) )
               case EE_RSCAN_INT_TXHL:
                EE_RSCAN_INT_M1THL1 = IntLevel_u16;
               break;
#endif
#if( defined( EE_RSCAN_INT_M1RXCF1 ) )
			 case EE_RSCAN_INT_RXCF:
                EE_RSCAN_INT_M1RXCF1 = IntLevel_u16;
               break;
#endif
#if( defined( EE_RSCAN_INT_M1TXCF1 ) )
               case EE_RSCAN_INT_TXCF:
                EE_RSCAN_INT_M1TXCF1 = IntLevel_u16;
               break;
#endif
            }
            break;
	    
	    default:
		    return( EE_RSCAN_ERROR );
  	  }
  	  break;
  	}
  }
  return( EE_RSCAN_OK );
}

//=============================================================================
// FunctionName: EE_RSCAN_SetInterrupt
// IN  :         UnitNumber, Channel Number, Int Mask
// OUT :         Success Status
// Description : Enables or disables dedicated Interrupts
// 
//=============================================================================
uint8_t EE_RSCAN_SetInterrupt( uint8_t UnitNumber_u08,
                           uint8_t ChannelNumber_u08,
                           uint8_t InterruptSelection_u08,
                           uint16_t InterruptSubSelection_u16 )
{
  uint8_t RegIndex_u08;
  uint8_t RegPos_u08;
  uint16_t RegBits_u16;
	
  if( UnitNumber_u08 >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
  	
  if( ChannelNumber_u08 == EE_RSCAN_GLOBAL )
  {
  	switch( InterruptSelection_u08 )
    {
      case EE_RSCAN_INT_GERR:
        ee_rscan_common_p[ UnitNumber_u08 ]->gctrl.ie = 
          InterruptSubSelection_u16;
        break;
      default:   /* RX FIFO Interrupt selected */
        if( InterruptSelection_u08 > EE_RSCAN_MAXRXFIFOS )
          return( EE_RSCAN_ERROR );
        ee_rscan_common_p[ UnitNumber_u08 ]->rfcc
                         [ InterruptSelection_u08 - EE_RSCAN_INT_RXF0 ].rfie = 
                         InterruptSubSelection_u16;
        break;
  	}
  }
  else
  {
    if( ChannelNumber_u08 >= EE_RSCAN_CHANNELS ) return( EE_RSCAN_ERROR );
		
    switch( InterruptSelection_u08 )
    {
      case EE_RSCAN_INT_TX:
      case EE_RSCAN_INT_TXA:
        RegIndex_u08 = ChannelNumber_u08 * ( EE_RSCAN_MAXTXBUFFERS + EE_RSCAN_COMSPAREBITS )
                                           / EE_RSCAN_COMREGSBITS;
        RegPos_u08   = ChannelNumber_u08 * ( EE_RSCAN_MAXTXBUFFERS + EE_RSCAN_COMSPAREBITS ) - 
                       RegIndex_u08      * EE_RSCAN_COMREGSBITS;
        if( InterruptSubSelection_u16 == EE_RSCAN_INT_NOINT )  /* clears all */
        {
          RegBits_u16 = ( uint16_t )( ( 1 << EE_RSCAN_MAXTXBUFFERS ) - 1 ) << RegPos_u08;
          ee_rscan_common_p[ UnitNumber_u08 ]->tmiec[ RegIndex_u08 ] &= ~RegBits_u16;
        }
        else  /* Sub selection defines the Tx Buffer IRQ to be enabled */
        {
          if( InterruptSubSelection_u16 >= EE_RSCAN_MAXTXBUFFERS ) 
            return( EE_RSCAN_ERROR );
          RegBits_u16 = ( uint16_t )( 1 << ( ( uint8_t )InterruptSubSelection_u16 + RegPos_u08 ) );
          ee_rscan_common_p[ UnitNumber_u08 ]->tmiec[ RegIndex_u08 ] |= RegBits_u16;
        }
        break;
      case EE_RSCAN_INT_CERR:
        if( InterruptSubSelection_u16 & EE_RSCAN_CINT_TXABORT )
        {
          ee_rscan_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ctrh.ieh =
            EE_RSCAN_SET;
        }
        ee_rscan_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ctrl.iel =
          InterruptSubSelection_u16;
        break;
      case EE_RSCAN_INT_TXHL:
        ee_rscan_common_p[ UnitNumber_u08 ]->thlcc[ ChannelNumber_u08 ].ie =
          InterruptSubSelection_u16;
        break;
      case EE_RSCAN_INT_RXCF:
        if( InterruptSubSelection_u16 == EE_RSCAN_INT_NOINT )  /* clears all of channel */
        {
          for( RegIndex_u08 = ( ChannelNumber_u08 * EE_RSCAN_MAXCOMFIFOS );
               RegIndex_u08 < ( ( ChannelNumber_u08 + 1 ) * EE_RSCAN_MAXCOMFIFOS );
               RegIndex_u08++ )
          {
            ee_rscan_common_p[ UnitNumber_u08 ]->cfcc[ RegIndex_u08 ].l.cfrxie = 
              EE_RSCAN_INT_DISABLE;
          }
        }
        else  /* Sub Index selects the COM FIFO number per channel */
        {
          RegIndex_u08 = ( ChannelNumber_u08 * EE_RSCAN_MAXCOMFIFOS ) + 
            InterruptSubSelection_u16;
          ee_rscan_common_p[ UnitNumber_u08 ]->cfcc[ RegIndex_u08 ].l.cfrxie = 
            EE_RSCAN_INT_ENABLE;
        }
        break;
      case EE_RSCAN_INT_TXCF:
        if( InterruptSubSelection_u16 == EE_RSCAN_INT_NOINT )  /* clears all */
        {
          for( RegIndex_u08 = ( ChannelNumber_u08 * EE_RSCAN_MAXCOMFIFOS );
               RegIndex_u08 < ( ( ChannelNumber_u08 + 1 ) * EE_RSCAN_MAXCOMFIFOS );
               RegIndex_u08++ )
            {
              ee_rscan_common_p[ UnitNumber_u08 ]->cfcc[ RegIndex_u08 ].l.cftxie = 
                EE_RSCAN_INT_DISABLE;
            }
        }
        else  /* Sub Index selects the COM FIFO number per channel */
        {
          RegIndex_u08 = ( ChannelNumber_u08 * EE_RSCAN_MAXCOMFIFOS ) + 
            InterruptSubSelection_u16;
          ee_rscan_common_p[ UnitNumber_u08 ]->cfcc[ RegIndex_u08 ].l.cftxie = 
            EE_RSCAN_INT_ENABLE;
        }
        break;
      }
  }
  
  return( EE_RSCAN_OK );
}    

//=============================================================================
// FunctionName: EE_RSCAN_GetError
// IN  :         UnitNumber, Channel Number
// OUT :         Success Status, Error States
// Description : Returns global or channel local error states
// 
//=============================================================================
uint8_t EE_RSCAN_GetError( uint8_t  UnitNumber_u08,
                       uint8_t  ChannelNumber_u08,
                       puint16_t InterruptErrorFlag_pu16,
                       puint16_t LastErrorFlag_pu16 )
{
  if( UnitNumber_u08 >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );

  if( ChannelNumber_u08 == EE_RSCAN_GLOBAL )
  {
      *InterruptErrorFlag_pu16 = ( ( UnitNumber_u08 == EE_RSCAN_InterruptFlag_Unit_u08 ) ? 
                                 ( uint16_t )EE_RSCAN_LastErrorCode_Global_u08 : EE_RSCAN_INT_NOINT );
      *LastErrorFlag_pu16      = ( uint16_t )( ee_rscan_common_p[ UnitNumber_u08 ]->gerfl.err );  	
	}
  else
	{
      if( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) return( EE_RSCAN_ERROR );
      
      *InterruptErrorFlag_pu16 = ( ( UnitNumber_u08 == EE_RSCAN_InterruptFlag_Unit_u08 ) ?
                                 EE_RSCAN_LastErrorCode_Channel_u16[ ChannelNumber_u08 ] : 
                                 EE_RSCAN_INT_NOINT );
      *LastErrorFlag_pu16      = ee_rscan_common_p[ UnitNumber_u08 ]->ch
                                                  [ ChannelNumber_u08 ].erfll.err;  	
	}  
  
  return( EE_RSCAN_OK );
}

//=============================================================================
// FunctionName: EE_RSCAN_GetStatus
// IN  :         UnitNumber, Channel Number
// OUT :         Success Status, Channel Status Values
// Description : Returns channel local status information flags
// 
//=============================================================================
uint8_t EE_RSCAN_GetStatus( uint8_t  UnitNumber_u08,
                     	  uint8_t  ChannelNumber_u08,
                     		uint8_t  StatusNumber_u08,
                     		puint8_t StatusValue_u08 )
{
  static uint8_t LocalStatusValue_THL;

  if( UnitNumber_u08 >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
  if( ( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) &&
  		( ChannelNumber_u08 != EE_RSCAN_GLOBAL ) )return( EE_RSCAN_ERROR );

  switch( StatusNumber_u08 )
  {
    case EE_RSCAN_STATUS_OPMODE:              /* Operation mode of channel */
      ( ( ChannelNumber_u08 == EE_RSCAN_GLOBAL ) ?
        ( *StatusValue_u08 = ( uint8_t ) ee_rscan_common_p[ UnitNumber_u08 ]->gsts.mds ) :
        ( *StatusValue_u08 = ( uint8_t ) ee_rscan_common_p[ UnitNumber_u08 ]->ch
          [ ChannelNumber_u08 ].stsl.mds ) );
      break;  

    case EE_RSCAN_STATUS_PSMODE:              /* Operation mode of channel */
      ( ( ChannelNumber_u08 == EE_RSCAN_GLOBAL  ) ?
  	  	( *StatusValue_u08 = ( uint8_t ) ee_rscan_common_p[ UnitNumber_u08 ]->gsts.slps ) :
  	  	( *StatusValue_u08 = ( uint8_t ) ee_rscan_common_p[ UnitNumber_u08 ]->ch
          [ ChannelNumber_u08 ].stsl.slps ) );
      break;  
            
    case EE_RSCAN_STATUS_RECEIVE:        /* indicates channel is receiving */
      if( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) 
        return( EE_RSCAN_ERROR );
      *StatusValue_u08 = ( uint8_t ) ee_rscan_common_p[ UnitNumber_u08 ]->ch
                                                  [ ChannelNumber_u08 ].stsl.recs;
      break;
            
    case EE_RSCAN_STATUS_TRANSMIT:        /* indicates channel is sending */
      if( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) 
        return( EE_RSCAN_ERROR );
      *StatusValue_u08 = ( uint8_t ) ee_rscan_common_p[ UnitNumber_u08 ]->ch
                                                  [ ChannelNumber_u08 ].stsl.trxs;
      break;
            
    case EE_RSCAN_STATUS_BUSOFF:         /* indicates channel is bus off */
      if( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) 
        return( EE_RSCAN_ERROR );
      *StatusValue_u08 = ( uint8_t ) ee_rscan_common_p[ UnitNumber_u08 ]->ch
                                                  [ ChannelNumber_u08 ].stsl.boffs;
      break;

    case EE_RSCAN_STATUS_ERRCNTLEV:                       /* error level */
      if( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) 
        return( EE_RSCAN_ERROR );
      *StatusValue_u08 = ( uint8_t )( ee_rscan_common_p[ UnitNumber_u08 ]->ch
                                                   [ ChannelNumber_u08 ].erfll.err &
                                                   ( EE_RSCAN_ERROR_WARNING |
                                                     EE_RSCAN_ERROR_PASSIVE |
                                                     EE_RSCAN_ERROR_BUSOFF ) );
      break;
            
    case EE_RSCAN_STATUS_TOVF:               /* send history overrun flag */
      if( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) 
        return( EE_RSCAN_ERROR );
      *StatusValue_u08 = ( uint8_t ) ee_rscan_common_p[ UnitNumber_u08 ]->thlsts
                                                  [ ChannelNumber_u08 ].elt;
      if( *StatusValue_u08 )
      {
        ee_rscan_common_p[ UnitNumber_u08 ]->thlsts[ ChannelNumber_u08 ].elt = 0;
      }
      break;

    case EE_RSCAN_STATUS_THPM:                 /* send history empty flag */
      if( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) 
        return( EE_RSCAN_ERROR );
      *StatusValue_u08 = ( uint8_t ) ee_rscan_common_p[ UnitNumber_u08 ]->thlsts
                                                  [ ChannelNumber_u08 ].emp;
      break;

    case EE_RSCAN_STATUS_TGPT:                    /* send history pointer */
      if( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) 
        return( EE_RSCAN_ERROR );
      if( !ee_rscan_common_p[ UnitNumber_u08 ]->thlsts[ ChannelNumber_u08 ].emp )
      {
        LocalStatusValue_THL = ( uint8_t )ee_rscan_thl_p[ UnitNumber_u08 ]
                                                    [ ChannelNumber_u08 ]->tid;
        if( LocalStatusValue_THL == EE_RSCAN_TID_NOTUSED )
        {
          LocalStatusValue_THL =  ( uint8_t )( ee_rscan_thl_p[ UnitNumber_u08 ]
                                                         [ ChannelNumber_u08 ]->bt );
          LocalStatusValue_THL += ( uint8_t )( ee_rscan_thl_p[ UnitNumber_u08 ]
                                                         [ ChannelNumber_u08 ]->bn 
                                                         << EE_RSCAN_THL_BN_P );
        }
        *StatusValue_u08 = LocalStatusValue_THL;
      }
      else
      {
        *StatusValue_u08 = EE_RSCAN_TID_NOTUSED;
      }
      break;
            
    case EE_RSCAN_STATUS_NEWTXHISTORY:               /* get next THL entry */
      if( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) 
        return( EE_RSCAN_ERROR );
      ee_rscan_common_p[ UnitNumber_u08 ]->thlpctr[ ChannelNumber_u08 ] = 
            EE_RSCAN_THL_NEXTELEMENT;
      break;

    case EE_RSCAN_STATUS_VALID:        /* channel has received sucessfully */
      if( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) 
        return( EE_RSCAN_ERROR );
      *StatusValue_u08 = ( uint8_t ) ee_rscan_common_p[ UnitNumber_u08 ]->ch
                                                  [ ChannelNumber_u08 ].stsl.coms;
      break;
            
    case EE_RSCAN_STATUS_TRERRCOUNT:       /* transmit error counter value */
      if( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) 
        return( EE_RSCAN_ERROR );
      *StatusValue_u08 = ( uint8_t ) ee_rscan_common_p[ UnitNumber_u08 ]->ch
                                                  [ ChannelNumber_u08 ].stsh.tec;
      break;

    case EE_RSCAN_STATUS_RXERRCOUNT:       /* receive error counter value */
      if( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) 
        return( EE_RSCAN_ERROR );
      *StatusValue_u08 = ( uint8_t ) ee_rscan_common_p[ UnitNumber_u08 ]->ch
                                                  [ ChannelNumber_u08 ].stsh.rec;
      break;
            
    case EE_RSCAN_STATUS_ERRPLEV:                /* error counter passive */
      if( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) 
        return( EE_RSCAN_ERROR );
      *StatusValue_u08 = ( uint8_t ) ee_rscan_common_p[ UnitNumber_u08 ]->ch
                                                  [ ChannelNumber_u08 ].stsl.eps;
      break;

    case EE_RSCAN_STATUS_INT_RXFIFO:
      *StatusValue_u08 = ( uint8_t )ee_rscan_common_p[ UnitNumber_u08 ]->rfists;
      break;
          
    case EE_RSCAN_STATUS_INTERRUPT:
      if( ChannelNumber_u08 == EE_RSCAN_GLOBAL )
      {
        if( UnitNumber_u08 == EE_RSCAN_InterruptFlag_Unit_u08 )
        {
          *StatusValue_u08 = EE_RSCAN_InterruptFlag_Global_u08;
          EE_RSCAN_InterruptFlag_Global_u08 = EE_RSCAN_INT_NOINT;
        }
        else
        {
          *StatusValue_u08 = EE_RSCAN_INT_NOINT;
        }
      }
      else
      {
        if( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) 
          return( EE_RSCAN_ERROR );
        if( UnitNumber_u08 == EE_RSCAN_InterruptFlag_Unit_u08 )
        {
          *StatusValue_u08 = EE_RSCAN_InterruptFlag_Channel_u08[ ChannelNumber_u08 ];
          EE_RSCAN_InterruptFlag_Channel_u08[ ChannelNumber_u08 ] = EE_RSCAN_INT_NOINT;
        }
        else
        {
          *StatusValue_u08 = EE_RSCAN_INT_NOINT;
        }
      }
      break;

    default: return( EE_RSCAN_ERROR );

  } // end switch( StatusNumber_u08 )
    
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
    
  if( ee_rscan_common_p[ UnitNumber_u08 ]->gsts.slps )  /* activate the unit */
  {
    ee_rscan_common_p[ UnitNumber_u08 ]->gctrl.gslpr = EE_RSCAN_SLEEP_DISABLE;
  }

  /* go globally to OPERATION */

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
      
    /* channels: cancel any sleep states */
    
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
      
    if( OperationMode_u08 == EE_RSCAN_OPMODE_OPER )    /* verify communication ready state */
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
// FunctionName: EE_RSCAN_SetGlobalConfiguration
// IN  :         UnitNumber, Global configuration set
// Description : Performs Global Configurations
// 
//=============================================================================

uint8_t EE_RSCAN_SetGlobalConfiguration( uint8_t UnitNumber_u08,
                                     const struct ee_rscan_cfg_global *Config )
{    
  if( UnitNumber_u08 >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );

  /* Must be in global reset to set the global configuration! */
  
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
// FunctionName: EE_RSCAN_SetBittiming
// IN  :         InputFrequency, Bitrate, TQ per Bit, Sampling Point, SJW
// OUT :         Main Prescaler Setting, Bit Rate Prescaler Setting, Bit Timing
// Description : Calculates Settings from Clock Supply and Parameters
// 
//=============================================================================

uint8_t EE_RSCAN_SetBittiming( uint8_t  UnitNumber_u08,
                           uint32_t  InputFrequency_u32,
                           uint32_t  Bitrate_u32,
                           uint8_t  TQPerBit_u08,         // optional Parameter, can be 0
                           uint8_t  SyncJumpWidth_u08,    // optional Parameter, can be 0
                           puint16_t BRPSetting_pu16,
                           puint8_t TSEG1Setting_pu08,
                           puint8_t TSEG2Setting_pu08,
                           puint8_t SJWSetting_pu08,
                           float  SamplingPointPos_flt ) // optional Parameter, can be 0.0
{
  uint16_t TQPerBitUsed_u16 = ( uint16_t )TQPerBit_u08;
  uint16_t TQPerBitMinDeviation_u16;
  uint16_t BRPSettingUsed_u16;
  uint8_t TSEG1SettingUsed_u16;
  uint8_t TSEG2SettingUsed_u16;
  float SamplingPointPosUsed_flt = SamplingPointPos_flt;
  uint32_t BitrateAchieved_u32;
  int32_t MinBitrateDeviation_s32;
  int32_t BitrateDeviation_s32;

  /* Automatic settings generation */

  if( TQPerBit_u08 == 0 ) 
    TQPerBitUsed_u16 = ( uint16_t )( InputFrequency_u32 / 
                                ( Bitrate_u32 * EE_RSCAN_TRLAYERFACTOR ) );
  if( TQPerBitUsed_u16 > EE_RSCAN_BT_MAXTQ ) TQPerBitUsed_u16 = EE_RSCAN_BT_MAXTQ;
  if( TQPerBitUsed_u16 < EE_RSCAN_BT_MINTQ ) return( EE_RSCAN_ERROR );

  if( SamplingPointPos_flt == 0.0 ) SamplingPointPosUsed_flt = EE_RSCAN_BT_SPTOPTIMUM;

  /* Other plausibility checks */
  
  if( ( SyncJumpWidth_u08 != 0 ) && ( ( SyncJumpWidth_u08 < EE_RSCAN_BT_MINSJW ) ||
                                      ( SyncJumpWidth_u08 > EE_RSCAN_BT_MAXSJW ) ) ) 
    return( EE_RSCAN_ERROR );

  if( ( InputFrequency_u32 / Bitrate_u32 ) < EE_RSCAN_CLKMINFACTOR )
    return( EE_RSCAN_ERROR );
  
  /* Maximum Bitrate check */

  if( ( InputFrequency_u32 / 
      ( ( uint32_t )TQPerBitUsed_u16 * EE_RSCAN_TRLAYERFACTOR ) ) < Bitrate_u32 )
    return( EE_RSCAN_ERROR );

  /* Minimum Bitrate check */

  if( ( InputFrequency_u32 / 
      ( ( uint32_t )TQPerBitUsed_u16 * EE_RSCAN_TRLAYERFACTOR * Bitrate_u32 ) ) >
      EE_RSCAN_BT_MAXBRP )
    return( EE_RSCAN_ERROR );

  /* Maximum Prescaler check */

  BRPSettingUsed_u16 = ( uint16_t )( InputFrequency_u32 / 
                              ( Bitrate_u32 *
                              ( uint32_t )TQPerBitUsed_u16 * 
                              EE_RSCAN_TRLAYERFACTOR ) );

  /* Frequency rounding optimization */
  
  BitrateAchieved_u32 = ( uint32_t )InputFrequency_u32 / 
                      ( ( uint32_t ) ( ( uint32_t )BRPSettingUsed_u16 *
                        ( uint32_t )TQPerBitUsed_u16 *
                        ( uint32_t )EE_RSCAN_TRLAYERFACTOR ) );

  MinBitrateDeviation_s32 = ( int32_t )( BitrateAchieved_u32 - Bitrate_u32 );
  if( MinBitrateDeviation_s32 < 0L ) 
    MinBitrateDeviation_s32 = -MinBitrateDeviation_s32;
  BitrateDeviation_s32    = MinBitrateDeviation_s32;

  while( BitrateAchieved_u32 != Bitrate_u32 )
  {
    TQPerBitUsed_u16--;
    if( TQPerBitUsed_u16 < EE_RSCAN_BT_MINTQ ) break;
     
    BRPSettingUsed_u16 = ( uint16_t )( InputFrequency_u32 / 
                                ( Bitrate_u32 *
                         ( uint32_t )TQPerBitUsed_u16 * 
                                EE_RSCAN_TRLAYERFACTOR ) );

    if( BRPSettingUsed_u16 > EE_RSCAN_BT_MAXBRP )
      return( EE_RSCAN_ERROR );
        
    BitrateAchieved_u32 = ( uint32_t )InputFrequency_u32 / 
                        ( ( uint32_t ) ( ( uint32_t )BRPSettingUsed_u16 *
                          ( uint32_t )TQPerBitUsed_u16 *
                          ( uint32_t )EE_RSCAN_TRLAYERFACTOR ) );

    BitrateDeviation_s32 = ( int32_t )( BitrateAchieved_u32 - Bitrate_u32 );
    if( BitrateDeviation_s32 < 0L ) BitrateDeviation_s32 = -BitrateDeviation_s32;
    if( BitrateDeviation_s32 < MinBitrateDeviation_s32 )
    {
      MinBitrateDeviation_s32  = BitrateDeviation_s32;
      TQPerBitMinDeviation_u16 = TQPerBitUsed_u16;
    }
  }

  if( BitrateAchieved_u32 != Bitrate_u32 )  /* Optimum Bitrate was not found */
  {
    TQPerBitUsed_u16 = TQPerBitMinDeviation_u16;   /* use the best value instead */
    BRPSettingUsed_u16 = ( uint16_t )( InputFrequency_u32 / 
                                ( Bitrate_u32 *
                         ( uint32_t )TQPerBitUsed_u16 * 
                                EE_RSCAN_TRLAYERFACTOR ) );
  }

  /* Sampling Point setting and segment splitting */

  TSEG1SettingUsed_u16 = ( uint16_t )( ( float )( TQPerBitUsed_u16 - EE_RSCAN_BT_SYNCSEGLEN ) 
                                         * SamplingPointPosUsed_flt );
  if( TSEG1SettingUsed_u16 < EE_RSCAN_BT_MINTSEG1 ) TSEG1SettingUsed_u16 = EE_RSCAN_BT_MINTSEG1;
  if( TSEG1SettingUsed_u16 > EE_RSCAN_BT_MAXTSEG1 ) TSEG1SettingUsed_u16 = EE_RSCAN_BT_MAXTSEG1;

  TSEG2SettingUsed_u16 = TQPerBitUsed_u16 - TSEG1SettingUsed_u16 - EE_RSCAN_BT_SYNCSEGLEN;
  if( TSEG2SettingUsed_u16 > EE_RSCAN_BT_MAXTSEG2 ) TSEG2SettingUsed_u16 = EE_RSCAN_BT_MAXTSEG2;
  if( TSEG2SettingUsed_u16 < EE_RSCAN_BT_MINTSEG2 ) TSEG2SettingUsed_u16 = EE_RSCAN_BT_MINTSEG2;

  TSEG1SettingUsed_u16 = TQPerBitUsed_u16 - TSEG2SettingUsed_u16 - EE_RSCAN_BT_SYNCSEGLEN;
  if( ( TSEG1SettingUsed_u16 < EE_RSCAN_BT_MINTSEG1 ) ||
      ( TSEG1SettingUsed_u16 > EE_RSCAN_BT_MAXTSEG1 ) ) return( EE_RSCAN_ERROR );

  /* Synchronisation Jump Width setting */
  
  if( ( SyncJumpWidth_u08 > ( uint8_t )TSEG2SettingUsed_u16 ) ||
      ( SyncJumpWidth_u08 == 0 ) )
  {
    *SJWSetting_pu08 = ( uint8_t )TSEG2SettingUsed_u16 - 1;
    if( *SJWSetting_pu08 >= EE_RSCAN_BT_MAXSJW )
    	*SJWSetting_pu08 = EE_RSCAN_BT_MAXSJW - 1;
  }
  else
  {
    *SJWSetting_pu08 = EE_RSCAN_BT_MAXSJW - 1;
  }

  /* Definition of Register Values */

  *BRPSetting_pu16   = ( uint16_t )( BRPSettingUsed_u16 - 1 );
  *TSEG1Setting_pu08 = ( uint8_t )( TSEG1SettingUsed_u16 - 1 );
  *TSEG2Setting_pu08 = ( uint8_t )( TSEG2SettingUsed_u16 - 1 );

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

  /* first, clear any sleep mode */
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

	/* Set Channel to HALT mode, in order to configure lists */

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
// FunctionName: EE_RSCAN_SetGlobalFIFOConfiguration
// IN  :         UnitNumber, Global configuration set
// Description : Performs Global Configurations
//
//=============================================================================

uint8_t EE_RSCAN_SetGlobalFIFOConfiguration( uint8_t UnitNumber_u08, 
                                         const struct ee_rscan_cfg_global *Config ) 
{
  uint8_t CurrentFIFO_u08;

  if( UnitNumber_u08 >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );

  /* Must be in global reset to set the global configuration! */

  if( ee_rscan_common_p[ UnitNumber_u08 ]->gsts.mds != EE_RSCAN_OPMODE_RESET ) return( EE_RSCAN_ERROR );
  if( ee_rscan_common_p[ UnitNumber_u08 ]->gsts.slps != 0 ) return( EE_RSCAN_ERROR );

  for( CurrentFIFO_u08 = 0; CurrentFIFO_u08 < EE_RSCAN_MAXRXFIFOS; CurrentFIFO_u08++ ) 
  {
    ee_rscan_common_p[ UnitNumber_u08 ]->rfcc[ CurrentFIFO_u08 ].rfie =   Config->rfcc[ CurrentFIFO_u08 ].rfie;
    ee_rscan_common_p[ UnitNumber_u08 ]->rfcc[ CurrentFIFO_u08 ].rfdc =   Config->rfcc[ CurrentFIFO_u08 ].rfdc;
    ee_rscan_common_p[ UnitNumber_u08 ]->rfcc[ CurrentFIFO_u08 ].rfim =   Config->rfcc[ CurrentFIFO_u08 ].rfim;
    ee_rscan_common_p[ UnitNumber_u08 ]->rfcc[ CurrentFIFO_u08 ].rfigcv = Config->rfcc[ CurrentFIFO_u08 ].rfigcv;
  }
  return( EE_RSCAN_OK );
}

//=============================================================================
// FunctionName: EE_RSCAN_SetCOMFIFOConfiguration
// IN  :         UnitNumber, Channel Number, Config Set
// OUT :         Success Status
// Description : Performs Channel COM FIFO Configurations
//
//=============================================================================

uint8_t EE_RSCAN_SetCOMFIFOConfiguration( uint8_t UnitNumber_u08,
                                      uint8_t ChannelNumber_u08,
                                      const struct ee_rscan_cfg_channel *Config )
{  
  uint8_t TXCounter_u08;
  
  if( UnitNumber_u08 >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );

  /* Must be in global reset to set the global configuration! */
  
  if( ee_rscan_common_p[ UnitNumber_u08 ]->gsts.mds != EE_RSCAN_OPMODE_RESET )
    return( EE_RSCAN_ERROR );

  for( TXCounter_u08 = 0;
       TXCounter_u08 < EE_RSCAN_MAXCOMFIFOS;
       TXCounter_u08++ )
  {
    ee_rscan_common_p[ UnitNumber_u08 ]->
      cfcc[ TXCounter_u08 + ChannelNumber_u08 * EE_RSCAN_MAXCOMFIFOS ].l.cfrxie =
      Config->cfcc[ TXCounter_u08 ].l.cfrxie;
    ee_rscan_common_p[ UnitNumber_u08 ]->
      cfcc[ TXCounter_u08 + ChannelNumber_u08 * EE_RSCAN_MAXCOMFIFOS ].l.cftxie =
      Config->cfcc[ TXCounter_u08 ].l.cftxie;
    ee_rscan_common_p[ UnitNumber_u08 ]->
      cfcc[ TXCounter_u08 + ChannelNumber_u08 * EE_RSCAN_MAXCOMFIFOS ].l.cfdc =
      Config->cfcc[ TXCounter_u08 ].l.cfdc;
    ee_rscan_common_p[ UnitNumber_u08 ]->
      cfcc[ TXCounter_u08 + ChannelNumber_u08 * EE_RSCAN_MAXCOMFIFOS ].l.cfim =
      Config->cfcc[ TXCounter_u08 ].l.cfim;
    ee_rscan_common_p[ UnitNumber_u08 ]->
      cfcc[ TXCounter_u08 + ChannelNumber_u08 * EE_RSCAN_MAXCOMFIFOS ].l.cfigcv =
      Config->cfcc[ TXCounter_u08 ].l.cfigcv;
    ee_rscan_common_p[ UnitNumber_u08 ]->
      cfcc[ TXCounter_u08 + ChannelNumber_u08 * EE_RSCAN_MAXCOMFIFOS ].h.cfm =
      Config->cfcc[ TXCounter_u08 ].h.cfm;
    ee_rscan_common_p[ UnitNumber_u08 ]->
      cfcc[ TXCounter_u08 + ChannelNumber_u08 * EE_RSCAN_MAXCOMFIFOS ].h.cfitss =
      Config->cfcc[ TXCounter_u08 ].h.cfitss;
    ee_rscan_common_p[ UnitNumber_u08 ]->
      cfcc[ TXCounter_u08 + ChannelNumber_u08 * EE_RSCAN_MAXCOMFIFOS ].h.cfitr =
      Config->cfcc[ TXCounter_u08 ].h.cfitr;
    ee_rscan_common_p[ UnitNumber_u08 ]->
      cfcc[ TXCounter_u08 + ChannelNumber_u08 * EE_RSCAN_MAXCOMFIFOS ].h.cftml =
      Config->cfcc[ TXCounter_u08 ].h.cftml;
    ee_rscan_common_p[ UnitNumber_u08 ]->
      cfcc[ TXCounter_u08 + ChannelNumber_u08 * EE_RSCAN_MAXCOMFIFOS ].h.cfitt =
      Config->cfcc[ TXCounter_u08 ].h.cfitt;
  }
	return( EE_RSCAN_OK ); 
}

//=============================================================================
// FunctionName: EE_RSCAN_EnableCOMFIFO
// IN  :         Unit, Channel, FIFO Number, Enable Flag
// OUT :         Success Status
// Description : Enable and Disable COMMON FIFO
// 
//=============================================================================

uint8_t EE_RSCAN_EnableCOMFIFO( uint8_t UnitNumber_u08,
                            uint8_t ChannelNumber_u08,
                            uint8_t FIFONumber_u08,
                            uint8_t EnableFlag_u08 )
{
  if( UnitNumber_u08 >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
  if( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) 
    return( EE_RSCAN_ERROR );
  if( ee_rscan_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].stsl.mds == EE_RSCAN_OPMODE_RESET )
    return( EE_RSCAN_ERROR );
  
  ee_rscan_common_p[ UnitNumber_u08 ]->
    cfcc[ FIFONumber_u08 + ChannelNumber_u08 * EE_RSCAN_MAXCOMFIFOS ].l.cfe =
    ( uint32_t )EnableFlag_u08;
  
  return( EE_RSCAN_OK );
}

//=============================================================================
// FunctionName: EE_RSCAN_EnableRXFIFO
// IN  :         Unit, FIFO Number, Enable Flag
// OUT :         Success Status
// Description : Enable and Disable RX FIFO
// 
//=============================================================================

uint8_t EE_RSCAN_EnableRXFIFO( uint8_t UnitNumber_u08,
                           uint8_t FIFONumber_u08,
                           uint8_t EnableFlag_u08 )
{
  if( UnitNumber_u08 >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
  if( ee_rscan_common_p[ UnitNumber_u08 ]->gsts.mds == EE_RSCAN_OPMODE_RESET )
    return( EE_RSCAN_ERROR );
  
  ee_rscan_common_p[ UnitNumber_u08 ]->
    rfcc[ FIFONumber_u08 ].rfe = ( uint16_t )EnableFlag_u08;
  while( ee_rscan_common_p[ UnitNumber_u08 ]-> 
                      rfcc[ FIFONumber_u08 ].rfe != ( uint16_t )EnableFlag_u08 );
    
  return( EE_RSCAN_OK );
}

//=============================================================================
// FunctionName: EE_RSCAN_GetFIFOStatus
// IN  :         Unit Number, Channel Number, FIFO Number, Status Type
// OUT :         Success Status, Status Value
// Description : Reads FIFO Status registers
// 
//=============================================================================

uint8_t EE_RSCAN_GetFIFOStatus( uint8_t  UnitNumber_u08,
                            uint8_t  ChannelNumber_u08,
                            uint8_t  FIFONumber_u08,
                            uint8_t  StatusType_u08,
                            puint8_t StatusValue_pu08 )
{
  if( UnitNumber_u08 >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
  if( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) 
    return( EE_RSCAN_ERROR );

  if( ChannelNumber_u08 == EE_RSCAN_GLOBAL )
  {
    switch( StatusType_u08 )
    {
      case EE_RSCAN_FIFO_STATUS_FULL:
        *StatusValue_pu08 = ( uint8_t )( ee_rscan_common_p[ UnitNumber_u08 ]->
                                     rfsts[ FIFONumber_u08 ].rffll );
        break;
        
      case EE_RSCAN_FIFO_STATUS_EMPTY:
        *StatusValue_pu08 = ( uint8_t )( ee_rscan_common_p[ UnitNumber_u08 ]->
                                     rfsts[ FIFONumber_u08 ].rfemp );
        break;
        
      case EE_RSCAN_FIFO_STATUS_LOST:
        *StatusValue_pu08 = ( uint8_t )( ee_rscan_common_p[ UnitNumber_u08 ]->
                                     rfsts[ FIFONumber_u08 ].rfmlt );
        break;
    }
  }
  else
  {
    FIFONumber_u08 = EE_RSCAN_MAXCOMFIFOS * ChannelNumber_u08 + FIFONumber_u08;

    switch( StatusType_u08 )
    {
      case EE_RSCAN_FIFO_STATUS_FULL:
        *StatusValue_pu08 = ( uint8_t )( ee_rscan_common_p[ UnitNumber_u08 ]->
                                     cfsts[ FIFONumber_u08 ].cffll );
        break;
        
      case EE_RSCAN_FIFO_STATUS_EMPTY:
        *StatusValue_pu08 = ( uint8_t )( ee_rscan_common_p[ UnitNumber_u08 ]->
                                     cfsts[ FIFONumber_u08 ].cfemp );
        break;
        
      case EE_RSCAN_FIFO_STATUS_LOST:
        *StatusValue_pu08 = ( uint8_t )( ee_rscan_common_p[ UnitNumber_u08 ]->
                                     cfsts[ FIFONumber_u08 ].cfmlt );
        break;
    }
  }
  return( EE_RSCAN_OK );
}

//=============================================================================
// FunctionName: EE_RSCAN_TxAbort
// IN  :         UnitNumber, Channel Number, Message
// OUT :         Success Status
// Description : Performs Message Sending
//=============================================================================
uint8_t EE_RSCAN_TxAbort( uint8_t  UnitNumber_u08,
                      uint8_t  ChannelNumber_u08,
                      struct ee_rscan_message *Message )
{
  uint8_t SendBox_u08;
  uint8_t FirstBox_u08;
  uint8_t LastBox_u08;

  if( UnitNumber_u08 >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
  if( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) 
    return( EE_RSCAN_ERROR );
  if( ee_rscan_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].stsl.mds != EE_RSCAN_OPMODE_OPER )
    return( EE_RSCAN_ERROR );

  switch( Message->path )
  {
    case EE_RSCAN_PATH_MSGBOX:         /* direct abortion of message box */
      if( Message->pathdetail == EE_RSCAN_PATHDETAIL_ANY )  /* abort all */
      {
        FirstBox_u08 = 0;
        LastBox_u08  = EE_RSCAN_MAXTXBUFFERS - 1;
      }
      else
      {
        FirstBox_u08 = Message->pathdetail;
        LastBox_u08  = FirstBox_u08;
      }
      break;

    case EE_RSCAN_PATH_COMFIFO:        /* only one FIFO abort at a time */
      if( Message->pathdetail == EE_RSCAN_PATHDETAIL_ANY )
      {
        return( EE_RSCAN_ERROR );
      }
      else
      {
        SendBox_u08 = Message->pathdetail;
        if( SendBox_u08 >= EE_RSCAN_MAXCOMFIFOS )
        {
          return( EE_RSCAN_ERROR );
        }
        else
        {
          SendBox_u08 = ( EE_RSCAN_MAXCOMFIFOS * ChannelNumber_u08 ) + 
                        Message->pathdetail;
          if( ee_rscan_common_p[ UnitNumber_u08 ]->cfcc[ SendBox_u08 ].l.cfe )
          {
            FirstBox_u08 = ee_rscan_common_p[ UnitNumber_u08 ]->
                                        cfcc[ SendBox_u08 ].h.cftml;
            LastBox_u08 = FirstBox_u08;
          }
          else return( EE_RSCAN_ERROR );
        }
      }
      break;

    default:
      return( EE_RSCAN_ERROR );
  }
  
  for( SendBox_u08 =  FirstBox_u08;
       SendBox_u08 <= LastBox_u08;
       SendBox_u08++ )
  {
    ee_rscan_common_p[ UnitNumber_u08 ]->tmc
                     [( EE_RSCAN_MAXTXBUFFERS * ChannelNumber_u08 + 
                        SendBox_u08 ) ] |= ( uint8_t )
                      ( EE_RSCAN_TMC_SET_AR );
  }

  return( EE_RSCAN_OK );
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
    case EE_RSCAN_PATH_MSGBOX:      /* search a free SendBox, if required */
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
                EE_RSCAN_TMSTS_CLEAR )    /* check pending TRQ */
        {
          for( FIFONumber_u08 = 0;
               FIFONumber_u08 < EE_RSCAN_MAXCOMFIFOS;
               FIFONumber_u08++ )   /* check any COM FIFO assignment */
          
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
          /* Initiate Sending with this box and exit the box searching */
          
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
          SendBoxOccupied_u08 = EE_RSCAN_CLEAR;   /* test next SendBox */
        }
      }
      
      if( SendBox_u08 >= EE_RSCAN_MAXTXBUFFERS )
      {
        *Status_pu08 = EE_RSCAN_FAULT_BUSY;
        return( EE_RSCAN_OK );
      }
      break;
    }
    
    case EE_RSCAN_PATH_COMFIFO:                    /* use dedicated FIFO */
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
      else                                  /* search enabled, non-full FIFO */
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
                break;             /* an empty FIFO can be used immediately */
              }
            }
          }
        }
      }
      
      if( SendBox_u08 != EE_RSCAN_FIFO_NEXTELEMENT ) /* feed message into FIFO */
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
      else                  /* free and enabled FIFO was not found */
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
      ( Message->path == EE_RSCAN_PATH_ANY ) ) /* check within message boxes */
  {
    if( Message->pathdetail == EE_RSCAN_GLOBAL )    /* read first filled box */
    {
      SearchBegin_u08 = 0;
      SearchEnd_u08   = EE_RSCAN_MAXRXBUFFERS - 1;
    }
    else                             /* read dedicated box (typical polling) */
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
                                                      /* Clear new data flag */
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
        ( *Status_pu08 == EE_RSCAN_FAULT_NODATA ) ) ) /* check within RX FIFO */
  {
    if( Message->pathdetail == EE_RSCAN_GLOBAL )    /* read first filled FIFO */
    {
      SearchBegin_u08 = 0;
      SearchEnd_u08   = EE_RSCAN_MAXRXFIFOS - 1;
    }
    else                                               /* read dedicated FIFO */
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
        ( *Status_pu08 == EE_RSCAN_FAULT_NODATA ) ) ) /* check within COMFIFO */
  {
    if( Message->pathdetail == EE_RSCAN_GLOBAL )    /* read first filled FIFO */
    {
      SearchBegin_u08 = 0;
      SearchEnd_u08   = EE_RSCAN_MAXCOMFIFOS * ee_rscan_channels[ UnitNumber_u08 ] - 1;
    }
    else                                               /* read dedicated FIFO */
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
// FunctionName: EE_RSCAN_SetAFLEntry
// IN  :         UnitNumber, Channel Number, AFL Entry object
// OUT :         Success Status
// Description : Enters a new entry into the AFL
//               Limitations for routing are not verified!
//=============================================================================
uint8_t EE_RSCAN_SetAFLEntry( uint8_t                    UnitNumber_u08, 
                          uint8_t                    ChannelNumber_u08, 
                          uint16_t                    RuleNumber_u16, 
                          struct ee_rscan_a_afl *AFLEntry ) 
{
  uint8_t AFLIndex_u08;
  uint16_t AFLElement_u16 = RuleNumber_u16;
  uint8_t AFLChannelEntry[ EE_RSCAN_MAXCHANNELS ];

  if( UnitNumber_u08 >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
  if( ChannelNumber_u08 >= ee_rscan_channels[ UnitNumber_u08 ] ) return( EE_RSCAN_ERROR );
  if( ee_rscan_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].stsl.mds == EE_RSCAN_OPMODE_OPER ) return( EE_RSCAN_ERROR );
  if( ee_rscan_common_p[ UnitNumber_u08 ]->gctrl.gslpr == EE_RSCAN_SET ) return( EE_RSCAN_ERROR );

  for( AFLIndex_u08 = 0;
       AFLIndex_u08 <= ChannelNumber_u08;
       AFLIndex_u08++ )
  {
    switch( AFLIndex_u08 )
    {
      case EE_RSCAN_CHANNEL0:
        AFLChannelEntry[ AFLIndex_u08 ] = 
          ( uint8_t )ee_rscan_common_p[ UnitNumber_u08 ]->gaflcfg.rnc0;
        break;
      case EE_RSCAN_CHANNEL1:
        AFLChannelEntry[ AFLIndex_u08 ] = 
          ( uint8_t )ee_rscan_common_p[ UnitNumber_u08 ]->gaflcfg.rnc1;
        AFLElement_u16 += ( uint16_t )AFLChannelEntry[ EE_RSCAN_CHANNEL0 ];
        break;
      default: 
        return( EE_RSCAN_ERROR );
    }
  }
  
  if( AFLElement_u16 >= EE_RSCAN_MAXAFLENTRIES ) 
    return( EE_RSCAN_ERROR );

  if( RuleNumber_u16 >= AFLChannelEntry[ ChannelNumber_u08 ] )
          return( EE_RSCAN_ERROR );

  if( AFLChannelEntry[ ChannelNumber_u08 ] > EE_RSCAN_MAXAFLCHANSET )
    return( EE_RSCAN_ERROR );

  AFLElement_u16 = AFLElement_u16 % EE_RSCAN_AFLPAGESIZE;

  ee_rscan_common_p[ UnitNumber_u08 ]->grwcr.rpage = EE_RSCAN_CLEAR;
 
  ee_rscan_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].idl.id 		= ( uint16_t )( AFLEntry->id.id & EE_RSCAN_ID_MASK_LOW );
  ee_rscan_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].idh.id 		= ( uint16_t )( ( AFLEntry->id.id >> 16 ) & EE_RSCAN_ID_MASK_HIGH );
  ee_rscan_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].idh.lb 		= ( uint16_t )AFLEntry->id.lb;
  ee_rscan_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].idh.rtr 	  = ( uint16_t )AFLEntry->id.rtr;
  ee_rscan_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].idh.ide 	  = ( uint16_t )AFLEntry->id.ide;
  ee_rscan_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].maskl.id   = ( uint16_t )( AFLEntry->mask.id & EE_RSCAN_ID_MASK_LOW );
  ee_rscan_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].maskh.id   = ( uint16_t )( ( AFLEntry->mask.id >> 16 ) & EE_RSCAN_ID_MASK_HIGH );
  ee_rscan_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].maskh.rtr 	= ( uint16_t )AFLEntry->mask.rtr;
  ee_rscan_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].maskh.ide 	= ( uint16_t )AFLEntry->mask.ide;
  ee_rscan_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].ptrl.rmdp 	= ( uint16_t )AFLEntry->ptr0.rmdp;
  ee_rscan_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].ptrl.rmv 	= ( uint16_t )AFLEntry->ptr0.rmv;
  ee_rscan_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].ptrh.ptr 	= ( uint16_t )AFLEntry->ptr0.ptr;
  ee_rscan_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].ptrh.dlc 	= ( uint16_t )AFLEntry->ptr0.dlc;
  ee_rscan_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].ptrl.rxfifomask  = ( uint16_t )AFLEntry->ptr1.rxfifomask;
  ee_rscan_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].ptrl.comfifomask = ( uint16_t )AFLEntry->ptr1.comfifomask;

  ee_rscan_common_p[ UnitNumber_u08 ]->grwcr.rpage = EE_RSCAN_SET;

  return( EE_RSCAN_OK );
}

//=============================================================================
// FunctionName: EE_RSCAN_GetTimeStampCounter
// IN  :         Unit Number
// OUT :         Success Status
// Description : Returns current value of Time Stamp Counter
// 
//=============================================================================
uint8_t EE_RSCAN_GetTimeStampCounter( uint8_t  UnitNumber_u08,
                                  puint32_t TimeStampValue_pu32 )
{
  if( UnitNumber_u08 >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
  
  *TimeStampValue_pu32 = ( uint32_t )ee_rscan_common_p[ UnitNumber_u08 ]->gtsc.ts;
  
  return( EE_RSCAN_OK );
}

//=============================================================================
// FunctionName: EE_RSCAN_RAMTest
// IN  :         Unit Number
// OUT :         Success Status
// Description : Executes RAM Test
// + 256 bytes per Page
//=============================================================================
uint8_t EE_RSCAN_RAMTest( uint8_t UnitNumber_u08 ) 
{
  uint8_t RAMPage_u08;
  uint16_t RAMElement_u16;
  uint16_t RAMData_u16 = 0x0001;

  if( UnitNumber_u08 >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
  while( ee_rscan_common_p[ UnitNumber_u08 ]->gsts.rsts );
  if( ee_rscan_common_p[ UnitNumber_u08 ]->gsts.mds != EE_RSCAN_OPMODE_HALT ) return( EE_RSCAN_ERROR );
  if( ee_rscan_common_p[ UnitNumber_u08 ]->gctrl.gslpr == EE_RSCAN_SET ) return( EE_RSCAN_ERROR );

  ee_rscan_common_p[ UnitNumber_u08 ]->grwcr.rpage = EE_RSCAN_CLEAR;

  // Unlock the test mode
  ee_rscan_common_p[ UnitNumber_u08 ]->glockk     = EE_RSCAN_RAMTEST_KEY1;
  ee_rscan_common_p[ UnitNumber_u08 ]->glockk     = EE_RSCAN_RAMTEST_KEY2;
  ee_rscan_common_p[ UnitNumber_u08 ]->gtstctr    = EE_RSCAN_RAMTEST_MODE;


  // Reading back zero value from cleared RAM
  for( RAMPage_u08 = 0; RAMPage_u08 < EE_RSCAN_RAMTEST_PAGES; RAMPage_u08++ )
  {
    ee_rscan_common_p[ UnitNumber_u08 ]->gtstcfg.rtmps = ( uint16_t )RAMPage_u08;
	
    for( RAMElement_u16 = 0; RAMElement_u16 < EE_RSCAN_RAMTEST_ENTRIES; RAMElement_u16++ )
    {
      
#ifdef EE_RSCAN_RAMTEST_LASTPGENTRIES
      if( ( RAMPage_u08 == ( EE_RSCAN_RAMTEST_PAGES-1 ) ) &
         ( RAMElement_u16 > EE_RSCAN_RAMTEST_LASTPGENTRIES ) ) break;
#endif
     
      ee_rscan_ram_p[ UnitNumber_u08 ]->cell[ RAMElement_u16 ] = 0x0000;
      if( ee_rscan_ram_p[ UnitNumber_u08 ]->cell[ RAMElement_u16 ] != 0x0000 )
      {
        return( EE_RSCAN_ERROR );
      }
    }
  }
  
  // Write walking-1 to all RAM pages
  for( RAMPage_u08 = 0; RAMPage_u08 < EE_RSCAN_RAMTEST_PAGES; RAMPage_u08++ )
  {
	ee_rscan_common_p[ UnitNumber_u08 ]->gtstcfg.rtmps = ( uint16_t )RAMPage_u08;
	
    for( RAMElement_u16 = 0; RAMElement_u16 < EE_RSCAN_RAMTEST_ENTRIES; RAMElement_u16++ )
    {
      
#ifdef EE_RSCAN_RAMTEST_LASTPGENTRIES
      if( ( RAMPage_u08 == ( EE_RSCAN_RAMTEST_PAGES-1 ) ) &
          ( RAMElement_u16 > EE_RSCAN_RAMTEST_LASTPGENTRIES ) ) break;
#endif
     
      ee_rscan_ram_p[ UnitNumber_u08 ]->cell[ RAMElement_u16 ] = RAMData_u16;
  	  if( RAMData_u16 >= 0x8000 )
  	  {
        RAMData_u16 = 0x0001;
  	  }
  	  else
  	  {
  	    RAMData_u16 = RAMData_u16 * 2;
  	  }
  	}
  }

    // Checking Walking-1 through all pages
  for( RAMPage_u08 = 0; RAMPage_u08 < EE_RSCAN_RAMTEST_PAGES; RAMPage_u08++ )
  {
    ee_rscan_common_p[ UnitNumber_u08 ]->gtstcfg.rtmps = ( uint16_t )RAMPage_u08;
	
    for( RAMElement_u16 = 0; RAMElement_u16 < EE_RSCAN_RAMTEST_ENTRIES; RAMElement_u16++ )
    {
      
#ifdef EE_RSCAN_RAMTEST_LASTPGENTRIES
      if( ( RAMPage_u08 == ( EE_RSCAN_RAMTEST_PAGES-1 ) ) &
          ( RAMElement_u16 > EE_RSCAN_RAMTEST_LASTPGENTRIES ) ) break;
#endif
     
  	  if ( ( RAMPage_u08 == 0 ) && ( RAMElement_u16 == 0 ) )
  	  {
  	    RAMData_u16 = 0x0001;
  	  }
  	  else if( RAMData_u16 >= 0x8000 )
  	  {
        RAMData_u16 = 0x0001;
  	  }
  	  else
  	  {
        RAMData_u16 = RAMData_u16 * 2;
  	  }
	  
      if( ee_rscan_ram_p[ UnitNumber_u08 ]->cell[ RAMElement_u16 ] != RAMData_u16 )
      {
        return( EE_RSCAN_ERROR );
      }
    }
  }

  // Repeat reading back zero value from cleared RAM
  for( RAMPage_u08 = 0; RAMPage_u08 < EE_RSCAN_RAMTEST_PAGES; RAMPage_u08++ )
  {
    ee_rscan_common_p[ UnitNumber_u08 ]->gtstcfg.rtmps = ( uint16_t )RAMPage_u08;
	
    for( RAMElement_u16 = 0; RAMElement_u16 < EE_RSCAN_RAMTEST_ENTRIES; RAMElement_u16++ )
    {
      
#ifdef EE_RSCAN_RAMTEST_LASTPGENTRIES
      if( ( RAMPage_u08 == ( EE_RSCAN_RAMTEST_PAGES-1 ) ) &
         ( RAMElement_u16 > EE_RSCAN_RAMTEST_LASTPGENTRIES ) ) break;
#endif
     
      ee_rscan_ram_p[ UnitNumber_u08 ]->cell[ RAMElement_u16 ] = 0x0000;
      if( ee_rscan_ram_p[ UnitNumber_u08 ]->cell[ RAMElement_u16 ] != 0x0000 )
      {
        return( EE_RSCAN_ERROR );
      }
    }
  }
  ee_rscan_common_p[ UnitNumber_u08 ]->grwcr.rpage = EE_RSCAN_SET;
  return( EE_RSCAN_OK );
}

//=============================================================================
// FunctionName: EE_RSCAN_IntCANBusActivate
// IN  :         Unit Number
// OUT :         Success Status
// Description : Activates internal CAN bus communication for testing
// 
//=============================================================================
uint8_t EE_RSCAN_IntCANBusActivate( uint8_t UnitNumber_u08 )
{
  if( UnitNumber_u08 >= EE_RSCAN_MACROS ) return( EE_RSCAN_ERROR );
  if( ee_rscan_common_p[ UnitNumber_u08 ]->gsts.mds != EE_RSCAN_OPMODE_HALT )
    return( EE_RSCAN_ERROR );
  
  ee_rscan_common_p[ UnitNumber_u08 ]->gtstcfg.icbce = EE_RSCAN_COMTEST_ALLON;
  
  ee_rscan_common_p[ UnitNumber_u08 ]->gtstctr = EE_RSCAN_COMTEST_MODE;
  while( ee_rscan_common_p[ UnitNumber_u08 ]->gtstctr != EE_RSCAN_COMTEST_MODE );
  
  return( EE_RSCAN_OK );
}
