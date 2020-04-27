#include "main.h"
#include "Charger.h"
#include "Api_IO.h"
#include "Driver_Uart1.h"
#include "AppTaskThread.h"
#include "Api_Command.h"
#include "Api_Pn532_Nfc.h"

uint8_t g_PN532_NfcScanFlag[CHARGER_GUN_NUMBER];//IC卡扫描标记
uint8_t g_PN532_NfcScanResult[CHARGER_GUN_NUMBER][3];//IC卡扫描结果
uint8_t g_PN532_NfcScanNumbers[CHARGER_GUN_NUMBER][17];
uint8_t g_PN532_NfcScanPassword[CHARGER_GUN_NUMBER][9];

void NFC_ScanCard(uint8_t channel)
{
	g_PN532_NfcScanFlag[channel]=1;
	memset(g_PN532_NfcScanResult[channel],0,3);
	memset(g_PN532_NfcScanNumbers[channel],0,17);
	memset(g_PN532_NfcScanPassword[channel],0,9);
}

void AppTaskNfcFuncion(void *arg)
{
	static uint8_t m_Channel=0;
  uint8_t NfcBuffer[17]={0};
	uint8_t StationID[4]={0};
	//uint8_t index=0;
	
	nfc_DeviceInit();
	BSP_DelayMS(1000);
	
	//创建管理卡，截止日期到2020年2月27日
	StationID[0]=0x00;
	StationID[1]=0x00;
	StationID[2]=0x00;
	StationID[3]=0x00;
	NfcBuffer[0]=20;
	NfcBuffer[1]=20;
	NfcBuffer[2]=02;
	NfcBuffer[3]=27;
	//nfc_CreateCard_Manage(StationID,NfcBuffer);
	//nfc_CreateCard_Network(StationID,(char*)NfcBuffer);
	//nfc_CreateCard_Offline(StationID,(char*)NfcBuffer,5123456);
	//strncpy((char*)NfcBuffer,DEVICE_CONFIG_DEFAULT_SN,16);
	//nfc_CreateCard_SelfUsed((char*)NfcBuffer);
	
	while(1)
	{
		BSP_DelayMS(3000);

		#if(CHARGER_GUN_NUMBER>=2)
		if(g_ChargerState.NfcScanFlag[0] && !g_ChargerState.NfcScanFlag[1])
		{
			m_Channel=0;
		}
		else if(g_ChargerState.NfcScanFlag[1] && !g_ChargerState.NfcScanFlag[0])
		{
			m_Channel=1;
		}
		else
		{
			continue;
		}
		#else
		m_Channel=0;
		#endif
		
		if(nfc_WakeUp())
			continue ;
		if(nfc_InListPassiveTarget())
			continue ;
		if(nfc_PsdVerifyKeyA((uint8_t*)g_PN532_KeyA))
		{
			g_PN532_NfcScanFlag[m_Channel]=0;
			g_PN532_NfcScanResult[m_Channel][0]=0;
			API_IO_NFC_Error();
			continue;
		}
		if(nfc_read16byte(1,NfcBuffer))
		{
			g_PN532_NfcScanFlag[m_Channel]=0;
			g_PN532_NfcScanResult[m_Channel][0]=0;
			API_IO_NFC_Error();
			continue;
		}
				
		if((uint8_t)(NfcBuffer[0]-g_PN532_NFC_UID[0])!='Y' || (uint8_t)(NfcBuffer[1]-g_PN532_NFC_UID[1])!='D')
		{
			g_PN532_NfcScanFlag[m_Channel]=0;
			g_PN532_NfcScanResult[m_Channel][0]=0;
			API_IO_NFC_Error();
			continue;
		}
		
		//管理卡（起停卡)
		if((NfcBuffer[2]-g_PN532_NFC_UID[2])==0x5a || (NfcBuffer[2]-g_PN532_NFC_UID[2])==0x52)
		{
			//判断KEY
			if(((uint8_t)(NfcBuffer[8]-(NfcBuffer[4]-g_PN532_NFC_UID[0]))!=(uint8_t)(NfcBuffer[0]-g_PN532_NFC_UID[0])) ||
				 ((uint8_t)(NfcBuffer[9]-(NfcBuffer[5]-g_PN532_NFC_UID[1]))!=(uint8_t)(NfcBuffer[1]-g_PN532_NFC_UID[1])) || 
			   ((uint8_t)(NfcBuffer[10]-(NfcBuffer[6]-g_PN532_NFC_UID[2]))!=(uint8_t)(NfcBuffer[2]-g_PN532_NFC_UID[2])))
			{
				g_PN532_NfcScanFlag[m_Channel]=0;
				g_PN532_NfcScanResult[m_Channel][0]=0;
				API_IO_NFC_Error();
				continue;
			}
			//判断站点
			if((g_Charger.StationID[0]!=(NfcBuffer[12]-g_PN532_NFC_UID[0]))||(g_Charger.StationID[1]!=(NfcBuffer[13]-g_PN532_NFC_UID[1]))
				||(g_Charger.StationID[2]!=(NfcBuffer[14]-g_PN532_NFC_UID[2]))||(g_Charger.StationID[3]!=(NfcBuffer[15]-g_PN532_NFC_UID[3])))
			{
				g_PN532_NfcScanFlag[m_Channel]=0;
				g_PN532_NfcScanResult[m_Channel][0]=0;
				API_IO_NFC_Error();
				continue;
			}
			//判断年月日
			
			//识别正确
			API_IO_NFC_OK();
			//BSP_DelayMS(500);
			g_PN532_NfcScanFlag[m_Channel]=1;
			g_PN532_NfcScanResult[m_Channel][0]=1;
			g_PN532_NfcScanResult[m_Channel][1]=NfcBuffer[2]-g_PN532_NFC_UID[2];
			g_PN532_NfcScanResult[m_Channel][2]=NfcBuffer[3]-g_PN532_NFC_UID[3];
				
			if(g_ChargerState.WorkState[m_Channel]!=CHARGER_WORK_STATE_CHARGING)
			{
				g_ChargerState.WorkState[m_Channel]=CHARGER_WORK_STATE_CHARGING;
				g_ChargerState.WorkStateCode[m_Channel]=CHARGER_STATE_ERROR_NONE;
				Charger_PrintfLog(LOG_SAVE,"GUN%d Setup charging by rfid of manager.\n",m_Channel);
			}
			else
			{
				g_ChargerState.WorkState[m_Channel]=CHARGER_WORK_STATE_OVER;
				g_ChargerState.WorkStateCode[m_Channel]=CHARGER_STATE_CHARGING_OVER;
				Charger_PrintfLog(LOG_SAVE,"GUN%d Stop charging by rfid of manager.\n",m_Channel);
			}
			continue ;
		}
		
		//网络卡
		if((NfcBuffer[2]-g_PN532_NFC_UID[2])==0x50 || (NfcBuffer[2]-g_PN532_NFC_UID[2])==0x53)
		{
			//判断KEY
			if(((uint8_t)(NfcBuffer[8]-(NfcBuffer[4]-g_PN532_NFC_UID[0]))!=(uint8_t)(NfcBuffer[0]-g_PN532_NFC_UID[0])) ||
				 ((uint8_t)(NfcBuffer[9]-(NfcBuffer[5]-g_PN532_NFC_UID[1]))!=(uint8_t)(NfcBuffer[1]-g_PN532_NFC_UID[1])) || 
			   ((uint8_t)(NfcBuffer[10]-(NfcBuffer[6]-g_PN532_NFC_UID[2]))!=(uint8_t)(NfcBuffer[2]-g_PN532_NFC_UID[2])))
			{
				g_PN532_NfcScanFlag[m_Channel]=0;
				g_PN532_NfcScanResult[m_Channel][0]=0;
				API_IO_NFC_Error();
				continue;
			}
			//判断站点
			if((g_Charger.StationID[0]!=(NfcBuffer[12]-g_PN532_NFC_UID[0]))||(g_Charger.StationID[1]!=(NfcBuffer[13]-g_PN532_NFC_UID[1]))
				||(g_Charger.StationID[2]!=(NfcBuffer[14]-g_PN532_NFC_UID[2]))||(g_Charger.StationID[3]!=(NfcBuffer[15]-g_PN532_NFC_UID[3])))
			{
				g_PN532_NfcScanFlag[m_Channel]=0;
				g_PN532_NfcScanResult[m_Channel][0]=0;
				API_IO_NFC_Error();
				continue;
			}
			//识别正确
			API_IO_NFC_OK();
			//BSP_DelayMS(500);
			g_PN532_NfcScanFlag[m_Channel]=1;
			g_PN532_NfcScanResult[m_Channel][0]=1;
			g_PN532_NfcScanResult[m_Channel][1]=NfcBuffer[2]-g_PN532_NFC_UID[2];
			g_PN532_NfcScanResult[m_Channel][2]=NfcBuffer[3]-g_PN532_NFC_UID[3];
			
			if(g_ChargerState.WorkState[m_Channel]!=CHARGER_WORK_STATE_CHARGING)
			{
				strncpy((char*)g_ChargerRecord[m_Channel].UserOrRfidID,"12345678",16);
				//snprintf((char*)g_ChargerRecord[m_Channel].UserID,16,"%02x%02x%02x%02x",g_PN532_NFC_UID[0],g_PN532_NFC_UID[1],g_PN532_NFC_UID[2],g_PN532_NFC_UID[3]);
				strncpy((char*)g_ChargerRecord[m_Channel].UserOrRfidPassword,"123456",8);
				
				Charger_PrintfLog(LOG_SAVE,"GUN%d Send setup charging by online rfid.\n",m_Channel);
				Api_Command_RequestCharging(m_Channel,0x01,(char*)&g_ChargerRecord[m_Channel].UserOrRfidID,(char*)g_ChargerRecord[m_Channel].UserOrRfidPassword);
			}
			else if(g_ChargerState.WorkState[m_Channel]==CHARGER_WORK_STATE_CHARGING)
			{
				//判断IC卡是否为相同卡
				
				Charger_PrintfLog(LOG_SAVE,"GUN%d Send stop charging by online rfid.\n",m_Channel);
				Api_Command_RequestCharging(m_Channel,0x02,(char*)&g_ChargerRecord[m_Channel].UserOrRfidID,(char*)g_ChargerRecord[m_Channel].UserOrRfidPassword);
			}
			continue ;
		}
		
		//离线计量卡
		if((NfcBuffer[2]-g_PN532_NFC_UID[2])==0x51 || (NfcBuffer[2]-g_PN532_NFC_UID[2])==0x54)
		{
			//判断金额是否相符
			if(((uint8_t)(NfcBuffer[8]-(NfcBuffer[12]-g_PN532_NFC_UID[0]))!=(uint8_t)(NfcBuffer[4]-g_PN532_NFC_UID[0])) ||
				 ((uint8_t)(NfcBuffer[9]-(NfcBuffer[13]-g_PN532_NFC_UID[1]))!=(uint8_t)(NfcBuffer[5]-g_PN532_NFC_UID[1])) || 
			   ((uint8_t)(NfcBuffer[10]-(NfcBuffer[14]-g_PN532_NFC_UID[2]))!=(uint8_t)(NfcBuffer[6]-g_PN532_NFC_UID[2]))|| 
			   ((uint8_t)(NfcBuffer[11]-(NfcBuffer[15]-g_PN532_NFC_UID[3]))!=(uint8_t)(NfcBuffer[7]-g_PN532_NFC_UID[3]))) 
			{
				g_PN532_NfcScanFlag[m_Channel]=0;
				g_PN532_NfcScanResult[m_Channel][0]=0;
				API_IO_NFC_Error();
				continue;
			}
			//判断站点是否为本桩站点
			if((g_Charger.StationID[0]!=(NfcBuffer[12]-g_PN532_NFC_UID[0]))||(g_Charger.StationID[1]!=(NfcBuffer[13]-g_PN532_NFC_UID[1]))
				||(g_Charger.StationID[2]!=(NfcBuffer[14]-g_PN532_NFC_UID[2]))||(g_Charger.StationID[3]!=(NfcBuffer[15]-g_PN532_NFC_UID[3])))
			{
				g_PN532_NfcScanFlag[m_Channel]=0;
				g_PN532_NfcScanResult[m_Channel][0]=0;
				API_IO_NFC_Error();
				continue;
			}
			
			//判断余额是否充足
			g_ChargerRecord[m_Channel].BillBalance=((uint8_t)(NfcBuffer[4]-g_PN532_NFC_UID[0])>>0) |((uint8_t)(NfcBuffer[5]-g_PN532_NFC_UID[1])<<8) | ((uint8_t)(NfcBuffer[6]-g_PN532_NFC_UID[2])<<16) | ((uint8_t)(NfcBuffer[7]-g_PN532_NFC_UID[3])<<24) ;
			if(g_ChargerRecord[m_Channel].BillBalance<=50)
			{
				g_PN532_NfcScanFlag[m_Channel]=0;
				g_PN532_NfcScanResult[m_Channel][0]=0;
				API_IO_NFC_Error();
				continue;
			}
			
			//判断卡是否有异常
			if((NfcBuffer[3]-g_PN532_NFC_UID[3])!=0xaa)
			{
				//查找充电记录并扣款
				g_PN532_NfcScanFlag[m_Channel]=0;
				g_PN532_NfcScanResult[m_Channel][0]=0;
				API_IO_NFC_Error();
				continue ;
			}
			
			//识别正确
			API_IO_NFC_OK();
			//BSP_DelayMS(500);
			g_PN532_NfcScanFlag[m_Channel]=1;
			g_PN532_NfcScanResult[m_Channel][0]=1;
			g_PN532_NfcScanResult[m_Channel][1]=NfcBuffer[2]-g_PN532_NFC_UID[2];
			g_PN532_NfcScanResult[m_Channel][2]=NfcBuffer[3]-g_PN532_NFC_UID[3];
						
			if(g_ChargerState.WorkState[m_Channel]!=CHARGER_WORK_STATE_CHARGING)
			{
				//修改可充电到正在充电中
				g_ChargerState.WorkState[m_Channel]=CHARGER_WORK_STATE_CHARGING;
				g_ChargerState.WorkStateCode[m_Channel]=CHARGER_STATE_ERROR_NONE;
				Charger_PrintfLog(LOG_SAVE,"GUN%d Send setup charging by offline rfid.\n",m_Channel);
			}
			else if(g_ChargerState.WorkState[m_Channel]==CHARGER_WORK_STATE_CHARGING)
			{
				//修改充电中到可充电
				g_ChargerState.WorkState[m_Channel]=CHARGER_WORK_STATE_OVER;
				g_ChargerState.WorkStateCode[m_Channel]=CHARGER_STATE_CHARGING_OVER;
				Charger_PrintfLog(LOG_SAVE,"GUN%d Send stop charging by offline rfid.\n",m_Channel);
			}
			continue ;
		}
		
		//单桩绑定卡
		if((NfcBuffer[2]-g_PN532_NFC_UID[2])==0x55)
		{
			//判断KEY
			if(((uint8_t)(NfcBuffer[8]-(NfcBuffer[4]-g_PN532_NFC_UID[0]))!=(uint8_t)(NfcBuffer[0]-g_PN532_NFC_UID[0])) ||
				 ((uint8_t)(NfcBuffer[9]-(NfcBuffer[5]-g_PN532_NFC_UID[1]))!=(uint8_t)(NfcBuffer[1]-g_PN532_NFC_UID[1])) || 
			   ((uint8_t)(NfcBuffer[10]-(NfcBuffer[6]-g_PN532_NFC_UID[2]))!=(uint8_t)(NfcBuffer[2]-g_PN532_NFC_UID[2])))
			{
				g_PN532_NfcScanFlag[m_Channel]=0;
				g_PN532_NfcScanResult[m_Channel][0]=0;
				API_IO_NFC_Error();
				continue;
			}
			if(nfc_read16byte(2,NfcBuffer))
			{
				g_PN532_NfcScanFlag[m_Channel]=0;
				g_PN532_NfcScanResult[m_Channel][0]=0;
				API_IO_NFC_Error();
				continue;
			}
			NfcBuffer[16]='\0';
			if(strncmp((char*)NfcBuffer,g_Charger.DeviceSN,16))
			{
				g_PN532_NfcScanFlag[m_Channel]=0;
				g_PN532_NfcScanResult[m_Channel][0]=0;
				API_IO_NFC_Error();
				continue;
			}
			
			//识别正确
			API_IO_NFC_OK();
			//BSP_DelayMS(500);
			g_PN532_NfcScanFlag[m_Channel]=1;
			g_PN532_NfcScanResult[m_Channel][0]=1;
			g_PN532_NfcScanResult[m_Channel][1]=NfcBuffer[2]-g_PN532_NFC_UID[2];
			g_PN532_NfcScanResult[m_Channel][2]=NfcBuffer[3]-g_PN532_NFC_UID[3];
			
			if(g_ChargerState.WorkState[m_Channel]!=CHARGER_WORK_STATE_CHARGING)
			{
				//修改可充电到正在充电中
				g_ChargerState.WorkState[m_Channel]=CHARGER_WORK_STATE_CHARGING;
				g_ChargerState.WorkStateCode[m_Channel]=CHARGER_STATE_ERROR_NONE;
				Charger_PrintfLog(LOG_SAVE,"GUN%d Send setup charging by self rfid.\n",m_Channel);
			}
			else if(g_ChargerState.WorkState[m_Channel]==CHARGER_WORK_STATE_CHARGING)
			{
				//修改充电中到可充电
				g_ChargerState.WorkState[m_Channel]=CHARGER_WORK_STATE_OVER;
				g_ChargerState.WorkStateCode[m_Channel]=CHARGER_STATE_CHARGING_OVER;
				Charger_PrintfLog(LOG_SAVE,"GUN%d Send stop charging by self rfid.\n",m_Channel);
			}
			continue ;
		}
		
		//无效卡
		g_PN532_NfcScanFlag[m_Channel]=0;
		g_PN532_NfcScanResult[m_Channel][0]=0;
		API_IO_NFC_Error();
	}
}
