#ifndef _MAP_DEVICE_H
#define _MAP_DEVICE_H

/* Define registers for RL78/F14 */
/* Select the device specific include here */


#include "iodefine.h"

/* Define device name, used e.g. for handling of shared interrupts */
#define RL78_F14

/* List of all included macros, to be supported */

/* ...MACROS: Number or macro units
 * ...TYPE:   Unique type identifier from Renesas_macros.h
 */

#define PORTS_TYPE     PORTS_STANDARD

#define INTC_MACROS    1
#define INTC_TYPE      QL85E70X

#define EE_RSCAN_MACROS   1
#define EE_RSCAN_TYPE     RSCAN_LITE
#define EE_RSCAN_SINGLECHANNEL

#endif  /* MAP_DEVICE_H */