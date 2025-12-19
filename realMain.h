#ifndef REALMAIN_H
#define REALMAIN_H

#include "r_cg_macrodriver.h"
#include "addl_types.h"


typedef enum { RELAY_ISO_POS = 0U, RELAY_ISO_NEG = 1U} relay_t;

typedef enum {ISO_STATUS_GOOD = 0U, ISO_STATUS_FAULT = 1U} iso_status_t;


#define TEST_MODE_PIN_READ()   (P1 & (1U << 0))   /* P1.0 */

#define ADC_MAX_COUNTS        1023U
#define ADC_REF_VOLTAGE_MV    5000U
#define ISO_REF_VOLTAGE_MV    2500U

#define ISO_REF_ADC_COUNTS \
    ((ISO_REF_VOLTAGE_MV * ADC_MAX_COUNTS) / ADC_REF_VOLTAGE_MV)

/* GREEN LED on P14.0 */
#define GREEN_LED_ON()    (P14 |=  (1U << 0))
#define GREEN_LED_OFF()   (P14 &= ~(1U << 0))

/* RED LED on P15.7 */
#define RED_LED_ON()      (P15 |=  (1U << 7))
#define RED_LED_OFF()     (P15 &= ~(1U << 7))

    
/* Allowed delta from 2.5 V (example: ±100 counts) */
#define ISO_THRESHOLD_COUNTS  100U

#define CONTACTOR_PIN_READ()   ((P12 & 0x01U) != 0U)

// USER FUNCTIONS VARIABLES / DECLARATIONS :

uint16_t ADC_Read_ISO_POS(void);

uint16_t ADC_Read_ISO_NEG(void);

uint16_t ADC_Read_V_BATT(void);

uint8_t Contactor_Read_Feedback(void);

void UART_SendStatus(const char *str);

void TestMode_Update(void);

void Relay_On(relay_t relay);

// MAIN FUNCTION VARIABLES:

extern uint8_t test_mode_button69420;

extern uint8_t channelnumber;

extern uint8_t unit_number69420;

extern uint8_t operationmode;

#endif