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

#include <stddef.h>
#include "r_cg_macrodriver.h"
#include "addl_types.h"
#include "rscan.h"

#define  DRIVER_LOCAL

/* Default Configuration Macros */

#define EE_RSCAN_A_COMFIFO_OFF { { 0, 0, 0, 0,  EE_RSCAN_FIFO_DEPTH_0, 0,\
                                   EE_RSCAN_FIFO_INT_ONLEVEL, \
                                   EE_RSCAN_FIFO_ILEVEL_1D8 }, \
                                 { EE_RSCAN_FIFO_MODE_RX, \
                                   EE_RSCAN_FIFO_IT_REFCLK, \
                                   EE_RSCAN_FIFO_IT_REFCLK1, \
                                   0, 0, 0 } }             /* COM FIFO disabled */

#define EE_RSCAN_A_RXFIFO_OFF  { 0, 0, 0, EE_RSCAN_FIFO_DEPTH_0, 0, \
                                 EE_RSCAN_FIFO_INT_ONLEVEL, \
                                 EE_RSCAN_FIFO_ILEVEL_1D8 } /* RX FIFO disabled */

#define EE_RSCAN_A_THL_OFF { 0, 0, 0, EE_RSCAN_THL_INT_ONLEVEL, \
                             EE_RSCAN_THL_ENTRY_FIFO, 0 }         /* THL OFF */
#define EE_RSCAN_A_THL_ON  { 1, 0, 0, EE_RSCAN_THL_INT_ONLEVEL, \
                             EE_RSCAN_THL_ENTRY_FIFO, 0 }          /* THL ON */

/* Default configurations */

const struct ee_rscan_cfg_channel EE_RSCAN_A_CHCFG_BASIC = 
{
  100000, 0, 0, 0.0,                /* bitrate 100 kbit/s, default bit-timing */
  
  {
    EE_RSCAN_OPMODE_KEEP, 0, 0, 0,    /* No implicit change of Operation Mode */
    EE_RSCAN_CINT_OFF                                  /* No Error Interrupts */
  },
  {
    EE_RSCAN_CINT_OFF, 0,                              /* No Error Interrupts */
    EE_RSCAN_BOM_ISO, 0,     /* Standard Bus Off behaviour & Error Signalling */
    0, EE_RSCAN_TEST_BASIC, 0                                /* Test Mode Off */
  },
  
  0xFFFF,                                     /* enable all IRQ of TX Buffers */
  
  EE_RSCAN_A_THL_OFF,                              /* disable lists and FIFOs */
  { 
    EE_RSCAN_A_COMFIFO_OFF,
    EE_RSCAN_A_COMFIFO_OFF 
  }
};

const struct ee_rscan_cfg_global EE_RSCAN_A_GCFG_BASIC = 
{
  {
    EE_RSCAN_TXPRIO_ID,                      /* TX priority by ID (standard) */
    EE_RSCAN_DLCCHECK_DISABLE, 
    EE_RSCAN_DLCREPL_DISABLE,                 /* no DLC check or replacement */
    EE_RSCAN_MIRROR_DISABLE,                               /* no Mirror Mode */
    EE_RSCAN_CLOCK_SYS,                              /* use peripheral clock */
    0, EE_RSCAN_CLOCK_TSBIT, 
    EE_RSCAN_CHANNEL0, 0        /* Use 1TQ Bit-Timing clock 0 for Timestamps */
  },
  {
    EE_RSCAN_CLOCK_FIFO_OFF               /* interval timer of FIFO disabled */
  },
  {
    EE_RSCAN_OPMODE_KEEP, 
    EE_RSCAN_SLEEP_DISABLE,          /* No implicit change of Operation Mode */
    0, EE_RSCAN_GINT_NONE, 0                          /* No Error Interrupts */
  },
  {
    EE_RSCAN_TIMESTAMP_RESET, 0                           /* Timestamp reset */
  },
  EE_RSCAN_MAXRXBUFFERS,          /* use max. amount of classical RX buffers */
  {             
	  1, 1                            /* every channel has one AFL entry */
  },
  {
    EE_RSCAN_A_RXFIFO_OFF,                           /* disable all RX FIFOs */
    EE_RSCAN_A_RXFIFO_OFF,
    EE_RSCAN_A_RXFIFO_OFF,
    EE_RSCAN_A_RXFIFO_OFF
  }
};

struct ee_rscan_a_afl EE_RSCAN_A_AFL_RXBOX_ANY = 
{
  {
    0x00000000,              /* Default ID, not relevant because mask is open */
    EE_RSCAN_AFL_RXENTRY,                        /* receive entry type of AFL */
    EE_RSCAN_FRAME_DATA,                      /* RTR data frame configuration */
    EE_RSCAN_ID_STD                           /* standard frame configuration */
  },
  {
    EE_RSCAN_MASK_IDDONTCARE,                     /* mask is open for all IDs */
    EE_RSCAN_MASK_DONTCARE,                  /* any type of frame is accepted */
    EE_RSCAN_MASK_DONTCARE
  },
  {
    0,                   /* RX Box Number - to be replaced with actual number */
    EE_RSCAN_SET,                                     /* RX Box is set active */
    0x000,          /* Receive HRH pointer - to be replaced with actual value */
    EE_RSCAN_DLCCHECK_DISABLE          /* to enable DLC check, enter DLC here */
  },
  {
    EE_RSCAN_AFL_RXFIFO_NONE,              /* this AFL entry only receives in */
    EE_RSCAN_AFL_COMFIFO_NONE                      /* classical message boxes */
  }
};

/* Configuration for CAN-FD Partial Networking Application */

#define EE_RSCAN_A_RXFIFO_FDPNW  { EE_RSCAN_FIFO_EN, \
                                   EE_RSCAN_FIFO_INT_EN, \
                                   0, EE_RSCAN_FIFO_DEPTH_4, \
                                   0, EE_RSCAN_FIFO_INT_ONEVERY, \
                                   0 } /* RX FIFO enabled */

const struct ee_rscan_cfg_channel EE_RSCAN_A_CHCFG_FDPNW = 
{
  500000, 0, 0, 0.0,                /* bitrate 500 kbit/s, default bit-timing */
  
  {
    EE_RSCAN_OPMODE_KEEP, 0, 0, 0,    /* No implicit change of Operation Mode */
    EE_RSCAN_CINT_BUSERR |                       /* Selected Error Interrupts */
    EE_RSCAN_CINT_WARNING |
    EE_RSCAN_CINT_PASSIVE |
    EE_RSCAN_CINT_BUSOFF 
  }, 
  {
    EE_RSCAN_CINT_OFF, 0,
    EE_RSCAN_BOM_ISO, 0,     /* Standard Bus Off behaviour & Error Signalling */
    0, EE_RSCAN_TEST_BASIC, 0                                /* Test Mode Off */
  },
  
  0xFFFF,                                     /* enable all IRQ of TX Buffers */
  
  EE_RSCAN_A_THL_OFF,                              /* disable lists and FIFOs */
  { 
    EE_RSCAN_A_COMFIFO_OFF,
    EE_RSCAN_A_COMFIFO_OFF 
  }
};

const struct ee_rscan_cfg_global EE_RSCAN_A_GCFG_FDPNW = 
{
  {
    EE_RSCAN_TXPRIO_ID,                      /* TX priority by ID (standard) */
    EE_RSCAN_DLCCHECK_DISABLE, 
    EE_RSCAN_DLCREPL_DISABLE,                 /* no DLC check or replacement */
    EE_RSCAN_MIRROR_DISABLE,                               /* no Mirror Mode */
    EE_RSCAN_CLOCK_SYS,                              /* use peripheral clock */
    0, EE_RSCAN_CLOCK_TSBIT, 
    EE_RSCAN_CHANNEL0, 0        /* Use 1TQ Bit-Timing clock 0 for Timestamps */
  },
  {
    EE_RSCAN_CLOCK_FIFO_OFF               /* interval timer of FIFO disabled */
  },
  {
    EE_RSCAN_OPMODE_KEEP, 
    EE_RSCAN_SLEEP_DISABLE,          /* No implicit change of Operation Mode */
    0, EE_RSCAN_GINT_MSGLOST, 0       /* Message Lost Error Interrupt active */
  },
  {
    EE_RSCAN_TIMESTAMP_RESET, 0                           /* Timestamp reset */
  },
  0,                                     /* no usage of classical RX buffers */
  {             
	  2, 2              				             /* two AFL entries on any channel */
  },
  {
    EE_RSCAN_A_RXFIFO_FDPNW,                       /* activate two RX FIFOs */
    EE_RSCAN_A_RXFIFO_FDPNW,
    EE_RSCAN_A_RXFIFO_OFF,
    EE_RSCAN_A_RXFIFO_OFF
  }
};

struct ee_rscan_a_afl EE_RSCAN_A_AFL_RXFIFO_FDPNW_ANY = 
{
  {
    0x00000000,              /* Default ID, not relevant because mask is open */
    EE_RSCAN_AFL_RXENTRY,                        /* receive entry type of AFL */
    EE_RSCAN_FRAME_DATA,                      /* RTR data frame configuration */
    EE_RSCAN_ID_STD                           /* standard frame configuration */
  },
  {
    0x00000001,                              /* mask is open for all even IDs */
    EE_RSCAN_MASK_DONTCARE,                  /* any type of frame is accepted */
    EE_RSCAN_MASK_DONTCARE
  },
  {
    0,                                            /* RX Box Number - not used */
    EE_RSCAN_CLEAR,                                 /* RX Box is set inactive */
    0x001,                                             /* Receive HRH pointer */
    EE_RSCAN_DLCCHECK_DISABLE          /* to enable DLC check, enter DLC here */
  },
  {
    EE_RSCAN_AFL_RXFIFO_EN0,             /* this AFL entry receives in FIFO 0 */
    EE_RSCAN_AFL_COMFIFO_NONE
  }
};

struct ee_rscan_a_afl EE_RSCAN_A_AFL_RXFIFO_FDPNW_SWITCH = 
{
  {
    0x0000000,                  /* ID=0, switching must have highest priority 
                   (all nodes abort FD sending in case of FD is swithced off) */
    EE_RSCAN_AFL_RXENTRY,                        /* receive entry type of AFL */
    EE_RSCAN_FRAME_DATA,                      /* RTR data frame configuration */
    EE_RSCAN_ID_STD                           /* standard frame configuration */
  },
  {
    EE_RSCAN_MASK_IDFULLCAN,                         /* only ID=0 is received */
    EE_RSCAN_MASK_FILTER,                    /* only DATA frames are accepted */
    EE_RSCAN_MASK_FILTER              /* only standard ID frames are accepted */
  },
  {
    0,                                            /* RX Box Number - not used */
    EE_RSCAN_CLEAR,                                 /* RX Box is set inactive */
    0x002,                                             /* Receive HRH pointer */
    EE_RSCAN_DLCCHECK_DISABLE          /* to enable DLC check, enter DLC here */
  },
  {
    EE_RSCAN_AFL_RXFIFO_EN1,             /* this AFL entry receives in FIFO 1 */
    EE_RSCAN_AFL_COMFIFO_NONE
  }
};
