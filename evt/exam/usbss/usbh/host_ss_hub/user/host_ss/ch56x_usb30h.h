/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_usb30h.h
* Author             : WCH
* Version            : V1.1
* Date               : 2023/02/16
*
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

#ifndef HOST_CH56X_USB30H_H_
#define HOST_CH56X_USB30H_H_

#ifdef __cplusplus
extern "C" {
#endif

#define USBSS_ENDP0_MAXSIZE   512
#define ENDP_0                0
#define ENDP_1                1
#define ENDP_2                2
#define ENDP_3                3
#define ENDP_4                4
#define ENDP_5                5
#define ENDP_6                6
#define ENDP_7                7

#define USB_U30_SPEED         (0x02)
#define USB_U20_SPEED         (0x01)

#define ERR_SUCCESS1            0x14
#define ERR_USB_LENGTH          0x18
#define ERR_USB_DATAERR         0x19

#define USB_OPERATE_SUCCESS                 0x00            /* USB Operation succeeded */
#define USB_OPERATE_ERROR                   0x01            /* USB operation failed */
#define USB_PARAMETER_ERROR                 0x03            /* Parameter error, range overflow */
#define USB_INT_CONNECT_U20                 0x13            /* USB device connection event detected */
#define USB_INT_SUCCESS                     0x14            /* USB transaction or transfer operation succeeded */
#define USB_INT_CONNECT                     0x15            /* USB device connection event detected */
#define USB_INT_DISCONNECT                  0x16            /* USB device disconnect event detected */
#define USB_INT_BUF_OVER                    0x17            /* Too much data transferred by USB control, buffer overflow */
#define USB_INT_DISK_ERR                    0x1F            /* USB memory operation failed */
#define USB_INT_DISK_ERR1                   0x20            /* USB memory operation failed */
#define USB_CH56XUSBTIMEOUT                 0x28            /* USB device timeout */

#define USB30_OUT_DISCONNECT        0xFA
#define USB30_IN_DISCONNECT         0xAAFF

#define U30_PID_OUT                     0x00            /* OUT */
#define U30_PID_IN                      0x01            /* IN */

typedef struct __PACKED  _HOST_STATUS
{
    uint8_t InSeqNum[8];
    uint8_t InMaxBurstSize[8];
    uint8_t OutSeqNum[8];
    uint8_t OutMaxBurstSize[8];
}DevInfo,PDevInfo;

typedef struct _USB_ENDPOINT_DESCRIPTOR_U30 /*Endpoint descriptor*/
{
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bEndpointAddress;
    uint8_t  bmAttributes;
    uint8_t  wMaxPacketSizeL;
    uint8_t  wMaxPacketSizeH;
    uint8_t  bInterval;

    uint8_t  bLength1;                //3.0 EndpointCompanion descriptor
    uint8_t  bDescriptorType1;
    uint8_t  bMaxBurst1;
    uint8_t  bmAttributes1;
    uint8_t  wBytesPerInterval_L;
    uint8_t  wBytesPerInterval_H;
}USB_ENDP_DESCR_U30, *PUSB_ENDP_DESCR_U30;

typedef struct _USB_CONFIG_DESCRIPTOR_LONG_U30
{
    USB_CFG_DESCR  cfg_descr;
    USB_ITF_DESCR  itf_descr;
    USB_ENDP_DESCR_U30 endp_descr[2];
}USB_CFG_DESCR_LONG_U30, *PUSB_CFG_DESCR_LONG_U30;

extern volatile uint8_t device_link_status;
extern volatile uint8_t gDeviceConnectstatus;                                                    /* USB connection status */
extern uint8_t  gDeviceUsbType;                                                      /* 01--USB2.0&1.1  02--USB3.0*/
extern uint8_t  gDeviceClassType;

extern const uint8_t get_descriptor[];
extern const uint8_t get_cfg_descriptor[];
extern const uint8_t get_cfg_descriptor_all[];
extern const uint8_t get_bos_descriptor[];
extern const uint8_t get_string_descriptor0[];
extern const uint8_t get_string_descriptor1[];
extern const uint8_t get_string_descriptor2[];
extern const uint8_t get_string_descriptor3[];
extern const uint8_t get_interface[];
extern const uint8_t set_configuration[];
extern const uint8_t set_address[];
extern const uint8_t set_isoch_delay[];
extern const uint8_t set_sel[];
extern const uint8_t tx_sel_data[];
extern const uint8_t set_feature_U1[];
extern const uint8_t set_feature_U2[];

extern __attribute__ ((aligned(16))) uint8_t endpRXbuff[512] __attribute__((section(".DMADATA")));
extern __attribute__ ((aligned(16))) uint8_t endpTXbuff[512] __attribute__((section(".DMADATA")));

extern __attribute__ ((aligned(16))) uint8_t Test_Buf[3072] __attribute__((section(".DMADATA")));



uint8_t USB30HOST_ClearEndpStall( uint8_t endp );
void USB30Host_Enum(uint8_t depth,uint8_t addr,  uint8_t port );
void USB30_link_status(uint8_t s);
uint16_t USB30HOST_INTransaction(uint8_t seq_num,uint8_t *recv_packnum ,uint8_t endp_num,uint16_t *status);
uint8_t  USB30HOST_OUTTransaction(uint8_t seq_num,uint8_t send_packnum ,uint8_t endp_num,uint32_t txlen);
uint16_t USB30HOST_CtrlTransaciton(uint8_t *databuf);
uint8_t U30HOST_GetHubDescr( uint8_t *buf ,uint16_t *len );
uint8_t U30HOST_GetDeviceStstus( void );
uint8_t U30HOST_GetPortStstus( uint8_t depth,uint8_t port );
uint8_t U30HOST_SetHubDepth( uint8_t depth );
uint8_t U30HOST_SetPortFeatrue( uint8_t port );
uint8_t USB30HSOT_Enumerate_Hotrst( uint8_t *pbuf );
uint8_t  USBSS_HUB_Main_Process( uint8_t depth ,uint8_t addr,uint8_t uplevelport,uint32_t routestring,uint8_t portnum);
uint8_t USBSS_HUBCheckPortConnect( uint8_t depth,uint8_t port );

void LINK_IRQHandler (void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USBSS_IRQHandler (void) __attribute__((interrupt("WCH-Interrupt-fast")));

#ifdef __cplusplus
}
#endif

#endif /* USER_USB30H_PROCESS_H_ */
