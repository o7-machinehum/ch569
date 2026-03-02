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
#define USB_INT_CONNECT_U20   (0x13)
#define USB_INT_SUCCESS       (0x14)
#define USB_INT_CONNECT       (0x15)
#define USB_INT_DISCONNECT    (0x16)

typedef struct __PACKED  _HOST_STATUS
{
    uint8_t InSeqNum[8];
    uint8_t InMaxBurstSize[8];
    uint8_t OutSeqNum[8];
    uint8_t OutMaxBurstSize[8];
}DevInfo,PDevInfo;

extern volatile uint8_t device_link_status;

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

extern __attribute__ ((aligned(16))) uint8_t endpRXbuff[4096] __attribute__((section(".DMADATA")));
extern __attribute__ ((aligned(16))) uint8_t endpTXbuff[4096] __attribute__((section(".DMADATA")));

extern void   USB30_Host_Enum(void);
extern void   USB30_link_status(uint8_t s);
extern uint16_t USBSS_INTransaction(uint8_t seq_num,uint8_t *recv_packnum ,uint8_t endp_num);
extern uint8_t  USBSS_OUTTransaction(uint8_t seq_num,uint8_t send_packnum ,uint8_t endp_num,uint32_t txlen);

uint16_t USB30HOST_CtrlTransaciton(uint8_t *databuf);
uint16_t GetDEV_Descriptor(void);
uint16_t GetConfig_Descriptor(void);
void Set_Address(uint8_t addr);
void Set_IsochDelay(void);
void Set_Sel(void);
void Set_Configuration(void);
void Analysis_Descr(uint8_t *pdesc, uint16_t l);

void LINK_IRQHandler (void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USBSS_IRQHandler (void) __attribute__((interrupt("WCH-Interrupt-fast")));

#ifdef __cplusplus
}
#endif

#endif /* USER_USB30H_PROCESS_H_ */
