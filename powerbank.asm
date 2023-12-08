//Deviec:FT61F14X
//-----------------------Variable---------------------------------
		_displayData		EQU		49H
		_displayHundred		EQU		3CH
		_displayDecade		EQU		3BH
		_displayDigit		EQU		3AH
		_dispTimer		EQU		39H
		_dispTimerFull		EQU		38H
		_dispTimerUnderVoltage		EQU		37H
		_bFlag_is_exception_full		EQU		20H
		_bFlag_gSysTick_change		EQU		7DH
		_bFlag_chg_or_dischg		EQU		7DH
		_bFlag_charge_on		EQU		7DH
		_bFlag_reg0xFD_bitx		EQU		7DH
		_bFlag_charge_qc		EQU		7DH
		_bFlag_in_small_current_mode		EQU		7DH
		_bFlag_sink_pd		EQU		7DH
		_bFlag_derating_power_non_pd_9v		EQU		29H
		_bFlag_double_key		EQU		28H
		_bFlag_discharge_qc		EQU		28H
		_bFlag_discharge_pd		EQU		28H
		_bFlag_ovp_in_pd_9v		EQU		28H
		_bFlag_under_3v3		EQU		28H
		_bFlag_Timeslice_16ms		EQU		28H
		_bFlag_Timeslice_display		EQU		28H
		_bFlag_led_blue_always_on		EQU		28H
		_bFlag_blink		EQU		27H
		_bFlag_disable_send_cmd		EQU		27H
		_bFlag_p_ext_int_is_high		EQU		27H
		_bFlag_isys_over_1A5		EQU		27H
		_bFlag_init_ip5356		EQU		6DH
		_bFlag_plus_in_12v		EQU		6DH
		_bFlag_light_load		EQU		27H
		_bFlag_Bat_CC		EQU		27H
		_bFlag_ad_voltage_battery_update		EQU		27H
		_bFlag_is_breathing_mode		EQU		27H
		_bFlag_temp_alarm		EQU		26H
		_bFlag_enable_charge		EQU		26H
		_bFlag_enable_discharge		EQU		26H
		_bFlag_temp_exception_over_chg		EQU		26H
		_bFlag_temp_exception_chg		EQU		26H
		_bFlag_temp_exception_dischg		EQU		26H
		_bFlag_ad_ntc_update		EQU		26H
		_bFlag_battery_is_low		EQU		26H
		_bFlag_shutdown_eta		EQU		25H
		_bFlag_reverse		EQU		25H
		_bFlag_charge_complete		EQU		25H
		_bFlag_bt_standby		EQU		25H
		_bFlag_init_ip53xs		EQU		25H
		_bFlag_charge_ext		EQU		25H
		_bFlag_Timeslice_1ms		EQU		25H
		_bFlag_is_trickle_charge		EQU		25H
		_bFlag_charging_from_empty		EQU		24H
		_bFlag_Calc_Coulomb_Counter		EQU		24H
		_bFlag_vsys_over_6v3		EQU		24H
		_bFlag_vsys_over_12v8		EQU		24H
		_bFlag_vsys_under_4v5		EQU		24H
		_bFlag_in_scp_A3		EQU		24H
		_bFlag_adjust_scp_ocp_5A		EQU		24H
		_bFlag_adjust_scp_ocp_4A5		EQU		24H
		_bFlag_typec_in		EQU		23H
		_bFlag_usb_a1_in		EQU		23H
		_bFlag_usb_a2_in		EQU		23H
		_bFlag_all_led_is_off		EQU		23H
		_bFlag_disable_quick_discharge		EQU		23H
		_bFlag_disable_quick_charge		EQU		23H
		_bFlag_input_ovp		EQU		23H
		_bFlag_ocp		EQU		23H
		_bFlag_short_circuit		EQU		22H
		_bFlag_disable_charge_on		EQU		22H
		_bFlag_disable_discharge_on		EQU		22H
		_bFlag_vol_bat_over_4v		EQU		22H
		_bFlag_derating_power_temp_ex		EQU		22H
		_bFlag_vol_bat_under_3v5		EQU		22H
		_bFlag_under_3v5_derating_power		EQU		22H
		_bFlag_change_total_i_limit		EQU		22H
		_bFlag_multi_port		EQU		21H
		_bFlag_trel_over_7v		EQU		21H
		_bFlag_v_chg_5v		EQU		21H
		_bFlag_v_chg_7v		EQU		21H
		_bFlag_v_chg_9v		EQU		21H
		_bFlag_v_chg_12v		EQU		21H
		_bFlag_cc_src_sink_ok		EQU		21H
		_bFlag_power_on		EQU		6DH
		_bFlag_init_battery_volume		EQU		6DH
		_bFlag_vsys_under_4v75		EQU		21H
		_bFlag_input_voltage_5v		EQU		20H
		_bFlag_bat_vol_alarm		EQU		20H
		_bFlag_under_voltage		EQU		20H
		_bFlag_bat_under_voltage		EQU		20H
		_bFlag_Timeslice_1sec		EQU		20H
		_bFlag_light_load_left		EQU		20H
		_bFlag_light_load_right		EQU		20H
		_underVoltageDispTimer		EQU		6CH
		_isys_grade		EQU		6BH
		_last_isys_grade		EQU		6AH
		_add_voltage_offset		EQU		69H
		_counter_isys_small		EQU		68H
		_counter_isys_big		EQU		67H
		_cc_dcp_mode		EQU		66H
		_last_cc_dcp_mode		EQU		65H
		_idexSum		EQU		64H
		_counter_dl		EQU		63H
		_counter_gl		EQU		62H
		_g_counter_cc		EQU		61H
		_g_counter_1sec		EQU		60H
		_timer_display_full		EQU		5FH
		_indicator_light_mode		EQU		B9H
		_displayDataLast		EQU		5EH
		_display_cycle		EQU		B6H
		_restore_reg0x86		EQU		5DH
		_restore_reg0xA6		EQU		5CH
		_restore_reg0xAC		EQU		5BH
		_restore_reg0xBB		EQU		5AH
		_timer_display_slice_16ms		EQU		59H
		_gl_timer_out		EQU		58H
		_dl_timer_out		EQU		57H
		_under_voltage_timer_out		EQU		56H
		_battery_volume_voltage		EQU		55H
		_restore_power		EQU		54H
		_restore_reg0xb1		EQU		53H
		_restore_reg0xb5		EQU		52H
		_restore_reg0xb9		EQU		51H
		_restore_reg0x29		EQU		50H
		_default_power		EQU		4FH
		_timer_derating_power		EQU		34H
		_derating_power_mode		EQU		4EH
		_timer_dly_chk_vsys		EQU		4DH
		_restore_chg_iset_vbus5v		EQU		4CH
		_restore_chg_iset_vbus9v		EQU		4BH
		_restore_chg_iset_vbus12v		EQU		4AH
		_ack_status		EQU		32H
		_ad_ntc		EQU		30H
		_ad_voltage_battery		EQU		2EH
		_ad_offset_by_power		EQU		2CH
		_timer_dly_chk_ovp		EQU		48H
		_compareTimer		EQU		47H
		_delaySleepTimer		EQU		B4H
		_sendTimer		EQU		46H
		_display_timer_mask		EQU		45H
		_forceDispTimer		EQU		6EH
		_ledDispTimer		EQU		B8H
		_timer_30_seconds		EQU		44H
		_timer_chg_minimum		EQU		43H
		_timer_dischg_minimum		EQU		42H
		_timer_led4_display		EQU		41H
		_gcounter		EQU		40H
		_display_timer_10minutes		EQU		A0H
		_gSysTickCurrent		EQU		B2H
		_gSysTick		EQU		2AH
		_current_battery		EQU		B0H
		_i_charge		EQU		AEH
		_i_discharge		EQU		ACH
		_system_voltage		EQU		AAH
		_system_current		EQU		A8H
		_ad_current_vout		EQU		A6H
		_timer_get_ip53xs_status		EQU		3FH
		_v_input_output		EQU		A4H
		_ad_i_input_output		EQU		A2H
		_gpioKeyState		EQU		3EH
		_gpioKeyWaitTimer		EQU		3DH
//		init_ip53xs@reg_ip53xs		EQU		7AH
//		init_ip53xs@Temp2		EQU		79H
//		ip53xs_writeByte@deviceAddr		EQU		77H
//		ip53xs_writeByte@deviceAddr		EQU		77H
//		ip53xs_writeByte@regAddr		EQU		75H
//		ip53xs_writeByte@sendByte		EQU		76H
//		ip53xs_writeByte@deviceAddr		EQU		77H
//		ip53xs_readByte@deviceAddr		EQU		77H
//		ip53xs_readByte@readByte		EQU		76H
//		ip53xs_readByte@deviceAddr		EQU		77H
//		ip53xs_readByte@regAddr		EQU		75H
//		ip53xs_readByte@deviceAddr		EQU		77H
//		i2c_writeByte@sendByte		EQU		73H
//		i2c_writeByte@i		EQU		74H
//		i2c_writeByte@sendByte		EQU		73H
//		i2c_writeByte@sendByte		EQU		73H
//		i2c_chk_ack@getAckTime		EQU		72H
//		i2c_readByte@readByte		EQU		73H
//		i2c_readByte@i		EQU		72H
//		get_p_ext_int_status@counter		EQU		36H
//		__dly_ms@timer		EQU		72H
//		__dly_ms@b		EQU		74H
//		__dly_ms@a		EQU		73H
//		__dly_ms@timer		EQU		72H
//		__dly_ms@timer		EQU		72H
//		__dly_us@Time		EQU		70H
//		__dly_us@a		EQU		71H
//		__dly_us@Time		EQU		70H
//		__dly_us@Time		EQU		70H
//		app_display_all@i		EQU		76H
//		app_display_all@j		EQU		75H
//		___lbmod@dividend		EQU		72H
//		___lbmod@rem		EQU		74H
//		___lbmod@counter		EQU		73H
//		___lbmod@dividend		EQU		72H
//		___lbmod@divisor		EQU		70H
//		___lbmod@dividend		EQU		72H
//		___lbdiv@dividend		EQU		71H
//		___lbdiv@quotient		EQU		73H
//		___lbdiv@counter		EQU		72H
//		___lbdiv@dividend		EQU		71H
//		___lbdiv@divisor		EQU		70H
//		___lbdiv@dividend		EQU		71H
//-----------------------Variable END---------------------------------

		MOVLP 	0H 			//0000 	0180
		LJUMP 	1BH 			//0001 	381B
		ORG		0004H
		BSR 	7EH, 0H 			//0004 	247E
		MOVLP 	0H 			//0005 	0180

		//;powerBank.c: 226: if (T4UIF)
		MOVLB 	2H 			//0006 	1022
		BTSS 	13H, 0H 		//0007 	2C13
		LJUMP 	13H 			//0008 	3813

		//;powerBank.c: 227: {
		//;powerBank.c: 230: bFlag_gSysTick_change = 1;
		BSR 	7DH, 6H 			//0009 	277D

		//;powerBank.c: 231: gSysTick++;
		MOVLB 	0H 			//000A 	1020
		INCR 	2AH, 1H 		//000B 	1AAA
		BTSC 	3H, 2H 			//000C 	2903
		INCR 	2BH, 1H 		//000D 	1AAB

		//;powerBank.c: 232: bFlag_Timeslice_1ms = 1;
		BSR 	25H, 1H 			//000E 	24A5

		//;powerBank.c: 234: if (!(gSysTick & 0x0F))
		LDR 	2AH, 0H 			//000F 	182A
		ANDWI 	FH 			//0010 	090F
		BTSC 	3H, 2H 			//0011 	2903

		//;powerBank.c: 235: {
		//;powerBank.c: 237: bFlag_Timeslice_16ms = 1;
		BSR 	28H, 2H 			//0012 	2528

		//;powerBank.c: 238: }
		//;powerBank.c: 239: }
		//;powerBank.c: 240: if (EPIF0)
		MOVLB 	0H 			//0013 	1020
		LDR 	14H, 0H 			//0014 	1814

		//;powerBank.c: 242: }
		//;powerBank.c: 244: EPIF0 = 0xFF;
		LDWI 	FFH 			//0015 	00FF
		STR 	14H 			//0016 	1094

		//;powerBank.c: 245: T4UIF = 1;
		MOVLB 	2H 			//0017 	1022
		BSR 	13H, 0H 			//0018 	2413
		BCR 	7EH, 0H 			//0019 	207E
		RETI 					//001A 	1009
		MOVLP 	0H 			//001B 	0180
		LJUMP 	1DH 			//001C 	381D
		LDWI 	20H 			//001D 	0020
		CLRF 	7DH 			//001E 	11FD
		STR 	4H 			//001F 	1084
		LDWI 	0H 			//0020 	0000
		STR 	5H 			//0021 	1085
		LDWI 	AH 			//0022 	000A
		MOVLP 	3H 			//0023 	0183
		LCALL 	3CFH 			//0024 	33CF
		MOVLP 	0H 			//0025 	0180
		LDWI 	2AH 			//0026 	002A
		STR 	4H 			//0027 	1084
		LDWI 	0H 			//0028 	0000
		STR 	5H 			//0029 	1085
		LDWI 	43H 			//002A 	0043
		MOVLP 	3H 			//002B 	0183
		LCALL 	3CFH 			//002C 	33CF
		MOVLP 	0H 			//002D 	0180
		LDWI 	A0H 			//002E 	00A0
		STR 	4H 			//002F 	1084
		LDWI 	0H 			//0030 	0000
		STR 	5H 			//0031 	1085
		LDWI 	14H 			//0032 	0014
		MOVLP 	3H 			//0033 	0183
		LCALL 	3CFH 			//0034 	33CF
		MOVLP 	0H 			//0035 	0180
		BCR 	7EH, 0H 			//0036 	207E
		MOVLB 	0H 			//0037 	1020
		LJUMP 	39H 			//0038 	3839

		//;powerBank.c: 38: init_gpio();
		LCALL 	171H 			//0039 	3171
		MOVLP 	0H 			//003A 	0180

		//;powerBank.c: 39: init_timer4();
		LCALL 	350H 			//003B 	3350
		MOVLP 	0H 			//003C 	0180

		//;powerBank.c: 40: init_system_parameter();
		LCALL 	333H 			//003D 	3333
		MOVLP 	0H 			//003E 	0180

		//;powerBank.c: 41: TRISA7 = 0;
		MOVLB 	1H 			//003F 	1021
		BCR 	CH, 7H 			//0040 	238C

		//;powerBank.c: 43: T4UIF = 1;
		MOVLB 	2H 			//0041 	1022
		BSR 	13H, 0H 			//0042 	2413

		//;powerBank.c: 45: EPIF0 = 0xFF;
		LDWI 	FFH 			//0043 	00FF
		MOVLB 	0H 			//0044 	1020
		STR 	14H 			//0045 	1094

		//;powerBank.c: 47: INTCON |= 0B11000000;
		LDWI 	C0H 			//0046 	00C0
		IORWR 	BH, 1H 		//0047 	148B

		//;powerBank.c: 48: GIE = 1;
		BSR 	BH, 7H 			//0048 	278B

		//;powerBank.c: 50: TRISA4 = 1;
		MOVLB 	1H 			//0049 	1021
		BSR 	CH, 4H 			//004A 	260C

		//;powerBank.c: 51: bFlag_init_ip5356 = 1;
		MOVLB 	0H 			//004B 	1020
		BSR 	6DH, 3H 			//004C 	25ED

		//;powerBank.c: 52: bFlag_plus_in_12v = 1;
		BSR 	6DH, 2H 			//004D 	256D

		//;powerBank.c: 55: {
		//;powerBank.c: 57: if (bFlag_Timeslice_1ms)
		BTSS 	25H, 1H 		//004E 	2CA5
		LJUMP 	4EH 			//004F 	384E

		//;powerBank.c: 58: {
		//;powerBank.c: 59: bFlag_Timeslice_1ms = 0;
		BCR 	25H, 1H 			//0050 	20A5

		//;powerBank.c: 60: if (bFlag_Timeslice_16ms)
		BTSS 	28H, 2H 		//0051 	2D28
		LJUMP 	73H 			//0052 	3873

		//;powerBank.c: 61: {
		//;powerBank.c: 62: bFlag_Timeslice_16ms = 0;
		BCR 	28H, 2H 			//0053 	2128

		//;powerBank.c: 65: }
		//;powerBank.c: 66: get_p_ext_int_status();
		//;powerBank.c: 63: if ((bFlag_p_ext_int_is_high) && (PA4))
		LCALL 	157H 			//0054 	3157
		MOVLP 	0H 			//0055 	0180

		//;powerBank.c: 68: {
		//;powerBank.c: 69: if (bFlag_plus_in_12v)
		MOVLB 	0H 			//0056 	1020
		BTSS 	6DH, 2H 		//0057 	2D6D
		LJUMP 	5CH 			//0058 	385C

		//;powerBank.c: 70: {
		//;powerBank.c: 71: bFlag_plus_in_12v = 0;
		BCR 	6DH, 2H 			//0059 	216D

		//;powerBank.c: 72: PA7 = 1;
		BSR 	CH, 7H 			//005A 	278C

		//;powerBank.c: 73: }
		LJUMP 	5EH 			//005B 	385E

		//;powerBank.c: 74: else
		//;powerBank.c: 75: {
		//;powerBank.c: 76: bFlag_plus_in_12v = 1;
		BSR 	6DH, 2H 			//005C 	256D

		//;powerBank.c: 77: PA7 = 0;
		BCR 	CH, 7H 			//005D 	238C

		//;powerBank.c: 78: }
		//;powerBank.c: 79: }
		//;powerBank.c: 157: timer_get_ip53xs_status++;
		INCR 	3FH, 1H 		//005E 	1ABF

		//;powerBank.c: 159: if (!(timer_get_ip53xs_status & 0x3F))
		LDR 	3FH, 0H 			//005F 	183F
		ANDWI 	3FH 			//0060 	093F
		BTSC 	3H, 2H 			//0061 	2903

		//;powerBank.c: 160: {
		//;powerBank.c: 161: bFlag_Timeslice_1sec = 1;
		BSR 	20H, 3H 			//0062 	25A0

		//;powerBank.c: 162: }
		//;powerBank.c: 163: timer_display_slice_16ms++;
		INCR 	59H, 1H 		//0063 	1AD9

		//;powerBank.c: 165: if (timer_display_slice_16ms >= display_cycle)
		LDR 	59H, 0H 			//0064 	1859
		STR 	7BH 			//0065 	10FB
		CLRF 	7CH 			//0066 	11FC
		MOVLB 	1H 			//0067 	1021
		LDR 	37H, 0H 			//0068 	1837
		SUBWR 	7CH, 0H 		//0069 	127C
		BTSS 	3H, 2H 			//006A 	2D03
		LJUMP 	6EH 			//006B 	386E
		LDR 	36H, 0H 			//006C 	1836
		SUBWR 	7BH, 0H 		//006D 	127B
		BTSS 	3H, 0H 			//006E 	2C03
		LJUMP 	73H 			//006F 	3873

		//;powerBank.c: 166: {
		//;powerBank.c: 167: timer_display_slice_16ms = 0;
		MOVLB 	0H 			//0070 	1020
		CLRF 	59H 			//0071 	11D9

		//;powerBank.c: 168: bFlag_Timeslice_display = 1;
		BSR 	28H, 1H 			//0072 	24A8

		//;powerBank.c: 169: }
		//;powerBank.c: 170: }
		//;powerBank.c: 171: if (bFlag_Timeslice_display)
		MOVLB 	0H 			//0073 	1020
		BTSS 	28H, 1H 		//0074 	2CA8
		LJUMP 	83H 			//0075 	3883

		//;powerBank.c: 172: {
		//;powerBank.c: 173: bFlag_Timeslice_display = 0;
		BCR 	28H, 1H 			//0076 	20A8

		//;powerBank.c: 174: if (bFlag_blink)
		BTSS 	27H, 7H 		//0077 	2FA7
		LJUMP 	7BH 			//0078 	387B

		//;powerBank.c: 175: {
		//;powerBank.c: 176: bFlag_blink = 0x00;
		BCR 	27H, 7H 			//0079 	23A7

		//;powerBank.c: 177: }
		LJUMP 	7CH 			//007A 	387C

		//;powerBank.c: 178: else
		//;powerBank.c: 179: {
		//;powerBank.c: 180: bFlag_blink = 0x01;
		BSR 	27H, 7H 			//007B 	27A7

		//;powerBank.c: 181: }
		//;powerBank.c: 182: if ((PA4) && (bFlag_p_ext_int_is_high))
		BTSC 	CH, 4H 			//007C 	2A0C
		BTSS 	27H, 5H 		//007D 	2EA7
		LJUMP 	81H 			//007E 	3881

		//;powerBank.c: 183: {
		//;powerBank.c: 184: init_ip53xs();
		LCALL 	196H 			//007F 	3196
		MOVLP 	0H 			//0080 	0180

		//;powerBank.c: 185: }
		//;powerBank.c: 198: app_display_all();
		LCALL 	89H 			//0081 	3089
		MOVLP 	0H 			//0082 	0180

		//;powerBank.c: 199: }
		//;powerBank.c: 200: if (bFlag_Timeslice_1sec)
		MOVLB 	0H 			//0083 	1020
		BTSS 	20H, 3H 		//0084 	2DA0
		LJUMP 	4EH 			//0085 	384E

		//;powerBank.c: 201: {
		//;powerBank.c: 202: bFlag_Timeslice_1sec = 0;
		BCR 	20H, 3H 			//0086 	21A0

		//;powerBank.c: 203: g_counter_1sec++;
		INCR 	60H, 1H 		//0087 	1AE0
		LJUMP 	4EH 			//0088 	384E

		//;app_display.c: 66: unsigned char i, j;
		//;app_display.c: 68: if (forceDispTimer)
		LDR 	6EH, 0H 			//0089 	186E
		BTSC 	3H, 2H 			//008A 	2903
		LJUMP 	A7H 			//008B 	38A7

		//;app_display.c: 69: {
		//;app_display.c: 70: forceDispTimer--;
		DECR 	6EH, 1H 		//008C 	13EE

		//;app_display.c: 72: if (0 == forceDispTimer)
		LDR 	6EH, 0H 			//008D 	186E

		//;app_display.c: 73: {
		//;app_display.c: 74: displayHundred = 0X80;
		LDWI 	80H 			//008E 	0080
		BTSS 	3H, 2H 			//008F 	2D03
		LJUMP 	99H 			//0090 	3899
		STR 	3CH 			//0091 	10BC

		//;app_display.c: 75: displayDecade = 0x00;
		CLRF 	3BH 			//0092 	11BB

		//;app_display.c: 76: displayDigit = 0x00;
		CLRF 	3AH 			//0093 	11BA

		//;app_display.c: 82: display_cycle = 31;
		LDWI 	1FH 			//0094 	001F
		MOVLB 	1H 			//0095 	1021
		STR 	36H 			//0096 	10B6
		CLRF 	37H 			//0097 	11B7

		//;app_display.c: 83: }
		RET 					//0098 	1008

		//;app_display.c: 84: else
		//;app_display.c: 85: {
		//;app_display.c: 86: displayHundred = 0X80;
		STR 	3CH 			//0099 	10BC

		//;app_display.c: 90: displayHundred |= 0X01;
		BSR 	3CH, 0H 			//009A 	243C

		//;app_display.c: 92: displayHundred |= DispTable[1];
		LDWI 	C4H 			//009B 	00C4
		STR 	4H 			//009C 	1084
		LDWI 	83H 			//009D 	0083
		STR 	5H 			//009E 	1085
		LDR 	0H, 0H 			//009F 	1800
		IORWR 	3CH, 1H 		//00A0 	14BC

		//;app_display.c: 93: displayDecade = DispTable[8];
		LCALL 	3AFH 			//00A1 	33AF
		MOVLP 	0H 			//00A2 	0180
		STR 	3BH 			//00A3 	10BB

		//;app_display.c: 94: displayDigit = DispTable[8];
		LCALL 	3AFH 			//00A4 	33AF
		STR 	3AH 			//00A5 	10BA
		RET 					//00A6 	1008

		//;app_display.c: 102: else if (bFlag_charge_on)
		BTSS 	7DH, 4H 		//00A7 	2E7D
		LJUMP 	E0H 			//00A8 	38E0

		//;app_display.c: 103: {
		//;app_display.c: 104: dispTimerUnderVoltage = 0;
		CLRF 	37H 			//00A9 	11B7

		//;app_display.c: 106: if (displayData < 100)
		LDWI 	64H 			//00AA 	0064
		SUBWR 	49H, 0H 		//00AB 	1249
		BTSC 	3H, 0H 			//00AC 	2803
		LJUMP 	D9H 			//00AD 	38D9

		//;app_display.c: 107: {
		//;app_display.c: 112: if (bFlag_blink)
		BTSS 	27H, 7H 		//00AE 	2FA7
		LJUMP 	CCH 			//00AF 	38CC

		//;app_display.c: 113: {
		//;app_display.c: 115: displayHundred = 0X80;
		LDWI 	80H 			//00B0 	0080
		STR 	3CH 			//00B1 	10BC

		//;app_display.c: 116: if (bFlag_charge_qc)
		BTSS 	7DH, 2H 		//00B2 	2D7D
		LJUMP 	B5H 			//00B3 	38B5

		//;app_display.c: 117: {
		//;app_display.c: 118: displayHundred |= 0X01;
		BSR 	3CH, 0H 			//00B4 	243C

		//;app_display.c: 119: }
		//;app_display.c: 121: i = displayData / 10;
		LDWI 	AH 			//00B5 	000A
		STR 	70H 			//00B6 	10F0
		LDR 	49H, 0H 			//00B7 	1849
		LCALL 	127H 			//00B8 	3127
		MOVLP 	0H 			//00B9 	0180

		//;app_display.c: 122: j = displayData % 10;
		LCALL 	3B5H 			//00BA 	33B5
		MOVLP 	0H 			//00BB 	0180
		LCALL 	13FH 			//00BC 	313F
		MOVLP 	0H 			//00BD 	0180
		STR 	75H 			//00BE 	10F5

		//;app_display.c: 126: if (i)
		LDR 	76H, 0H 			//00BF 	1876
		BTSC 	3H, 2H 			//00C0 	2903
		LJUMP 	C7H 			//00C1 	38C7

		//;app_display.c: 127: {
		//;app_display.c: 128: displayDecade = DispTable[i];
		LDR 	76H, 0H 			//00C2 	1876
		LCALL 	39BH 			//00C3 	339B
		MOVLP 	0H 			//00C4 	0180
		STR 	3BH 			//00C5 	10BB

		//;app_display.c: 129: }
		LJUMP 	C8H 			//00C6 	38C8

		//;app_display.c: 130: else
		//;app_display.c: 131: {
		//;app_display.c: 132: displayDecade = 0x00;
		CLRF 	3BH 			//00C7 	11BB

		//;app_display.c: 133: }
		//;app_display.c: 137: displayDigit = DispTable[j];
		LDR 	75H, 0H 			//00C8 	1875
		LCALL 	39BH 			//00C9 	339B
		STR 	3AH 			//00CA 	10BA

		//;app_display.c: 139: }
		RET 					//00CB 	1008

		//;app_display.c: 140: else
		//;app_display.c: 141: {
		//;app_display.c: 142: displayDigit = 0x00;
		CLRF 	3AH 			//00CC 	11BA
		LJUMP 	D6H 			//00CD 	38D6

		//;app_display.c: 149: {
		//;app_display.c: 150: dispTimerFull--;
		DECR 	38H, 1H 		//00CE 	13B8

		//;app_display.c: 154: displayHundred = 0X80;
		LDWI 	80H 			//00CF 	0080
		STR 	3CH 			//00D0 	10BC

		//;app_display.c: 155: if (bFlag_charge_qc)
		BTSC 	7DH, 2H 		//00D1 	297D

		//;app_display.c: 156: {
		//;app_display.c: 157: displayHundred |= 0X01;
		BSR 	3CH, 0H 			//00D2 	243C

		//;app_display.c: 158: }
		//;app_display.c: 159: displayHundred |= DispTable[1];
		LDWI 	C4H 			//00D3 	00C4
		STR 	4H 			//00D4 	1084

		//;app_display.c: 160: displayDecade = DispTable[0];
		//;app_display.c: 161: displayDigit = DispTable[0];
		LCALL 	38AH 			//00D5 	338A

		//;app_display.c: 143: dispTimer = (11);
		LDWI 	BH 			//00D6 	000B
		STR 	39H 			//00D7 	10B9
		RET 					//00D8 	1008

		//;app_display.c: 146: else
		//;app_display.c: 147: {
		//;app_display.c: 148: if (dispTimerFull)
		LDR 	38H, 0H 			//00D9 	1838
		BTSS 	3H, 2H 			//00DA 	2D03
		LJUMP 	CEH 			//00DB 	38CE

		//;app_display.c: 164: else
		//;app_display.c: 165: {
		//;app_display.c: 166: displayHundred = 0x00;
		CLRF 	3CH 			//00DC 	11BC

		//;app_display.c: 167: displayDecade = 0x00;
		CLRF 	3BH 			//00DD 	11BB

		//;app_display.c: 168: displayDigit = 0x00;
		CLRF 	3AH 			//00DE 	11BA
		RET 					//00DF 	1008

		//;app_display.c: 177: else
		//;app_display.c: 178: {
		//;app_display.c: 179: if (dispTimerUnderVoltage)
		LDR 	37H, 0H 			//00E0 	1837
		BTSC 	3H, 2H 			//00E1 	2903
		LJUMP 	111H 			//00E2 	3911

		//;app_display.c: 180: {
		//;app_display.c: 181: dispTimerUnderVoltage--;
		DECR 	37H, 1H 		//00E3 	13B7

		//;app_display.c: 182: dispTimer = 0;
		CLRF 	39H 			//00E4 	11B9

		//;app_display.c: 183: displayHundred = 0X80;
		LDWI 	80H 			//00E5 	0080
		STR 	3CH 			//00E6 	10BC

		//;app_display.c: 184: if (bFlag_discharge_qc)
		BTSC 	28H, 6H 		//00E7 	2B28

		//;app_display.c: 185: {
		//;app_display.c: 186: displayHundred |= 0X01;
		BSR 	3CH, 0H 			//00E8 	243C

		//;app_display.c: 187: }
		//;app_display.c: 194: if (dispTimerUnderVoltage % 2)
		BTSS 	37H, 0H 		//00E9 	2C37
		LJUMP 	103H 			//00EA 	3903

		//;app_display.c: 195: {
		//;app_display.c: 196: i = displayData / 10;
		LDWI 	AH 			//00EB 	000A
		STR 	70H 			//00EC 	10F0
		LDR 	49H, 0H 			//00ED 	1849
		LCALL 	127H 			//00EE 	3127
		MOVLP 	0H 			//00EF 	0180

		//;app_display.c: 197: j = displayData % 10;
		LCALL 	3B5H 			//00F0 	33B5
		MOVLP 	0H 			//00F1 	0180
		LCALL 	13FH 			//00F2 	313F
		MOVLP 	0H 			//00F3 	0180
		STR 	75H 			//00F4 	10F5

		//;app_display.c: 201: if (i)
		LDR 	76H, 0H 			//00F5 	1876
		BTSC 	3H, 2H 			//00F6 	2903
		LJUMP 	FDH 			//00F7 	38FD

		//;app_display.c: 202: {
		//;app_display.c: 203: displayDecade = DispTable[i];
		LDR 	76H, 0H 			//00F8 	1876
		LCALL 	39BH 			//00F9 	339B
		MOVLP 	0H 			//00FA 	0180
		STR 	3BH 			//00FB 	10BB

		//;app_display.c: 204: }
		LJUMP 	FEH 			//00FC 	38FE

		//;app_display.c: 205: else
		//;app_display.c: 206: {
		//;app_display.c: 207: displayDecade = 0x00;
		CLRF 	3BH 			//00FD 	11BB

		//;app_display.c: 208: }
		//;app_display.c: 212: displayDigit = DispTable[j];
		LDR 	75H, 0H 			//00FE 	1875
		LCALL 	39BH 			//00FF 	339B
		MOVLP 	0H 			//0100 	0180
		STR 	3AH 			//0101 	10BA

		//;app_display.c: 213: }
		LJUMP 	107H 			//0102 	3907

		//;app_display.c: 214: else
		//;app_display.c: 215: {
		//;app_display.c: 216: if (0 == displayData)
		LDR 	49H, 0H 			//0103 	1849
		BTSS 	3H, 2H 			//0104 	2D03
		LJUMP 	107H 			//0105 	3907

		//;app_display.c: 217: {
		//;app_display.c: 218: displayDigit = 0x00;
		CLRF 	3AH 			//0106 	11BA

		//;app_display.c: 219: }
		//;app_display.c: 220: }
		//;app_display.c: 222: if (0 == dispTimerUnderVoltage)
		LDR 	37H, 0H 			//0107 	1837
		BTSS 	3H, 2H 			//0108 	2D03
		RET 					//0109 	1008

		//;app_display.c: 223: {
		//;app_display.c: 224: if (displayData)
		LDR 	49H, 0H 			//010A 	1849
		BTSC 	3H, 2H 			//010B 	2903
		RET 					//010C 	1008

		//;app_display.c: 225: {
		//;app_display.c: 226: displayData--;
		DECR 	49H, 1H 		//010D 	13C9

		//;app_display.c: 227: dispTimerUnderVoltage = ((11) - 1);
		LDWI 	AH 			//010E 	000A
		STR 	37H 			//010F 	10B7

		//;app_display.c: 228: }
		RET 					//0110 	1008

		//;app_display.c: 237: else if (dispTimer)
		LDR 	39H, 0H 			//0111 	1839
		BTSC 	3H, 2H 			//0112 	2903
		LJUMP 	DCH 			//0113 	38DC

		//;app_display.c: 238: {
		//;app_display.c: 240: dispTimer--;
		DECR 	39H, 1H 		//0114 	13B9

		//;app_display.c: 244: displayHundred = 0X80;
		LDWI 	80H 			//0115 	0080
		STR 	3CH 			//0116 	10BC

		//;app_display.c: 245: if (bFlag_discharge_qc)
		BTSC 	28H, 6H 		//0117 	2B28

		//;app_display.c: 246: {
		//;app_display.c: 247: displayHundred |= 0X01;
		BSR 	3CH, 0H 			//0118 	243C

		//;app_display.c: 248: }
		//;app_display.c: 249: if (displayData < 100)
		LDWI 	64H 			//0119 	0064
		SUBWR 	49H, 0H 		//011A 	1249
		BTSC 	3H, 0H 			//011B 	2803
		LJUMP 	123H 			//011C 	3923

		//;app_display.c: 250: {
		//;app_display.c: 253: if (bFlag_blink)
		BTSC 	27H, 7H 		//011D 	2BA7
		LJUMP 	B5H 			//011E 	38B5

		//;app_display.c: 273: else
		//;app_display.c: 274: {
		//;app_display.c: 276: if (0 == displayData)
		//;app_display.c: 260: if (i)
		//;app_display.c: 256: j = displayData % 10;
		//;app_display.c: 254: {
		//;app_display.c: 255: i = displayData / 10;
		LDR 	49H, 0H 			//011F 	1849
		BTSC 	3H, 2H 			//0120 	2903

		//;app_display.c: 277: {
		//;app_display.c: 278: displayDigit = 0x00;
		CLRF 	3AH 			//0121 	11BA
		RET 					//0122 	1008

		//;app_display.c: 282: else
		//;app_display.c: 283: {
		//;app_display.c: 284: displayHundred |= DispTable[1];
		LDWI 	C4H 			//0123 	00C4
		STR 	4H 			//0124 	1084

		//;app_display.c: 285: displayDecade = DispTable[0];
		//;app_display.c: 286: displayDigit = DispTable[0];
		LCALL 	38AH 			//0125 	338A
		RET 					//0126 	1008
		STR 	71H 			//0127 	10F1
		CLRF 	73H 			//0128 	11F3
		LDR 	70H, 0H 			//0129 	1870
		BTSC 	3H, 2H 			//012A 	2903
		LJUMP 	13DH 			//012B 	393D
		CLRF 	72H 			//012C 	11F2
		INCR 	72H, 1H 		//012D 	1AF2
		BTSC 	70H, 7H 		//012E 	2BF0
		LJUMP 	132H 			//012F 	3932
		LSLF 	70H, 1H 		//0130 	05F0
		LJUMP 	12DH 			//0131 	392D
		LSLF 	73H, 1H 		//0132 	05F3
		LDR 	70H, 0H 			//0133 	1870
		SUBWR 	71H, 0H 		//0134 	1271
		BTSS 	3H, 0H 			//0135 	2C03
		LJUMP 	13AH 			//0136 	393A
		LDR 	70H, 0H 			//0137 	1870
		SUBWR 	71H, 1H 		//0138 	12F1
		BSR 	73H, 0H 			//0139 	2473
		LSRF 	70H, 1H 		//013A 	06F0
		DECRSZ 	72H, 1H 		//013B 	1BF2
		LJUMP 	132H 			//013C 	3932
		LDR 	73H, 0H 			//013D 	1873
		RET 					//013E 	1008
		STR 	72H 			//013F 	10F2
		LDWI 	8H 			//0140 	0008
		STR 	73H 			//0141 	10F3
		CLRF 	74H 			//0142 	11F4
		LDR 	72H, 0H 			//0143 	1872
		STR 	71H 			//0144 	10F1
		LDWI 	7H 			//0145 	0007
		LSRF 	71H, 1H 		//0146 	06F1
		DECRSZ 	9H, 1H 		//0147 	1B89
		LJUMP 	146H 			//0148 	3946
		LSLF 	74H, 0H 		//0149 	0574
		IORWR 	71H, 0H 		//014A 	1471
		STR 	74H 			//014B 	10F4
		LSLF 	72H, 1H 		//014C 	05F2
		LDR 	70H, 0H 			//014D 	1870
		SUBWR 	74H, 0H 		//014E 	1274
		BTSS 	3H, 0H 			//014F 	2C03
		LJUMP 	153H 			//0150 	3953
		LDR 	70H, 0H 			//0151 	1870
		SUBWR 	74H, 1H 		//0152 	12F4
		DECRSZ 	73H, 1H 		//0153 	1BF3
		LJUMP 	143H 			//0154 	3943
		LDR 	74H, 0H 			//0155 	1874
		RET 					//0156 	1008

		//;app_bms_ip53xs.c: 1026: static unsigned char counter;
		//;app_bms_ip53xs.c: 1028: if (bFlag_p_ext_int_is_high)
		BTSS 	27H, 5H 		//0157 	2EA7
		LJUMP 	166H 			//0158 	3966

		//;app_bms_ip53xs.c: 1029: {
		//;app_bms_ip53xs.c: 1030: if (!PA4)
		BTSC 	CH, 4H 			//0159 	2A0C
		LJUMP 	164H 			//015A 	3964

		//;app_bms_ip53xs.c: 1031: {
		//;app_bms_ip53xs.c: 1032: if (++counter > 3)
		LDWI 	4H 			//015B 	0004
		INCR 	36H, 1H 		//015C 	1AB6
		SUBWR 	36H, 0H 		//015D 	1236
		BTSS 	3H, 0H 			//015E 	2C03
		RET 					//015F 	1008

		//;app_bms_ip53xs.c: 1033: {
		//;app_bms_ip53xs.c: 1034: counter = 0;
		CLRF 	36H 			//0160 	11B6

		//;app_bms_ip53xs.c: 1035: bFlag_p_ext_int_is_high = 0;
		BCR 	27H, 5H 			//0161 	22A7

		//;app_bms_ip53xs.c: 1036: bFlag_init_ip5356 = 1;
		BSR 	6DH, 3H 			//0162 	25ED
		RET 					//0163 	1008

		//;app_bms_ip53xs.c: 1039: else
		//;app_bms_ip53xs.c: 1040: {
		//;app_bms_ip53xs.c: 1041: counter = 0;
		CLRF 	36H 			//0164 	11B6
		RET 					//0165 	1008

		//;app_bms_ip53xs.c: 1044: else
		//;app_bms_ip53xs.c: 1045: {
		//;app_bms_ip53xs.c: 1046: if (PA4)
		BTSS 	CH, 4H 			//0166 	2E0C
		LJUMP 	164H 			//0167 	3964

		//;app_bms_ip53xs.c: 1047: {
		//;app_bms_ip53xs.c: 1048: if (++counter > 7)
		LDWI 	8H 			//0168 	0008
		INCR 	36H, 1H 		//0169 	1AB6
		SUBWR 	36H, 0H 		//016A 	1236
		BTSS 	3H, 0H 			//016B 	2C03
		RET 					//016C 	1008

		//;app_bms_ip53xs.c: 1049: {
		//;app_bms_ip53xs.c: 1050: counter = 0;
		CLRF 	36H 			//016D 	11B6

		//;app_bms_ip53xs.c: 1051: bFlag_p_ext_int_is_high = 1;
		BSR 	27H, 5H 			//016E 	26A7

		//;app_bms_ip53xs.c: 1052: _dly_ms(100);
		LDWI 	64H 			//016F 	0064
		LJUMP 	35FH 			//0170 	3B5F

		//;app_global.c: 61: OSCCON = 0B01110001;
		LDWI 	71H 			//0171 	0071
		MOVLB 	1H 			//0172 	1021
		STR 	19H 			//0173 	1099

		//;app_global.c: 62: PCKEN |= 0B00000001;
		BSR 	1AH, 0H 			//0174 	241A

		//;app_global.c: 64: INTCON = 0;
		CLRF 	BH 			//0175 	118B

		//;app_global.c: 67: PORTA = 0B00000000;
		MOVLB 	0H 			//0176 	1020
		CLRF 	CH 			//0177 	118C

		//;app_global.c: 69: TRISA = 0B11111110;
		LDWI 	FEH 			//0178 	00FE
		MOVLB 	1H 			//0179 	1021
		STR 	CH 			//017A 	108C

		//;app_global.c: 71: PORTB = 0B00000000;
		MOVLB 	0H 			//017B 	1020
		CLRF 	DH 			//017C 	118D

		//;app_global.c: 73: TRISB = 0B11111111;
		LDWI 	FFH 			//017D 	00FF
		MOVLB 	1H 			//017E 	1021
		STR 	DH 			//017F 	108D

		//;app_global.c: 75: PORTC = 0B00000000;
		MOVLB 	0H 			//0180 	1020
		CLRF 	EH 			//0181 	118E

		//;app_global.c: 77: TRISC = 0B11111111;
		MOVLB 	1H 			//0182 	1021
		STR 	EH 			//0183 	108E

		//;app_global.c: 79: WPUA = 0B00000000;
		MOVLB 	3H 			//0184 	1023
		CLRF 	CH 			//0185 	118C

		//;app_global.c: 80: WPUB = 0B00010000;
		LDWI 	10H 			//0186 	0010
		STR 	DH 			//0187 	108D

		//;app_global.c: 81: WPUC = 0B00000000;
		CLRF 	EH 			//0188 	118E

		//;app_global.c: 83: WPDA = 0B00000000;
		MOVLB 	4H 			//0189 	1024
		CLRF 	CH 			//018A 	118C

		//;app_global.c: 84: WPDB = 0B00000000;
		CLRF 	DH 			//018B 	118D

		//;app_global.c: 85: WPDC = 0B00000000;
		CLRF 	EH 			//018C 	118E

		//;app_global.c: 87: PSRC0 = 0B11111111;
		LDWI 	FFH 			//018D 	00FF
		MOVLB 	2H 			//018E 	1022
		STR 	1AH 			//018F 	109A

		//;app_global.c: 88: PSRC1 = 0B11111111;
		STR 	1BH 			//0190 	109B

		//;app_global.c: 90: PSINK0 = 0B11111111;
		MOVLB 	3H 			//0191 	1023
		STR 	1AH 			//0192 	109A

		//;app_global.c: 91: PSINK1 = 0B11111111;
		STR 	1BH 			//0193 	109B

		//;app_global.c: 92: PSINK2 = 0B11111111;
		STR 	1CH 			//0194 	109C
		RET 					//0195 	1008

		//;app_bms_ip53xs.c: 1164: unsigned char reg_ip53xs;
		//;app_bms_ip53xs.c: 1165: unsigned char Temp2;
		//;app_bms_ip53xs.c: 1167: reg_ip53xs = ip53xs_readByte(0xE8,0x03);
		LDWI 	3H 			//0196 	0003
		STR 	75H 			//0197 	10F5
		LDWI 	E8H 			//0198 	00E8
		LCALL 	290H 			//0199 	3290
		MOVLP 	0H 			//019A 	0180
		STR 	7AH 			//019B 	10FA

		//;app_bms_ip53xs.c: 1168: if(reg_ip53xs & 0x04)
		BTSS 	7AH, 2H 		//019C 	2D7A
		LJUMP 	1A6H 			//019D 	39A6

		//;app_bms_ip53xs.c: 1169: {
		//;app_bms_ip53xs.c: 1170: ip53xs_writeByte(0xE8,0x03,reg_ip53xs & 0xFB);
		LDR 	7AH, 0H 			//019E 	187A
		STR 	76H 			//019F 	10F6
		LDWI 	3H 			//01A0 	0003
		BCR 	76H, 2H 			//01A1 	2176
		STR 	75H 			//01A2 	10F5
		LDWI 	E8H 			//01A3 	00E8
		LCALL 	2B4H 			//01A4 	32B4
		MOVLP 	0H 			//01A5 	0180

		//;app_bms_ip53xs.c: 1171: }
		//;app_bms_ip53xs.c: 1173: reg_ip53xs = ip53xs_readByte(0xE8,0x33);
		LDWI 	33H 			//01A6 	0033
		STR 	75H 			//01A7 	10F5
		LDWI 	E8H 			//01A8 	00E8
		LCALL 	290H 			//01A9 	3290
		MOVLP 	0H 			//01AA 	0180
		STR 	7AH 			//01AB 	10FA

		//;app_bms_ip53xs.c: 1174: if(reg_ip53xs & 0x10)
		BTSS 	7AH, 4H 		//01AC 	2E7A
		LJUMP 	1B6H 			//01AD 	39B6

		//;app_bms_ip53xs.c: 1175: {
		//;app_bms_ip53xs.c: 1176: ip53xs_writeByte(0xE8,0x33,reg_ip53xs & 0xEF);
		LDR 	7AH, 0H 			//01AE 	187A
		STR 	76H 			//01AF 	10F6
		LDWI 	33H 			//01B0 	0033
		BCR 	76H, 4H 			//01B1 	2276
		STR 	75H 			//01B2 	10F5
		LDWI 	E8H 			//01B3 	00E8
		LCALL 	2B4H 			//01B4 	32B4
		MOVLP 	0H 			//01B5 	0180

		//;app_bms_ip53xs.c: 1177: }
		//;app_bms_ip53xs.c: 1179: reg_ip53xs = ip53xs_readByte(0xEA,0x3A);
		LDWI 	3AH 			//01B6 	003A
		STR 	75H 			//01B7 	10F5
		LDWI 	EAH 			//01B8 	00EA
		LCALL 	290H 			//01B9 	3290
		MOVLP 	0H 			//01BA 	0180
		STR 	7AH 			//01BB 	10FA

		//;app_bms_ip53xs.c: 1180: if((reg_ip53xs & 0x0F) != 0x07)
		ANDWI 	FH 			//01BC 	090F
		STR 	78H 			//01BD 	10F8
		XORWI 	7H 			//01BE 	0A07
		BTSC 	3H, 2H 			//01BF 	2903
		LJUMP 	1CAH 			//01C0 	39CA

		//;app_bms_ip53xs.c: 1181: {
		//;app_bms_ip53xs.c: 1182: reg_ip53xs &= 0xF0;
		LDWI 	F0H 			//01C1 	00F0
		ANDWR 	7AH, 1H 		//01C2 	15FA

		//;app_bms_ip53xs.c: 1183: ip53xs_writeByte(0xEA,0x3A,reg_ip53xs);
		LDWI 	3AH 			//01C3 	003A
		STR 	75H 			//01C4 	10F5
		LDR 	7AH, 0H 			//01C5 	187A
		STR 	76H 			//01C6 	10F6
		LDWI 	EAH 			//01C7 	00EA
		LCALL 	2B4H 			//01C8 	32B4
		MOVLP 	0H 			//01C9 	0180

		//;app_bms_ip53xs.c: 1184: }
		//;app_bms_ip53xs.c: 1186: reg_ip53xs = ip53xs_readByte(0xE8,0x24);
		LDWI 	24H 			//01CA 	0024
		STR 	75H 			//01CB 	10F5
		LDWI 	E8H 			//01CC 	00E8
		LCALL 	290H 			//01CD 	3290
		MOVLP 	0H 			//01CE 	0180
		STR 	7AH 			//01CF 	10FA

		//;app_bms_ip53xs.c: 1187: if(reg_ip53xs & 0x20)
		BTSS 	7AH, 5H 		//01D0 	2EFA
		LJUMP 	1DAH 			//01D1 	39DA

		//;app_bms_ip53xs.c: 1188: {
		//;app_bms_ip53xs.c: 1189: ip53xs_writeByte(0xE8,0x24,reg_ip53xs & 0xDF);
		LDR 	7AH, 0H 			//01D2 	187A
		STR 	76H 			//01D3 	10F6
		LDWI 	24H 			//01D4 	0024
		BCR 	76H, 5H 			//01D5 	22F6
		STR 	75H 			//01D6 	10F5
		LDWI 	E8H 			//01D7 	00E8
		LCALL 	2B4H 			//01D8 	32B4
		MOVLP 	0H 			//01D9 	0180

		//;app_bms_ip53xs.c: 1190: }
		//;app_bms_ip53xs.c: 1192: reg_ip53xs = ip53xs_readByte(0xE8,0xF5);
		LDWI 	F5H 			//01DA 	00F5
		STR 	75H 			//01DB 	10F5
		LDWI 	E8H 			//01DC 	00E8
		LCALL 	290H 			//01DD 	3290
		MOVLP 	0H 			//01DE 	0180
		STR 	7AH 			//01DF 	10FA

		//;app_bms_ip53xs.c: 1193: if(reg_ip53xs & 0x40)
		BTSS 	7AH, 6H 		//01E0 	2F7A
		LJUMP 	1EAH 			//01E1 	39EA

		//;app_bms_ip53xs.c: 1194: {
		//;app_bms_ip53xs.c: 1195: ip53xs_writeByte(0xE8,0xF5,reg_ip53xs & 0xBF);
		LDR 	7AH, 0H 			//01E2 	187A
		STR 	76H 			//01E3 	10F6
		LDWI 	F5H 			//01E4 	00F5
		BCR 	76H, 6H 			//01E5 	2376
		STR 	75H 			//01E6 	10F5
		LDWI 	E8H 			//01E7 	00E8
		LCALL 	2B4H 			//01E8 	32B4
		MOVLP 	0H 			//01E9 	0180
		LDWI 	EAH 			//01EA 	00EA

		//;app_bms_ip53xs.c: 1196: }
		//;app_bms_ip53xs.c: 1198: reg_ip53xs = ip53xs_readByte(0xEA,0x01);
		CLRF 	75H 			//01EB 	11F5
		INCR 	75H, 1H 		//01EC 	1AF5
		LCALL 	290H 			//01ED 	3290
		MOVLP 	0H 			//01EE 	0180
		STR 	7AH 			//01EF 	10FA

		//;app_bms_ip53xs.c: 1199: if(reg_ip53xs & 0x30)
		ANDWI 	30H 			//01F0 	0930
		BTSC 	3H, 2H 			//01F1 	2903
		LJUMP 	1FCH 			//01F2 	39FC

		//;app_bms_ip53xs.c: 1200: {
		//;app_bms_ip53xs.c: 1201: ip53xs_writeByte(0xEA,0x01,reg_ip53xs & 0xCF);
		LDR 	7AH, 0H 			//01F3 	187A
		STR 	76H 			//01F4 	10F6
		LDWI 	CFH 			//01F5 	00CF
		ANDWR 	76H, 1H 		//01F6 	15F6
		LDWI 	EAH 			//01F7 	00EA
		CLRF 	75H 			//01F8 	11F5
		INCR 	75H, 1H 		//01F9 	1AF5
		LCALL 	2B4H 			//01FA 	32B4
		MOVLP 	0H 			//01FB 	0180

		//;app_bms_ip53xs.c: 1202: }
		//;app_bms_ip53xs.c: 1205: if(bFlag_plus_in_12v)
		BTSS 	6DH, 2H 		//01FC 	2D6D
		LJUMP 	247H 			//01FD 	3A47

		//;app_bms_ip53xs.c: 1206: {
		//;app_bms_ip53xs.c: 1208: reg_ip53xs = ip53xs_readByte(0xE8,0x10);
		LDWI 	10H 			//01FE 	0010
		STR 	75H 			//01FF 	10F5
		LDWI 	E8H 			//0200 	00E8
		LCALL 	290H 			//0201 	3290
		MOVLP 	0H 			//0202 	0180
		STR 	7AH 			//0203 	10FA

		//;app_bms_ip53xs.c: 1209: if(reg_ip53xs & 0x04)
		BTSS 	7AH, 2H 		//0204 	2D7A
		LJUMP 	213H 			//0205 	3A13

		//;app_bms_ip53xs.c: 1210: {
		//;app_bms_ip53xs.c: 1211: if(reg_ip53xs & 0x01)
		BTSS 	7AH, 0H 		//0206 	2C7A
		LJUMP 	20DH 			//0207 	3A0D

		//;app_bms_ip53xs.c: 1212: {
		//;app_bms_ip53xs.c: 1213: ip53xs_writeByte(0xE8,0x10,reg_ip53xs & 0xFE);
		LDR 	7AH, 0H 			//0208 	187A
		STR 	76H 			//0209 	10F6
		LDWI 	10H 			//020A 	0010
		BCR 	76H, 0H 			//020B 	2076
		LJUMP 	211H 			//020C 	3A11

		//;app_bms_ip53xs.c: 1214: }
		//;app_bms_ip53xs.c: 1215: else
		//;app_bms_ip53xs.c: 1216: {
		//;app_bms_ip53xs.c: 1217: ip53xs_writeByte(0xE8,0x10,reg_ip53xs & 0xFB);
		LDR 	7AH, 0H 			//020D 	187A
		STR 	76H 			//020E 	10F6
		LDWI 	10H 			//020F 	0010
		BCR 	76H, 2H 			//0210 	2176
		STR 	75H 			//0211 	10F5
		LJUMP 	21AH 			//0212 	3A1A

		//;app_bms_ip53xs.c: 1220: else if((reg_ip53xs & 0x01) == 0x00)
		BTSC 	7AH, 0H 		//0213 	287A
		LJUMP 	21DH 			//0214 	3A1D

		//;app_bms_ip53xs.c: 1221: {
		//;app_bms_ip53xs.c: 1222: ip53xs_writeByte(0xE8,0x10,reg_ip53xs | 0x01);
		LDWI 	10H 			//0215 	0010
		STR 	75H 			//0216 	10F5
		LDR 	7AH, 0H 			//0217 	187A
		IORWI 	1H 			//0218 	0801
		STR 	76H 			//0219 	10F6
		LDWI 	E8H 			//021A 	00E8
		LCALL 	2B4H 			//021B 	32B4
		MOVLP 	0H 			//021C 	0180

		//;app_bms_ip53xs.c: 1223: }
		//;app_bms_ip53xs.c: 1225: reg_ip53xs = ip53xs_readByte(0xE8,0x18);
		LDWI 	18H 			//021D 	0018
		STR 	75H 			//021E 	10F5
		LDWI 	E8H 			//021F 	00E8
		LCALL 	290H 			//0220 	3290
		MOVLP 	0H 			//0221 	0180

		//;app_bms_ip53xs.c: 1226: Temp2 = ip53xs_readByte(0xEA,0x97);
		LCALL 	3BAH 			//0222 	33BA
		MOVLP 	0H 			//0223 	0180
		LCALL 	290H 			//0224 	3290
		MOVLP 	0H 			//0225 	0180
		STR 	79H 			//0226 	10F9

		//;app_bms_ip53xs.c: 1227: if((reg_ip53xs & 0x04) || ((Temp2 & 0xC0) != 0x40))
		BTSC 	7AH, 2H 		//0227 	297A
		LJUMP 	22DH 			//0228 	3A2D
		LCALL 	3BEH 			//0229 	33BE
		MOVLP 	0H 			//022A 	0180
		BTSC 	3H, 2H 			//022B 	2903
		LJUMP 	242H 			//022C 	3A42

		//;app_bms_ip53xs.c: 1228: {
		//;app_bms_ip53xs.c: 1229: if(reg_ip53xs & 0x01)
		BTSS 	7AH, 0H 		//022D 	2C7A
		LJUMP 	232H 			//022E 	3A32

		//;app_bms_ip53xs.c: 1230: {
		//;app_bms_ip53xs.c: 1231: ip53xs_writeByte(0xE8,0x18,reg_ip53xs & 0xFE);
		LCALL 	3A9H 			//022F 	33A9
		MOVLP 	0H 			//0230 	0180
		LJUMP 	2B4H 			//0231 	3AB4

		//;app_bms_ip53xs.c: 1232: }
		//;app_bms_ip53xs.c: 1233: else
		//;app_bms_ip53xs.c: 1234: {
		//;app_bms_ip53xs.c: 1235: ip53xs_writeByte(0xE8,0x18,reg_ip53xs & 0xFB);
		LDR 	7AH, 0H 			//0232 	187A
		STR 	76H 			//0233 	10F6
		LDWI 	18H 			//0234 	0018
		BCR 	76H, 2H 			//0235 	2176
		STR 	75H 			//0236 	10F5
		LDWI 	E8H 			//0237 	00E8
		LCALL 	2B4H 			//0238 	32B4
		MOVLP 	0H 			//0239 	0180

		//;app_bms_ip53xs.c: 1236: ip53xs_writeByte(0xEA,0x97,(Temp2 & 0x3F) | 0x40);
		LDWI 	97H 			//023A 	0097
		STR 	75H 			//023B 	10F5
		LDR 	79H, 0H 			//023C 	1879
		ANDWI 	3FH 			//023D 	093F
		IORWI 	40H 			//023E 	0840
		STR 	76H 			//023F 	10F6
		LDWI 	EAH 			//0240 	00EA
		LJUMP 	2B4H 			//0241 	3AB4

		//;app_bms_ip53xs.c: 1239: else if((reg_ip53xs & 0x01) == 0x00)
		BTSC 	7AH, 0H 		//0242 	287A
		RET 					//0243 	1008

		//;app_bms_ip53xs.c: 1240: {
		//;app_bms_ip53xs.c: 1241: ip53xs_writeByte(0xE8,0x18,reg_ip53xs | 0x01);
		LCALL 	3A3H 			//0244 	33A3
		MOVLP 	0H 			//0245 	0180
		LJUMP 	2B4H 			//0246 	3AB4

		//;app_bms_ip53xs.c: 1244: else
		//;app_bms_ip53xs.c: 1245: {
		//;app_bms_ip53xs.c: 1247: reg_ip53xs = ip53xs_readByte(0xE8,0x10);
		LDWI 	10H 			//0247 	0010
		STR 	75H 			//0248 	10F5
		LDWI 	E8H 			//0249 	00E8
		LCALL 	290H 			//024A 	3290
		MOVLP 	0H 			//024B 	0180
		STR 	7AH 			//024C 	10FA

		//;app_bms_ip53xs.c: 1248: if((reg_ip53xs & 0x04) == 0x00)
		BTSC 	7AH, 2H 		//024D 	297A
		LJUMP 	25CH 			//024E 	3A5C

		//;app_bms_ip53xs.c: 1249: {
		//;app_bms_ip53xs.c: 1250: if(reg_ip53xs & 0x01)
		BTSS 	7AH, 0H 		//024F 	2C7A
		LJUMP 	257H 			//0250 	3A57

		//;app_bms_ip53xs.c: 1251: {
		//;app_bms_ip53xs.c: 1252: ip53xs_writeByte(0xE8,0x10,reg_ip53xs & 0xFE);
		LDR 	7AH, 0H 			//0251 	187A
		STR 	76H 			//0252 	10F6
		LDWI 	10H 			//0253 	0010
		BCR 	76H, 0H 			//0254 	2076
		STR 	75H 			//0255 	10F5
		LJUMP 	263H 			//0256 	3A63

		//;app_bms_ip53xs.c: 1253: }
		//;app_bms_ip53xs.c: 1254: else
		//;app_bms_ip53xs.c: 1255: {
		//;app_bms_ip53xs.c: 1256: ip53xs_writeByte(0xE8,0x10,reg_ip53xs | 0x04);
		LDWI 	10H 			//0257 	0010
		STR 	75H 			//0258 	10F5
		LDR 	7AH, 0H 			//0259 	187A
		IORWI 	4H 			//025A 	0804
		LJUMP 	262H 			//025B 	3A62

		//;app_bms_ip53xs.c: 1259: else if((reg_ip53xs & 0x01) == 0x00)
		BTSC 	7AH, 0H 		//025C 	287A
		LJUMP 	266H 			//025D 	3A66

		//;app_bms_ip53xs.c: 1260: {
		//;app_bms_ip53xs.c: 1261: ip53xs_writeByte(0xE8,0x10,reg_ip53xs | 0x01);
		LDWI 	10H 			//025E 	0010
		STR 	75H 			//025F 	10F5
		LDR 	7AH, 0H 			//0260 	187A
		IORWI 	1H 			//0261 	0801
		STR 	76H 			//0262 	10F6
		LDWI 	E8H 			//0263 	00E8
		LCALL 	2B4H 			//0264 	32B4
		MOVLP 	0H 			//0265 	0180

		//;app_bms_ip53xs.c: 1262: }
		//;app_bms_ip53xs.c: 1264: reg_ip53xs = ip53xs_readByte(0xE8,0x18);
		LDWI 	18H 			//0266 	0018
		STR 	75H 			//0267 	10F5
		LDWI 	E8H 			//0268 	00E8
		LCALL 	290H 			//0269 	3290
		MOVLP 	0H 			//026A 	0180

		//;app_bms_ip53xs.c: 1265: Temp2 = ip53xs_readByte(0xEA,0x97);
		LCALL 	3BAH 			//026B 	33BA
		MOVLP 	0H 			//026C 	0180
		LCALL 	290H 			//026D 	3290
		MOVLP 	0H 			//026E 	0180
		STR 	79H 			//026F 	10F9

		//;app_bms_ip53xs.c: 1266: if(((reg_ip53xs & 0x04) == 0x00) || ((Temp2 & 0xC0) == 0x40))
		BTSS 	7AH, 2H 		//0270 	2D7A
		LJUMP 	276H 			//0271 	3A76
		LCALL 	3BEH 			//0272 	33BE
		MOVLP 	0H 			//0273 	0180
		BTSS 	3H, 2H 			//0274 	2D03
		LJUMP 	28BH 			//0275 	3A8B

		//;app_bms_ip53xs.c: 1267: {
		//;app_bms_ip53xs.c: 1268: if(reg_ip53xs & 0x01)
		BTSS 	7AH, 0H 		//0276 	2C7A
		LJUMP 	27BH 			//0277 	3A7B

		//;app_bms_ip53xs.c: 1269: {
		//;app_bms_ip53xs.c: 1270: ip53xs_writeByte(0xE8,0x18,reg_ip53xs & 0xFE);
		LCALL 	3A9H 			//0278 	33A9
		MOVLP 	0H 			//0279 	0180
		LJUMP 	2B4H 			//027A 	3AB4

		//;app_bms_ip53xs.c: 1271: }
		//;app_bms_ip53xs.c: 1272: else
		//;app_bms_ip53xs.c: 1273: {
		//;app_bms_ip53xs.c: 1274: ip53xs_writeByte(0xE8,0x18,reg_ip53xs | 0x04);
		LDWI 	18H 			//027B 	0018
		STR 	75H 			//027C 	10F5
		LDR 	7AH, 0H 			//027D 	187A
		IORWI 	4H 			//027E 	0804
		STR 	76H 			//027F 	10F6
		LDWI 	E8H 			//0280 	00E8
		LCALL 	2B4H 			//0281 	32B4
		MOVLP 	0H 			//0282 	0180

		//;app_bms_ip53xs.c: 1275: ip53xs_writeByte(0xEA,0x97,Temp2 & 0x3F);
		LDR 	79H, 0H 			//0283 	1879
		STR 	76H 			//0284 	10F6
		LDWI 	3FH 			//0285 	003F
		ANDWR 	76H, 1H 		//0286 	15F6
		LDWI 	97H 			//0287 	0097
		STR 	75H 			//0288 	10F5
		LDWI 	EAH 			//0289 	00EA
		LJUMP 	2B4H 			//028A 	3AB4

		//;app_bms_ip53xs.c: 1278: else if((reg_ip53xs & 0x01) == 0x00)
		BTSC 	7AH, 0H 		//028B 	287A
		RET 					//028C 	1008

		//;app_bms_ip53xs.c: 1279: {
		//;app_bms_ip53xs.c: 1280: ip53xs_writeByte(0xE8,0x18,reg_ip53xs | 0x01);
		LCALL 	3A3H 			//028D 	33A3
		MOVLP 	0H 			//028E 	0180
		LJUMP 	2B4H 			//028F 	3AB4
		STR 	77H 			//0290 	10F7

		//;bsp_ip53xs.c: 56: unsigned char readByte;
		//;bsp_ip53xs.c: 57: if (PA4)
		BTSS 	CH, 4H 			//0291 	2E0C
		LJUMP 	2B2H 			//0292 	3AB2

		//;bsp_ip53xs.c: 58: {
		//;bsp_ip53xs.c: 59: i2c_start();
		LCALL 	2E3H 			//0293 	32E3
		MOVLP 	0H 			//0294 	0180

		//;bsp_ip53xs.c: 61: if (i2c_writeByte(deviceAddr | (0)))
		LDR 	77H, 0H 			//0295 	1877
		LCALL 	2C9H 			//0296 	32C9
		MOVLP 	0H 			//0297 	0180
		XORWI 	0H 			//0298 	0A00
		BTSC 	3H, 2H 			//0299 	2903
		LJUMP 	29DH 			//029A 	3A9D

		//;bsp_ip53xs.c: 62: {
		//;bsp_ip53xs.c: 63: i2c_stop();
		LCALL 	2FCH 			//029B 	32FC

		//;bsp_ip53xs.c: 64: return (0);
		RETW 	0H 			//029C 	0400

		//;bsp_ip53xs.c: 65: }
		//;bsp_ip53xs.c: 67: if (i2c_writeByte(regAddr))
		LDR 	75H, 0H 			//029D 	1875
		LCALL 	2C9H 			//029E 	32C9
		MOVLP 	0H 			//029F 	0180
		XORWI 	0H 			//02A0 	0A00
		BTSS 	3H, 2H 			//02A1 	2D03
		LJUMP 	29BH 			//02A2 	3A9B

		//;bsp_ip53xs.c: 71: }
		//;bsp_ip53xs.c: 73: i2c_start();
		LCALL 	2E3H 			//02A3 	32E3
		MOVLP 	0H 			//02A4 	0180

		//;bsp_ip53xs.c: 75: if (i2c_writeByte(deviceAddr | (1)))
		LDR 	77H, 0H 			//02A5 	1877
		IORWI 	1H 			//02A6 	0801
		LCALL 	2C9H 			//02A7 	32C9
		MOVLP 	0H 			//02A8 	0180
		XORWI 	0H 			//02A9 	0A00
		BTSS 	3H, 2H 			//02AA 	2D03
		LJUMP 	29BH 			//02AB 	3A9B

		//;bsp_ip53xs.c: 79: }
		//;bsp_ip53xs.c: 81: readByte = i2c_readByte();
		LCALL 	309H 			//02AC 	3309
		MOVLP 	0H 			//02AD 	0180
		STR 	76H 			//02AE 	10F6

		//;bsp_ip53xs.c: 82: i2c_send_nack();
		LCALL 	325H 			//02AF 	3325
		MOVLP 	0H 			//02B0 	0180

		//;bsp_ip53xs.c: 83: i2c_stop();
		LCALL 	2FCH 			//02B1 	32FC

		//;bsp_ip53xs.c: 84: }
		//;bsp_ip53xs.c: 86: return readByte;
		LDR 	76H, 0H 			//02B2 	1876
		RET 					//02B3 	1008
		STR 	77H 			//02B4 	10F7

		//;bsp_ip53xs.c: 26: if (PA4)
		BTSS 	CH, 4H 			//02B5 	2E0C
		RET 					//02B6 	1008

		//;bsp_ip53xs.c: 27: {
		//;bsp_ip53xs.c: 28: i2c_start();
		LCALL 	2E3H 			//02B7 	32E3
		MOVLP 	0H 			//02B8 	0180

		//;bsp_ip53xs.c: 30: if (i2c_writeByte(deviceAddr | (0)))
		LDR 	77H, 0H 			//02B9 	1877
		LCALL 	2C9H 			//02BA 	32C9
		MOVLP 	0H 			//02BB 	0180
		XORWI 	0H 			//02BC 	0A00
		BTSS 	3H, 2H 			//02BD 	2D03
		LJUMP 	2C8H 			//02BE 	3AC8

		//;bsp_ip53xs.c: 34: }
		//;bsp_ip53xs.c: 36: if (i2c_writeByte(regAddr))
		LDR 	75H, 0H 			//02BF 	1875
		LCALL 	2C9H 			//02C0 	32C9
		MOVLP 	0H 			//02C1 	0180
		XORWI 	0H 			//02C2 	0A00
		BTSS 	3H, 2H 			//02C3 	2D03
		LJUMP 	2C8H 			//02C4 	3AC8

		//;bsp_ip53xs.c: 40: }
		//;bsp_ip53xs.c: 42: if (i2c_writeByte(sendByte))
		LDR 	76H, 0H 			//02C5 	1876
		LCALL 	2C9H 			//02C6 	32C9
		MOVLP 	0H 			//02C7 	0180

		//;bsp_ip53xs.c: 31: {
		//;bsp_ip53xs.c: 32: i2c_stop();
		LJUMP 	2FCH 			//02C8 	3AFC
		STR 	73H 			//02C9 	10F3

		//;bsp_i2c.c: 90: unsigned char i = 8;
		LDWI 	8H 			//02CA 	0008
		STR 	74H 			//02CB 	10F4

		//;bsp_i2c.c: 92: while (i--)
		LJUMP 	2DFH 			//02CC 	3ADF

		//;bsp_i2c.c: 93: {
		//;bsp_i2c.c: 94: PB7 = 0;
		MOVLB 	0H 			//02CD 	1020
		BCR 	DH, 7H 			//02CE 	238D

		//;bsp_i2c.c: 99: _dly_us(0);
		LDWI 	0H 			//02CF 	0000
		LCALL 	2F3H 			//02D0 	32F3
		MOVLP 	0H 			//02D1 	0180

		//;bsp_i2c.c: 100: if (sendByte & 0x80)
		BTSS 	73H, 7H 		//02D2 	2FF3
		LJUMP 	2D7H 			//02D3 	3AD7

		//;bsp_i2c.c: 101: {
		//;bsp_i2c.c: 102: PC1 = 1;
		MOVLB 	0H 			//02D4 	1020
		BSR 	EH, 1H 			//02D5 	248E

		//;bsp_i2c.c: 103: }
		LJUMP 	2D9H 			//02D6 	3AD9

		//;bsp_i2c.c: 104: else
		//;bsp_i2c.c: 105: {
		//;bsp_i2c.c: 106: PC1 = 0;
		MOVLB 	0H 			//02D7 	1020
		BCR 	EH, 1H 			//02D8 	208E

		//;bsp_i2c.c: 107: }
		//;bsp_i2c.c: 108: sendByte <<= 1;
		LSLF 	73H, 1H 		//02D9 	05F3

		//;bsp_i2c.c: 109: PB7 = 1;
		BSR 	DH, 7H 			//02DA 	278D

		//;bsp_i2c.c: 110: _dly_us(0);
		LDWI 	0H 			//02DB 	0000
		LCALL 	2F3H 			//02DC 	32F3
		MOVLP 	0H 			//02DD 	0180

		//;bsp_i2c.c: 111: __nop();
		NOP 					//02DE 	1000
		DECR 	74H, 1H 		//02DF 	13F4
		INCRSZ 	74H, 0H 		//02E0 	1F74
		LJUMP 	2CDH 			//02E1 	3ACD

		//;bsp_i2c.c: 116: }
		//;bsp_i2c.c: 118: return i2c_chk_ack();
		LJUMP 	370H 			//02E2 	3B70

		//;bsp_i2c.c: 18: PC1 = 1;
		MOVLB 	0H 			//02E3 	1020
		BSR 	EH, 1H 			//02E4 	248E

		//;bsp_i2c.c: 19: PB7 = 1;
		BSR 	DH, 7H 			//02E5 	278D

		//;bsp_i2c.c: 20: TRISC1 = 0;
		MOVLB 	1H 			//02E6 	1021
		BCR 	EH, 1H 			//02E7 	208E

		//;bsp_i2c.c: 21: TRISB7 = 0;
		BCR 	DH, 7H 			//02E8 	238D

		//;bsp_i2c.c: 22: _dly_us(10);
		LDWI 	AH 			//02E9 	000A
		LCALL 	2F3H 			//02EA 	32F3
		MOVLP 	0H 			//02EB 	0180

		//;bsp_i2c.c: 23: PC1 = 0;
		MOVLB 	0H 			//02EC 	1020
		BCR 	EH, 1H 			//02ED 	208E

		//;bsp_i2c.c: 24: _dly_us(10);
		LDWI 	AH 			//02EE 	000A
		LCALL 	2F3H 			//02EF 	32F3

		//;bsp_i2c.c: 25: PB7 = 0;
		MOVLB 	0H 			//02F0 	1020
		BCR 	DH, 7H 			//02F1 	238D
		RET 					//02F2 	1008
		STR 	70H 			//02F3 	10F0

		//;app_global.c: 19: unsigned char a;
		//;app_global.c: 20: for (a = 0; a < Time; a++)
		CLRF 	71H 			//02F4 	11F1
		LDR 	70H, 0H 			//02F5 	1870
		SUBWR 	71H, 0H 		//02F6 	1271
		BTSC 	3H, 0H 			//02F7 	2803
		RET 					//02F8 	1008

		//;app_global.c: 21: {
		//;app_global.c: 22: __nop();
		NOP 					//02F9 	1000
		INCR 	71H, 1H 		//02FA 	1AF1
		LJUMP 	2F5H 			//02FB 	3AF5

		//;bsp_i2c.c: 31: PB7 = 0;
		MOVLB 	0H 			//02FC 	1020
		BCR 	DH, 7H 			//02FD 	238D

		//;bsp_i2c.c: 32: PC1 = 0;
		BCR 	EH, 1H 			//02FE 	208E

		//;bsp_i2c.c: 33: _dly_us(10);
		LDWI 	AH 			//02FF 	000A
		LCALL 	2F3H 			//0300 	32F3
		MOVLP 	0H 			//0301 	0180

		//;bsp_i2c.c: 34: PB7 = 1;
		MOVLB 	0H 			//0302 	1020
		BSR 	DH, 7H 			//0303 	278D

		//;bsp_i2c.c: 35: _dly_us(10);
		LDWI 	AH 			//0304 	000A
		LCALL 	2F3H 			//0305 	32F3

		//;bsp_i2c.c: 36: PC1 = 1;
		MOVLB 	0H 			//0306 	1020
		BSR 	EH, 1H 			//0307 	248E
		RET 					//0308 	1008

		//;bsp_i2c.c: 123: unsigned char i = 8;
		LDWI 	8H 			//0309 	0008
		STR 	72H 			//030A 	10F2

		//;bsp_i2c.c: 124: unsigned char readByte = 0;
		CLRF 	73H 			//030B 	11F3

		//;bsp_i2c.c: 126: PB7 = 0;
		MOVLB 	0H 			//030C 	1020
		BCR 	DH, 7H 			//030D 	238D

		//;bsp_i2c.c: 127: TRISC1 = 1;
		MOVLB 	1H 			//030E 	1021
		BSR 	EH, 1H 			//030F 	248E

		//;bsp_i2c.c: 129: while (i--)
		LJUMP 	31EH 			//0310 	3B1E

		//;bsp_i2c.c: 130: {
		//;bsp_i2c.c: 132: PB7 = 1;
		MOVLB 	0H 			//0311 	1020
		BSR 	DH, 7H 			//0312 	278D

		//;bsp_i2c.c: 133: _dly_us(0);
		LDWI 	0H 			//0313 	0000
		LCALL 	2F3H 			//0314 	32F3
		MOVLP 	0H 			//0315 	0180

		//;bsp_i2c.c: 134: readByte <<= 1;
		LSLF 	73H, 1H 		//0316 	05F3

		//;bsp_i2c.c: 136: if (PC1)
		MOVLB 	0H 			//0317 	1020
		BTSC 	EH, 1H 			//0318 	288E

		//;bsp_i2c.c: 137: {
		//;bsp_i2c.c: 138: readByte |= 0x01;
		BSR 	73H, 0H 			//0319 	2473

		//;bsp_i2c.c: 139: }
		//;bsp_i2c.c: 141: PB7 = 0;
		BCR 	DH, 7H 			//031A 	238D

		//;bsp_i2c.c: 142: _dly_us(0);
		LDWI 	0H 			//031B 	0000
		LCALL 	2F3H 			//031C 	32F3
		MOVLP 	0H 			//031D 	0180
		DECR 	72H, 1H 		//031E 	13F2
		INCRSZ 	72H, 0H 		//031F 	1F72
		LJUMP 	311H 			//0320 	3B11

		//;bsp_i2c.c: 143: }
		//;bsp_i2c.c: 146: TRISC1 = 0;
		MOVLB 	1H 			//0321 	1021
		BCR 	EH, 1H 			//0322 	208E

		//;bsp_i2c.c: 147: return readByte;
		LDR 	73H, 0H 			//0323 	1873
		RET 					//0324 	1008

		//;bsp_i2c.c: 79: PB7 = 0;
		MOVLB 	0H 			//0325 	1020
		BCR 	DH, 7H 			//0326 	238D

		//;bsp_i2c.c: 80: PC1 = 1;
		BSR 	EH, 1H 			//0327 	248E

		//;bsp_i2c.c: 81: _dly_us(10);
		LDWI 	AH 			//0328 	000A
		LCALL 	2F3H 			//0329 	32F3
		MOVLP 	0H 			//032A 	0180

		//;bsp_i2c.c: 82: PB7 = 1;
		MOVLB 	0H 			//032B 	1020
		BSR 	DH, 7H 			//032C 	278D

		//;bsp_i2c.c: 83: _dly_us(10);
		LDWI 	AH 			//032D 	000A
		LCALL 	2F3H 			//032E 	32F3

		//;bsp_i2c.c: 84: PB7 = 0;
		MOVLB 	0H 			//032F 	1020
		BCR 	DH, 7H 			//0330 	238D

		//;bsp_i2c.c: 85: PC1 = 0;
		BCR 	EH, 1H 			//0331 	208E
		RET 					//0332 	1008

		//;app_global.c: 178: bFlag_gSysTick_change = 0;
		BCR 	7DH, 6H 			//0333 	237D

		//;app_global.c: 179: forceDispTimer = 5;
		LDWI 	5H 			//0334 	0005
		MOVLB 	0H 			//0335 	1020
		STR 	6EH 			//0336 	10EE

		//;app_global.c: 180: bFlag_reverse = 0;
		BCR 	25H, 6H 			//0337 	2325

		//;app_global.c: 181: delaySleepTimer = (32);
		LDWI 	20H 			//0338 	0020
		MOVLB 	1H 			//0339 	1021
		STR 	34H 			//033A 	10B4
		CLRF 	35H 			//033B 	11B5

		//;app_global.c: 182: display_cycle = 8;
		LDWI 	8H 			//033C 	0008
		STR 	36H 			//033D 	10B6
		CLRF 	37H 			//033E 	11B7

		//;app_global.c: 183: displayData = 0;
		MOVLB 	0H 			//033F 	1020
		CLRF 	49H 			//0340 	11C9

		//;app_global.c: 184: underVoltageDispTimer = 0;
		CLRF 	6CH 			//0341 	11EC

		//;app_global.c: 185: indicator_light_mode = 0x0F;
		LDWI 	FH 			//0342 	000F
		MOVLB 	1H 			//0343 	1021
		STR 	39H 			//0344 	10B9

		//;app_global.c: 186: ledDispTimer = (10);
		LDWI 	AH 			//0345 	000A
		STR 	38H 			//0346 	10B8

		//;app_global.c: 187: bFlag_disable_charge_on = 0;
		MOVLB 	0H 			//0347 	1020
		BCR 	22H, 6H 			//0348 	2322

		//;app_global.c: 188: bFlag_temp_exception_chg = 0;
		BCR 	26H, 3H 			//0349 	21A6

		//;app_global.c: 189: bFlag_temp_exception_dischg = 0;
		BCR 	26H, 2H 			//034A 	2126

		//;app_global.c: 190: bFlag_charge_on = 0;
		BCR 	7DH, 4H 			//034B 	227D

		//;app_global.c: 191: bFlag_power_on = 1;
		BSR 	6DH, 1H 			//034C 	24ED

		//;app_global.c: 192: bFlag_init_battery_volume = 1;
		BSR 	6DH, 0H 			//034D 	246D

		//;app_global.c: 193: forceDispTimer = 10;
		STR 	6EH 			//034E 	10EE
		RET 					//034F 	1008

		//;app_global.c: 103: PCKEN |= 0B00001000;
		MOVLB 	1H 			//0350 	1021
		BSR 	1AH, 3H 			//0351 	259A

		//;app_global.c: 107: TIM4CR1 = 0B00000101;
		LDWI 	5H 			//0352 	0005
		MOVLB 	2H 			//0353 	1022
		STR 	11H 			//0354 	1091

		//;app_global.c: 143: TIM4IER = 0B00000001;
		LDWI 	1H 			//0355 	0001
		STR 	12H 			//0356 	1092

		//;app_global.c: 146: TIM4SR = 0B00000000;
		CLRF 	13H 			//0357 	1193

		//;app_global.c: 153: TIM4EGR = 0B00000000;
		CLRF 	14H 			//0358 	1194

		//;app_global.c: 160: TIM4CNTR = 0;
		CLRF 	15H 			//0359 	1195

		//;app_global.c: 162: TIM4PSCR = 0B00000110;
		LDWI 	6H 			//035A 	0006
		STR 	16H 			//035B 	1096

		//;app_global.c: 171: TIM4ARR = 248;
		LDWI 	F8H 			//035C 	00F8
		STR 	17H 			//035D 	1097
		RET 					//035E 	1008
		STR 	72H 			//035F 	10F2

		//;app_global.c: 27: unsigned char a, b;
		//;app_global.c: 28: for (a = 0; a < timer; a++)
		CLRF 	73H 			//0360 	11F3
		LDR 	72H, 0H 			//0361 	1872
		SUBWR 	73H, 0H 		//0362 	1273
		BTSC 	3H, 0H 			//0363 	2803
		RET 					//0364 	1008

		//;app_global.c: 29: {
		//;app_global.c: 30: for (b = 0; b < 5; b++)
		CLRF 	74H 			//0365 	11F4

		//;app_global.c: 31: {
		//;app_global.c: 32: _dly_us(197);
		LDWI 	C5H 			//0366 	00C5
		LCALL 	2F3H 			//0367 	32F3
		MOVLP 	0H 			//0368 	0180
		LDWI 	5H 			//0369 	0005
		INCR 	74H, 1H 		//036A 	1AF4
		SUBWR 	74H, 0H 		//036B 	1274
		BTSS 	3H, 0H 			//036C 	2C03
		LJUMP 	366H 			//036D 	3B66
		INCR 	73H, 1H 		//036E 	1AF3
		LJUMP 	361H 			//036F 	3B61

		//;bsp_i2c.c: 44: PB7 = 0;
		MOVLB 	0H 			//0370 	1020
		BCR 	DH, 7H 			//0371 	238D

		//;bsp_i2c.c: 46: TRISC1 = 1;
		MOVLB 	1H 			//0372 	1021
		BSR 	EH, 1H 			//0373 	248E

		//;bsp_i2c.c: 47: unsigned char getAckTime = 250;
		LDWI 	FAH 			//0374 	00FA
		STR 	72H 			//0375 	10F2

		//;bsp_i2c.c: 48: _dly_us(0);
		LDWI 	0H 			//0376 	0000
		LCALL 	2F3H 			//0377 	32F3
		MOVLP 	0H 			//0378 	0180

		//;bsp_i2c.c: 49: PB7 = 1;
		MOVLB 	0H 			//0379 	1020
		BSR 	DH, 7H 			//037A 	278D

		//;bsp_i2c.c: 50: _dly_us(0);
		LDWI 	0H 			//037B 	0000
		LCALL 	2F3H 			//037C 	32F3
		MOVLP 	0H 			//037D 	0180

		//;bsp_i2c.c: 51: while (PC1)
		MOVLB 	0H 			//037E 	1020
		BTSS 	EH, 1H 			//037F 	2C8E
		LJUMP 	386H 			//0380 	3B86

		//;bsp_i2c.c: 52: {
		//;bsp_i2c.c: 53: --getAckTime;
		DECR 	72H, 1H 		//0381 	13F2

		//;bsp_i2c.c: 55: if (0 == getAckTime)
		LDR 	72H, 0H 			//0382 	1872
		BTSC 	3H, 2H 			//0383 	2903

		//;bsp_i2c.c: 56: {
		//;bsp_i2c.c: 57: return 1;
		RETW 	1H 			//0384 	0401
		LJUMP 	37EH 			//0385 	3B7E

		//;bsp_i2c.c: 58: }
		//;bsp_i2c.c: 59: }
		//;bsp_i2c.c: 61: PB7 = 0;
		BCR 	DH, 7H 			//0386 	238D

		//;bsp_i2c.c: 62: TRISC1 = 0;
		MOVLB 	1H 			//0387 	1021
		BCR 	EH, 1H 			//0388 	208E

		//;bsp_i2c.c: 63: return 0;
		RETW 	0H 			//0389 	0400
		LDWI 	83H 			//038A 	0083
		STR 	5H 			//038B 	1085
		LDR 	0H, 0H 			//038C 	1800
		IORWR 	3CH, 1H 		//038D 	14BC
		LDWI 	C3H 			//038E 	00C3
		STR 	4H 			//038F 	1084
		LDWI 	83H 			//0390 	0083
		STR 	5H 			//0391 	1085
		LDR 	0H, 0H 			//0392 	1800
		STR 	3BH 			//0393 	10BB
		LDWI 	C3H 			//0394 	00C3
		STR 	4H 			//0395 	1084
		LDWI 	83H 			//0396 	0083
		STR 	5H 			//0397 	1085
		LDR 	0H, 0H 			//0398 	1800
		STR 	3AH 			//0399 	10BA
		RET 					//039A 	1008
		ADDWI 	C3H 			//039B 	0EC3
		STR 	4H 			//039C 	1084
		LDWI 	83H 			//039D 	0083
		BTSC 	3H, 0H 			//039E 	2803
		ADDWI 	1H 			//039F 	0E01
		STR 	5H 			//03A0 	1085
		LDR 	0H, 0H 			//03A1 	1800
		RET 					//03A2 	1008
		LDWI 	18H 			//03A3 	0018
		STR 	75H 			//03A4 	10F5
		LDR 	7AH, 0H 			//03A5 	187A
		IORWI 	1H 			//03A6 	0801
		STR 	76H 			//03A7 	10F6
		RETW 	E8H 			//03A8 	04E8
		LDR 	7AH, 0H 			//03A9 	187A
		STR 	76H 			//03AA 	10F6
		LDWI 	18H 			//03AB 	0018
		BCR 	76H, 0H 			//03AC 	2076
		STR 	75H 			//03AD 	10F5
		RETW 	E8H 			//03AE 	04E8
		LDWI 	CBH 			//03AF 	00CB
		STR 	4H 			//03B0 	1084
		LDWI 	83H 			//03B1 	0083
		STR 	5H 			//03B2 	1085
		LDR 	0H, 0H 			//03B3 	1800
		RET 					//03B4 	1008
		STR 	76H 			//03B5 	10F6
		LDWI 	AH 			//03B6 	000A
		STR 	70H 			//03B7 	10F0
		LDR 	49H, 0H 			//03B8 	1849
		RET 					//03B9 	1008
		STR 	7AH 			//03BA 	10FA
		LDWI 	97H 			//03BB 	0097
		STR 	75H 			//03BC 	10F5
		RETW 	EAH 			//03BD 	04EA
		LDWI 	C0H 			//03BE 	00C0
		ANDWR 	79H, 0H 		//03BF 	1579
		STR 	78H 			//03C0 	10F8
		XORWI 	40H 			//03C1 	0A40
		RET 					//03C2 	1008
		RETW 	3FH 			//03C3 	043F
		RETW 	6H 			//03C4 	0406
		RETW 	5BH 			//03C5 	045B
		RETW 	4FH 			//03C6 	044F
		RETW 	66H 			//03C7 	0466
		RETW 	6DH 			//03C8 	046D
		RETW 	7DH 			//03C9 	047D
		RETW 	7H 			//03CA 	0407
		RETW 	7FH 			//03CB 	047F
		RETW 	6FH 			//03CC 	046F
		RETW 	40H 			//03CD 	0440
		RETW 	0H 			//03CE 	0400
		CLRWDT 			//03CF 	1064
		CLRF 	0H 			//03D0 	1180
		ADDFSR 	0H, 1H 		//03D1 	0101
		DECRSZ 	9H, 1H 		//03D2 	1B89
		LJUMP 	3D0H 			//03D3 	3BD0
		RETW 	0H 			//03D4 	0400
			END
