/********************************** (C) COPYRIGHT *******************************
* File Name          : fat_process.h
* Author             : WCH
* Version            : V1.1
* Date               : 2023/02/16
*
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

#ifndef UDISK_LIB_FAT_PROCESS_H_
#define UDISK_LIB_FAT_PROCESS_H_

#ifdef __cplusplus
extern "C" {
#endif

#define     MAX_LEN_MCU         32

typedef struct              //Data bit alignment
{
    uint8_t   Name[ 13 ];             // Short file name 8+3 format (converted)
    uint8_t   attrib;                 // File or folder 0--File£¬1--folder
    uint32_t  FileLen;                // File length, folder is 0
    uint16_t  UpdateDate;             // modification date
    uint16_t  UpdateTime;             // Modification time
    uint16_t  CreateDate;             // Creation data
    uint16_t  CreateTime;             // Creation time
    uint16_t  LongNameLen;            // The valid length of long file name is equal to RecCmd.len - 25
} disk_2;


//#pragma pack(1)
typedef  union
    {
    unsigned char   buf[ MAX_LEN_MCU];  // save data
    disk_2  FileDef;
} DiskData_1;
DiskData_1  DiskData;

extern  uint8_t  Fat_Init( void );
extern  unsigned char Enum_Dir( void );
extern  unsigned char Manual_Send_Dir( void );
extern  uint8_t path_name[255],back_path_name[255];

#ifdef __cplusplus
}
#endif

#endif /* UDISK_LIB_FAT_PROCESS_H_ */
