typedef enum
{
    RELAY_ISO_POS = 0,
    RELAY_ISO_NEG
} relay_t;


typedef enum
{
    ISO_STATUS_GOOD = 0,
    ISO_STATUS_FAULT
} iso_status_t;


uint8_t test_mode_status = 0U;


#define TEST_MODE_PIN_READ()   (P1 & (1U << 0))   /* P1.0 */
