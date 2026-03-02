/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_COMM.h
* Author             : WCH
* Version            : V1.0
* Date               : 2020/07/31
* Description
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/


#ifndef __CH56x_COMM_H__
#define __CH56x_COMM_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "stdio.h"
#include "string.h"
#include "core_riscv.h"
#include "ch56x_sys.h"
#include "ch56x_clk.h"
#include "ch56x_uart.h"
#include "ch56x_gpio.h"
#include "ch56x_pwm.h"
#include "ch56x_timer.h"
#include "ch56x_spi.h"
#include "ch56x_hspi.h"
#include "ch56x_dvp.h"
#include "ch56x_bus8.h"
#include "ch56x_ecdc.h"
#include "ch56x_pwr.h"
#include "ch56x_emmc.h"
#include "ch56x_eth.h"

/* UART Printf Definition */
#define Debug_UART0        0
#define Debug_UART1        1
#define Debug_UART2        2
#define Debug_UART3        3

/* SystemCoreClock */ 
#ifndef	 FREQ_SYS  
#define  FREQ_SYS		80000000   
#endif   


#define DelayMs(x)      mDelaymS(x)	  
#define DelayUs(x)      mDelayuS(x)	  



#ifdef __cplusplus
}
#endif

#endif  // __CH56x_COMM_H__	 

