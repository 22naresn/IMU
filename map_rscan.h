/*===========================================================================*/
/* PROJECT = RL78 / F14                                                      */
/*===========================================================================*/
/*                                  COPYRIGHT                                */
/*===========================================================================*/
/* Copyright (c) 2013 by Renesas Electronics Europe GmbH,                    */
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
/* Environment:                                                              */
/*              Device:          RL78 including RSCAN macro                  */
/*              IDE:             IAR Systems                                 */
/*                               Embedded Workbench for RL78 V1.30.x         */
/*                                                                           */
/*===========================================================================*/

#ifndef _MAP_RSCAN_H
#define _MAP_RSCAN_H

#include <stddef.h>


/* MAPPED RSCAN: RSCAN_LITE_1CH */

#include <map_device.h>
#include "rscan.h"
#include "rscan_a.h"
#include "rscan_p.h"

/* The EE_AFCAN_VERBOSE within the Application Interface Functions 
 * wants to report to the communications interface... */

#ifdef  APPLICATION_INTERFACE
//#include <uartf\qlapbuartfv1\qlapbuartfv1.h>
//#include <uartf\qlapbuartfv1\qlapbuartfv1_a.h>
#endif
 
/* FURTHER RSCAN OPERATION PROPERTIES */

#define EE_RSCAN_BASE           ( 0xF0300 )

#define EE_RSCAN_OFFSET_COMMON  ( 0x00000 )
#define EE_RSCAN_OFFSET_AFL     ( 0x000A0 )
#define EE_RSCAN_OFFSET_RXMSG   ( 0x000A0 )
#define EE_RSCAN_OFFSET_RXFIFO  ( 0x002A0 )
#define EE_RSCAN_OFFSET_COMFIFO ( 0x002E0 )
#define EE_RSCAN_OFFSET_TXMSG   ( 0x00300 )
#define EE_RSCAN_OFFSET_TXHL    ( 0x00380 )
#define EE_RSCAN_OFFSET_RAM     ( 0x00280 )

#define EE_RSCAN_FREQFACTOR  ( 0.5 )

#define EE_RSCAN_MAXBAUDRATE ( ( uint32_t )( OSCILLATOR_FREQUENCY * EE_RSCAN_FREQFACTOR )\
                               / EE_RSCAN_CLKMINFACTOR )

#define EE_RSCAN_FREQFACTORPLLBP  ( 0.125 )

#define EE_RSCAN_MAXBAUDRATEPLLBP ( ( uint32_t )( OSCILLATOR_FREQUENCY * EE_RSCAN_FREQFACTORPLLBP )\
                                    / EE_RSCAN_CLKMINFACTOR )

#define EE_RSCAN_SHUTDOWNTIMEOUT ( 1000000L )

#define EE_RSCAN_VERBOSE            0

/* PORT DEFINITIONS */

#define EE_RSCAN_PORT_M0RX0       PORT_1
#define EE_RSCAN_PORT_M0TX0       PORT_1

#define EE_RSCAN_PORT_BIT_M0RX0   BIT_1
#define EE_RSCAN_PORT_BIT_M0TX0   BIT_0

#define EE_RSCAN_PORT_FUNC_M0RX0  PORT_FUNCTION_ALTERN   // set Px
#define EE_RSCAN_PORT_FUNC_M0TX0  PORT_FUNCTION_ALTERN   // set Px

/* INTERRUPT REGISTER MAPPING */

//#define EE_RSCAN_INT_BUNDLINGHOOK ( RSCAN_IntBundlingDecode )  // external bundling decoder

#define EE_RSCAN_INT_M0GERR     ( CANGERRMK )
#define EE_RSCAN_INT_M0RXF0     ( CANGRFRMK )
#define EE_RSCAN_INT_M0RXF1     ( CANGRFRMK )

#define EE_RSCAN_INT_M0TX0      ( CAN0TRMMK )
#define EE_RSCAN_INT_M0TXA0     ( CAN0TRMMK )
#define EE_RSCAN_INT_M0ERR0     ( CAN0ERRMK )
#define EE_RSCAN_INT_M0THL0     ( CAN0TRMMK )
#define EE_RSCAN_INT_M0RXCF0    ( CAN0CFRMK )
#define EE_RSCAN_INT_M0TXCF0    ( CAN0TRMMK )

#define EE_RSCAN_INTCLEAR         ( 0x01 )        // Interrupt mask bit
#define EE_RSCAN_INTENABLEDEFAULT ( 0x00 )

/* The RSCAN Memory Mapping */  

#define EE_RSCAN_RAMTEST_PAGES          ( 3 )
#define EE_RSCAN_RAMTEST_LASTPGENTRIES  ( 16 )     /* short words (16-BIT) */

static const uint8_t ee_rscan_channels[ EE_RSCAN_MACROS ] =
{
    1                                                               /* unit 0 */
};   

static volatile struct ee_rscan_common *ee_rscan_common_p[ EE_RSCAN_MACROS ] =
{
    ( ee_rscan_common * )( EE_RSCAN_BASE + EE_RSCAN_OFFSET_COMMON
                       + 0x00000000 )                               /* unit 0 */
};   

static struct ee_rscan_aflpage *ee_rscan_aflpage_p[ EE_RSCAN_MACROS ] =
{
    ( ee_rscan_aflpage * )( EE_RSCAN_BASE + EE_RSCAN_OFFSET_AFL 
                        + 0x00000000 )                              /* unit 0 */
};   

static struct ee_rscan_rxmsg *ee_rscan_rxmsg_p[ EE_RSCAN_MACROS ] =
{
    ( ee_rscan_rxmsg * )( EE_RSCAN_BASE + EE_RSCAN_OFFSET_RXMSG 
                      + 0x00000000 )                                /* unit 0 */
};   

static struct ee_rscan_txmsg *ee_rscan_txmsg_p[ EE_RSCAN_MACROS ]
                                              [ EE_RSCAN_MAXCHANNELS ] =
{
    ( ee_rscan_txmsg * )( EE_RSCAN_BASE + EE_RSCAN_OFFSET_TXMSG 
                      + 0x00000000 ),                               /* unit 0, ch 0 */
    NULL
};   

static struct ee_rscan_rxfifo *ee_rscan_rxfifo_p[ EE_RSCAN_MACROS ] =
{
    ( ee_rscan_rxfifo * )( EE_RSCAN_BASE + EE_RSCAN_OFFSET_RXFIFO 
                       + 0x00000000 )                               /* unit 0 */
};   

static struct ee_rscan_comfifo *ee_rscan_comfifo_p[ EE_RSCAN_MACROS ]
                                                  [ EE_RSCAN_MAXCHANNELS ] =
{
    ( ee_rscan_comfifo * )( EE_RSCAN_BASE + EE_RSCAN_OFFSET_COMFIFO 
                        + 0x00000000 ),                             /* unit 0, ch 0 */
    NULL
};   

static struct ee_rscan_thl *ee_rscan_thl_p[ EE_RSCAN_MACROS ]
                                          [ EE_RSCAN_MAXCHANNELS ] =
{
    ( ee_rscan_thl * )( EE_RSCAN_BASE + EE_RSCAN_OFFSET_TXHL 
                    + 0x00000000 ),                                 /* unit 0, ch 0 */
    NULL
};

static struct ee_rscan_ram *ee_rscan_ram_p[ EE_RSCAN_MACROS ] =
{
  ( ee_rscan_ram * )( EE_RSCAN_BASE + EE_RSCAN_OFFSET_RAM
                    + 0x00000000 )                                  /* unit 0, ch 0 */
};


#endif
