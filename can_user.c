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

uint8_t CAN_SendStatus(uint16_t can_id, uint8_t *data, uint8_t dlc)
{
    struct ee_rscan_message msg;
    uint8_t status;

    if (dlc > 8U)
    {
        return EE_RSCAN_ERROR;
    }

    /* Populate CAN message header */
    msg.hdr.id  = can_id;   /* 11-bit or 29-bit ID */
    msg.hdr.ide = 0U;       /* 0 = Standard ID, 1 = Extended ID */
    msg.hdr.rtr = 0U;       /* 0 = Data frame, 1 = Remote frame */
    msg.flag.dlc = dlc;      /* 0–8 */


    for (uint8_t i = 0U; i < dlc; i++)
    {
        msg.data[i] = data[i];
    }

    /* Transmission routing */
    msg.path       = EE_RSCAN_PATH_MSGBOX;
    msg.pathdetail = EE_RSCAN_PATHDETAIL_ANY;

    /* Send */
    if (EE_RSCAN_SendMessage(EE_RSCAN_0,
                             EE_RSCAN_CHANNEL0,
                             &status,
                             &msg) != EE_RSCAN_OK)
    {
        return EE_RSCAN_ERROR;
    }

    /* If hardware busy, caller may retry later */
    if (status == EE_RSCAN_FAULT_BUSY)
    {
        return EE_RSCAN_ERROR;
    }

    return EE_RSCAN_OK;
}
