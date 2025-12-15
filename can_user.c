#include <stdbool.h>
#include "r_cg_macrodriver.h"
#include "iodefine.h"
#include "r_cg_userdefine.h"
#include "map_rscan.h"
#include "rscan.h"
#include "rscan_p.h"
#include "rscan_a.h"
#include "addl_types.h"
#include "standardports.h"

uint8_t CAN_SendStatus(uint16_t can_id, uint8_t *data, uint8_t dlc)
{
    struct ee_rscan_message msg;
    uint8_t status;

    if (dlc > 8U)
    {
        return EE_RSCAN_ERROR;
    }

    /* Populate CAN message */
    msg.id        = can_id;
    msg.ide       = 0U;              /* Standard ID */
    msg.rtr       = 0U;              /* Data frame */
    msg.dlc       = dlc;

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
