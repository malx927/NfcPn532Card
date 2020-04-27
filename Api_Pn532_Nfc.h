#ifndef __NFC_H__
#define __NFC_H__
#include "main.h"

extern uint8_t g_PN532_NFC_UID[4]; //�洢 UID
extern uint8_t g_PN532_NFC_UID[4]; //�洢 UID
extern uint8_t g_PN532_SequenceLength;//�������кų���
extern uint8_t g_PN532_Sequence[10];//�������к�
extern uint8_t g_PN532_NFC_Type;//�������ͣ�04-S50,02-S70,44-UL��
extern const uint8_t g_PN532_KeyA_Default[6];
extern const uint8_t g_PN532_KeyA[6];
extern const uint8_t g_PN532_KeyB[6];

void nfc_DeviceInit(void);
int nfc_WakeUp(void);//����
int nfc_InListPassiveTarget(void);   //���� 106 kbps type A (ISO/IEC14443 Type A),
int nfc_PsdVerifyKeyA(uint8_t *pKeyA_6Byte);         //������Ȩ����֤KeyA
int nfc_PsdVerifyKeyB(uint8_t *pKeyA_6Byte);         //������Ȩ����֤KeyB
int nfc_write16byte(uint8_t nPageNumber,uint8_t *pBuff); //д������16�ֽ�
int nfc_read16byte(uint8_t nPageNumber,uint8_t *pBuff);  //��������16�ֽ�

//������
int nfc_CreateCard_Manage(uint8_t *pStationID,uint8_t *StopDate);//����-��ͣ��
int nfc_CreateCard_Network(uint8_t *pStationID,char *pOutRfidNumbers);//����-��̨��
int nfc_CreateCard_Offline(uint8_t *pStationID,char *pOutRfidNumbers,uint32_t Money);//����-������
int nfc_CreateCard_SelfUsed(char *DeviceSN);//��׮-�󶨿�

#endif /* __NFC_H__ */
