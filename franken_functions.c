#include "r_cg_macrodriver.h"
#include "addl_types.h"
#include "standard_ports.h"
#include <stdbool.h>
#include <stddef.h>
#include "iodefine.h"
#include "rscan.h"

uint8_t PORT_Enable( uint16_t port,
                     uint16_t bitmask,
                     uint8_t  direction,
                     uint8_t  mode,
                     uint8_t  function )
{
	/* Only Port 7 is valid for CAN on PPJ */
	if (port != 7)
		return PORT_ERROR;

	/* Peripheral vs GPIO */
	if (mode == PORT_MODE_PERIPHERAL)
        	PMC7 &= ~bitmask;   /* 0 = peripheral */
    	else
        	PMC7 |= bitmask;    /* 1 = GPIO */

    	/* Direction */
   	if (direction == PORT_DIR_INPUT)
    	{
        	PM7 |= bitmask;        /* input */
        	PITHL7 &= ~bitmask;   /* default threshold */
    	}
    	else
    	{
        	PM7 &= ~bitmask;      /* output */
        	POM7 &= ~bitmask;     /* CMOS output */
    	}

    	return PORT_OK;
}

uint8_t PORT_Disable( uint16_t port,
                      uint16_t bitmask )
{
	return PORT_Enable( port,
                            bitmask,
                            PORT_DIR_INPUT,
                            PORT_MODE_IO,
                            PORT_FUNCTION_KEEP );
}