#ifndef __HUB_H
#define __HUB_H
#define    HUB_ERR_SCUESS       0x02
#define    HUB_ERR_CONNECT      0x01
#define    HUB_ERR_DISCONNECT   0x00
#define    HUB_CS_NAK           0x2a
#define    DEVICE_ADDR          0x08                                        /* U30 device address*/

#define MAX_HUBNUMPORT 4

 typedef struct  __attribute__((packed)) _HUB_Endp_Info {
     uint8_t num;          // Endpoint number
     uint8_t endptype;     // Endpoint Type:1-IOS, 2-BULK, 3-INT
     uint8_t tog;
     uint8_t HighTransNum; // Number of transactions within a microframe(<=3) USB2.0
     uint16_t endp_size;   // Endpoint size
 } HUB_Endp_Info, *PHUB_Enpd_Info;


 typedef struct  __attribute__((packed)) _HUB_Port_Info {
     uint8_t status;          //0x01:Device connection
     uint8_t speed;           // 0-fullspeed, 1-highspeed, 2-lowspeed,3-sspeed
     uint8_t port_num;        // Endpoint number
     uint8_t addr;            //HUB The following device address
     uint8_t devicetype;      //Device type
     uint8_t endpnum;         //Number of endpoints
     uint8_t portpchangefield;//Port state change
     HUB_Endp_Info portEndp[8];
 } HUB_Port_Info, *PHUB_Port_Info;

 typedef struct  __attribute__((packed)) _USB_HUB_Info {
     uint8_t status;      // 0-disconnect  1-connect  2-config
     uint8_t speed;       // 0-fullspeed, 1-highspeed, 2-lowspeed,3-sspeed
     uint8_t devaddr;     //hub address
     uint8_t endpsize;    //HUB Endpoint size
     uint8_t numofport;   //hub Number of ports
     uint8_t device_type; //Device type
     uint8_t time_out;
     HUB_Endp_Info rootEndp[2];
     HUB_Port_Info portD[MAX_HUBNUMPORT];
 } USB_HUB_Info, *PUSB_HUB_Info;

 typedef struct  __attribute__((packed)) _USB_HUB_SaveData {

     uint8_t Depth;
     uint8_t UpLevelPort;
     uint8_t CurrentPort;
     USB_HUB_Info HUB_Info;

 } USB_HUB_SaveData;

 //HUB structure of nodes in a data linked list
 typedef struct __attribute__((packed)) _Link_HUBSaveData
 {
     USB_HUB_SaveData HUB_SaveData;
     struct _Link_HUBSaveData* next;
 }Link_HUBSaveData;

 extern Link_HUBSaveData* Hub_LinkHead;
 Link_HUBSaveData* InitHubLink(void);

 void AssignHubData(USB_HUB_SaveData *hubdata ,uint8_t depth,uint8_t uplevelport,uint8_t currentport,USB_HUB_Info hub_info);
 uint8_t SearchHubData(Link_HUBSaveData* p, USB_HUB_SaveData *HUB_SaveData);
 uint8_t InsertHubData(Link_HUBSaveData* p, USB_HUB_SaveData HUB_SaveData);
 uint8_t DeleteHubData(Link_HUBSaveData* p, USB_HUB_SaveData HUB_SaveData);
 uint8_t ModifyHubData(Link_HUBSaveData* p, USB_HUB_SaveData oldhubdata, USB_HUB_SaveData newhubdata);
 uint8_t  Hublink_judgingstructures( USB_HUB_SaveData hubdata );
 void Hublink_finesubstructures( USB_HUB_SaveData hubdata );
 extern uint8_t AddressNum[127];
 uint8_t USB_SetAddressNumber(void);
 uint8_t USB_DelAddressNumber(uint8_t addr);

 extern __attribute__ ((aligned(16))) uint8_t pNTFS_BUF[512] __attribute__((section(".DMADATA")));


#define     PORT_DISCONNECT         0x00        //The device is disconnected or not connected
#define     PORT_CONNECTION         0x01        //Device connection
#define     PORT_INIT               0x02        //Device connection, enumerated
#define     PORT_INIT_OK            0x03        //Device connection, enumerated, class command initialization completed

#define     PORT_RESET                  4         //Reset the device under the port
#define     PORT_POWER                  8         //HUB power on
#define     C_PORT_CONNECTION           16        //Port change status
#define     C_PORT_ENABLE               17        //device enable
#define     C_PORT_SUSPEND              18        //Device Pending
#define     C_PORT_OVER_CURRENT         19        //Overcurrent state clearing
#define     C_PORT_RESET                20        //Port change status
#define     C_BH_PORT_RESET             29        //Port change status
#define     C_PORT_LINK_STATE           25        //Port change status
#define     C_PORT_CONFIG_ERROR         26        //Port change status
#define     PORT_REMOTE_WAKE_MASK       27

/*HUB The following device speed types*/
#define     PORT_FULL_SPEED     0X00           //full speed
#define     PORT_HIGH_SPEED     0X01           //high speed
#define     PORT_LOW_SPEED      0X02           //low speed
#define     PORT_SS_SPEED       0X03           //super speed

typedef enum
{
    SS_HUBNUM = 5,
    HS_HUBNUM = 7,
}HUBNUM;



extern USB_HUB_Info ss_hub_info[SS_HUBNUM];
extern USB_HUB_Info hs_hub_info[HS_HUBNUM];
extern uint8_t U30HOST_Hub_Connect_Process( uint8_t depth );
extern void U30HOST_Hub_Device_Process( uint8_t depth,uint8_t port );
extern uint8_t U20HOST_Hub_Connect_Process( uint8_t depth );
extern uint8_t U20USBHostTransact( uint8_t endp_pid, uint8_t tog, uint32_t timeout );


#endif
