#ifndef CANDRIVER_H
#define CANDRIVER_H

/* =========================================================
 * Required CS+ / Code Generator headers
 * ========================================================= */
#include "r_cg_macrodriver.h"
#include "addl_types.h"
#include "iodefine.h"
/* =========================================================
 * RSCAN public constants
 * ========================================================= */

/* Return values */
#define EE_RSCAN_OK        (1U)
#define EE_RSCAN_ERROR     (0U)

/* Units / macros */
#define EE_RSCAN_0         (0U)
#define EE_RSCAN_1         (1U)
#define EE_RSCAN_MACROS    (1U)

/* Channels */
#define EE_RSCAN_CHANNEL0  (0U)
#define EE_RSCAN_CHANNEL1  (1U)
#define EE_RSCAN_GLOBAL    (0xFFU)

/* Operation / stop modes */
#define EE_RSCAN_OPMODE_RESET     (0U)
#define EE_RSCAN_OPMODE_HALT      (1U)
#define EE_RSCAN_OPMODE_OPER      (2U)
#define EE_RSCAN_OPMODE_SLEEP     (3U)
#define EE_RSCAN_OPMODE_RECONLY   (4U)
#define EE_RSCAN_OPMODE_STEST     (5U)

/* Global operation status */
#define EE_RSCAN_RSTATUS_OPERATION (2U)

/* =========================================================
 * Message routing
 * ========================================================= */

#define EE_RSCAN_PATH_MSGBOX      (0U)
#define EE_RSCAN_PATH_RXFIFO      (1U)
#define EE_RSCAN_PATH_COMFIFO     (2U)
#define EE_RSCAN_PATH_ANY         (3U)

#define EE_RSCAN_PATHDETAIL_ANY   (0xFFU)

/* =========================================================
 * Status / fault codes (returned via Status_puint8_t)
 * ========================================================= */

#define EE_RSCAN_FAULT_NONE       (0U)
#define EE_RSCAN_FAULT_BUSY       (1U)
#define EE_RSCAN_FAULT_PARAMETER  (2U)
#define EE_RSCAN_FAULT_NODATA     (3U)

/* =========================================================
 * Forward declarations of RSCAN data structures
 * ========================================================= */
/*
 * Full definitions are provided by the RSCAN-lite source
 * and remain private to candriver.c or its internal headers.
 */

struct ee_rscan_cfg_global;
struct ee_rscan_cfg_channel;
struct ee_rscan_message;

/* =========================================================
 * CAN driver public API
 * ========================================================= */

uint8_t EE_RSCAN_PortEnable(
        uint8_t UnitNumber_uint8_t,
        uint8_t ChannelNumber_uint8_t);

uint8_t EE_RSCAN_SetGlobalConfiguration(
        uint8_t UnitNumber_uint8_t,
        const struct ee_rscan_cfg_global *Config);

uint8_t EE_RSCAN_SetChannelConfiguration(
        uint8_t UnitNumber_uint8_t,
        uint8_t ChannelNumber_uint8_t,
        const struct ee_rscan_cfg_channel *Config);

uint8_t EE_RSCAN_Start(
        uint8_t UnitNumber_uint8_t,
        uint8_t ChannelNumber_uint8_t,
        uint8_t OperationMode_uint8_t,
        uint8_t ClearErrorCounter_uint8_t,
        uint16_t TimeStampSetting_uint16_t);

uint8_t EE_RSCAN_Stop(
        uint8_t UnitNumber_uint8_t,
        uint8_t ChannelNumber_uint8_t,
        uint8_t StopMode_uint8_t);

uint8_t EE_RSCAN_SendMessage(
        uint8_t UnitNumber_uint8_t,
        uint8_t ChannelNumber_uint8_t,
        puint8_t Status_puint8_t,
        struct ee_rscan_message *Message);

uint8_t EE_RSCAN_ReceiveMessage(
        uint8_t UnitNumber_uint8_t,
        puint8_t Status_puint8_t,
        struct ee_rscan_message *Message);

uint8_t EE_RSCAN_PortDisable(
        uint8_t UnitNumber_uint8_t,
        uint8_t ChannelNumber_uint8_t);

#endif /* CANDRIVER_H */
