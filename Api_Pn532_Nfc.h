#ifndef __NFC_H__
#define __NFC_H__
#include "main.h"

extern uint8_t g_PN532_NFC_UID[4]; //存储 UID
extern uint8_t g_PN532_NFC_UID[4]; //存储 UID
extern uint8_t g_PN532_SequenceLength;//卡的序列号长度
extern uint8_t g_PN532_Sequence[10];//卡的序列号
extern uint8_t g_PN532_NFC_Type;//卡的类型，04-S50,02-S70,44-UL卡
extern const uint8_t g_PN532_KeyA_Default[6];
extern const uint8_t g_PN532_KeyA[6];
extern const uint8_t g_PN532_KeyB[6];

void nfc_DeviceInit(void);
int nfc_WakeUp(void);//唤醒
int nfc_InListPassiveTarget(void);   //配置 106 kbps type A (ISO/IEC14443 Type A),
int nfc_PsdVerifyKeyA(uint8_t *pKeyA_6Byte);         //密码授权，验证KeyA
int nfc_PsdVerifyKeyB(uint8_t *pKeyA_6Byte);         //密码授权，验证KeyB
int nfc_write16byte(uint8_t nPageNumber,uint8_t *pBuff); //写，长度16字节
int nfc_read16byte(uint8_t nPageNumber,uint8_t *pBuff);  //读，长度16字节

//创建卡
int nfc_CreateCard_Manage(uint8_t *pStationID,uint8_t *StopDate);//管理卡-起停卡
int nfc_CreateCard_Network(uint8_t *pStationID,char *pOutRfidNumbers);//网络-后台卡
int nfc_CreateCard_Offline(uint8_t *pStationID,char *pOutRfidNumbers,uint32_t Money);//离线-计量卡
int nfc_CreateCard_SelfUsed(char *DeviceSN);//单桩-绑定卡

#endif /* __NFC_H__ */
