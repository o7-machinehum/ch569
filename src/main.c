/********************************** (C) COPYRIGHT *******************************
* File Name          : Main.c
* Author             : WCH
* Version            : V1.1
* Date               : 2023/02/16
*
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

/*
 * @Note
 * This routine is used for USB3.0 device.Simulated a CH372 device.
 * The host can burst 4 packets of data to endpoint 1 and then take 4 packets of data from endpoint 1.
 * The host can continuously send or receive data to endpoint 2-7 (to test the speed).
*/

#include "ch56x_common.h"
#include "ch56x_usb30.h"
#include "ch56x_usb20.h"
#include "sw_udisk.h"
#include "sd.h"
/* Global define */
#define  UART1_BAUD     115200

/*******************************************************************************
 * @fn        DebugInit
 *
 * @brief     Initializes the UART1 peripheral.
 *
 * @param     baudrate: UART1 communication baud rate.
 *
 * @return    None
 */
void DebugInit(uint32_t baudrate)
{
	uint32_t x;
	uint32_t t = FREQ_SYS;
	x = 10 * t * 2 / 16 / baudrate;
	x = ( x + 5 ) / 10;
	R8_UART1_DIV = 1;
	R16_UART1_DL = x;
	R8_UART1_FCR = RB_FCR_FIFO_TRIG | RB_FCR_TX_FIFO_CLR | RB_FCR_RX_FIFO_CLR | RB_FCR_FIFO_EN;
	R8_UART1_LCR = RB_LCR_WORD_SZ;
	R8_UART1_IER = RB_IER_TXD_EN;
	R32_PA_SMT |= (1<<8) |(1<<7); // PA8, PX7
	R32_PA_DIR |= (1<<8); // PA8
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main( void )
{
    uint8_t   s;
    uint16_t  i;

    SystemInit(FREQ_SYS);
	Delay_Init(FREQ_SYS);

	/* LED on PA9 for status */
	R32_PA_DIR |= (1<<9);
	R32_PA_OUT &= ~(1<<9);

	/* Configure serial port debugging */
	DebugInit(UART1_BAUD);
	PRINT("CH56x USB3.0 & USB2.0 device test(80MHz) !\n");

	/* SD card initialization */
    PFIC_EnableIRQ(EMMC_IRQn);
    R32_EMMC_TRAN_MODE = 0;

    /* GPIO config: pull-ups, clock output, start in 1-bit mode at low speed */
    R32_PB_PU  |= bSDCMD;
    R32_PB_PU  |= (0x1f<<17);
    R32_PA_PU  |= (7<<0);
    R32_PB_DIR |= bSDCK;
    R32_PA_DRV |= (7<<0);
    R32_PB_DRV |= (0x1f<<17);
    R32_PB_DRV |= bSDCMD;
    R32_PB_DRV |= bSDCK;

    R8_EMMC_CONTROL = RB_EMMC_ALL_CLR | RB_EMMC_RST_LGC;
    R8_EMMC_CONTROL = RB_EMMC_NEGSMP | RB_EMMC_DMAEN;
    R8_EMMC_CONTROL = (R8_EMMC_CONTROL & ~RB_EMMC_LW_MASK) | bLW_OP_DAT0;
    R16_EMMC_CLK_DIV = RB_EMMC_CLKOE | RB_EMMC_PHASEINV | LOWEMMCCLK;

    R16_EMMC_INT_FG = 0xffff;
    R16_EMMC_INT_EN = RB_EMMC_IE_FIFO_OV | RB_EMMC_IE_TRANERR |
                      RB_EMMC_IE_DATTMO | RB_EMMC_IE_REIDX_ER |
                      RB_EMMC_IE_RECRC_WR | RB_EMMC_IE_RE_TMOUT;
    R8_EMMC_TIMEOUT = 14;

    /* SD init sequence: CMD0, CMD8, ACMD41, CMD2, CMD3, CMD9, CMD7 */
    EMMCResetIdle(&TF_EMMCParam);
    mDelaymS(30);
    EMMCResetIdle(&TF_EMMCParam);
    mDelaymS(30);

    /* CMD8 - voltage check */
    for(i = 0; i < 3; i++) {
        EMMCSendCmd(0x01AA, RB_EMMC_CKIDX | RB_EMMC_CKCRC | RESP_TYPE_48 | EMMC_CMD8);
        while(1) {
            s = CheckCMDComp(&TF_EMMCParam);
            if(s != CMD_NULL) break;
        }
        if(s == CMD_SUCCESS) break;
        mDelaymS(30);
    }
    if(s != CMD_SUCCESS) { PRINT("SD CMD8 Failed\n"); R32_PA_OUT |= (1<<9); while(1); }

    s = SDReadOCR(&TF_EMMCParam);
    if(s != CMD_SUCCESS) { PRINT("SD ACMD41 Failed\n"); R32_PA_OUT |= (1<<9); while(1); }

    s = EMMCReadCID(&TF_EMMCParam);
    if(s != CMD_SUCCESS) { PRINT("SD CMD2 Failed\n"); R32_PA_OUT |= (1<<9); while(1); }

    s = SDSetRCA(&TF_EMMCParam);
    if(s != CMD_SUCCESS) { PRINT("SD CMD3 Failed\n"); R32_PA_OUT |= (1<<9); while(1); }

    s = SDReadCSD(&TF_EMMCParam);
    if(s != CMD_SUCCESS) { PRINT("SD CMD9 Failed\n"); R32_PA_OUT |= (1<<9); while(1); }

    mDelaymS(5);
    s = SelectEMMCCard(&TF_EMMCParam);
    if(s != CMD_SUCCESS) { PRINT("SD CMD7 Failed\n"); R32_PA_OUT |= (1<<9); while(1); }

    /* Switch to 4-bit bus */
    s = SDSetBusWidth(&TF_EMMCParam, 1);
    if(s != CMD_SUCCESS) { PRINT("SD bus width Failed\n"); R32_PA_OUT |= (1<<9); while(1); }
    R8_EMMC_CONTROL = (R8_EMMC_CONTROL & ~RB_EMMC_LW_MASK) | bLW_OP_DAT4;

    /* Increase clock speed */
    R16_EMMC_CLK_DIV = RB_EMMC_CLKMode | RB_EMMC_PHASEINV | RB_EMMC_CLKOE | 10;

    TF_EMMCParam.EMMCOpErr = 0;
    PRINT("SD Init OK SecNum:%x SecSize:%x\r\n",
          TF_EMMCParam.EMMCSecNum, TF_EMMCParam.EMMCSecSize);

	/* USB initialization - skip USB3.0, go straight to USB2.0 */
    R32_USB_CONTROL = 0;
    PFIC_EnableIRQ(USBHS_IRQn);
    USB20_Device_Init(ENABLE);

    /* Enable Udisk */
	Udisk_Capability = TF_EMMCParam.EMMCSecNum;
    Udisk_Status |= DEF_UDISK_EN_FLAG;

	while(1)
	{
	    UDISK_onePack_Deal();
	}
}

