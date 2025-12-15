/*===========================================================================*/
/* PROJECT = STANDARD PORTS DRIVER                                           */
/*****************************************************************************/
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


#ifndef _STANDARDPORTS_H
#define _STANDARDPORTS_H
            
#include "r_cg_macrodriver.h"
#include "addl_types.h"
             
#define PORT_OK      true
#define PORT_ERROR   false

#define PORT_NUMERIC            /* PORT DEFINITIONS */

#define PORT_0   0x0000         
#define PORT_1   0x0001
#define PORT_2   0x0002
#define PORT_3   0x0003
#define PORT_4   0x0004
#define PORT_5   0x0005
#define PORT_6   0x0006
#define PORT_7   0x0007
#define PORT_8   0x0008
#define PORT_9   0x0009
#define PORT_10   0x000A
#define PORT_11   0x000B
#define PORT_12   0x000C
#define PORT_13   0x000D
#define PORT_14   0x000E
#define PORT_15   0x000F
#define PORT_16   0x0010
#define PORT_17   0x0011
#define PORT_20   0x0014
#define PORT_22   0x0016
#define PORT_24   0x0018
#define PORT_25   0x0019
#define PORT_29   0x001D
#define PORT_32   0x0020
#define PORT_33   0x0021
#define PORT_34   0x0022

#define PORT_ALPHA

#define PORT_DL  0x0100
#define PORT_DH  0x0101

#define PORT_AL  0x0200
#define PORT_AH  0x0201

#define PORT_CS  0x0300
#define PORT_CT  0x0301
#define PORT_CM  0x0302
#define PORT_CD  0x0303

#define PORT_NOPORT 0xFFFF

#define uint8_t_0    0x01         /* uint8_t DEFINITIONS */
#define uint8_t_1    0x02
#define uint8_t_2    0x04
#define uint8_t_3    0x08
#define uint8_t_4    0x10
#define uint8_t_5    0x20
#define uint8_t_6    0x40
#define uint8_t_7    0x80

#define uint8_t_8    0x0100
#define uint8_t_9    0x0200
#define uint8_t_10   0x0400
#define uint8_t_11   0x0800
#define uint8_t_12   0x1000
#define uint8_t_13   0x2000
#define uint8_t_14   0x4000
#define uint8_t_15   0x8000  

#define uint8_t_ALL16 0xFFFF
#define uint8_t_ALL8  0xFF
#define uint8_t_NONE  0x0000

#define uint8_t_0_P  0
#define uint8_t_1_P  1
#define uint8_t_2_P  2
#define uint8_t_3_P  3
#define uint8_t_4_P  4
#define uint8_t_5_P  5
#define uint8_t_6_P  6
#define uint8_t_7_P  7

#define uint8_t_8_P  8
#define uint8_t_9_P  9
#define uint8_t_10_P 10
#define uint8_t_11_P 11
#define uint8_t_12_P 12
#define uint8_t_13_P 13
#define uint8_t_14_P 14
#define uint8_t_15_P 15


#define PORT_DIR_INPUT  1       /* Port Direction */
#define PORT_DIR_OUTPUT 0
#define PORT_DIR_KEEP   2

#define PORT_MODE_IO         0  /* Port Mode Control */
#define PORT_MODE_PERIPHERAL 1
#define PORT_MODE_KEEP       2

#define PORT_FUNCTION_NORMAL  0x00 /* Port Function Control */
#define PORT_FUNCTION_ALTERN  0x01
#define PORT_FUNCTION_ALTERN2 0x10
#define PORT_FUNCTION_ALTERN4 0x20
#define PORT_FUNCTION_ALTLV0  ( PORT_FUNCTION_NORMAL )
#define PORT_FUNCTION_ALTLV1  ( PORT_FUNCTION_ALTERN )
#define PORT_FUNCTION_ALTLV2  ( PORT_FUNCTION_ALTERN2 )
#define PORT_FUNCTION_ALTLV3  ( PORT_FUNCTION_ALTERN | PORT_FUNCTION_ALTERN2 )
#define PORT_FUNCTION_ALTLV4  ( PORT_FUNCTION_ALTERN4 )
#define PORT_FUNCTION_ALTLV5  ( PORT_FUNCTION_ALTERN | PORT_FUNCTION_ALTERN4 )
#define PORT_FUNCTION_ALTLV6  ( PORT_FUNCTION_ALTERN2 | PORT_FUNCTION_ALTERN4 )
#define PORT_FUNCTION_ALTLV7  ( PORT_FUNCTION_ALTERN | PORT_FUNCTION_ALTERN2 | PORT_FUNCTION_ALTERN4 )
#define PORT_FUNCTION_KEEP    0xFF

#endif
