/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_host_hs.h
* Author             : WCH
* Version            : V1.1
* Date               : 2023/02/16
*
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#ifndef HOST_HS_CH56X_HOST_HS_H_
#define HOST_HS_CH56X_HOST_HS_H_

#ifdef __cplusplus
extern "C" {
#endif

//#include "core_riscv.h"
#define U20_MAXPACKET_LEN       512
#define WAIT_TIME               10000000

#ifndef  ENDPOINT_NUM
#define  ENDP_0                 0
#define  ENDP_1                 1
#define  ENDP_2                 2
#define  ENDP_3                 3
#define  ENDP_4                 4
#define  ENDP_5                 5
#define  ENDP_6                 6
#define  ENDP_7                 7
#endif
/*******************TRANSFER STATUS***********************/
#ifndef ERR_SUCCESS
#define ERR_SUCCESS           (0x00)
#define ERR_USB_CONNECT       (0x15)
#define ERR_USB_DISCON        (0x16)
#define ERR_USB_BUF_OVER      (0x17)
#define ERR_USB_DISK_ERR      (0x1F)
#define ERR_USB_TRANSFER      (0x20)
#define ERR_USB_UNSUPPORT     (0xFB)
#define ERR_USB_UNKNOWN       (0xFE)
#define ERR_AOA_PROTOCOL      (0x41)
#define ERR_TIME_OUT          (0xFF)
#endif

typedef struct
{
    uint16_t  OutEndpMaxSize;
    uint16_t  InEndpMaxSize;
    uint8_t   InEndpNum;
    uint8_t   InEndpCount;
    uint8_t   InTog;
    uint8_t   OutEndpNum;
    uint8_t   OutTog;
    uint8_t   OutEndpCount;
}DEVENDP;

typedef struct  __attribute__((packed))
{
     DEVENDP DevEndp;
     uint8_t   DeviceStatus;
     uint8_t   DeviceAddress;
     uint8_t   DeviceSpeed;
     uint8_t   DeviceType;
     uint8_t   DeviceEndp0Size;
     uint8_t   DeviceCongValue;

 }DEV_INFO_Typedef,*pDEV_INFO_Typedef;


 void  CopySetupReqPkg( const uint8_t *pReqPkt );
 void  SetBusReset(void);
 void  USBHS_CurrentAddr( uint8_t addr );
 void  USBHS_Host_Init(FunctionalState sta);
 void  USBHS_Analysis_Descr(pDEV_INFO_Typedef pusbdev,uint8_t * pdesc, uint16_t l);

 uint8_t USBHS_Transact( uint8_t endp_pid, uint8_t toggle,uint32_t timeout);
 uint8_t USBHS_HostCtrlTransfer(uint8_t *databuf,uint16_t * len);
 uint8_t USBHS_Host_Enum(uint8_t *Databuf);
 uint8_t CtrlGetDevDescr( uint8_t *databuf );
 uint8_t CtrlGetConfigDescr( uint8_t *databuf );
 uint8_t CtrlSetAddress( uint8_t addr );
 uint8_t CtrlSetConfig( uint8_t cfg_val );

#ifdef __cplusplus
}
#endif

#endif /* HOST_HS_CH56X_HOST_HS_H_ */

