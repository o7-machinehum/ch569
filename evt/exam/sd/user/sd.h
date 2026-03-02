/********************************** (C) COPYRIGHT *******************************
* File Name          : SD.h
* Author             : WCH
* Version            : V1.0
* Date               : 2020/07/31
* Description
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/


#ifndef __SD_H__
#define __SD_H__
#include "ch56xsfr.h"
#include "ch56x_emmc.h"

uint8_t SDReadOCR( PSD_PARAMETER pEMMCPara );
uint8_t SDSetRCA( PSD_PARAMETER pEMMCPara );
uint8_t SDReadCSD( PSD_PARAMETER pEMMCPara );
uint8_t SDSetBusWidth(PSD_PARAMETER pEMMCPara, uint8_t bus_mode);
uint8_t SD_ReadSCR(PSD_PARAMETER pEMMCPara, uint8_t * pRdatbuf);
uint8_t SDCardReadOneSec( PSD_PARAMETER pEMMCPara, uint8_t * pRdatbuf, uint32_t Lbaaddr );
uint8_t SDCardWriteONESec( PSD_PARAMETER pEMMCPara,  uint8_t * pWdatbuf, uint32_t Lbaaddr );

#endif
