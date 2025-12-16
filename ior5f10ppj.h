/*-------------------------------------------------------------------------
 *      Declarations of SFR registers, interrupt and callt vector addresses
 *      for RL78 microcontroller R5F10PPJ.
 *
 *      This file can be used by both the RL78,
 *      Assembler, ARL78, and the C/C++ compiler, ICCRL78.
 *
 *      This header file is generated from the device file:
 *          DR5F10PPJ.DVF
 *          Copyright(C) 2015 Renesas
 *          Format version V3.00, File version V1.11
 *-------------------------------------------------------------------------*/

#ifndef __IOR5F10PPJ_H__
#define __IOR5F10PPJ_H__

#if !defined(__ARL78__) && !defined(__ICCRL78__)
  #error "IOR5F10PPJ.H file for use with RL78 Assembler or Compiler only"
#endif

#if defined(__ARL78__)
  #if __CORE__ != __RL78_2__
    #error "IOR5F10PPJ.H file for use with ARL78 option --core rl78_2 only"
  #endif
#endif
#if defined(__ICCRL78__)
  #if __CORE__ != __RL78_2__
    #error "IOR5F10PPJ.H file for use with ICCRL78 option --core rl78_2 only"
  #endif
#endif

#ifdef __IAR_SYSTEMS_ICC__

#pragma system_include

#pragma language=save
#pragma language=extended

/*----------------------------------------------
 * SFR bits (default names)
 *--------------------------------------------*/

#ifndef __RL78_BIT_STRUCTURE__
  #define __RL78_BIT_STRUCTURE__
  typedef struct
  {
    unsigned char no0:1;
    unsigned char no1:1;
    unsigned char no2:1;
    unsigned char no3:1;
    unsigned char no4:1;
    unsigned char no5:1;
    unsigned char no6:1;
    unsigned char no7:1;
  } __BITS8;
#endif

#ifndef __RL78_BIT_STRUCTURE2__
  #define __RL78_BIT_STRUCTURE2__
  typedef struct
  {
    unsigned short no0:1;
    unsigned short no1:1;
    unsigned short no2:1;
    unsigned short no3:1;
    unsigned short no4:1;
    unsigned short no5:1;
    unsigned short no6:1;
    unsigned short no7:1;
    unsigned short no8:1;
    unsigned short no9:1;
    unsigned short no10:1;
    unsigned short no11:1;
    unsigned short no12:1;
    unsigned short no13:1;
    unsigned short no14:1;
    unsigned short no15:1;
  } __BITS16;
#endif

/*----------------------------------------------
 *       SFR declarations
 *--------------------------------------------*/

__saddr __no_init volatile union { unsigned char P0; __BITS8 P0_bit; } @ 0xFFF00;
__saddr __no_init volatile union { unsigned char P1; __BITS8 P1_bit; } @ 0xFFF01;
__saddr __no_init volatile union { unsigned char P3; __BITS8 P3_bit; } @ 0xFFF03;
__saddr __no_init volatile union { unsigned char P4; __BITS8 P4_bit; } @ 0xFFF04;
__saddr __no_init volatile union { unsigned char P5; __BITS8 P5_bit; } @ 0xFFF05;
__saddr __no_init volatile union { unsigned char P6; __BITS8 P6_bit; } @ 0xFFF06;
__saddr __no_init volatile union { unsigned char P7; __BITS8 P7_bit; } @ 0xFFF07;
__saddr __no_init volatile union { unsigned char P8; __BITS8 P8_bit; } @ 0xFFF08;
__saddr __no_init volatile union { unsigned char P9; __BITS8 P9_bit; } @ 0xFFF09;
__saddr __no_init volatile union { unsigned char P10; __BITS8 P10_bit; } @ 0xFFF0A;
__saddr __no_init volatile union { unsigned char P12; __BITS8 P12_bit; } @ 0xFFF0C;
__saddr __no_init volatile union { unsigned char P13; __BITS8 P13_bit; } @ 0xFFF0D;
__saddr __no_init volatile union { unsigned char P14; __BITS8 P14_bit; } @ 0xFFF0E;
__saddr __no_init volatile union { unsigned char P15; __BITS8 P15_bit; } @ 0xFFF0F;
__saddr __no_bit_access __no_init volatile union { unsigned short SDR00; __BITS16 SDR00_bit; struct { union { unsigned char SDR00L; __BITS8 SDR00L_bit; }; }; } @ 0xFFF10;
__saddr __no_bit_access __no_init volatile union { unsigned short SDR01; __BITS16 SDR01_bit; struct { union { unsigned char SDR01L; __BITS8 SDR01L_bit; }; }; } @ 0xFFF12;
__saddr __no_bit_access __no_init volatile union { unsigned short TDR00; __BITS16 TDR00_bit; } @ 0xFFF18;
__saddr __no_bit_access __no_init volatile union { unsigned short TDR01; __BITS16 TDR01_bit; struct { union { unsigned char TDR01L; __BITS8 TDR01L_bit; }; union { unsigned char TDR01H; __BITS8 TDR01H_bit; }; }; } @ 0xFFF1A;
__saddr __no_bit_access __no_init volatile const union { unsigned short ADCR; __BITS16 ADCR_bit; struct { union { unsigned char dummy; __BITS8 dummy_bit; }; union { const unsigned char ADCRH; const __BITS8 ADCRH_bit; }; }; } @ 0xFFF1E;
__sfr __no_init volatile union { unsigned char PM0; __BITS8 PM0_bit; } @ 0xFFF20;
__sfr __no_init volatile union { unsigned char PM1; __BITS8 PM1_bit; } @ 0xFFF21;
__sfr __no_init volatile union { unsigned char PM3; __BITS8 PM3_bit; } @ 0xFFF23;
__sfr __no_init volatile union { unsigned char PM4; __BITS8 PM4_bit; } @ 0xFFF24;
__sfr __no_init volatile union { unsigned char PM5; __BITS8 PM5_bit; } @ 0xFFF25;
__sfr __no_init volatile union { unsigned char PM6; __BITS8 PM6_bit; } @ 0xFFF26;
__sfr __no_init volatile union { unsigned char PM7; __BITS8 PM7_bit; } @ 0xFFF27;
__sfr __no_init volatile union { unsigned char PM8; __BITS8 PM8_bit; } @ 0xFFF28;
__sfr __no_init volatile union { unsigned char PM9; __BITS8 PM9_bit; } @ 0xFFF29;
__sfr __no_init volatile union { unsigned char PM10; __BITS8 PM10_bit; } @ 0xFFF2A;
__sfr __no_init volatile union { unsigned char PM12; __BITS8 PM12_bit; } @ 0xFFF2C;
__sfr __no_init volatile union { unsigned char PM14; __BITS8 PM14_bit; } @ 0xFFF2E;
__sfr __no_init volatile union { unsigned char PM15; __BITS8 PM15_bit; } @ 0xFFF2F;
__sfr __no_init volatile union { unsigned char ADM0; __BITS8 ADM0_bit; } @ 0xFFF30;
__sfr __no_init volatile union { unsigned char ADS; __BITS8 ADS_bit; } @ 0xFFF31;
__sfr __no_init volatile union { unsigned char ADM1; __BITS8 ADM1_bit; } @ 0xFFF32;
__sfr __no_bit_access __no_init volatile union { unsigned char DACS0; __BITS8 DACS0_bit; } @ 0xFFF34;
__sfr __no_init volatile union { unsigned char DAM; __BITS8 DAM_bit; } @ 0xFFF36;
__sfr __no_init volatile union { unsigned char KRM; __BITS8 KRM_bit; } @ 0xFFF37;
__sfr __no_init volatile union { unsigned char EGP0; __BITS8 EGP0_bit; } @ 0xFFF38;
__sfr __no_init volatile union { unsigned char EGN0; __BITS8 EGN0_bit; } @ 0xFFF39;
__sfr __no_init volatile union { unsigned char EGP1; __BITS8 EGP1_bit; } @ 0xFFF3A;
__sfr __no_init volatile union { unsigned char EGN1; __BITS8 EGN1_bit; } @ 0xFFF3B;
__sfr __no_bit_access __no_init volatile union { unsigned short SDR10; __BITS16 SDR10_bit; struct { union { unsigned char SDR10L; __BITS8 SDR10L_bit; }; }; } @ 0xFFF48;
__sfr __no_bit_access __no_init volatile union { unsigned short SDR11; __BITS16 SDR11_bit; struct { union { unsigned char SDR11L; __BITS8 SDR11L_bit; }; }; } @ 0xFFF4A;
__sfr __no_bit_access __no_init volatile union { unsigned char IICA0; __BITS8 IICA0_bit; } @ 0xFFF50;
__sfr __no_init volatile const union { unsigned char IICS0; __BITS8 IICS0_bit; } @ 0xFFF51;
__sfr __no_init volatile union { unsigned char IICF0; __BITS8 IICF0_bit; } @ 0xFFF52;
__sfr __no_bit_access __no_init volatile union { unsigned short SUBCUDW; __BITS16 SUBCUDW_bit; } @ 0xFFF54;
__sfr __no_bit_access __no_init volatile union { unsigned short TRDGRC0; __BITS16 TRDGRC0_bit; } @ 0xFFF58;
__sfr __no_bit_access __no_init volatile union { unsigned short TRDGRD0; __BITS16 TRDGRD0_bit; } @ 0xFFF5A;
__sfr __no_bit_access __no_init volatile union { unsigned short TRDGRC1; __BITS16 TRDGRC1_bit; } @ 0xFFF5C;
__sfr __no_bit_access __no_init volatile union { unsigned short TRDGRD1; __BITS16 TRDGRD1_bit; } @ 0xFFF5E;
__sfr __no_bit_access __no_init volatile union { unsigned short TDR02; __BITS16 TDR02_bit; } @ 0xFFF64;
__sfr __no_bit_access __no_init volatile union { unsigned short TDR03; __BITS16 TDR03_bit; struct { union { unsigned char TDR03L; __BITS8 TDR03L_bit; }; union { unsigned char TDR03H; __BITS8 TDR03H_bit; }; }; } @ 0xFFF66;
__sfr __no_bit_access __no_init volatile union { unsigned short TDR04; __BITS16 TDR04_bit; } @ 0xFFF68;
__sfr __no_bit_access __no_init volatile union { unsigned short TDR05; __BITS16 TDR05_bit; } @ 0xFFF6A;
__sfr __no_bit_access __no_init volatile union { unsigned short TDR06; __BITS16 TDR06_bit; } @ 0xFFF6C;
__sfr __no_bit_access __no_init volatile union { unsigned short TDR07; __BITS16 TDR07_bit; } @ 0xFFF6E;
__sfr __no_bit_access __no_init volatile union { unsigned short TDR10; __BITS16 TDR10_bit; } @ 0xFFF70;
__sfr __no_bit_access __no_init volatile union { unsigned short TDR11; __BITS16 TDR11_bit; struct { union { unsigned char TDR11L; __BITS8 TDR11L_bit; }; union { unsigned char TDR11H; __BITS8 TDR11H_bit; }; }; } @ 0xFFF72;
__sfr __no_bit_access __no_init volatile union { unsigned short TDR12; __BITS16 TDR12_bit; } @ 0xFFF74;
__sfr __no_bit_access __no_init volatile union { unsigned short TDR13; __BITS16 TDR13_bit; struct { union { unsigned char TDR13L; __BITS8 TDR13L_bit; }; union { unsigned char TDR13H; __BITS8 TDR13H_bit; }; }; } @ 0xFFF76;
__sfr __no_bit_access __no_init volatile union { unsigned short TDR14; __BITS16 TDR14_bit; } @ 0xFFF78;
__sfr __no_bit_access __no_init volatile union { unsigned short TDR15; __BITS16 TDR15_bit; } @ 0xFFF7A;
__sfr __no_bit_access __no_init volatile union { unsigned short TDR16; __BITS16 TDR16_bit; } @ 0xFFF7C;
__sfr __no_bit_access __no_init volatile union { unsigned short TDR17; __BITS16 TDR17_bit; } @ 0xFFF7E;
__sfr __no_bit_access __no_init volatile union { unsigned char SEC; __BITS8 SEC_bit; } @ 0xFFF92;
__sfr __no_bit_access __no_init volatile union { unsigned char MIN; __BITS8 MIN_bit; } @ 0xFFF93;
__sfr __no_bit_access __no_init volatile union { unsigned char HOUR; __BITS8 HOUR_bit; } @ 0xFFF94;
__sfr __no_bit_access __no_init volatile union { unsigned char WEEK; __BITS8 WEEK_bit; } @ 0xFFF95;
__sfr __no_bit_access __no_init volatile union { unsigned char DAY; __BITS8 DAY_bit; } @ 0xFFF96;
__sfr __no_bit_access __no_init volatile union { unsigned char MONTH; __BITS8 MONTH_bit; } @ 0xFFF97;
__sfr __no_bit_access __no_init volatile union { unsigned char YEAR; __BITS8 YEAR_bit; } @ 0xFFF98;
__sfr __no_bit_access __no_init volatile union { unsigned char SUBCUD; __BITS8 SUBCUD_bit; } @ 0xFFF99;
__sfr __no_bit_access __no_init volatile union { unsigned char ALARMWM; __BITS8 ALARMWM_bit; } @ 0xFFF9A;
__sfr __no_bit_access __no_init volatile union { unsigned char ALARMWH; __BITS8 ALARMWH_bit; } @ 0xFFF9B;
__sfr __no_bit_access __no_init volatile union { unsigned char ALARMWW; __BITS8 ALARMWW_bit; } @ 0xFFF9C;
__sfr __no_init volatile union { unsigned char RTCC0; __BITS8 RTCC0_bit; } @ 0xFFF9D;
__sfr __no_init volatile union { unsigned char RTCC1; __BITS8 RTCC1_bit; } @ 0xFFF9E;
__sfr __no_bit_access __no_init volatile union { unsigned char CMC; __BITS8 CMC_bit; } @ 0xFFFA0;
__sfr __no_init volatile union { unsigned char CSC; __BITS8 CSC_bit; } @ 0xFFFA1;
__sfr __no_init volatile const union { unsigned char OSTC; __BITS8 OSTC_bit; } @ 0xFFFA2;
__sfr __no_bit_access __no_init volatile union { unsigned char OSTS; __BITS8 OSTS_bit; } @ 0xFFFA3;
__sfr __no_init volatile union { unsigned char CKC; __BITS8 CKC_bit; } @ 0xFFFA4;
__sfr __no_init volatile union { unsigned char CKS0; __BITS8 CKS0_bit; } @ 0xFFFA5;
__sfr __no_bit_access __no_init volatile const union { unsigned char RESF; __BITS8 RESF_bit; } @ 0xFFFA8;
__sfr __no_init volatile union { unsigned char LVIM; __BITS8 LVIM_bit; } @ 0xFFFA9;
__sfr __no_init volatile union { unsigned char LVIS; __BITS8 LVIS_bit; } @ 0xFFFAA;
__sfr __no_bit_access __no_init volatile union { unsigned char WDTE; __BITS8 WDTE_bit; } @ 0xFFFAB;
__sfr __no_bit_access __no_init volatile union { unsigned char CRCIN; __BITS8 CRCIN_bit; } @ 0xFFFAC;
__sfr __no_init volatile union { unsigned short IF2; struct { union { unsigned char IF2L; __BITS8 IF2L_bit; }; union { unsigned char IF2H; __BITS8 IF2H_bit; }; }; } @ 0xFFFD0;
__sfr __no_init volatile union { unsigned char IF3L; __BITS8 IF3L_bit; } @ 0xFFFD2;
__sfr __no_init volatile union { unsigned short MK2; struct { union { unsigned char MK2L; __BITS8 MK2L_bit; }; union { unsigned char MK2H; __BITS8 MK2H_bit; }; }; } @ 0xFFFD4;
__sfr __no_init volatile union { unsigned char MK3L; __BITS8 MK3L_bit; } @ 0xFFFD6;
__sfr __no_init volatile union { unsigned short PR02; struct { union { unsigned char PR02L; __BITS8 PR02L_bit; }; union { unsigned char PR02H; __BITS8 PR02H_bit; }; }; } @ 0xFFFD8;
__sfr __no_init volatile union { unsigned char PR03L; __BITS8 PR03L_bit; } @ 0xFFFDA;
__sfr __no_init volatile union { unsigned short PR12; struct { union { unsigned char PR12L; __BITS8 PR12L_bit; }; union { unsigned char PR12H; __BITS8 PR12H_bit; }; }; } @ 0xFFFDC;
__sfr __no_init volatile union { unsigned char PR13L; __BITS8 PR13L_bit; } @ 0xFFFDE;
__sfr __no_init volatile union { unsigned short IF0; struct { union { unsigned char IF0L; __BITS8 IF0L_bit; }; union { unsigned char IF0H; __BITS8 IF0H_bit; }; }; } @ 0xFFFE0;
__sfr __no_init volatile union { unsigned short IF1; struct { union { unsigned char IF1L; __BITS8 IF1L_bit; }; union { unsigned char IF1H; __BITS8 IF1H_bit; }; }; } @ 0xFFFE2;
__sfr __no_init volatile union { unsigned short MK0; struct { union { unsigned char MK0L; __BITS8 MK0L_bit; }; union { unsigned char MK0H; __BITS8 MK0H_bit; }; }; } @ 0xFFFE4;
__sfr __no_init volatile union { unsigned short MK1; struct { union { unsigned char MK1L; __BITS8 MK1L_bit; }; union { unsigned char MK1H; __BITS8 MK1H_bit; }; }; } @ 0xFFFE6;
__sfr __no_init volatile union { unsigned short PR00; struct { union { unsigned char PR00L; __BITS8 PR00L_bit; }; union { unsigned char PR00H; __BITS8 PR00H_bit; }; }; } @ 0xFFFE8;
__sfr __no_init volatile union { unsigned short PR01; struct { union { unsigned char PR01L; __BITS8 PR01L_bit; }; union { unsigned char PR01H; __BITS8 PR01H_bit; }; }; } @ 0xFFFEA;
__sfr __no_init volatile union { unsigned short PR10; struct { union { unsigned char PR10L; __BITS8 PR10L_bit; }; union { unsigned char PR10H; __BITS8 PR10H_bit; }; }; } @ 0xFFFEC;
__sfr __no_init volatile union { unsigned short PR11; struct { union { unsigned char PR11L; __BITS8 PR11L_bit; }; union { unsigned char PR11H; __BITS8 PR11H_bit; }; }; } @ 0xFFFEE;
__sfr __no_bit_access __no_init volatile union { unsigned short MACRL; __BITS16 MACRL_bit; } @ 0xFFFF0;
__sfr __no_bit_access __no_init volatile union { unsigned short MACRH; __BITS16 MACRH_bit; } @ 0xFFFF2;
__sfr __no_init volatile union { unsigned char PMC; __BITS8 PMC_bit; } @ 0xFFFFE;

/*----------------------------------------------
 *       SFR bit declarations
 *--------------------------------------------*/

#define ADCE              ADM0_bit.no0
#define ADCS              ADM0_bit.no7

#define DACE0             DAM_bit.no4

#define SPD0              IICS0_bit.no0
#define STD0              IICS0_bit.no1
#define ACKD0             IICS0_bit.no2
#define TRC0              IICS0_bit.no3
#define COI0              IICS0_bit.no4
#define EXC0              IICS0_bit.no5
#define ALD0              IICS0_bit.no6
#define MSTS0             IICS0_bit.no7

#define IICRSV0           IICF0_bit.no0
#define STCEN0            IICF0_bit.no1
#define IICBSY0           IICF0_bit.no6
#define STCF0             IICF0_bit.no7

#define RCLOE1            RTCC0_bit.no5
#define RTCE              RTCC0_bit.no7

#define RWAIT             RTCC1_bit.no0
#define RWST              RTCC1_bit.no1
#define RIFG              RTCC1_bit.no3
#define WAFG              RTCC1_bit.no4
#define WALIE             RTCC1_bit.no6
#define WALE              RTCC1_bit.no7

#define HIOSTOP           CSC_bit.no0
#define XTSTOP            CSC_bit.no6
#define MSTOP             CSC_bit.no7

#define MCM0              CKC_bit.no4
#define MCS               CKC_bit.no5
#define CSS               CKC_bit.no6
#define CLS               CKC_bit.no7

#define PCLOE0            CKS0_bit.no7

#define LVIF              LVIM_bit.no0
#define LVIOMSK           LVIM_bit.no1
#define LVISEN            LVIM_bit.no7

#define LVILV             LVIS_bit.no0
#define LVIMD             LVIS_bit.no7

#define TMIF05            IF2L_bit.no0
#define TMIF06            IF2L_bit.no1
#define TMIF07            IF2L_bit.no2
#define LIN0WUPIF         IF2L_bit.no3
#define PIF11             IF2L_bit.no3
#define KRIF              IF2L_bit.no4
#define CAN0ERRIF         IF2L_bit.no5
#define CAN0WUPIF         IF2L_bit.no6
#define CAN0CFRIF         IF2L_bit.no7

#define CAN0TRMIF         IF2H_bit.no0
#define CANGRFRIF         IF2H_bit.no1
#define CANGERRIF         IF2H_bit.no2
#define TMIF10            IF2H_bit.no3
#define TMIF11            IF2H_bit.no4
#define TMIF12            IF2H_bit.no5
#define TMIF13            IF2H_bit.no6
#define FLIF              IF2H_bit.no7

#define LIN1WUPIF         IF3L_bit.no0
#define PIF12             IF3L_bit.no0
#define LIN1TRMIF         IF3L_bit.no1
#define LIN1RVCIF         IF3L_bit.no2
#define LIN1IF            IF3L_bit.no3
#define LIN1STAIF         IF3L_bit.no3
#define TMIF14            IF3L_bit.no4
#define TMIF15            IF3L_bit.no5
#define TMIF16            IF3L_bit.no6
#define TMIF17            IF3L_bit.no7

#define TMMK05            MK2L_bit.no0
#define TMMK06            MK2L_bit.no1
#define TMMK07            MK2L_bit.no2
#define LIN0WUPMK         MK2L_bit.no3
#define PMK11             MK2L_bit.no3
#define KRMK              MK2L_bit.no4
#define CAN0ERRMK         MK2L_bit.no5
#define CAN0WUPMK         MK2L_bit.no6
#define CAN0CFRMK         MK2L_bit.no7

#define CAN0TRMMK         MK2H_bit.no0
#define CANGRFRMK         MK2H_bit.no1
#define CANGERRMK         MK2H_bit.no2
#define TMMK10            MK2H_bit.no3
#define TMMK11            MK2H_bit.no4
#define TMMK12            MK2H_bit.no5
#define TMMK13            MK2H_bit.no6
#define FLMK              MK2H_bit.no7

#define LIN1WUPMK         MK3L_bit.no0
#define PMK12             MK3L_bit.no0
#define LIN1TRMMK         MK3L_bit.no1
#define LIN1RVCMK         MK3L_bit.no2
#define LIN1MK            MK3L_bit.no3
#define LIN1STAMK         MK3L_bit.no3
#define TMMK14            MK3L_bit.no4
#define TMMK15            MK3L_bit.no5
#define TMMK16            MK3L_bit.no6
#define TMMK17            MK3L_bit.no7

#define TMPR005           PR02L_bit.no0
#define TMPR006           PR02L_bit.no1
#define TMPR007           PR02L_bit.no2
#define LIN0WUPPR0        PR02L_bit.no3
#define PPR011            PR02L_bit.no3
#define KRPR0             PR02L_bit.no4
#define CAN0ERRPR0        PR02L_bit.no5
#define CAN0WUPPR0        PR02L_bit.no6
#define CAN0CFRPR0        PR02L_bit.no7

#define CAN0TRMPR0        PR02H_bit.no0
#define CANGRFRPR0        PR02H_bit.no1
#define CANGERRPR0        PR02H_bit.no2
#define TMPR010           PR02H_bit.no3
#define TMPR011           PR02H_bit.no4
#define TMPR012           PR02H_bit.no5
#define TMPR013           PR02H_bit.no6
#define FLPR0             PR02H_bit.no7

#define LIN1WUPPR0        PR03L_bit.no0
#define PPR012            PR03L_bit.no0
#define LIN1TRMPR0        PR03L_bit.no1
#define LIN1RVCPR0        PR03L_bit.no2
#define LIN1PR0           PR03L_bit.no3
#define LIN1STAPR0        PR03L_bit.no3
#define TMPR014           PR03L_bit.no4
#define TMPR015           PR03L_bit.no5
#define TMPR016           PR03L_bit.no6
#define TMPR017           PR03L_bit.no7

#define TMPR105           PR12L_bit.no0
#define TMPR106           PR12L_bit.no1
#define TMPR107           PR12L_bit.no2
#define LIN0WUPPR1        PR12L_bit.no3
#define PPR111            PR12L_bit.no3
#define KRPR1             PR12L_bit.no4
#define CAN0ERRPR1        PR12L_bit.no5
#define CAN0WUPPR1        PR12L_bit.no6
#define CAN0CFRPR1        PR12L_bit.no7

#define CAN0TRMPR1        PR12H_bit.no0
#define CANGRFRPR1        PR12H_bit.no1
#define CANGERRPR1        PR12H_bit.no2
#define TMPR110           PR12H_bit.no3
#define TMPR111           PR12H_bit.no4
#define TMPR112           PR12H_bit.no5
#define TMPR113           PR12H_bit.no6
#define FLPR1             PR12H_bit.no7

#define LIN1WUPPR1        PR13L_bit.no0
#define PPR112            PR13L_bit.no0
#define LIN1TRMPR1        PR13L_bit.no1
#define LIN1RVCPR1        PR13L_bit.no2
#define LIN1PR1           PR13L_bit.no3
#define LIN1STAPR1        PR13L_bit.no3
#define TMPR114           PR13L_bit.no4
#define TMPR115           PR13L_bit.no5
#define TMPR116           PR13L_bit.no6
#define TMPR117           PR13L_bit.no7

#define WDTIIF            IF0L_bit.no0
#define LVIIF             IF0L_bit.no1
#define PIF0              IF0L_bit.no2
#define PIF1              IF0L_bit.no3
#define PIF2              IF0L_bit.no4
#define PIF3              IF0L_bit.no5
#define PIF4              IF0L_bit.no6
#define SPMIF             IF0L_bit.no6
#define CMPIF0            IF0L_bit.no7
#define PIF5              IF0L_bit.no7

#define CLMIF             IF0H_bit.no0
#define PIF13             IF0H_bit.no0
#define CSIIF00           IF0H_bit.no1
#define IICIF00           IF0H_bit.no1
#define STIF0             IF0H_bit.no1
#define CSIIF01           IF0H_bit.no2
#define IICIF01           IF0H_bit.no2
#define SRIF0             IF0H_bit.no2
#define TRDIF0            IF0H_bit.no3
#define TRDIF1            IF0H_bit.no4
#define TRJIF0            IF0H_bit.no5
#define RAMIF             IF0H_bit.no6
#define LIN0TRMIF         IF0H_bit.no7

#define LIN0RVCIF         IF1L_bit.no0
#define LIN0IF            IF1L_bit.no1
#define LIN0STAIF         IF1L_bit.no1
#define IICAIF0           IF1L_bit.no2
#define PIF8              IF1L_bit.no3
#define RTCIF             IF1L_bit.no3
#define TMIF00            IF1L_bit.no4
#define TMIF01            IF1L_bit.no5
#define TMIF02            IF1L_bit.no6
#define TMIF03            IF1L_bit.no7

#define ADIF              IF1H_bit.no0
#define PIF6              IF1H_bit.no1
#define TMIF11H           IF1H_bit.no1
#define PIF7              IF1H_bit.no2
#define TMIF13H           IF1H_bit.no2
#define PIF9              IF1H_bit.no3
#define TMIF01H           IF1H_bit.no3
#define PIF10             IF1H_bit.no4
#define TMIF03H           IF1H_bit.no4
#define CSIIF10           IF1H_bit.no5
#define IICIF10           IF1H_bit.no5
#define STIF1             IF1H_bit.no5
#define CSIIF11           IF1H_bit.no6
#define IICIF11           IF1H_bit.no6
#define SRIF1             IF1H_bit.no6
#define TMIF04            IF1H_bit.no7

#define WDTIMK            MK0L_bit.no0
#define LVIMK             MK0L_bit.no1
#define PMK0              MK0L_bit.no2
#define PMK1              MK0L_bit.no3
#define PMK2              MK0L_bit.no4
#define PMK3              MK0L_bit.no5
#define PMK4              MK0L_bit.no6
#define SPMMK             MK0L_bit.no6
#define CMPMK0            MK0L_bit.no7
#define PMK5              MK0L_bit.no7

#define CLMMK             MK0H_bit.no0
#define PMK13             MK0H_bit.no0
#define CSIMK00           MK0H_bit.no1
#define IICMK00           MK0H_bit.no1
#define STMK0             MK0H_bit.no1
#define CSIMK01           MK0H_bit.no2
#define IICMK01           MK0H_bit.no2
#define SRMK0             MK0H_bit.no2
#define TRDMK0            MK0H_bit.no3
#define TRDMK1            MK0H_bit.no4
#define TRJMK0            MK0H_bit.no5
#define RAMMK             MK0H_bit.no6
#define LIN0TRMMK         MK0H_bit.no7

#define LIN0RVCMK         MK1L_bit.no0
#define LIN0MK            MK1L_bit.no1
#define LIN0STAMK         MK1L_bit.no1
#define IICAMK0           MK1L_bit.no2
#define PMK8              MK1L_bit.no3
#define RTCMK             MK1L_bit.no3
#define TMMK00            MK1L_bit.no4
#define TMMK01            MK1L_bit.no5
#define TMMK02            MK1L_bit.no6
#define TMMK03            MK1L_bit.no7

#define ADMK              MK1H_bit.no0
#define PMK6              MK1H_bit.no1
#define TMMK11H           MK1H_bit.no1
#define PMK7              MK1H_bit.no2
#define TMMK13H           MK1H_bit.no2
#define PMK9              MK1H_bit.no3
#define TMMK01H           MK1H_bit.no3
#define PMK10             MK1H_bit.no4
#define TMMK03H           MK1H_bit.no4
#define CSIMK10           MK1H_bit.no5
#define IICMK10           MK1H_bit.no5
#define STMK1             MK1H_bit.no5
#define CSIMK11           MK1H_bit.no6
#define IICMK11           MK1H_bit.no6
#define SRMK1             MK1H_bit.no6
#define TMMK04            MK1H_bit.no7

#define WDTIPR0           PR00L_bit.no0
#define LVIPR0            PR00L_bit.no1
#define PPR00             PR00L_bit.no2
#define PPR01             PR00L_bit.no3
#define PPR02             PR00L_bit.no4
#define PPR03             PR00L_bit.no5
#define PPR04             PR00L_bit.no6
#define SPMPR0            PR00L_bit.no6
#define CMPPR00           PR00L_bit.no7
#define PPR05             PR00L_bit.no7

#define CLMPR0            PR00H_bit.no0
#define PPR013            PR00H_bit.no0
#define CSIPR000          PR00H_bit.no1
#define IICPR000          PR00H_bit.no1
#define STPR00            PR00H_bit.no1
#define CSIPR001          PR00H_bit.no2
#define IICPR001          PR00H_bit.no2
#define SRPR00            PR00H_bit.no2
#define TRDPR00           PR00H_bit.no3
#define TRDPR01           PR00H_bit.no4
#define TRJPR00           PR00H_bit.no5
#define RAMPR0            PR00H_bit.no6
#define LIN0TRMPR0        PR00H_bit.no7

#define LIN0RVCPR0        PR01L_bit.no0
#define LIN0PR0           PR01L_bit.no1
#define LIN0STAPR0        PR01L_bit.no1
#define IICAPR00          PR01L_bit.no2
#define PPR08             PR01L_bit.no3
#define RTCPR0            PR01L_bit.no3
#define TMPR000           PR01L_bit.no4
#define TMPR001           PR01L_bit.no5
#define TMPR002           PR01L_bit.no6
#define TMPR003           PR01L_bit.no7

#define ADPR0             PR01H_bit.no0
#define PPR06             PR01H_bit.no1
#define TMPR011H          PR01H_bit.no1
#define PPR07             PR01H_bit.no2
#define TMPR013H          PR01H_bit.no2
#define PPR09             PR01H_bit.no3
#define TMPR001H          PR01H_bit.no3
#define PPR010            PR01H_bit.no4
#define TMPR003H          PR01H_bit.no4
#define CSIPR010          PR01H_bit.no5
#define IICPR010          PR01H_bit.no5
#define STPR01            PR01H_bit.no5
#define CSIPR011          PR01H_bit.no6
#define IICPR011          PR01H_bit.no6
#define SRPR01            PR01H_bit.no6
#define TMPR004           PR01H_bit.no7

#define WDTIPR1           PR10L_bit.no0
#define LVIPR1            PR10L_bit.no1
#define PPR10             PR10L_bit.no2
#define PPR11             PR10L_bit.no3
#define PPR12             PR10L_bit.no4
#define PPR13             PR10L_bit.no5
#define PPR14             PR10L_bit.no6
#define SPMPR1            PR10L_bit.no6
#define CMPPR10           PR10L_bit.no7
#define PPR15             PR10L_bit.no7

#define CLMPR1            PR10H_bit.no0
#define PPR113            PR10H_bit.no0
#define CSIPR100          PR10H_bit.no1
#define IICPR100          PR10H_bit.no1
#define STPR10            PR10H_bit.no1
#define CSIPR101          PR10H_bit.no2
#define IICPR101          PR10H_bit.no2
#define SRPR10            PR10H_bit.no2
#define TRDPR10           PR10H_bit.no3
#define TRDPR11           PR10H_bit.no4
#define TRJPR10           PR10H_bit.no5
#define RAMPR1            PR10H_bit.no6
#define LIN0TRMPR1        PR10H_bit.no7

#define LIN0RVCPR1        PR11L_bit.no0
#define LIN0PR1           PR11L_bit.no1
#define LIN0STAPR1        PR11L_bit.no1
#define IICAPR10          PR11L_bit.no2
#define PPR18             PR11L_bit.no3
#define RTCPR1            PR11L_bit.no3
#define TMPR100           PR11L_bit.no4
#define TMPR101           PR11L_bit.no5
#define TMPR102           PR11L_bit.no6
#define TMPR103           PR11L_bit.no7

#define ADPR1             PR11H_bit.no0
#define PPR16             PR11H_bit.no1
#define TMPR111H          PR11H_bit.no1
#define PPR17             PR11H_bit.no2
#define TMPR113H          PR11H_bit.no2
#define PPR19             PR11H_bit.no3
#define TMPR101H          PR11H_bit.no3
#define PPR110            PR11H_bit.no4
#define TMPR103H          PR11H_bit.no4
#define CSIPR110          PR11H_bit.no5
#define IICPR110          PR11H_bit.no5
#define STPR11            PR11H_bit.no5
#define CSIPR111          PR11H_bit.no6
#define IICPR111          PR11H_bit.no6
#define SRPR11            PR11H_bit.no6
#define TMPR104           PR11H_bit.no7

#define MAA               PMC_bit.no0

#pragma language=restore

#endif /* __IAR_SYSTEMS_ICC__ */

#ifdef __IAR_SYSTEMS_ASM__

/*----------------------------------------------
 *       SFR declarations
 *--------------------------------------------*/

P0         DEFINE  0xFFF00
P1         DEFINE  0xFFF01
P3         DEFINE  0xFFF03
P4         DEFINE  0xFFF04
P5         DEFINE  0xFFF05
P6         DEFINE  0xFFF06
P7         DEFINE  0xFFF07
P8         DEFINE  0xFFF08
P9         DEFINE  0xFFF09
P10        DEFINE  0xFFF0A
P12        DEFINE  0xFFF0C
P13        DEFINE  0xFFF0D
P14        DEFINE  0xFFF0E
P15        DEFINE  0xFFF0F
SDR00      DEFINE  0xFFF10
SDR00L     DEFINE  0xFFF10
SDR01      DEFINE  0xFFF12
SDR01L     DEFINE  0xFFF12
TDR00      DEFINE  0xFFF18
TDR01      DEFINE  0xFFF1A
TDR01L     DEFINE  0xFFF1A
TDR01H     DEFINE  0xFFF1B
ADCR       DEFINE  0xFFF1E
ADCRH      DEFINE  0xFFF1F
PM0        DEFINE  0xFFF20
PM1        DEFINE  0xFFF21
PM3        DEFINE  0xFFF23
PM4        DEFINE  0xFFF24
PM5        DEFINE  0xFFF25
PM6        DEFINE  0xFFF26
PM7        DEFINE  0xFFF27
PM8        DEFINE  0xFFF28
PM9        DEFINE  0xFFF29
PM10       DEFINE  0xFFF2A
PM12       DEFINE  0xFFF2C
PM14       DEFINE  0xFFF2E
PM15       DEFINE  0xFFF2F
ADM0       DEFINE  0xFFF30
ADS        DEFINE  0xFFF31
ADM1       DEFINE  0xFFF32
DACS0      DEFINE  0xFFF34
DAM        DEFINE  0xFFF36
KRM        DEFINE  0xFFF37
EGP0       DEFINE  0xFFF38
EGN0       DEFINE  0xFFF39
EGP1       DEFINE  0xFFF3A
EGN1       DEFINE  0xFFF3B
SDR10      DEFINE  0xFFF48
SDR10L     DEFINE  0xFFF48
SDR11      DEFINE  0xFFF4A
SDR11L     DEFINE  0xFFF4A
IICA0      DEFINE  0xFFF50
IICS0      DEFINE  0xFFF51
IICF0      DEFINE  0xFFF52
SUBCUDW    DEFINE  0xFFF54
TRDGRC0    DEFINE  0xFFF58
TRDGRD0    DEFINE  0xFFF5A
TRDGRC1    DEFINE  0xFFF5C
TRDGRD1    DEFINE  0xFFF5E
TDR02      DEFINE  0xFFF64
TDR03      DEFINE  0xFFF66
TDR03L     DEFINE  0xFFF66
TDR03H     DEFINE  0xFFF67
TDR04      DEFINE  0xFFF68
TDR05      DEFINE  0xFFF6A
TDR06      DEFINE  0xFFF6C
TDR07      DEFINE  0xFFF6E
TDR10      DEFINE  0xFFF70
TDR11      DEFINE  0xFFF72
TDR11L     DEFINE  0xFFF72
TDR11H     DEFINE  0xFFF73
TDR12      DEFINE  0xFFF74
TDR13      DEFINE  0xFFF76
TDR13L     DEFINE  0xFFF76
TDR13H     DEFINE  0xFFF77
TDR14      DEFINE  0xFFF78
TDR15      DEFINE  0xFFF7A
TDR16      DEFINE  0xFFF7C
TDR17      DEFINE  0xFFF7E
SEC        DEFINE  0xFFF92
MIN        DEFINE  0xFFF93
HOUR       DEFINE  0xFFF94
WEEK       DEFINE  0xFFF95
DAY        DEFINE  0xFFF96
MONTH      DEFINE  0xFFF97
YEAR       DEFINE  0xFFF98
SUBCUD     DEFINE  0xFFF99
ALARMWM    DEFINE  0xFFF9A
ALARMWH    DEFINE  0xFFF9B
ALARMWW    DEFINE  0xFFF9C
RTCC0      DEFINE  0xFFF9D
RTCC1      DEFINE  0xFFF9E
CMC        DEFINE  0xFFFA0
CSC        DEFINE  0xFFFA1
OSTC       DEFINE  0xFFFA2
OSTS       DEFINE  0xFFFA3
CKC        DEFINE  0xFFFA4
CKS0       DEFINE  0xFFFA5
RESF       DEFINE  0xFFFA8
LVIM       DEFINE  0xFFFA9
LVIS       DEFINE  0xFFFAA
WDTE       DEFINE  0xFFFAB
CRCIN      DEFINE  0xFFFAC
IF2        DEFINE  0xFFFD0
IF2L       DEFINE  0xFFFD0
IF2H       DEFINE  0xFFFD1
IF3L       DEFINE  0xFFFD2
MK2        DEFINE  0xFFFD4
MK2L       DEFINE  0xFFFD4
MK2H       DEFINE  0xFFFD5
MK3L       DEFINE  0xFFFD6
PR02       DEFINE  0xFFFD8
PR02L      DEFINE  0xFFFD8
PR02H      DEFINE  0xFFFD9
PR03L      DEFINE  0xFFFDA
PR12       DEFINE  0xFFFDC
PR12L      DEFINE  0xFFFDC
PR12H      DEFINE  0xFFFDD
PR13L      DEFINE  0xFFFDE
IF0        DEFINE  0xFFFE0
IF0L       DEFINE  0xFFFE0
IF0H       DEFINE  0xFFFE1
IF1        DEFINE  0xFFFE2
IF1L       DEFINE  0xFFFE2
IF1H       DEFINE  0xFFFE3
MK0        DEFINE  0xFFFE4
MK0L       DEFINE  0xFFFE4
MK0H       DEFINE  0xFFFE5
MK1        DEFINE  0xFFFE6
MK1L       DEFINE  0xFFFE6
MK1H       DEFINE  0xFFFE7
PR00       DEFINE  0xFFFE8
PR00L      DEFINE  0xFFFE8
PR00H      DEFINE  0xFFFE9
PR01       DEFINE  0xFFFEA
PR01L      DEFINE  0xFFFEA
PR01H      DEFINE  0xFFFEB
PR10       DEFINE  0xFFFEC
PR10L      DEFINE  0xFFFEC
PR10H      DEFINE  0xFFFED
PR11       DEFINE  0xFFFEE
PR11L      DEFINE  0xFFFEE
PR11H      DEFINE  0xFFFEF
PMC        DEFINE  0xFFFFE

#endif /* __IAR_SYSTEMS_ASM__ */

/*----------------------------------------------
 *       Interrupt vector addresses
 *--------------------------------------------*/

#define RST_vect                 (0x00)
#define INTDBG_vect              (0x02)
#define INTSRO_vect              (0x04)
#define INTWDTI_vect             (0x04)
#define INTLVI_vect              (0x06)
#define INTP0_vect               (0x08)
#define INTP1_vect               (0x0A)
#define INTP2_vect               (0x0C)
#define INTP3_vect               (0x0E)
#define INTP4_vect               (0x10)
#define INTSPM_vect              (0x10)
#define INTCMP0_vect             (0x12)
#define INTP5_vect               (0x12)
#define INTCLM_vect              (0x14)
#define INTP13_vect              (0x14)
#define INTCSI00_vect            (0x16)
#define INTIIC00_vect            (0x16)
#define INTST0_vect              (0x16)
#define INTCSI01_vect            (0x18)
#define INTIIC01_vect            (0x18)
#define INTSR0_vect              (0x18)
#define INTTRD0_vect             (0x1A)
#define INTTRD1_vect             (0x1C)
#define INTTRJ0_vect             (0x1E)
#define INTRAM_vect              (0x20)
#define INTLIN0TRM_vect          (0x22)
#define INTLIN0RVC_vect          (0x24)
#define INTLIN0_vect             (0x26)
#define INTLIN0STA_vect          (0x26)
#define INTIICA0_vect            (0x28)
#define INTP8_vect               (0x2A)
#define INTRTC_vect              (0x2A)
#define INTTM00_vect             (0x2C)
#define INTTM01_vect             (0x2E)
#define INTTM02_vect             (0x30)
#define INTTM03_vect             (0x32)
#define INTAD_vect               (0x34)
#define INTP6_vect               (0x36)
#define INTTM11H_vect            (0x36)
#define INTP7_vect               (0x38)
#define INTTM13H_vect            (0x38)
#define INTP9_vect               (0x3A)
#define INTTM01H_vect            (0x3A)
#define INTP10_vect              (0x3C)
#define INTTM03H_vect            (0x3C)
#define INTCSI10_vect            (0x3E)
#define INTIIC10_vect            (0x3E)
#define INTST1_vect              (0x3E)
#define INTCSI11_vect            (0x40)
#define INTIIC11_vect            (0x40)
#define INTSR1_vect              (0x40)
#define INTTM04_vect             (0x42)
#define INTTM05_vect             (0x44)
#define INTTM06_vect             (0x46)
#define INTTM07_vect             (0x48)
#define INTLIN0WUP_vect          (0x4A)
#define INTP11_vect              (0x4A)
#define INTKR_vect               (0x4C)
#define INTCAN0ERR_vect          (0x4E)
#define INTCAN0WUP_vect          (0x50)
#define INTCAN0CFR_vect          (0x52)
#define INTCAN0TRM_vect          (0x54)
#define INTCANGRFR_vect          (0x56)
#define INTCANGERR_vect          (0x58)
#define INTTM10_vect             (0x5A)
#define INTTM11_vect             (0x5C)
#define INTTM12_vect             (0x5E)
#define INTTM13_vect             (0x60)
#define INTFL_vect               (0x62)
#define INTLIN1WUP_vect          (0x64)
#define INTP12_vect              (0x64)
#define INTLIN1TRM_vect          (0x66)
#define INTLIN1RVC_vect          (0x68)
#define INTLIN1_vect             (0x6A)
#define INTLIN1STA_vect          (0x6A)
#define INTTM14_vect             (0x6C)
#define INTTM15_vect             (0x6E)
#define INTTM16_vect             (0x70)
#define INTTM17_vect             (0x72)
#define BRK_I_vect               (0x7E)

/*----------------------------------------------
 *       Callt vector addresses
 *--------------------------------------------*/

#define CALLT_80_vect            (0x80)
#define CALLT_82_vect            (0x82)
#define CALLT_84_vect            (0x84)
#define CALLT_86_vect            (0x86)
#define CALLT_88_vect            (0x88)
#define CALLT_8A_vect            (0x8A)
#define CALLT_8C_vect            (0x8C)
#define CALLT_8E_vect            (0x8E)
#define CALLT_90_vect            (0x90)
#define CALLT_92_vect            (0x92)
#define CALLT_94_vect            (0x94)
#define CALLT_96_vect            (0x96)
#define CALLT_98_vect            (0x98)
#define CALLT_9A_vect            (0x9A)
#define CALLT_9C_vect            (0x9C)
#define CALLT_9E_vect            (0x9E)
#define CALLT_A0_vect            (0xA0)
#define CALLT_A2_vect            (0xA2)
#define CALLT_A4_vect            (0xA4)
#define CALLT_A6_vect            (0xA6)
#define CALLT_A8_vect            (0xA8)
#define CALLT_AA_vect            (0xAA)
#define CALLT_AC_vect            (0xAC)
#define CALLT_AE_vect            (0xAE)
#define CALLT_B0_vect            (0xB0)
#define CALLT_B2_vect            (0xB2)
#define CALLT_B4_vect            (0xB4)
#define CALLT_B6_vect            (0xB6)
#define CALLT_B8_vect            (0xB8)
#define CALLT_BA_vect            (0xBA)
#define CALLT_BC_vect            (0xBC)
#define CALLT_BE_vect            (0xBE)

#endif /* __IOR5F10PPJ_H__ */
