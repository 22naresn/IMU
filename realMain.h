typedef enum { RELAY_ISO_POS = 0U, RELAY_ISO_NEG = 1U} relay_t;

typedef enum {ISO_STATUS_GOOD = 0U, ISO_STATUS_FAULT = 1U} iso_status_t;


#define TEST_MODE_PIN_READ()   (P1 & (1U << 0))   /* P1.0 */

#define ADC_MAX_COUNTS        1023U
#define ADC_REF_VOLTAGE_MV    5000U
#define ISO_REF_VOLTAGE_MV    2500U

#define ISO_REF_ADC_COUNTS \
    ((ISO_REF_VOLTAGE_MV * ADC_MAX_COUNTS) / ADC_REF_VOLTAGE_MV)

    
/* Allowed delta from 2.5 V (example: ±100 counts) */
#define ISO_THRESHOLD_COUNTS  100U

#define TEST_MODE_PIN_READ()   ((P7 & 0x01U) != 0U)

#define CONTACTOR_PIN_READ()   ((P12 & 0x01U) != 0U)

uint8_t test_mode_button = 0U;

