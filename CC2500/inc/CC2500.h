/***************************************************************
 *  SmartRF Studio(tm) Export
 *
 *  Radio register settings specifed with C-code
 *  compatible #define statements.
 *
 ***************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CC2500
#define CC2500

 #include "stm32f4xx.h"
 #include "stm32f4xx_conf.h"


/* CC2500 structs */




#define CC2500_FLAG_TIMEOUT         ((uint32_t)0x1000)

/**
  * @brief  CC2500 SPI Interface pins
  */
	
#define CC2500_SPI                       SPI2
#define CC2500_SPI_CLK                   RCC_APB1Periph_SPI2

	
	

/******************************************************************************/
/*************************** START REGISTER MAPPING  **************************/
/******************************************************************************/

//Frequency Synthesizer Control
#define CC2500_FSCTRL1    0x0C//0x12 //Frequency offset = 457kHz  Frequency Synthesizer Control
/*
Bit 	Field Name 				Description
7:5 	Reserved
4:0 	FREQ_IF[4:0]			The desired IF frequency to employ in RX. Subtracted from FS
												base frequency in RX and controls the digital complex mixer in
												the demodulator.
												The default value gives an IF frequency of 381 kHz, assuming
												a 26.0 MHz crystal.
*/

#define CC2500_FSCTRL0    0x00 //Frequency Synthesizer Control
/*
Bit 		Field Name 			Description
7:0 		FREQOFF[7:0]  	Frequency offset added to the base frequency before being
												used by the FS. (2�s complement).
												Resolution is FXTAL/214 (1.59 - 1.65 kHz); range is �202 kHz to
												�210 kHz, dependent of XTAL frequency.
*/


//Frequency Control Word, High Byte
#define CC2500_FREQ2      0x5D // Carrier Frequency is 2.433GHz
/*
Bit 		Field Name			Description
7:6 		FREQ[23:22] 		FREQ[23:22] is always binary 01 (the FREQ2 register is in the range 85 to
												95 with 26-27 MHz crystal)
5:0 		FREQ[21:16] 		FREQ[23:0] is the base frequency for the frequency synthesiser in
												increments of FXOSC/2^16.
*/


//Frequency Control Word, Middle Byte
#define CC2500_FREQ1      0x93
/*
Bit 		Field Name 			Description
7:0 		FREQ[15:8] 			FREQ2 register
*/


//Frequency Control Word, Low Byte
#define CC2500_FREQ0      0xB1
/*
Bit 		Field Name 			Description
7:0 		FREQ[7:0] 			Ref. FREQ2 register
*/


//Modem Configuration
#define CC2500_MDMCFG4    0x0E //0x2D // BW of channel = 541.666kHz

#define CC2500_MDMCFG3    0x3B // Baud Rate = 125kb, Modem Config

#define CC2500_MDMCFG2    0x73 //0xF3 // Disable digital DC blocking filter before demodulator, MSK modulation, 16/16 sync word bits detected

#define CC2500_MDMCFG1    0x42 //0x22 Modem Config

#define CC2500_MDMCFG0    0xF8 // Default Channel Spacing of 200kHz


//Channel Number
#define CC2500_CHANNR     0x00 // Channel 0

//Modem Deviation Setting
#define CC2500_DEVIATN    0x00 //0x01 // 1785kHz

//Front End RX Configuration
#define CC2500_FREND1     0xB6

//Front End TX configuration
#define CC2500_FREND0     0x10

#define CC2500_MCSM0      0x18 // Automatically calibrate When going from IDLE to RX or TX (or FSTXON) check CC2500 datasheet
/*
Main Radio Control State Machine
Bit 		Field Name 			Description
7:6 		Reserved
5:4 		FS_AUTOCAL[1:0] Automatically calibrate when going to RX or TX, or back to IDLE
												Setting 	When to perform automatic calibration
												0 (00) 		Never (manually calibrate using SCAL strobe)
												1 (01) 		When going from IDLE to RX or TX (or FSTXON)
												2 (10) 		When going from RX or TX back to IDLE
																	automatically
												3 (11)		Every 4th time when going from RX or TX to IDLE
																	automatically
																	In some automatic wake-on-radio (WOR) applications, using
																	setting 3 (11) can significantly reduce current consumption.
3:2 PO_TIMEOUT 					Programs the number of times the six-bit ripple counter must
												expire after XOSC has stabilized before CHP_RDYn goes low.
												If XOSC is on (stable) during power-down, PO_TIMEOUT
												should be set so that the regulated digital supply voltage has
												time to stabilize before CHP_RDYn goes low (PO_TIMEOUT=2
												recommended). Typical start-up time for the voltage regulator is
												50 us.
												If XOSC is off during power-down and the regulated digital
												supply voltage has sufficient time to stabilize while waiting for
												the crystal to be stable, PO_TIMEOUT can be set to 0. For
												robust operation it is recommended to use PO_TIMEOUT=2.
																	Setting Expire count 		Timeout after XOSC start
																	0 (00) 	1 							Approx. 2.3 � 2.4 �s
																	1 (01) 	16 							Approx. 37 � 39 �s
																	2 (10) 	64 							Approx. 149 � 155 �s
																	3 (11) 	256 						Approx. 597 � 620 �s
																	Exact timeout depends on crystal frequency.
1 PIN_CTRL_EN						Enables the pin radio control option
0 XOSC_FORCE_ON					Force the XOSC to stay on in the SLEEP state.

*/


#define CC2500_FOCCFG     0x1D // Frequency Offset Compensation Configuration
/*
Bit 		Field Name 			Description
7:6 		Reserved 
5 			FOC_BS_CS_GATE  If set, the demodulator freezes the frequency offset
												compensation and clock recovery feedback loops until the
												CARRIER_SENSE signal goes high.
4:3 		FOC_PRE_K[1:0] 	The frequency compensation loop gain to be used before a sync
												word is detected.
															Setting 			Freq. compensation loop gain before sync word
																	0 (00) 				K
																	1 (01) 				2K
																	2 (10) 				3K
																	3 (11) 				4K
2 FOC_POST_K 						The frequency compensation loop gain to be used after a sync
												word is detected.
															Setting 		Freq. compensation loop gain after sync word
																	0 					Same as FOC_PRE_K
																	1 					K/2
1:0 FOC_LIMIT[1:0]			The saturation point for the frequency offset compensation
												algorithm:
															Setting 		Saturation point (max compensated offset)
															0 (00) 						�0 (no frequency offset compensation)
															1 (01) 						�BWCHAN/8
															2 (10) 						�BWCHAN/4
															3 (11) 						�BWCHAN/2
												Frequency offset compensation is not supported for OOK;
												Always use FOC_LIMIT=0 with this modulation format.
*/

#define CC2500_BSCFG      0x1C

#define CC2500_AGCCTRL2   0xC7

#define CC2500_AGCCTRL1   0x40 //0x00

#define CC2500_AGCCTRL0   0xB0

#define CC2500_FSCAL3     0xEA

#define CC2500_FSCAL2     0x0A

#define CC2500_FSCAL1     0x00

#define CC2500_FSCAL0     0x19 //0x11

#define CC2500_FSTEST     0x59

#define CC2500_TEST2      0x88

#define CC2500_TEST1      0x31

#define CC2500_TEST0      0x0B

#define CC2500_FIFOTHR    0x07	//RX FIFO and TX FIFO Thresholds
/*
Bit		Description
7:4		Reserved
3:0		Set threshold for TX FIFO and RX FIFO
			Setting 						Bytes in TX FIFO 					Bytes in RX FIFO
				0 	(0000) 					61					 							4
				1 	(0001) 					57 												8
				2 	(0010) 					53 												12
				3 	(0011) 					49 												16
				4 	(0100) 					45 												20
				5 	(0101) 					41 												24
				6 	(0110) 					37 												28
				7 	(0111) 					33 												32
				8 	(1000) 					29 												36
				9 	(1001) 					25 												40
				10 	(1010) 					21 												44
				11 	(1011) 					17 												48
				12 	(1100) 					13 												52
				13 	(1101) 					9 												56
				14 	(1110) 					5 												60
				15 	(1111) 					1 												64

*/

#define CC2500_IOCFG2     0x29
/*
Bit		Description
7			Reserved		
6			Invert output, i.e. select active low (1) / high (0)
5:0		Default is CHIP_RDYn
*/

#define CC2500_IOCFG0D    0x06
/*
Bit 			Field Name 					Description
7 				TEMP_SENSOR_ENABLE 	Enable analog temperature sensor. Write 0 in all other
															register bits when using temperature sensor.
6 				GDO0_INV 						Invert output, i.e. select active low (1) / high (0)
5:0 			GDO0_CFG[5:0] 			Default is CLK_XOSC/192 (see Table 33 on page 53 of Datasheet).
*/

#define CC2500_PKTCTRL1   0x04  //Packet Automation Control
/*
Bit				Field Name			Description
7:5				PQT[2:0]				
4					Reserved				
3					CRC_AUTOFLUSH		
2					APPEND_STATUS		
1:0				ADR_CHK[1:0]		Setting  			Address check configuration
														0 (00) 			No address check
														1 (01) 			Address check, no broadcast
														2 (10) 			Address check and 0 (0x00) broadcast
														3 (11) 			Address check and 0 (0x00) and 255 (0xFF)
																				broadcast

*/

#define CC2500_PKTCTRL0   0x05 //0x05 // Fixed Packet Length (0x05)
/*
Bit				Field Name				Description
7					Reserved
6					WHITE_DATA				Turn data whitening on / off
														0: Whitening off
														1: Whitening on
														Data whitening can only be used when
														PKTCTRL0.CC2400_EN=0 (default).					
5:4				PKT_FORMAT[1:0]		Format of RX and TX data
														Setting			Packet format
														0 (00) 			Normal mode, use FIFOs for RX and TX
														1 (01) 			Synchronous serial mode, used for backwards
																				compatibility. Data in on GDO0
														2 (10) 			Random TX mode; sends random data using PN9
																				generator. Used for test.
																				Works as normal mode, setting 0 (00), in RX.
														3 (11) 			Asynchronous serial mode. Data in on
3					CC2400_EN					Enable CC2400 support. Use same CRC implementation as
														CC2400.
														PKTCTRL1.CRC_AUTOFLUSH must be 0 if
														PKTCTRL0.CC2400_EN=1.
														PKTCTRL0.WHITE_DATA must be 0 if
														PKTCTRL0.CC2400_EN=1.
2					CRC_EN						1: CRC calculation in TX and CRC check in RX enabled
														0: CRC disabled for TX and RX
1:0				LENGTH_CONFIG[1:0]Configure the packet length
														Setting			Packet length configuration
														0 (00) 			Fixed packet length mode. Length configured in
																				PKTLEN register
														1 (01) 			Variable packet length mode. Packet length
																				configured by the first byte after sync word
														2 (10) 			Infinite packet length mode
														3 (11) 			Reserved


*/

#define CC2500_ADDR       0x00 // Global Broadcast Address
/*
Bit			Field Name
7:0 		DEVICE_ADDR[7:0] 0    Address used for packet filtration. Optional
*/

#define CC2500_PKTLEN     0x0A // Packet Length of 10bytes (0xFF)
/*
Bit 		Field Name 			Description
7:0 		PACKET_LENGTH 	Indicates the packet length when fixed packet length is
												enabled. If variable length packets are used, this value
												indicates the maximum length packets allowed.
*/

#endif