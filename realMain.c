#include <stdbool.h>
#include <stddef.h>
#include "r_cg_macrodriver.h"
#include "iodefine.h"
#include "r_cg_userdefine.h"
#include "map_rscan.h"
#include "rscan.h"
#include "rscan_p.h"
#include "rscan_a.h"
#include "addl_types.h"
#include "realMain.h"
#include "r_cg_adc.h"
#include "r_cg_port.h"
#include "r_cg_serial.h"
#include "r_cg_cgc.h"


// FUNCTION TO READ POSITIVE ISOLATION VALUE
uint16_t ADC_Read_ISO_POS(void)
{
    uint16_t adc_result;

    /* Select ANI0 (ISO_POS) */
    ADS = _00_AD_INPUT_CHANNEL_0_3;

    /* Start conversion */
    R_ADC_Start();
    R_ADC_Set_OperationOn();

    /* Wait until conversion completes */
    while (ADIF == 0U)
    {
        ;
    }

    R_ADC_Set_OperationOff();
    R_ADC_Stop();

    /* Read result */
    R_ADC_Get_Result(&adc_result);

    return adc_result;
}

//FUNCTION TO READ NEGATIVE ISOLATION VALUE
uint16_t ADC_Read_ISO_NEG(void)
{
    uint16_t adc_result;

    /* Select ANI1 (ISO_NEG) */
    ADS = _04_AD_INPUT_CHANNEL_4;

    /* Start conversion */
    R_ADC_Start();

    /* Wait until conversion completes */
    while (ADIF == 0U)
    {
        ;
    }

    /* Stop ADC */
    R_ADC_Stop();

    /* Read result */
    R_ADC_Get_Result(&adc_result);

    return adc_result;
}


// FUNCTION TO READ V_BATT ADC VALUE AND MULTIPLY WITH CONSTANT
// TO RETURN THE VOLTAGE OF THE BATTERY (2ND PART PENDING)!!
uint16_t ADC_Read_V_BATT(void)
{
    uint16_t adc_result;

    /* Select ANI2 (V_BATT) */
    ADS = _08_AD_INPUT_CHANNEL_8_11;

    /* Start conversion */
    R_ADC_Start();

    /* Wait until conversion completes */
    while (ADIF == 0U)
    {
        ;
    }

    /* Stop ADC */
    R_ADC_Stop();

    /* Read result */
    R_ADC_Get_Result(&adc_result);
    
    /* Multiply with coefficient */
    adc_result *= 19.243;
    
    /* Return the value */
    
    return adc_result;
}

// Contactor read function (Digital)
uint8_t Contactor_Read_Feedback(void)
{
    /* Read P12.0 */
    if (P12_uint8_t.no0 == 1U)
    {
        return 1U;   /* Contactor closed */
    }
    else
    {
        return 0U;   /* Contactor open */
    }
}

// UART send function (boutta be called to the ground)
void UART_SendStatus(const char *str)
{
    uint16_t length = 0U;

    /* Calculate string length */
    while (str[length] != '\0')
    {
        length++;
    }

    /* Send string */
    R_UART0_Send((uint8_t *)str, length);
}


// CAN send frame function: (pending)

// Test mode function

void TestMode_Update(void)
{
    if (TEST_MODE_PIN_READ())
    {
        test_mode_status = 1U;
    }
    else
    {
        test_mode_status = 0U;
    }
}


// Relay ON function:

void Relay_On(relay_t relay)
{
    switch (relay)
    {
        case RELAY_ISO_POS:
            P3 |= _01_Pn0_OUTPUT_1;   /* P3.0 HIGH */
            break;

        case RELAY_ISO_NEG:
            P3 |= _04_Pn2_OUTPUT_1;   /* P3.2 HIGH */
            break;

        default:
            /* do nothing */
            break;
    }
}

// Relay OFF function:

void Relay_Off(relay_t relay)
{
    switch (relay)
    {
        case RELAY_ISO_POS:
            P3 &= (uint8_t) ~ _01_Pn0_OUTPUT_1;   /* P3.0 LOW */
            break;

        case RELAY_ISO_NEG:
            P3 &= (uint8_t)~_04_Pn2_OUTPUT_1;   /* P3.2 LOW */
            break;

        default:
            /* do nothing */
            break;
    }
}


// Delay function for LED:
static void LED_Delay(void)
{
    volatile uint32_t i;
    for (i = 0; i < 50000UL; i++)
    {
        __nop();
    }
}

// LED Red/Green Status Blink
void LED_IndicateIsolationStatus(iso_status_t status)
{
    if (status == ISO_STATUS_GOOD)
    {
        /* Green blink */
        RED_LED_OFF();

        GREEN_LED_ON();
        LED_Delay();
        GREEN_LED_OFF();
        LED_Delay();
    }
    else
    {
        /* Red blink */
        GREEN_LED_OFF();

        RED_LED_ON();
        LED_Delay();
        RED_LED_OFF();
        LED_Delay();
    }
}


/* **********************************************************



========================MAIN STARTS HERE======================



*********************************************************** */


uint8_t infiloop = 1;

while(infiloop)

{
	
	
	