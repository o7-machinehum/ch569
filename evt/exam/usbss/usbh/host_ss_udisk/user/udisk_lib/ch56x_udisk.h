/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56X_UDISK.h
* Author             : WCH
* Version            : V1.1
* Date               : 2023/02/16
*
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

#include "ch56x_common.h"
#include "ch56xusb30h_lib.h"
#include "ch56x_usb30h.h"
#include "ch56x_host_hs.h"/******************************************************************************/

#define USB_BO_CBW_SIG			  0x43425355									/* Command block CBW identification flag'USBC' */
#define USB_BO_CSW_SIG			  0x53425355									/* Command block CSW identification flag'USBC' */

#define USB_BO_CBW_SIZE			  0x1F											/* Total length of command block CBW */
#define USB_BO_CSW_SIZE			  0x0D											/* Total length of command status block CSW */
#define USB_BO_DATA_IN			  0x80
#define USB_BO_DATA_OUT			  0x00


typedef union _BULK_ONLY_CMD
{
	struct
	{
		uint32_t mCBW_Sig;
		uint32_t mCBW_Tag;
		uint32_t mCBW_DataLen;													/* Input: data transmission length */
		uint8_t  mCBW_Flag;														/* Input: transmission direction and other signs */
		uint8_t  mCBW_LUN;
		uint8_t  mCBW_CB_Len;														/* Input: length of command block, valid values are 1 to 16 */
		uint8_t  mCBW_CB_Buf[16];													/* Input: Command block, the buffer is up to 16 bytes */
	} mCBW;																		/* Command block of BulkOnly protocol, input CBW structure */
	struct
	{
		uint32_t mCSW_Sig;
		uint32_t mCSW_Tag;
		uint32_t mCSW_Residue;													/* Return: Remaining data length */
		uint8_t  mCSW_Status;														/* Return: command execution result status */
	} mCSW;																		/* Command status block of BulkOnly protocol, output CSW structure */
} BULK_ONLY_CMD;


/******************************************************************************/
extern uint8_t  gDiskMaxLun;                                                             /* Maximum logical unit number of disk */
extern uint8_t  gDiskCurLun;                                                             /* Current operating logical unit number of the disk */
extern uint32_t gDiskCapability;                                                         /* Total disk capacity */
extern uint32_t gDiskPerSecSize;                                                         /* Disk sector size */
extern uint8_t  gDiskBulkInEp;                                                           /* IN endpoint address of USB mass storage device */
extern uint8_t  gDiskBulkInTog;                                                          /* USB mass transfer synchronization flag : 0-31 */
extern uint8_t  gDiskBulkOutEp;                                                          /* OUT endpoint address of USB mass storage device */
extern uint8_t  gDiskBulkOutTog;                                                         /* USB mass transfer synchronization flag : 0-31 */
extern uint16_t gDiskBulkInEpSize;                                                       /* Maximum packet size of IN endpoint of USB mass storage device */
extern uint16_t gDiskBulkOutEpSize;                                                      /* The maximum packet size of the OUT endpoint of the USB mass storage device */
extern uint8_t  gDiskInterfNumber;                                                       /* Interface number of USB mass storage device */
extern volatile uint8_t gDeviceConnectstatus;                                                    /* USB connection status */
extern uint8_t  gDeviceUsbType;                                                          /* 01--USB2.0&1.1  02--USB3.0*/

#define	DEFAULT_MAX_OPERATE_SIZE      	8*1024					/***Default maximum packet size for current operation***/
#define	MAX_DATA_ADDR	0x20020000
extern volatile uint8_t U30_TIME_OUT;
extern volatile uint8_t tx_lmp_port;
extern volatile uint8_t Hot_ret_flag;
extern __attribute__ ((aligned(16))) uint8_t pNTFS_BUF[512] __attribute__((section(".DMADATA")));
extern uint8_t gUdisk_flag;
extern uint8_t gUdisk_flag1;
extern uint16_t gUdisk_delay;

extern uint8_t MS_U30HOST_CofDescrAnalyse( uint8_t *pbuf );
extern uint8_t MS_Init(  uint8_t *pbuf );
extern uint8_t MS_ReadSector( uint32_t StartLba, uint16_t SectCount, uint8_t * DataBuf );
extern uint8_t MS_WriteSector( uint32_t StartLba, uint8_t SectCount, uint8_t * DataBuf );


extern uint8_t CHRV3BulkOnlyCmd( uint8_t *DataBuf );
extern uint8_t MS_U20HOST_BulkOutHandle( uint8_t *pDatBuf, uint32_t *pSize );
extern uint8_t MS_U20HOST_BulkInHandle( uint8_t *pDatBuf, uint32_t *pSize );
extern uint8_t MS_U20HOST_CofDescrAnalyse( uint8_t *pbuf );
extern uint8_t Hot_Reset( uint8_t *pdata );



