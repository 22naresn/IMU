#ifndef FRANKEN_FUNCTIONS_H
#define FRANKEN_FUNCTIONS_H

#include <stdint.h>

/* --------------------------------------------------------------------------
 * Common return values
 * -------------------------------------------------------------------------- */
#define PORT_OK     ((uint8_t)1U)
#define PORT_ERROR  ((uint8_t)0U)

/* --------------------------------------------------------------------------
 * Port direction
 * -------------------------------------------------------------------------- */
#define PORT_DIR_INPUT   ((uint8_t)1U)
#define PORT_DIR_OUTPUT  ((uint8_t)0U)

/* --------------------------------------------------------------------------
 * Port mode
 * -------------------------------------------------------------------------- */
#define PORT_MODE_IO          ((uint8_t)1U)
#define PORT_MODE_PERIPHERAL  ((uint8_t)0U)

/* --------------------------------------------------------------------------
 * Port function selection
 * -------------------------------------------------------------------------- */
#define PORT_FUNCTION_KEEP    ((uint8_t)0U)
#define PORT_FUNCTION_NORMAL  ((uint8_t)1U)
#define PORT_FUNCTION_ALTERN  ((uint8_t)2U)

/* --------------------------------------------------------------------------
 * Function prototypes
 * -------------------------------------------------------------------------- */
uint8_t PORT_Enable( uint16_t port,
                     uint16_t bitmask,
                     uint8_t  direction,
                     uint8_t  mode,
                     uint8_t  function );

uint8_t PORT_Disable( uint16_t port,
                      uint16_t bitmask );
		     

#endif /* FRANKEN_FUNCTIONS_H */
