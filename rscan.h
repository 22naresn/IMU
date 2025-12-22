#ifndef _RSCAN_LITE_H
#define _RSCAN_LITE_H
                   
#include "r_cg_macrodriver.h"
#include "addl_types.h"

/* RSCAN-Lite Globals */

#define EE_RSCAN_0       ( 0 )         /* RSCAN-Lite unit selection */
#define EE_RSCAN_1       ( 1 )
#define EE_RSCAN_INVALID ( 0xFF )      /* no macro assignment */

#define EE_RSCAN_NOIRQ   false         /* status report defines */
#define EE_RSCAN_IRQ     true
#define EE_RSCAN_OK      true
#define EE_RSCAN_ERROR   false

                                        /* RSCAN-Lite dimensions */
#define EE_RSCAN_MAXMACROS      ( 2 )   /* max. units */
#define EE_RSCAN_MAXCHANNELS   	( 2 )   /* max. channels per unit */

#define EE_RSCAN_AFLPAGESIZE    ( 40 )  /* common AFL page size */
#define EE_RSCAN_MAXAFLENTRIES 	( 40 )  /* max. entries in AFL total */
#define EE_RSCAN_MAXAFLCHANSET 	( 40 )  /* max. entries in AFL per channel */
#define EE_RSCAN_MAXRXFIFOS    	( 4 )   /* for all channels */
#define EE_RSCAN_MAXRXBUFFERS  	( 32 )  /* for all channels */
#define EE_RSCAN_MAXCOMFIFOS   	( 1 )   /* per channel */
#define EE_RSCAN_MAXTXBUFFERS  	( 4 )   /* per channel */

#define EE_RSCAN_CHANNEL0      	( 0 )    /* RSCAN channels */
#define EE_RSCAN_CHANNEL1      	( 1 )
#define EE_RSCAN_GLOBAL        	( 0xFF ) /* for ALL channels */

#define EE_RSCAN_CHANNELS       ( ee_rscan_channels[ UnitNumber_u08 ] )

#define EE_RSCAN_MAXREGWIDTH    ( 16 )

#define EE_RSCAN_COMREGSBITS	  ( EE_RSCAN_MAXREGWIDTH )
#define EE_RSCAN_COMSPAREBITS   ( 4 )
#define EE_RSCAN_COMTXREGS     	( 1 )
#define EE_RSCAN_COMTXREG( N )  ( EE_RSCAN_MAXTXBUFFERS * N / EE_RSCAN_COMREGSBITS ) 
#define EE_RSCAN_COMRXREGS     	( EE_RSCAN_MAXRXBUFFERS / EE_RSCAN_COMREGSBITS )
#define EE_RSCAN_COMRXREG( N ) 	( N / EE_RSCAN_COMREGSBITS )
#define EE_RSCAN_COMRXBIT( N ) 	( N % EE_RSCAN_COMREGSBITS )

#define EE_RSCAN_GTINT_MSGBOX_TR  ( 0x01 )
#define EE_RSCAN_GTINT_MSGBOX_AR  ( 0x02 )
#define EE_RSCAN_GTINT_FIFO       ( 0x04 )
#define EE_RSCAN_GTINT_THL        ( 0x08 )

#define EE_RSCAN_COMGTINTBITS      ( EE_RSCAN_MAXREGWIDTH )
#define EE_RSCAN_COMGTINTBITSPERCH ( 8 )
#define EE_RSCAN_COMGTINTREGS      ( ( ( EE_RSCAN_COMGTINTBITSPERCH * EE_RSCAN_MAXCHANNELS ) / EE_RSCAN_COMGTINTBITS ) + 1 )
#define EE_RSCAN_COMGTINTREG( N )  ( 0 )
#define EE_RSCAN_COMGTINTBIT( N )  ( ( N % ( EE_RSCAN_COMGTINTBITS / EE_RSCAN_COMGTINTBITSPERCH ) ) * EE_RSCAN_COMGTINTBITSPERCH )

#define EE_RSCAN_COMCFINT_FLAG     ( 0x01 )

#define EE_RSCAN_COMCFINTBITS      ( 8 )
#define EE_RSCAN_COMCFINTREGS      ( ( ( EE_RSCAN_MAXCOMFIFOS * EE_RSCAN_MAXCHANNELS ) / EE_RSCAN_COMCFINTBITS ) + 1 )
#define EE_RSCAN_COMCFINTREG( N )  ( 0 )
#define EE_RSCAN_COMCFINTBIT( N )  ( N )

#define EE_RSCAN_ID_STD        ( 0 )
#define EE_RSCAN_ID_EXT        ( 1 )
#define EE_RSCAN_ID_MAX        ( 0x1FFFFFFF )
#define EE_RSCAN_ID_MASK_LOW   ( 0xFFFF )
#define EE_RSCAN_ID_MASK_HIGH  ( 0x1FFF )

#define EE_RSCAN_FRAME_DATA    ( 0 )
#define EE_RSCAN_FRAME_REMOTE  ( 1 )

#define EE_RSCAN_MASK_IDFULLCAN  ( 0xFFFFFFFF )
#define EE_RSCAN_MASK_IDDONTCARE ( 0x00000000 )
#define EE_RSCAN_MASK_DONTCARE   ( 0 )
#define EE_RSCAN_MASK_FILTER     ( 1 )

#define EE_RSCAN_DLC_MAX   ( 8 )     /* Max. Data Length Code */

#define EE_RSCAN_INT_GERR  ( 0x00 )  /* Interrupt vector definition */
#define EE_RSCAN_INT_RXF0  ( 0x01 )  /* Global vectors */
#define EE_RSCAN_INT_RXF1  ( 0x02 )
#define EE_RSCAN_INT_RXF2  ( 0x03 )
#define EE_RSCAN_INT_RXF3  ( 0x04 )

#define EE_RSCAN_INT_TX    ( 0x00 )  /* Channel vectors */
#define EE_RSCAN_INT_TXA   ( 0x01 )
#define EE_RSCAN_INT_CERR  ( 0x02 )
#define EE_RSCAN_INT_TXHL  ( 0x03 )
#define EE_RSCAN_INT_RXCF  ( 0x04 )
#define EE_RSCAN_INT_TXCF  ( 0x05 )

#define EE_RSCAN_INT_NOINT ( 0xFF )

#define EE_RSCAN_INT_ENABLE  ( 0x01 )
#define EE_RSCAN_INT_DISABLE ( 0x00 )

#define EE_RSCAN_INT_GLOBAL  ( 1 + EE_RSCAN_MAXRXFIFOS )
#define EE_RSCAN_INT_CHANNEL ( 6 )
#define EE_RSCFD_INT_MACRO   ( EE_RSCAN_INT_GLOBAL + EE_RSCAN_INT_CHANNEL )

/* Bittiming settings */

#define EE_RSCAN_BT_MAXTQ           ( 25 )
#define EE_RSCAN_BT_MINTQ           ( 8 )
#define EE_RSCAN_BT_MINTSEG1        ( 4 )
#define EE_RSCAN_BT_MAXTSEG1        ( 16 )
#define EE_RSCAN_BT_MINTSEG2        ( 2 )
#define EE_RSCAN_BT_MAXTSEG2        ( 8 )
#define EE_RSCAN_BT_MINSJW          ( 1 )
#define EE_RSCAN_BT_MAXSJW          ( 4 )
#define EE_RSCAN_BT_SYNCSEGLEN      ( 1 )

#define EE_RSCAN_BT_MAXBRP          ( 1024 )
#define EE_RSCAN_BT_SPTOPTIMUM      ( 0.75 )

#define EE_RSCAN_TRLAYERFACTOR      ( 1 )
#define EE_RSCAN_CLKMINFACTOR       ( 8 )

/* Prescaler settings (FIFO interval, Timestamp) */

#define EE_RSCAN_FIFO_MAXPRS        ( 256 )
#define EE_RSCAN_FIFO_MINPRS        ( 1 )
#define EE_RSCAN_FIFO_CKPRS         ( 10 )
#define EE_RSCAN_TS_MAXPRS          ( 32768 )
#define EE_RSCAN_TS_MINPRS          ( 1 )


/* Constant Values */   

#define EE_RSCAN_SET              ( 1 )
#define EE_RSCAN_CLEAR            ( 0 )

#define EE_RSCAN_OPMODE_OPER      ( 0x00 )
#define EE_RSCAN_OPMODE_RESET     ( 0x01 )
#define EE_RSCAN_OPMODE_HALT      ( 0x02 )
#define EE_RSCAN_OPMODE_KEEP      ( 0x03 )
#define EE_RSCAN_OPMODE_SLEEP     ( 0x04 )
#define EE_RSCAN_OPMODE_RECONLY   ( 0x05 )
#define EE_RSCAN_OPMODE_STEST     ( 0x06 )

#define EE_RSCAN_SLEEP_ENABLE     ( 0x01 )
#define EE_RSCAN_SLEEP_DISABLE    ( 0x00 )

#define EE_RSCAN_CINT_OFF         ( 0x000 )
#define EE_RSCAN_CINT_BUSERR      ( 0x001 )
#define EE_RSCAN_CINT_WARNING     ( 0x002 )
#define EE_RSCAN_CINT_PASSIVE     ( 0x004 )
#define EE_RSCAN_CINT_BUSOFF      ( 0x008 )
#define EE_RSCAN_CINT_RECOVERY    ( 0x010 )
#define EE_RSCAN_CINT_OVERLOAD    ( 0x020 )
#define EE_RSCAN_CINT_BUSLOCK     ( 0x040 )
#define EE_RSCAN_CINT_ARBLOST     ( 0x080 )
#define EE_RSCAN_CINT_TXABORT     ( 0x100 )

#define EE_RSCAN_GINT_NONE        ( 0x00 )
#define EE_RSCAN_GINT_DLCCHECK    ( 0x01 )
#define EE_RSCAN_GINT_MSGLOST     ( 0x02 )
#define EE_RSCAN_GINT_THLLOST     ( 0x04 )

#define EE_RSCAN_BOM_ISO          ( 0x00 )
#define EE_RSCAN_BOM_HALTBOFF     ( 0x01 )
#define EE_RSCAN_BOM_HALTRECV     ( 0x02 )
#define EE_RSCAN_BOM_SW           ( 0x03 )

#define EE_RSCAN_TEST_BASIC       ( 0x00 )
#define EE_RSCAN_TEST_RXONLY      ( 0x01 )
#define EE_RSCAN_TEST_EXTLOOP     ( 0x02 )
#define EE_RSCAN_TEST_INTLOOP     ( 0x03 )

#define EE_RSCAN_TXPRIO_ID        ( 0x00 )
#define EE_RSCAN_TXPRIO_MBOX      ( 0x01 )

#define EE_RSCAN_CLOCK_SYS        ( 0x00 )
#define EE_RSCAN_CLOCK_MOSC       ( 0x01 )
#define EE_RSCAN_CLOCK_TSMACRO    ( 0x00 )
#define EE_RSCAN_CLOCK_TSBIT      ( 0x01 )
#define EE_RSCAN_CLOCK_FIFO_OFF   ( 0x0000 )


/* Status Return identifiers */

#define EE_RSCAN_STATUS_OPMODE       ( 0 )
#define EE_RSCAN_STATUS_PSMODE       ( 1 )
#define EE_RSCAN_STATUS_RECEIVE      ( 2 )
#define EE_RSCAN_STATUS_TRANSMIT     ( 3 )
#define EE_RSCAN_STATUS_BUSOFF       ( 4 )
#define EE_RSCAN_STATUS_TOVF         ( 10 )
#define EE_RSCAN_STATUS_THPM         ( 11 )
#define EE_RSCAN_STATUS_TGPT         ( 12 )
#define EE_RSCAN_STATUS_VALID        ( 13 )
#define EE_RSCAN_STATUS_TRERRCOUNT   ( 16 )
#define EE_RSCAN_STATUS_RXERRCOUNT   ( 17 )
#define EE_RSCAN_STATUS_NEWTXHISTORY ( 22 )
#define EE_RSCAN_STATUS_INTERRUPT    ( 24 )
#define EE_RSCAN_STATUS_ERRCNTLEV    ( 25 )
#define EE_RSCAN_STATUS_ERRPLEV      ( 26 )
#define EE_RSCAN_STATUS_INT_RXFIFO   ( 27 )
#define EE_RSCAN_STATUS_MLT_RXFIFO   ( 28 )
#define EE_RSCAN_STATUS_MLT_COMFIFO  ( 29 )

/* Status Return values */

#define EE_RSCAN_RSTATUS_OPERATION ( 0x00 )
#define EE_RSCAN_RSTATUS_RESET     ( 0x01 )
#define EE_RSCAN_RSTATUS_HALT      ( 0x02 )
#define EE_RSCAN_RSTATUS_SLEEP     ( 0x04 )
#define EE_RSCAN_RSTATUS_PASSIVE   ( 0x08 )
#define EE_RSCAN_RSTATUS_BUSOFF    ( 0x10 )
#define EE_RSCAN_RSTATUS_TRANSMIT  ( 0x20 )
#define EE_RSCAN_RSTATUS_RECEIVE   ( 0x40 )
#define EE_RSCAN_RSTATUS_RDY       ( 0x80 )
#define EE_RSCAN_RSTATUS_RAMINIT   ( 0x08 )

/* Error Status Return values */

#define EE_RSCAN_GERROR_DLCCHECK  ( 0x01 )
#define EE_RSCAN_GERROR_MSGLOST   ( 0x02 )
#define EE_RSCAN_GERROR_THLLOST   ( 0x04 )

#define EE_RSCAN_ERROR_BUSERR     ( 0x0001 )
#define EE_RSCAN_ERROR_WARNING    ( 0x0002 )
#define EE_RSCAN_ERROR_PASSIVE    ( 0x0004 )
#define EE_RSCAN_ERROR_BUSOFF     ( 0x0008 )
#define EE_RSCAN_ERROR_RECOVERY   ( 0x0010 )
#define EE_RSCAN_ERROR_OVERLOAD   ( 0x0020 )
#define EE_RSCAN_ERROR_BUSLOCK    ( 0x0040 )
#define EE_RSCAN_ERROR_ARBLOST    ( 0x0080 )
#define EE_RSCAN_ERROR_STUFFING   ( 0x0100 )
#define EE_RSCAN_ERROR_FORM       ( 0x0200 )
#define EE_RSCAN_ERROR_ACK        ( 0x0400 )
#define EE_RSCAN_ERROR_CRC        ( 0x0800 )
#define EE_RSCAN_ERROR_BITLEV1    ( 0x1000 )
#define EE_RSCAN_ERROR_BITLEV0    ( 0x2000 )
#define EE_RSCAN_ERROR_ACKDELIM   ( 0x4000 )

#define EE_RSCAN_ERROR_CLEARALL   ( 0x0000 )

/* Constant Values */   

#define EE_RSCAN_DN_CLEARALL      ( 0x0000 )

/* FIFO Settings */

#define EE_RSCAN_FIFO_DIS	  ( 0x00 )
#define EE_RSCAN_FIFO_EN	  ( 0x01 )
#define EE_RSCAN_FIFO_TX_DIS      ( 0x00 )
#define EE_RSCAN_FIFO_TX_EN	  ( 0x01 )
#define EE_RSCAN_FIFO_RX_DIS      ( 0x00 )
#define EE_RSCAN_FIFO_RX_EN	  ( 0x01 )

#define EE_RSCAN_FIFO_DEPTH_0     ( 0x00 )
#define EE_RSCAN_FIFO_DEPTH_4     ( 0x01 )
#define EE_RSCAN_FIFO_DEPTH_8     ( 0x02 )
#define EE_RSCAN_FIFO_DEPTH_16    ( 0x03 )
#define EE_RSCAN_FIFO_DEPTH_32    ( 0x04 )
#define EE_RSCAN_FIFO_DEPTH_48    ( 0x05 )
#define EE_RSCAN_FIFO_DEPTH_64    ( 0x06 )
#define EE_RSCAN_FIFO_DEPTH_128   ( 0x07 )

#define EE_RSCAN_FIFO_ILEVEL_1D8  ( 0x00 )
#define EE_RSCAN_FIFO_ILEVEL_2D8  ( 0x01 )
#define EE_RSCAN_FIFO_ILEVEL_3D8  ( 0x02 )
#define EE_RSCAN_FIFO_ILEVEL_4D8  ( 0x03 )
#define EE_RSCAN_FIFO_ILEVEL_5D8  ( 0x04 )
#define EE_RSCAN_FIFO_ILEVEL_6D8  ( 0x05 )
#define EE_RSCAN_FIFO_ILEVEL_7D8  ( 0x06 )
#define EE_RSCAN_FIFO_ILEVEL_8D8  ( 0x07 )

#define EE_RSCAN_FIFO_INT_EN      ( 0x01 )
#define EE_RSCAN_FIFO_INT_DIS     ( 0x00 )
#define EE_RSCAN_FIFO_INT_ONEVERY ( 0x01 )
#define EE_RSCAN_FIFO_INT_ONLEVEL ( 0x00 )

#define EE_RSCAN_FIFO_MODE_RX     ( 0x00 )
#define EE_RSCAN_FIFO_MODE_TX     ( 0x01 )
#define EE_RSCAN_FIFO_MODE_GW     ( 0x02 )

#define EE_RSCAN_FIFO_IT_REFCLK   ( 0x00 )
#define EE_RSCAN_FIFO_IT_BTCLK    ( 0x01 )
#define EE_RSCAN_FIFO_IT_REFCLK1  ( 0x00 )
#define EE_RSCAN_FIFO_IT_REFCLK10 ( 0x01 )

#define EE_RSCAN_FIFO_NEXTELEMENT ( 0xFF )

#define EE_RSCAN_TID_NOTUSED      ( 0xFF )

#define EE_RSCAN_FIFO_STATUS_FULL  ( 0 )
#define EE_RSCAN_FIFO_STATUS_EMPTY ( 1 )
#define EE_RSCAN_FIFO_STATUS_LOST  ( 2 )

/* Transmit Box Settings */

#define EE_RSCAN_TRQ_ONGOING      ( 0x00 )
#define EE_RSCAN_TRQ_CLEAR        ( 0x00 )
#define EE_RSCAN_TRQ_ABORTED      ( 0x01 )
#define EE_RSCAN_TRQ_COMPLETED    ( 0x02 )
#define EE_RSCAN_TRQ_ABORTERROR   ( 0x03 )

#define EE_RSCAN_TMC_SET_TR       ( 0x01 )
#define EE_RSCAN_TMC_SET_AR       ( 0x02 )
#define EE_RSCAN_TMC_SET_OM       ( 0x04 )

#define EE_RSCAN_TMSTS_CLEAR      ( 0x00 )
#define EE_RSCAN_TMSTS_STSMSK     ( 0x19 )  /* checks TMTSTS, TMTRM and TMTARM flags! */
#define EE_RSCAN_TMSTS_RFMSK      ( 0x06 )

/* TX History List settings */

#define EE_RSCAN_THL_INT_ONLEVEL  ( 0x00 )
#define EE_RSCAN_THL_INT_ONEVERY  ( 0x01 )
#define EE_RSCAN_THL_ENTRY_ALL    ( 0x01 )
#define EE_RSCAN_THL_ENTRY_FIFO   ( 0x00 )

#define EE_RSCAN_THL_NEXTELEMENT  ( 0xFF )
#define EE_RSCAN_THL_EMPTY        ( 0x01 )

#define EE_RSCAN_THL_TX_BUFFER    ( 0x01 )
#define EE_RSCAN_THL_TX_FIFO      ( 0x02 )
#define EE_RSCAN_THL_BN_P         ( 3 )

/* AFL Settings */

#define EE_RSCAN_AFL_RXENTRY      ( 0x00 )
#define EE_RSCAN_AFL_TXENTRY      ( 0x01 )

#define EE_RSCAN_AFL_RXMB_VALID   ( 0x01 )
#define EE_RSCAN_AFL_RXMB_INVALID ( 0x00 )

#define EE_RSCAN_AFL_RXFIFO_NONE  ( 0x00 )
#define EE_RSCAN_AFL_RXFIFO_EN0   ( 0x01 )
#define EE_RSCAN_AFL_RXFIFO_EN1   ( 0x02 )
#define EE_RSCAN_AFL_RXFIFO_EN2   ( 0x04 )
#define EE_RSCAN_AFL_RXFIFO_EN3   ( 0x08 )

#define EE_RSCAN_AFL_COMFIFO_NONE ( 0x00 )
#define EE_RSCAN_AFL_COMFIFO_C0E0 ( 0x10 )
#define EE_RSCAN_AFL_COMFIFO_C1E0 ( 0x20 )

#define EE_RSCAN_BUF_DATA0_MASK   ( 0x000000FF )
#define EE_RSCAN_BUF_DATA1_MASK   ( 0x0000FF00 )
#define EE_RSCAN_BUF_DATA2_MASK   ( 0x00FF0000 )
#define EE_RSCAN_BUF_DATA3_MASK   ( 0xFF000000 )
#define EE_RSCAN_BUF_DATA4_MASK   ( 0x000000FF )
#define EE_RSCAN_BUF_DATA5_MASK   ( 0x0000FF00 )
#define EE_RSCAN_BUF_DATA6_MASK   ( 0x00FF0000 )
#define EE_RSCAN_BUF_DATA7_MASK   ( 0xFF000000 )

#define EE_RSCAN_DLCCHECK_ENABLE  ( 0x01 )
#define EE_RSCAN_DLCCHECK_DISABLE ( 0x00 )

#define EE_RSCAN_DLCREPL_ENABLE   ( 0x01 )
#define EE_RSCAN_DLCREPL_DISABLE  ( 0x00 )

#define EE_RSCAN_MIRROR_ENABLE    ( 0x01 )
#define EE_RSCAN_MIRROR_DISABLE   ( 0x00 )

#define EE_RSCAN_TIMESTAMP_RESET  ( 0x01 )
#define EE_RSCAN_TIMESTAMP_KEEP   ( 0x00 )
#define EE_RSCAN_TIMESTAMP_WRITE  ( 0x01 )

#define EE_RSCAN_PATH_MSGBOX      ( 0x00 )
#define EE_RSCAN_PATH_COMFIFO     ( 0x01 )
#define EE_RSCAN_PATH_RXFIFO      ( 0x03 )
#define EE_RSCAN_PATH_ANY         ( 0xFF )

#define EE_RSCAN_PATHDETAIL_ANY   ( 0xFF )

#define EE_RSCAN_FAULT_NONE       ( 0x00 )
#define EE_RSCAN_FAULT_PARAMETER  ( 0x01 )
#define EE_RSCAN_FAULT_BUSY       ( 0x02 )
#define EE_RSCAN_FAULT_NODATA     ( 0x04 )
#define EE_RSCAN_FAULT_OTHER      ( 0xFF )

#define EE_RSCAN_RAMTEST_KEY1     ( 0x7575 )
#define EE_RSCAN_RAMTEST_KEY2     ( 0x8A8A )
#define EE_RSCAN_RAMTEST_ENTRIES  ( 128 )    /* short words access (16-bit): 256/2 */
#define EE_RSCAN_RAMTEST_MODE     ( 0x04 )

#define EE_RSCAN_COMTEST_ALLON    ( 0x03 )
#define EE_RSCAN_COMTEST_OFF      ( 0 )
#define EE_RSCAN_COMTEST_MODE     ( 0x01 )

/*............... The RSCAN LITE access structures ............................*/

typedef struct ee_rscan_c_cfgl
{
  volatile uint16_t brp       : 10;
  volatile uint16_t RESERVED0 : 6;

} ee_rscan_c_cfgl;

typedef struct ee_rscan_c_cfgh
{
  volatile uint16_t tseg1     : 4;
  volatile uint16_t tseg2     : 3;
  volatile uint16_t RESERVED0 : 1;
  volatile uint16_t sjw       : 2;
  volatile uint16_t RESERVED1 : 6;

} ee_rscan_c_cfgh;

typedef struct ee_rscan_c_ctrl
{
  volatile uint16_t chmdc     : 2;
  volatile uint16_t cslpr     : 1;
  volatile uint16_t rtbo      : 1;
  volatile uint16_t RESERVED0 : 4;
  volatile uint16_t iel       : 8;

} ee_rscan_c_ctrl;

typedef struct ee_rscan_c_ctrh
{
  volatile uint16_t ieh       : 1;
  volatile uint16_t RESERVED0 : 4;
  volatile uint16_t bom       : 2;
  volatile uint16_t errd      : 1;
  volatile uint16_t ctme      : 1;
  volatile uint16_t ctms      : 2;
  volatile uint16_t RESERVED1 : 5;

} ee_rscan_c_ctrh;

typedef struct ee_rscan_c_stsl
{
  volatile uint16_t mds       : 2;
  volatile uint16_t slps      : 1;
  volatile uint16_t eps       : 1;
  volatile uint16_t boffs     : 1;
  volatile uint16_t trxs      : 1;
  volatile uint16_t recs      : 1;
  volatile uint16_t coms      : 1;
  volatile uint16_t RESERVED0 : 8;

} ee_rscan_c_stsl;

typedef struct ee_rscan_c_stsh
{
  volatile uint16_t rec       : 8;
  volatile uint16_t tec       : 8;

} ee_rscan_c_stsh;

typedef struct ee_rscan_c_erfll
{
  volatile uint16_t err       : 15;
  volatile uint16_t RESERVED0 : 1;

} ee_rscan_c_erfll;

typedef struct ee_rscan_c_erflh
{
  volatile uint16_t crc       : 15;
  volatile uint16_t RESERVED0 : 1;

} ee_rscan_c_erflh;

typedef struct ee_rscan_c_ch
{
  struct ee_rscan_c_cfgl  cfgl;
  struct ee_rscan_c_cfgh  cfgh;
  struct ee_rscan_c_ctrl  ctrl;
  struct ee_rscan_c_ctrh  ctrh;
  struct ee_rscan_c_stsl  stsl;
  struct ee_rscan_c_stsh  stsh;
  struct ee_rscan_c_erfll erfll;
  struct ee_rscan_c_erflh erflh;

} ee_rscan_c_ch;

typedef struct ee_rscan_c_gcfgl
{
  volatile uint16_t tpri      : 1;
  volatile uint16_t dce       : 1;
  volatile uint16_t dre       : 1;
  volatile uint16_t mme       : 1;
  volatile uint16_t dcs       : 1;
  volatile uint16_t RESERVED0 : 3;
  volatile uint16_t tsp       : 4;
  volatile uint16_t tsss      : 1;
  volatile uint16_t RESERVED1 : 3;
  
} ee_rscan_c_gcfgl;

typedef struct ee_rscan_c_gcfgh
{
  volatile uint16_t itrcp     : 16;
  
} ee_rscan_c_gcfg;

typedef struct ee_rscan_c_gctrl
{
  volatile uint16_t gmdc      : 2;
  volatile uint16_t gslpr     : 1;
  volatile uint16_t RESERVED0 : 5;
  volatile uint16_t ie        : 3;
  volatile uint16_t RESERVED1 : 5;

} ee_rscan_c_gctrl;

typedef struct ee_rscan_c_gctrh
{
  volatile uint16_t tsrst     : 1;
  volatile uint16_t RESERVED0 : 15;

} ee_rscan_c_gctr;

typedef struct ee_rscan_c_gsts
{
  volatile uint16_t mds       : 2;
  volatile uint16_t slps      : 1;
  volatile uint16_t rsts      : 1;
  volatile uint16_t RESERVED0 : 12;

} ee_rscan_c_gsts;

typedef struct ee_rscan_c_gerfl
{
  volatile uint8_t  err       : 3;
  volatile uint8_t  RESERVED0 : 5;

} ee_rscan_c_gerfl;


typedef struct ee_rscan_c_gaflcfg
{
  volatile uint16_t rnc0      : 6;
  volatile uint16_t RESERVED0 : 2;
  volatile uint16_t rnc1      : 6;
  volatile uint16_t RESERVED1 : 2;

} ee_rscan_c_gaflcfg;

typedef struct ee_rscan_c_rfcc
{
  volatile uint16_t rfe       : 1;
  volatile uint16_t rfie      : 1;
  volatile uint16_t RESERVED0 : 6;
  volatile uint16_t rfdc      : 3;
  volatile uint16_t RESERVED1 : 1;
  volatile uint16_t rfim      : 1;
  volatile uint16_t rfigcv    : 3;

} ee_rscan_c_rfcc;


typedef struct ee_rscan_c_cfccl
{
  volatile uint16_t cfe       : 1;
  volatile uint16_t cfrxie    : 1;
  volatile uint16_t cftxie    : 1;
  volatile uint16_t RESERVED0 : 5;
  volatile uint16_t cfdc      : 3;
  volatile uint16_t RESERVED1 : 1;
  volatile uint16_t cfim      : 1;
  volatile uint16_t cfigcv    : 3;

} ee_rscan_c_cfccl;

typedef struct ee_rscan_c_cfcch
{
  volatile uint16_t cfm       : 2;
  volatile uint16_t cfitss    : 1;
  volatile uint16_t cfitr     : 1;
  volatile uint16_t cftml     : 2;
  volatile uint16_t RESERVED0 : 2;
  volatile uint16_t cfitt     : 8;

} ee_rscan_c_cfcch;

typedef struct ee_rscan_c_cfcc
{
  struct ee_rscan_c_cfccl l;
  struct ee_rscan_c_cfcch h;
  
} ee_rscan_c_cfcc;

typedef struct ee_rscan_c_rfsts
{
  volatile uint16_t rfemp     : 1;
  volatile uint16_t rffll     : 1;
  volatile uint16_t rfmlt     : 1;
  volatile uint16_t rfif      : 1;
  volatile uint16_t RESERVED0 : 4;
  volatile uint16_t rfmc      : 8;

} ee_rscan_c_rfsts;

typedef struct ee_rscan_c_cfsts
{
  volatile uint16_t cfemp     : 1;
  volatile uint16_t cffll     : 1;
  volatile uint16_t cfmlt     : 1;
  volatile uint16_t cfrxif    : 1;
  volatile uint16_t cftxif    : 1;
  volatile uint16_t RESERVED0 : 3;
  volatile uint16_t cfmc      : 6;
  volatile uint16_t RESERVED1 : 2;

} ee_rscan_c_cfsts;

typedef struct ee_rscan_c_rfpctr
{
  volatile uint16_t fpc       : 8;
  volatile uint16_t RESERVED0 : 8;

} ee_rscan_c_rfpctr;

typedef struct ee_rscan_c_cfpctr
{
  volatile uint16_t fpc       : 8;
  volatile uint16_t RESERVED0 : 8;

} ee_rscan_c_cfpctr;

typedef struct ee_rscan_c_tmc
{
  volatile uint8_t tr        : 1;
  volatile uint8_t ar        : 1;
  volatile uint8_t om        : 1;
  volatile uint8_t RESERVED0 : 5;

} ee_rscan_c_tmc;

typedef struct ee_rscan_c_tmsts
{
  volatile uint8_t sts       : 1;
  volatile uint8_t rf        : 2;
  volatile uint8_t rm        : 1;
  volatile uint8_t arm       : 1;
  volatile uint8_t RESERVED0 : 3;

} ee_rscan_c_tmsts;


typedef struct ee_rscan_c_thlcc
{
  volatile uint16_t thle      : 1;
  volatile uint16_t RESERVED0 : 7;
  volatile uint16_t ie        : 1;
  volatile uint16_t im        : 1;
  volatile uint16_t dte       : 1;
  volatile uint16_t RESERVED1 : 5;

} ee_rscan_c_thlcc;

typedef struct ee_rscan_c_thlsts
{
  volatile uint16_t emp       : 1;
  volatile uint16_t fll       : 1;
  volatile uint16_t elt       : 1;
  volatile uint16_t irq       : 1;
  volatile uint16_t RESERVED0 : 4;
  volatile uint16_t mc        : 4;
  volatile uint16_t RESERVED1 : 4;

} ee_rscan_c_thlsts;

typedef struct ee_rscan_c_gtstcfg
{
  volatile uint16_t icbce	   : 2;
  volatile uint16_t RESERVED0 : 6;
  volatile uint16_t rtmps     : 3;
  volatile uint16_t RESERVED1 : 5;
  
} ee_rscan_c_gtstcfg;

typedef struct ee_rscan_c_grwcr
{
  volatile uint16_t rpage	 : 1;
  volatile uint16_t RESERVED0 : 15;
  
} ee_rscan_c_grwcr;

typedef struct ee_rscan_c_gtsc
{
 volatile uint16_t ts		 : 16;
} ee_rscan_c_gtsc;


typedef struct ee_rscan_common
{
  struct ee_rscan_c_ch      ch[ EE_RSCAN_MAXCHANNELS ];       /* channel registers */
  volatile uint16_t         RESERVED0;
  struct ee_rscan_c_gcfgl   gcfgl;
  struct ee_rscan_c_gcfgh   gcfgh;
  struct ee_rscan_c_gctrl   gctrl;
  struct ee_rscan_c_gctrh   gctrh;
  struct ee_rscan_c_gsts    gsts;                             /* global status */
  struct ee_rscan_c_gerfl   gerfl;
  volatile uint8_t			   RESERVED1;
  struct ee_rscan_c_gtsc    gtsc;
  struct ee_rscan_c_gaflcfg gaflcfg;							            /* global AFL configuration */
  volatile uint16_t              rmnb;                            	/* RX buffer configuration */
  volatile uint16_t              rmnd[ EE_RSCAN_COMRXREGS ];
  struct ee_rscan_c_rfcc    rfcc[ EE_RSCAN_MAXRXFIFOS ];      /* RX FIFO configuration */
  struct ee_rscan_c_rfsts   rfsts[ EE_RSCAN_MAXRXFIFOS ];
  struct ee_rscan_c_rfpctr  rfpctr[ EE_RSCAN_MAXRXFIFOS ];
  struct ee_rscan_c_cfcc    cfcc[ EE_RSCAN_MAXCOMFIFOS * EE_RSCAN_MAXCHANNELS ];    /* Common FIFO configuration */
  struct ee_rscan_c_cfsts   cfsts[ EE_RSCAN_MAXCOMFIFOS * EE_RSCAN_MAXCHANNELS ];
  struct ee_rscan_c_cfpctr  cfpctr[ EE_RSCAN_MAXCOMFIFOS * EE_RSCAN_MAXCHANNELS ];
  volatile uint8_t              rfmsts;
  volatile uint8_t              cfmsts;
  volatile uint8_t              rfists;
  volatile uint8_t              cfists[ EE_RSCAN_COMCFINTREGS ];  /* TX buffer configuration */
  volatile uint8_t              tmc[ EE_RSCAN_MAXTXBUFFERS * EE_RSCAN_MAXCHANNELS ]; 
  volatile uint8_t              tmsts[ EE_RSCAN_MAXTXBUFFERS * EE_RSCAN_MAXCHANNELS ];
  volatile uint16_t              tmtrsts[ EE_RSCAN_COMTXREGS ];    /* TX buffer status */
  volatile uint16_t              tmtcsts[ EE_RSCAN_COMTXREGS ];
  volatile uint16_t              tmtasts[ EE_RSCAN_COMTXREGS ];
  volatile uint16_t              tmiec[ EE_RSCAN_COMTXREGS ];
  struct ee_rscan_c_thlcc   thlcc[ EE_RSCAN_MAXCHANNELS ];    /* THL configuration */
  struct ee_rscan_c_thlsts  thlsts[ EE_RSCAN_MAXCHANNELS ];
  volatile uint16_t              thlpctr[ EE_RSCAN_MAXCHANNELS ];
  volatile uint16_t              gtintsts[ EE_RSCAN_COMTXREGS ];
  struct ee_rscan_c_grwcr   grwcr;
  struct ee_rscan_c_gtstcfg gtstcfg;
  volatile uint8_t              gtstctr;
  volatile uint8_t			   RESERVED2;
  volatile uint16_t         RESERVED3[ 2 ];
  volatile uint16_t              glockk;	
  
} ee_rscan_common;

typedef struct ee_rscan_a_aflidl
{
  volatile uint16_t id  : 16;

} ee_rscan_a_aflidl;

typedef struct ee_rscan_a_aflidh
{
  volatile uint16_t id  : 13;
  volatile uint16_t lb  : 1;
  volatile uint16_t rtr : 1;
  volatile uint16_t ide : 1;

} ee_rscan_a_aflidh;

typedef struct ee_rscan_a_aflid
{
  volatile uint32_t id  : 29;
  volatile uint32_t lb  : 1;
  volatile uint32_t rtr : 1;
  volatile uint32_t ide : 1;

} ee_rscan_a_aflid;

typedef struct ee_rscan_r_maskl
{
  volatile uint16_t id        : 16;

} ee_rscan_r_maskl;

typedef struct ee_rscan_r_maskh
{
  volatile uint16_t id        : 13;
  volatile uint16_t RESERVED0 : 1;
  volatile uint16_t rtr       : 1;
  volatile uint16_t ide       : 1;

} ee_rscan_r_maskh;

typedef struct ee_rscan_r_mask
{
  volatile uint32_t id        : 29;
  volatile uint32_t rtr       : 1;
  volatile uint32_t ide       : 1;

} ee_rscan_r_mask;

typedef struct ee_rscan_t_maskl
{
  volatile uint16_t id        : 16;

} ee_rscan_t_maskl;

typedef struct ee_rscan_t_maskh
{
  volatile uint16_t id        : 13;
  volatile uint16_t thlen     : 1;
  volatile uint16_t rtr       : 1;
  volatile uint16_t ide       : 1;

} ee_rscan_t_maskh;

typedef struct ee_rscan_a_aflptrl
{  
  volatile uint16_t rxfifomask 	: 4;
  volatile uint16_t comfifomask 	: 2;
  volatile uint16_t RESERVED0  	: 2;
  volatile uint16_t rmdp        	: 7;
  volatile uint16_t rmv          : 1;

} ee_rscan_a_aflptrl;

typedef struct ee_rscan_a_aflptrh
{  
  volatile uint16_t ptr        	: 12;
  volatile uint16_t dlc        	: 4;

} ee_rscan_a_aflptrh;

typedef struct ee_rscan_a_aflptr0
{  
  volatile uint32_t rmdp        	: 7;
  volatile uint32_t rmv              : 1;
  volatile uint32_t ptr        	: 12;
  volatile uint32_t dlc        	: 4;

} ee_rscan_a_aflptr0;

typedef struct ee_rscan_a_aflptr1
{  
  volatile uint32_t rxfifomask 	: 4;
  volatile uint32_t comfifomask 	: 2;

} ee_rscan_a_aflptr1;

typedef struct ee_rscan_a_aflhw
{
  struct ee_rscan_a_aflidl   idl;
  struct ee_rscan_a_aflidh   idh;
  struct ee_rscan_r_maskl    maskl;
  struct ee_rscan_r_maskh    maskh;
  struct ee_rscan_a_aflptrl  ptrl;
  struct ee_rscan_a_aflptrh  ptrh;

} ee_rscan_a_aflhw;

typedef struct ee_rscan_aflpage
{
  struct ee_rscan_a_aflhw af[ EE_RSCAN_AFLPAGESIZE ];

} ee_rscan_aflpage;

typedef struct ee_rscan_r_ptr
{
  volatile uint16_t ptr : 12;
  volatile uint16_t dlc : 4;	

} ee_rscan_r_ptr;

typedef struct ee_rscan_ptr
{
  uint16_t ptr;
  uint16_t dlc;	
  uint16_t ts;

} ee_rscan_ptr;

typedef struct ee_rscan_t_ptr
{
  volatile uint16_t ptr       : 8;
  volatile uint16_t RESERVED0 : 4;
  volatile uint16_t dlc       : 4;	

} ee_rscan_t_ptr;

typedef struct ee_rscan_r_rmsg
{
  struct ee_rscan_r_maskl idl;
  struct ee_rscan_r_maskh idh;
  volatile uint16_t            ts;
  struct ee_rscan_r_ptr   ptr;
  volatile uint16_t            data[ 4 ];

} ee_rscan_r_rmsg;

typedef struct ee_rscan_r_cmsg
{
  struct ee_rscan_t_maskl idl;
  struct ee_rscan_t_maskh idh;
  volatile uint16_t            ts;
  struct ee_rscan_r_ptr   ptr;
  volatile uint16_t            data[ 4 ];

} ee_rscan_r_cmsg;

typedef struct ee_rscan_t_msg
{
  struct ee_rscan_t_maskl idl;
  struct ee_rscan_t_maskh idh;
  volatile uint16_t            RESERVED0;
  struct ee_rscan_t_ptr   ptr;
  volatile uint16_t            data[ 4 ];

} ee_rscan_t_msg;

typedef struct ee_rscan_hdr
{
  uint32_t id;
  uint16_t rtr;
  uint16_t ide;
  uint16_t thlen;
  
} ee_rscan_hdr;

typedef struct ee_rscan_message
{
  struct ee_rscan_hdr    hdr;
  struct ee_rscan_ptr   flag;
  uint8_t                    data[ EE_RSCAN_DLC_MAX ];
  uint8_t                    path;
  uint8_t                    pathdetail;
  
} ee_rscan_message;

typedef struct ee_rscan_rxmsg
{
  struct ee_rscan_r_rmsg buf[ EE_RSCAN_MAXRXBUFFERS ];

} ee_rscan_rxmsg;

typedef struct ee_rscan_rxfifo
{
  struct ee_rscan_r_rmsg buf[ EE_RSCAN_MAXRXFIFOS ];

} ee_rscan_rxfifo;

typedef struct ee_rscan_comfifo
{
  struct ee_rscan_r_cmsg buf[ EE_RSCAN_MAXCOMFIFOS ];

} ee_rscan_comfifo;

typedef struct ee_rscan_txmsg
{
  struct ee_rscan_t_msg buf[ EE_RSCAN_MAXTXBUFFERS ];

} ee_rscan_txmsg;

typedef struct ee_rscan_thl
{
  volatile uint16_t bt        : 2;
  volatile uint16_t RESERVED0 : 1;
  volatile uint16_t bn        : 2;
  volatile uint16_t RESERVED1 : 3;
  volatile uint16_t tid       : 8;

} ee_rscan_thl;

typedef struct ee_rscan_ram
{
  volatile uint16_t cell[ EE_RSCAN_RAMTEST_ENTRIES ];

} ee_rscan_ram;

/* SW Channel configuration */

typedef struct ee_rscan_cfg_channel
{
  uint32_t                     bitrate;
  uint8_t                     tq_perbit;                  /* optional Parameter, can be 0 */
  uint8_t                     syncjumpwidth;              /* optional Parameter, can be 0 */
  float                     samplingpointpos;         /* optional Parameter, can be 0.0 */
  struct ee_rscan_c_ctrl  ctrl;
  struct ee_rscan_c_ctrh  ctrh;
  uint16_t                     tmiec;                   /* TX Interrupt Enable per channel */
  struct ee_rscan_c_thlcc thlcc;                                 /* THL configuration */
  struct ee_rscan_c_cfcc  cfcc[ EE_RSCAN_MAXCOMFIFOS * EE_RSCAN_MAXCHANNELS ];     
                                                            /* COM FIFO configuration */
} ee_rscan_cfg_channel;

/* Global configuration */

typedef struct ee_rscan_cfg_global
{
  struct ee_rscan_c_gcfgl  gcfgl;
  struct ee_rscan_c_gcfgh  gcfgh;
  struct ee_rscan_c_gctrl  gctrl;
  struct ee_rscan_c_gctrh  gctrh;
  volatile uint16_t             rmnb;
  volatile uint16_t             rnc[ EE_RSCAN_MAXCHANNELS ];
  struct ee_rscan_c_rfcc   rfcc[ EE_RSCAN_MAXRXFIFOS ];

} ee_rscan_cfg_global;

/* AFL Entry configuration */

typedef struct ee_rscan_a_afl
{
  struct ee_rscan_a_aflid   id;
  struct ee_rscan_r_mask    mask;
  struct ee_rscan_a_aflptr0 ptr0;
  struct ee_rscan_a_aflptr1 ptr1;

} ee_rscan_a_afl;

#endif

