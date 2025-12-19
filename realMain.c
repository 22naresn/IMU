#include <stdbool.h>
#include <stddef.h>
#include <math.h>
#include "r_cg_macrodriver.h"
#include "iodefine.h"
#include "r_cg_userdefine.h"
#include "r_cg_adc.h"
#include "r_cg_port.h"
#include "r_cg_serial.h"
#include "r_cg_cgc.h"
#include "map_rscan.h"
#include "addl_types.h"
#include "rscan_a.h"
#include "rscan_p.h"
#include "rscan.h"
#include "realMain.h"
//#include "rscan_s.h";

uint8_t test_mode_button69420 = 0U;


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
    adc_result = (uint16_t)((float)adc_result * 19.243f);

    
    /* Return the value */
    
    return adc_result;
}

// Contactor read function (Digital)
uint8_t Contactor_Read_Feedback(void)
{
    /* Read P12.0 */
    if (CONTACTOR_PIN_READ())
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
/************
*************/

// Test mode function

void TestMode_Update(void)
{
    if (TEST_MODE_PIN_READ())
    {
        test_mode_button69420 = 1U;
    }
    else
    {
        test_mode_button69420 = 0U;
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


// Comparator Function

static void Comparator_Check(uint16_t iso_pos, uint16_t iso_neg)
{
    uint16_t delta_pos;
    uint16_t delta_neg;


    /* Compute absolute deltas from 2.5 V reference */
    if (iso_pos > ISO_REF_ADC_COUNTS)
    {
        delta_pos = iso_pos - ISO_REF_ADC_COUNTS;
    }
    else
    {
        delta_pos = ISO_REF_ADC_COUNTS - iso_pos;
    }

    if (iso_neg > ISO_REF_ADC_COUNTS)
    {
        delta_neg = iso_neg - ISO_REF_ADC_COUNTS;
    }
    else
    {
        delta_neg = ISO_REF_ADC_COUNTS - iso_neg;
    }

    /* Check against threshold */
    if ((delta_pos > ISO_THRESHOLD_COUNTS) ||
        (delta_neg > ISO_THRESHOLD_COUNTS))
    {
        /* Isolation fault */
        LED_IndicateIsolationStatus(ISO_STATUS_FAULT);

        UART_SendStatus("ISOLATION FAULT DETECTED\r\n");
        //EE_RSCAN_SendMessage(); // YOO ADD PARAMETERS
    }
    else
    {
        /* Isolation OK */
        LED_IndicateIsolationStatus(ISO_STATUS_GOOD);
    }
}

/* *************************************************************************



==============================MAIN STARTS HERE==============================



*************************************************************************** */


void main(void)
{
	EI();
	
	uint16_t iso_pos_val;
	uint16_t iso_neg_val;
	uint16_t vbatt_val;  
	while(1)
	
	{
		

		// 1. initialise ADC ports
		R_ADC_Create();

		// 2. initialise GPIO ports 
		R_PORT_Create();
		TestMode_Update();

		// 3. initialise CAN peripheral
		//EE_RSCAN_PortEnable();            /// ADD PARAMETERS TO PASS!
		//EE_RSCAN_Start();         
		//EE_RSCAN_SetGlobalConfiguration();
		//EE_RSCAN_SetBittiming();
		//EE_RSCAN_SetChannelConfiguration();

		// 4. initialise UART peripheral
		R_UART0_Create();
		R_UART0_Start();
		TestMode_Update();
		Contactor_Read_Feedback();

		UART_SendStatus("System init complete\r\n");



		// 5. measure ISO_POS 
		iso_pos_val = ADC_Read_ISO_POS();
		UART_SendStatus("ISO_POS read\r\n");
		TestMode_Update();
		Contactor_Read_Feedback();


		// 6. measure ISO_NEG
		iso_neg_val = ADC_Read_ISO_NEG();
		UART_SendStatus("ISO_NEG read\r\n");
		TestMode_Update();
		Contactor_Read_Feedback();

		// 7. measure V_BATT
		if (test_mode_button69420 != 1)
		{
		        vbatt_val = ADC_Read_V_BATT();
		        UART_SendStatus("VBATT read, reading = vbatt_val\n");
		}
		else
		{
			UART_SendStatus("Testing Mode ON, VBATT reading paused\n");
		}

		// 8. send GPIO out to RELAY_POS enable pin 
		Relay_On(RELAY_ISO_POS);
		UART_SendStatus("Relay POS ON\r\n");
		TestMode_Update();
		Contactor_Read_Feedback();

		// 9. run the values through comparator 
		Comparator_Check(iso_pos_val, iso_neg_val);
		TestMode_Update();
		Contactor_Read_Feedback();

		// 10. send GPIO out to RELAY_NEG enable pin 
		Relay_On(RELAY_ISO_NEG);
		UART_SendStatus("Relay NEG ON\r\n");
		TestMode_Update();
		Contactor_Read_Feedback();

		// 11. run the values through comparator function 
		Comparator_Check(iso_pos_val, iso_neg_val);
		TestMode_Update();
		Contactor_Read_Feedback();

		// 12. send GPIO out to RELAY_POS (relay pos off) 
		Relay_Off(RELAY_ISO_POS);
		UART_SendStatus("Relay POS OFF\r\n");
		TestMode_Update();
		Contactor_Read_Feedback();

		// 13. run the values through the comparator function 
		Comparator_Check(iso_pos_val, iso_neg_val);
		TestMode_Update();
		Contactor_Read_Feedback();

		/* 14. called by the main program to loop all over again forever*/
	    }
}


/*void main(void)
{
    EI();   // enables interrupts 

    while (1)
    {
        realMain();
    }
}
*/
	
	