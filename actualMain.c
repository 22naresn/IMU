#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_serial.h"
#include "r_cg_adc.h"
#include "candriver.h"
#include "r_cg_userdefine.h"


/******** USER DEFINED FUNCTIONS **********/


// READS POSITIVE ISOLATION VALUE
uint16_t ADC_Read_ISO_POS(void)
{
    uint16_t adc_result;

    /* Select ANI0 (ISO_POS) */
    ADS = _00_AD_INPUT_CHANNEL_0_3;

    /* Start conversion */
    R_ADC_Start();

    /* Wait until conversion completes */
    while (ADIF == 0U)
    {
        ;
    }

    /* Stop ADC to be clean */
    R_ADC_Stop();

    /* Read result */
    R_ADC_Get_Result(&adc_result);

    return adc_result;
}





//READS NEGATIVE ISOLATION VALUE
uint16_t ADC_Read_ISO_NEG(void)
{
    uint16_t adc_result;

    /* Select ANI1 (ISO_NEG) */
    ADS = _04_AD_INPUT_CHANNEL_4_7;

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





// READS V_BATT ADC VALUE AND MULTIPLIES WITH CONSTANT TO RETURN THE VOLTAGE OF THE BATTERY (PENDING)!!
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

    return adc_result;
}





// Contactor Feedback Function
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





// UART Send Status Function (ts boutta get spammed fr)
void UART_SendStatus(const char *str)
{
    uint16_t length = 0U;

    /* Calculate string length */
    while (str[length] != '\0')
    {
        length++;
    }

    /* Send string (non-blocking, driver-handled) */
    R_UART0_Send((uint8_t *)str, length);
}





// Test Mode Initialisation Function: (Basicallly kills V_Batt measurement)




