/* RENESAS OPTIMIZING LINKER GENERATED FILE 2025.12.23 */
/*** variable information ***/
/* #pragma saddr ee_rscan_common_p@2 */ /* count:208,size:2,near,static,rscan_p.obj */
/* #pragma saddr ee_rscan_channels@1 */ /* count:37,size:1,near,const,static,rscan_p.obj */
/* #pragma saddr EE_RSCAN_A_IRQ_TRX_0@6 */ /* count:12,size:1,near,static,rscan_a.obj */
/* #pragma saddr ee_rscan_aflpage_p@3 */ /* count:15,size:2,near,static,rscan_p.obj */
/* #pragma saddr LocalStatusValue_THL@11@EE_RSCAN_GetStatus */ /* count:6,size:1,near,static,rscan_p.obj */
/* #pragma saddr PNWUnit_u08@7 */ /* count:6,size:1,near,static,rscan_a.obj */
#pragma saddr EE_RSCAN_InterruptFlag_Global_u08 /* count:6,size:1,near,rscan_p.obj */
#pragma saddr EE_RSCAN_LastErrorCode_Global_u08 /* count:6,size:1,near,rscan_p.obj */
#pragma saddr EE_RSCAN_LastTxObjectChannel0_u08 /* count:6,size:1,near,rscan_p.obj */
#pragma saddr EE_RSCAN_LastTxObjectChannel1_u08 /* count:6,size:1,near,rscan_p.obj */
#pragma saddr EE_RSCAN_InterruptFlag_Unit_u08 /* count:5,size:1,near,rscan_p.obj */
#pragma saddr EE_RSCAN_InterruptFlag_Channel0_u08 /* count:4,size:1,near,rscan_p.obj */
#pragma saddr EE_RSCAN_InterruptFlag_Channel1_u08 /* count:4,size:1,near,rscan_p.obj */
#pragma saddr test_mode_button69420 /* count:3,size:1,near,realMain.obj */
/* #pragma saddr ee_rscan_ram_p@9 */ /* count:6,size:2,near,static,rscan_p.obj */
#pragma saddr gp_uart0_tx_address /* count:5,size:2,near,r_cg_serial.obj */
#pragma saddr g_uart0_tx_count /* count:4,size:2,near,r_cg_serial.obj */
#pragma saddr g_uart0_rx_count /* count:4,size:2,near,r_cg_serial.obj */
#pragma saddr EE_RSCAN_InterruptFlag_Channel_u08 /* count:4,size:2,near,rscan_p.obj */
/* #pragma saddr EE_RSCAN_A_IRQ_REC_0@4 */ /* count:1,size:1,near,static,rscan_a.obj */
/* #pragma saddr EE_RSCAN_A_IRQ_REC_1@5 */ /* count:1,size:1,near,static,rscan_a.obj */
#pragma saddr gp_uart0_rx_address /* count:3,size:2,near,r_cg_serial.obj */
#pragma saddr g_uart0_rx_length /* count:3,size:2,near,r_cg_serial.obj */
/* #pragma saddr ee_rscan_rxmsg_p@4 */ /* count:1,size:2,near,static,rscan_p.obj */
/* #pragma saddr ee_rscan_rxfifo_p@6 */ /* count:1,size:2,near,static,rscan_p.obj */
/* #pragma saddr ee_rscan_txmsg_p@5 */ /* count:1,size:4,near,static,rscan_p.obj */
/* #pragma saddr ee_rscan_comfifo_p@7 */ /* count:2,size:4,near,static,rscan_p.obj */
/* #pragma saddr ee_rscan_thl_p@8 */ /* count:3,size:4,near,static,rscan_p.obj */
#pragma saddr EE_RSCAN_LastErrorCode_Channel_u16 /* count:3,size:4,near,rscan_p.obj */
/* #pragma saddr EE_RSCAN_A_AFL_RXBOX_ANY@3 */ /* count:4,size:14,near,static,rscan_a.obj */
/* #pragma saddr EE_RSCAN_A_GCFG_BASIC@2 */ /* count:1,size:22,near,const,static,realMain.obj */
/* #pragma saddr EE_RSCAN_A_CHCFG_BASIC@1 */ /* count:1,size:26,near,const,static,realMain.obj */
/* #pragma saddr EE_RSCAN_CIVector@10 */ /* count:33,size:68,near,static,rscan_p.obj */

/*** function information ***/
#pragma callt EE_RSCAN_IRQDefault /* count:24,far,rscan_p.obj */
#pragma callt EE_RSCAN_Start /* count:19,far,rscan_p.obj */
#pragma callt RSCAN_A_UnitChannel1TransmitIRQ /* count:12,far,rscan_a.obj */
#pragma callt TestMode_Update /* count:9,far,realMain.obj */
#pragma callt Contactor_Read_Feedback /* count:9,far,realMain.obj */
#pragma callt EE_RSCAN_Stop /* count:9,far,rscan_p.obj */
#pragma callt EE_RSCAN_SetChannelConfiguration /* count:8,far,rscan_p.obj */
#pragma callt UART_SendStatus /* count:7,far,realMain.obj */
#pragma callt EE_RSCAN_PortEnable /* count:7,far,rscan_p.obj */
#pragma callt EE_RSCAN_SetGlobalConfiguration /* count:7,far,rscan_p.obj */
#pragma callt EE_RSCAN_Shutdown /* count:5,far,rscan_a.obj */
#pragma callt EE_RSCAN_SendMessage /* count:5,far,rscan_p.obj */
/* #pragma near LED_Delay@1 */ /* count:4,far,static,realMain.obj */
#pragma callt EE_RSCAN_GetTxBuffer /* count:4,far,rscan_p.obj */
#pragma callt EE_RSCAN_GetComFIFOIntStatus /* count:4,far,rscan_p.obj */
#pragma callt EE_RSCAN_EnableRXFIFO /* count:4,far,rscan_p.obj */
#pragma callt EE_RSCAN_CreateInterrupt /* count:4,far,rscan_p.obj */
#pragma callt EE_RSCAN_ReceiveMessage /* count:4,far,rscan_p.obj */
#pragma callt EE_RSCAN_SetAFLEntry /* count:4,far,rscan_p.obj */
#pragma callt R_ADC_Start /* count:3,far,r_cg_adc.obj */
#pragma callt R_ADC_Stop /* count:3,far,r_cg_adc.obj */
#pragma callt R_ADC_Get_Result /* count:3,far,r_cg_adc.obj */
#pragma callt UART_SendStatus_U16 /* count:3,far,realMain.obj */
/* #pragma near Comparator_Check@1 */ /* count:3,far,static,realMain.obj */
#pragma near PORT_Enable /* count:3,far,franken_functions.obj */
#pragma near PORT_Disable /* count:2,far,franken_functions.obj */
#pragma near Relay_On /* count:2,far,realMain.obj */
#pragma near R_PORT_Create /* count:2,far,r_cg_port.obj */
#pragma near LED_IndicateIsolationStatus /* count:2,far,realMain.obj */
/* #pragma near CAN_SendIsolation@1 */ /* count:2,far,static,realMain.obj */
#pragma near R_ADC_Create /* count:2,far,r_cg_adc.obj */
#pragma near R_UART0_Send /* count:2,far,r_cg_serial.obj */
#pragma near R_UART0_Create /* count:2,far,r_cg_serial.obj */
#pragma near EE_RSCAN_PortDisable /* count:2,far,rscan_p.obj */
#pragma near EE_RSCAN_GetFIFOStatus /* count:2,far,rscan_p.obj */
#pragma near EE_RSCAN_GetMessage /* count:2,far,rscan_p.obj */
/* #pragma near r_uart0_callback_receiveend@1 */ /* count:1,far,static,r_cg_serial_user.obj */
/* #pragma near r_uart0_callback_sendend@1 */ /* count:1,far,static,r_cg_serial_user.obj */
#pragma near R_ADC_Set_OperationOn /* count:1,far,r_cg_adc.obj */
#pragma near R_ADC_Set_OperationOff /* count:1,far,r_cg_adc.obj */
/* #pragma near r_uart0_callback_softwareoverrun@1 */ /* count:1,far,static,r_cg_serial_user.obj */
/* #pragma near r_uart0_callback_error@1 */ /* count:1,far,static,r_cg_serial_user.obj */
#pragma near hdwinit /* count:1,far,r_systeminit.obj */
#pragma near R_CGC_Get_ResetSource /* count:1,far,r_cg_cgc_user.obj */
#pragma near CAN_SendIsolationGood /* count:1,far,realMain.obj */
#pragma near CAN_SendIsolationBad /* count:1,far,realMain.obj */
#pragma near R_SAU0_Create /* count:1,far,r_cg_serial.obj */
#pragma near Relay_Off /* count:1,far,realMain.obj */
#pragma near ADC_Read_ISO_NEG /* count:1,far,realMain.obj */
#pragma near ADC_Read_ISO_POS /* count:1,far,realMain.obj */
#pragma near R_UART0_Start /* count:1,far,r_cg_serial.obj */
#pragma near R_CGC_Create /* count:1,far,r_cg_cgc.obj */
#pragma near R_Systeminit /* count:1,far,r_systeminit.obj */
#pragma near ADC_Read_V_BATT /* count:1,far,realMain.obj */
#pragma near EE_RSCAN_IntCANBusActivate /* count:1,far,rscan_p.obj */
#pragma near EE_RSCAN_GetMessageCF /* count:1,far,rscan_p.obj */
#pragma near main /* count:1,far,realMain.obj */
#pragma near EE_RSCAN_SetIDDataCFIFO /* count:1,far,rscan_p.obj */
#pragma near EE_RSCAN_SetIDData /* count:1,far,rscan_p.obj */
#pragma near EE_RSCAN_RAMTest /* count:1,far,rscan_p.obj */
#pragma near EE_RSCAN_SetBittiming /* count:1,far,rscan_p.obj */
/* #pragma near r_adc_interrupt@1 */ /* count:0,near,unref,interrupt,static,r_cg_adc_user.obj */
/* #pragma near RSCAN_A_UnitChannel1ReceiveIRQ */ /* count:0,far,unref,rscan_a.obj */
/* #pragma near RSCAN_A_UnitChannel2ReceiveIRQ */ /* count:0,far,unref,rscan_a.obj */
/* #pragma near RSCAN_A_DoNothing */ /* count:0,far,unref,rscan_a.obj */
/* #pragma near R_UART0_Stop */ /* count:0,far,unref,r_cg_serial.obj */
/* #pragma near R_UART0_Receive */ /* count:0,far,unref,r_cg_serial.obj */
/* #pragma near EE_RSCAN_GetTimeStampCounter */ /* count:0,far,unref,rscan_p.obj */
/* #pragma near r_uart0_interrupt_send@1 */ /* count:0,near,unref,interrupt,static,r_cg_serial_user.obj */
/* #pragma near EE_RSCAN_RAMTestApp */ /* count:0,far,unref,rscan_a.obj */
/* #pragma near RSCAN_A_PNWGlobalErrorIRQ */ /* count:0,far,unref,rscan_a.obj */
/* #pragma near r_uart0_interrupt_receive@1 */ /* count:0,near,unref,interrupt,static,r_cg_serial_user.obj */
/* #pragma near EE_RSCAN_EnableCOMFIFO */ /* count:0,far,unref,rscan_p.obj */
/* #pragma near EE_RSCAN_GetError */ /* count:0,far,unref,rscan_p.obj */
/* #pragma near EE_RSCAN_SetGlobalFIFOConfiguration */ /* count:0,far,unref,rscan_p.obj */
/* #pragma near EE_RSCAN_BasicTest_Rx */ /* count:0,far,unref,rscan_a.obj */
/* #pragma near EE_RSCAN_TxAbort */ /* count:0,far,unref,rscan_p.obj */
/* #pragma near EE_RSCAN_BasicTest_Tx */ /* count:0,far,unref,rscan_a.obj */
/* #pragma near EE_RSCAN_BasicIntSelfTest */ /* count:0,far,unref,rscan_a.obj */
/* #pragma near EE_RSCAN_SetCOMFIFOConfiguration */ /* count:0,far,unref,rscan_p.obj */
/* #pragma near EE_RSCAN_SetInterrupt */ /* count:0,far,unref,rscan_p.obj */
/* #pragma near EE_RSCAN_BasicSelfTest */ /* count:0,far,unref,rscan_a.obj */
/* #pragma near EE_RSCAN_BasicTest */ /* count:0,far,unref,rscan_a.obj */
/* #pragma near EE_RSCAN_GetStatus */ /* count:0,far,unref,rscan_p.obj */
/* #pragma near EE_RSCAN_Interrupt */ /* count:0,far,unref,rscan_p.obj */

