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
    uint16_t  InEndpMaxSize;          // IN  Maximum packet size of endpoint
    uint8_t   InEndpNum;              // IN  endpoint number
    uint8_t   InEndpCount;            // IN  endpoint count
    uint8_t   InTog;                  // IN Synchronization flag
    uint8_t   OutEndpNum;             // OUT endpoint number
    uint8_t   OutTog;
    uint8_t   OutEndpCount;           // IN  endpoint count
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
 void  USB20HOST_SetBusReset(void);
 void  USB20Host_Init(FunctionalState sta);
 uint8_t USB20HOST_CtrlTransfer(uint8_t *ReqBuf, uint8_t *DataBuf, uint8_t *RetLen );
 uint8_t USB20HOST_ClearEndpStall( uint8_t endp );
 uint8_t USB20HOST_Transact( uint8_t endp_pid, uint8_t toggle,uint32_t timeout);
 uint8_t USB20Host_Enum(uint8_t *Databuf);


#ifdef __cplusplus
}
#endif

#endif /* HOST_HS_CH56X_HOST_HS_H_ */

