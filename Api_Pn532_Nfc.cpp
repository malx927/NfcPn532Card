#include "Api_Pn532_Nfc.h"
#include "Driver_Uart1.h"
#include "Api_RTCBkpRegister.h"

uint8_t g_PN532_NFC_UID[4]; //�洢 UID
uint8_t g_PN532_SequenceLength=0;//�������кų���
uint8_t g_PN532_Sequence[10];//�������к�
uint8_t g_PN532_NFC_Type;//�������ͣ�04-S50,02-S70,44-UL��
const uint8_t g_PN532_KeyA_Default[6]={0xff,0xff,0xff,0xff,0xff,0xff};
const uint8_t g_PN532_KeyA[6]= {0xaa,0x55,0x7e,0xe7,0xaa,0x55};
const uint8_t g_PN532_KeyB[6]= {'1','3','5','3','6','9'};

//��USART1������ length���ȵ�����data
static void PN532_SendData(uint8_t *data,uint8_t length)
{
  USART1_Send_Data((uint8_t *)data,length);
}

static void PN532_CleanBuffer(void)
{
  USART1_ClearRecvBuff();
}

void nfc_DeviceInit(void)
{
	USART1_Periph_Init(115200);
}

//55 55 00 00 00 00 00 00 00 00 00 00 00 00 00 00 FF 03 FD D4 14 01 17 00  
int nfc_WakeUp(void)
{
  uint8_t data[24];
  uint8_t CheckCode=0; //����У����
  uint8_t temp=0;
	uint8_t index=0,count=0;
  
  data[0]=0x55;
  data[1]=0x55;
  data[2]=0x00;
  data[3]=0x00;
  data[4]=0x00;
	data[5]=0x00;
  data[6]=0x00;
  data[7]=0x00;
  data[8]=0x00;  
	data[9]=0x00;
  data[10]=0x00;
  data[11]=0x00;
  data[12]=0x00;
  data[13]=0x00;
  data[14]=0x00;
  data[15]=0x00;
  data[16]=0xFF;
  data[17]=0x03; //�� ����
  data[18]=0xFD; //�� ���� У��  0x100-data[3]
  data[19]=0xD4; //�����ʶ��
  data[20]=0x14; //�����ʶ��
  data[21]=0x01;
  data[22]=0x17; //���� У��   0x100-
  data[23]=0x00;
	PN532_CleanBuffer();
  PN532_SendData(data,24);//��USART1������ length���ȵ�����data
  //BSP_DelayMS(200); 
  //00 00 FF 00 FF 00 00 00 FF 02 FE D5 15 16 00 
	for(index=0;index<20;index++)	
	{
		BSP_DelayMS(10); 
		if(g_USART1_Recv_Count>=15)
		{
			temp=0;
			for(count=11;count<13;count++)
			{
				temp+=g_USART1_Recv_Buff[count];
			}
			CheckCode=0x100-temp;
			if(CheckCode==g_USART1_Recv_Buff[13])
			{
				return 0;
			}
			return -1;
		}
	}
	return -1;
}

//���� 106 kbps type A (ISO/IEC14443 Type A),
//00 00 FF 04 FC D4 4A 01 00 E1 00
int nfc_InListPassiveTarget(void)
{
  uint8_t data[11];
  uint8_t CheckCode=0; //����У����
  uint8_t temp=0;
	uint8_t index=0,count=0;
  
	data[0]=0x00;
  data[1]=0x00;
  data[2]=0xFF;
  data[3]=0x04; //�� ����
  data[4]=0xFC; //�� ���� У��  0x100-data[3]
  data[5]=0xD4; //�����ʶ��
  data[6]=0x4A; //�����ʶ��
  data[7]=0x01;
  data[8]=0x00;
  data[9]=0xE1; //���� У��   0x100-
  data[10]=0x00;
  PN532_CleanBuffer();
  PN532_SendData(data,11);//��USART1������ length���ȵ�����data
  //BSP_DelayMS(200); 
  for(count=0;count<20;count++)
	{	
		BSP_DelayMS(10);
		if(g_USART1_Recv_Count>=25)
		{
			temp=0;
			for(index=11;index<23;index++)
			{
				temp+=g_USART1_Recv_Buff[index];
			}
			CheckCode=0x100-temp;
			if(CheckCode==g_USART1_Recv_Buff[23])
			{
				if((g_USART1_Recv_Buff[15]&0xc0) == 0x00)
				{
					g_PN532_SequenceLength=4;//�������кų���=4���ֽ�
				}
				else if((g_USART1_Recv_Buff[15]&0xc0) == 0x40)
				{
					g_PN532_SequenceLength=7;//�������кų���=7���ֽ�
				}
				else if((g_USART1_Recv_Buff[15]&0xc0) == 0x80)
				{
					g_PN532_SequenceLength=10;//�������кų���=10���ֽ�
				}
				
				if(g_USART1_Recv_Buff[16]==0x04)
				{
					g_PN532_NFC_Type=0x04;//Mifare S50��
				}
				else if(g_USART1_Recv_Buff[16]==0x02)
				{
					g_PN532_NFC_Type=0x02;//Mifare S70��
				}
				else /*if(g_USART1_Recv_Buff[16]==0x44)*/
				{
					g_PN532_NFC_Type=0x44;//Mifare UltraLight��
					return -1;
				}
				
				g_PN532_NFC_UID[0]=g_USART1_Recv_Buff[19];
				g_PN532_NFC_UID[1]=g_USART1_Recv_Buff[20];
				g_PN532_NFC_UID[2]=g_USART1_Recv_Buff[21];
				g_PN532_NFC_UID[3]=g_USART1_Recv_Buff[22];             
				return 0;
			}
			return -1;
		}
	}
	memset(g_PN532_NFC_UID,0,4);
  return -1;
}

// ������Ȩ��nBlock=3 ��֤KeyA
//00 00 FF 0F F1 D4 40 01 60 03 FF FF FF FF FF FF UID1 UID2 UID3 UID4 2A 00
//00 00 FF 0F F1 D4 40 01 60 03 FF FF FF FF FF FF 94 8A 3B 0B 2A 00
int nfc_PsdVerifyKeyA(uint8_t *pKeyA_6Byte)
{
	uint8_t data[22];
  uint8_t temp=0; 
  uint8_t index=0,count=0;
  uint8_t CheckCode=0; //����У����

	data[0]=0x00;
  data[1]=0x00;
  data[2]=0xFF;
  data[3]=0x0F; //�� ����
  data[4]=0xF1; //�� ���� У��  0x100-data[3]
  data[5]=0xD4; //�����ʶ��
  data[6]=0x40; //�����ʶ��
  data[7]=0x01;
  data[8]=0x60;//��֤KEYA����֤KEYBΪ0x61
  data[9]=0x03; 
  data[10]=pKeyA_6Byte[0]; //KEY A ���� FF FF FF FF FF FF
  data[11]=pKeyA_6Byte[1];
  data[12]=pKeyA_6Byte[2];
  data[13]=pKeyA_6Byte[3];
  data[14]=pKeyA_6Byte[4];
  data[15]=pKeyA_6Byte[5];
  data[16]=g_PN532_NFC_UID[0];
  data[17]=g_PN532_NFC_UID[1];
  data[18]=g_PN532_NFC_UID[2];
  data[19]=g_PN532_NFC_UID[3];
  for(index=5;index<20;index++)
  {
		temp+=data[index];
  }
	data[20]=0x100-temp;   //���� У��   0x100-
  data[21]=0x00;
  PN532_CleanBuffer();  
  PN532_SendData(data,22);//��USART1������ length���ȵ�����data
  //BSP_DelayMS(200);
  for(count=0;count<20;count++)
	{
		BSP_DelayMS(10);
		if(g_USART1_Recv_Count>=0x010)
		{
			temp=0;
			for(index=11;index<14;index++)
			{
					temp+=g_USART1_Recv_Buff[index];
			}
			CheckCode=0x100-temp;
			if(CheckCode==g_USART1_Recv_Buff[14])
			{
				 if(g_USART1_Recv_Buff[13]==0x00)
				 {
					 return 0;
				 }
			}
			return -1;
		}
	}
	return -1;
}

//Ĭ�� �� 02����16���ֽ�
//00 00 FF 05 FB D4 40 01 30 02 B9 00
int nfc_read16byte(uint8_t nPageNumber,uint8_t *pBuff)
{
	uint8_t data[12];
  uint8_t temp=0; 
  uint8_t index,count=0;
  uint8_t CheckCode=0; //����У����

  data[0]=0x00;
  data[1]=0x00;
  data[2]=0xFF;
  data[3]=0x05; //�� ����
  data[4]=0xFB; //�� ���� У��  0x100-data[3]
  data[5]=0xD4; //�����ʶ��
  data[6]=0x40; //�����ʶ��
  data[7]=0x01;
  data[8]=0x30;
  data[9]=nPageNumber; //���ڶ����16�ֽ����� 
  data[10]=0xB9; //����У��
  data[11]=0x00;
	temp=0;
	for(index=5;index<10;index++)
	{
		temp+=data[index];
	}
	data[10]=0x100-temp;
	PN532_CleanBuffer();  
  PN532_SendData(data,12);//��USART1������ length���ȵ�����data
  //BSP_DelayMS(200);
	for(count=0;count<20;count++)
	{
		BSP_DelayMS(10);
		if(g_USART1_Recv_Count>=0x20)
		{
			temp=0;
			for(index=11;index<30;index++)
			{
				temp+=g_USART1_Recv_Buff[index];
			}
			CheckCode=0x100-temp;
			if(CheckCode==g_USART1_Recv_Buff[30] && g_USART1_Recv_Buff[13]==0x00)
			{
				for(index=0;index<16;index++)
				{
					pBuff[index]=g_USART1_Recv_Buff[14+index];
				}
				return 0;
			}
			return -1;
		}
	}
	return -1;
}



//Ĭ���� 02��д 16���ֽڵĵ�һ���ֽ�
//00 00 FF 15 EB D4 40 01 A0 02 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F D1 00
int nfc_write16byte(uint8_t nPageNumber,uint8_t *pBuff)
{
	uint8_t data[28];
  uint8_t temp=0;
  uint8_t index,count=0;
  uint8_t CheckCode=0;
    
  data[0]=0x00;
  data[1]=0x00;
  data[2]=0xFF;
  data[3]=0x15; //�� ����
  data[4]=0xEB; //�� ���� У��  0x100-data[3]
  data[5]=0xD4; //�����ʶ��
  data[6]=0x40; //�����ʶ��
  data[7]=0x01; //��д����6�ֽ� ����1�����ֲ�
  data[8]=0xA0; //д
  data[9]=nPageNumber; //д�ڶ����16�ֽ����� 
	for(index=0;index<16;index++)
	{
		data[10+index]=pBuff[index]; //�� 1 �ֽ� ����
	}
	temp=0;
	for(index=5;index<26;index++)
  {
      temp+=data[index];
  }
  data[26]=0x100-temp; //���� У����
  data[27]=0x00;
	PN532_CleanBuffer();  
  PN532_SendData(data,28);//��USART1������ length���ȵ�����data
  //BSP_DelayMS(200);
	for(count=0;count<20;count++)
	{
		BSP_DelayMS(10);
		//00 00 FF 00 FF 00 00 00 FF 03 FD D5 41 00 EA 00
		if(g_USART1_Recv_Count>=0x10)
		{
			temp=0;
			for(index=11;index<14;index++)
			{
				temp+=g_USART1_Recv_Buff[index];
			}
			CheckCode=0x100-temp;
			if(CheckCode==g_USART1_Recv_Buff[14])
			{
				 if(g_USART1_Recv_Buff[13]==0x00)
				 {
					 return 0;
				 }
			}
			return -1;
		}
	}
	return -1;
}

/*page 0:NULL
 *Page 1:����ʶ����(����ʶ��UUID���ۼӺ�4byte),������(RMB*100��UUID���ۼӺ�4byte),��վIDֵ(����ʶ��UUID���ۼӺ�4byte)���쳣��ʶ��(1�ֽ�)
 *Page 2:device SN(16byte)
 *Page 3:����Կ��
 *˵��:����ʶ4�ֽڣ���˾��ʶ�̶�Ϊ2�ֽڡ�YD����
                   �����͹̶�Ϊ1�ֽڣ�0x5a:��ͣ����0x50:��˾���翨��0x51:��˾���߿���0x52:��վ������0x53:��վ���翨��0x54:��վ���߿���0x55����׮��ͣ����
                   ����ǹ̶�Ϊ1�ֽڣ���������߼�������0xaa:����������磬0xa0:���ڳ�磬�����ʵ�δ����
       ���1����(RMB*100��UUID���ۼӺ�4byte)����������߼�����Ϊ���� �������������ֵ��4�ֽڵ����KEY��
       ���2����(RMB*100�볡վID���ۼӺ�4byte)����������߼�����Ϊ�����������������ֵ�ǿ���ʶ�������KEY�Ķ��μ���У��, 
       ��վIDֵ(4byte,��UUID���ۼӺ�),��������߼���������ֵ���ǽ��2����ֵ��Ҳ�ǳ�վ��IDֵ����˾���г�վ�̶�Ϊ0x00000000;
       device SN(16byte)�����߼���ʱ����ֵΪ���ڳ���δ������豸SN�����˵�׮��ƥ���׮SN�����ڹ�������Ϊ��Ч�ڽ�ֹ����                                        
 */

//4�ֽ�ʱ��ֵ��0�ֽ�*100+1�ֽ�=�꣬2�ֽ��£�3�ֽ��� 
int nfc_CreateCard_Manage(uint8_t *pStationID,uint8_t *StopDate)
{
	uint8_t index=0;
	uint8_t DataBuffer[16];
	
	uint32_t key=RTCTime_Time_t();

	nfc_DeviceInit();
	BSP_DelayMS(1000);
	
	if(nfc_WakeUp())
		return -1;
	if(nfc_InListPassiveTarget())
		return -1;
	if(nfc_PsdVerifyKeyA((uint8_t*)g_PN532_KeyA_Default))//g_PN532_KeyA_Default
		return -1;
	
	//��������
	memset(DataBuffer,0,16);
	//������
	DataBuffer[0]='Y';
	DataBuffer[1]='D';
	if(pStationID[0]==0x00 && pStationID[1]==0x00 && pStationID[2]==0x00 && pStationID[3]==0x00)
	{
		DataBuffer[2]=0x5a;//����
	}
	else
	{
		DataBuffer[2]=0x52;//����
	}
	DataBuffer[3]=0xaa;//���Գ��
	//��վID
	DataBuffer[12]=pStationID[0]+g_PN532_NFC_UID[0];//����
	DataBuffer[13]=pStationID[1]+g_PN532_NFC_UID[1];
	DataBuffer[14]=pStationID[2]+g_PN532_NFC_UID[2];
	DataBuffer[15]=pStationID[3]+g_PN532_NFC_UID[3];
	//�����Ͷ��μ���
	for(index=8;index<12;index++)
	{
		DataBuffer[index]=DataBuffer[index%4]+(uint8_t)(key>>((index%4)*8));//����
	}
	//��KEY
	for(index=4;index<8;index++)
	{
		DataBuffer[index]=(uint8_t)(key>>((index%4)*8))+g_PN532_NFC_UID[index%4];//����
	}
	//������һ�μ���
	for(index=0;index<4;index++)
	{
		DataBuffer[index]+=g_PN532_NFC_UID[index%4];//����
	}
	if(nfc_write16byte(1,DataBuffer))
		return -1;
	
	//��������
	memset(DataBuffer,0,16);
	for(index=0;index<4;index++)
	{
		DataBuffer[index]=StopDate[index]+g_PN532_NFC_UID[index%4];//����
	}
	if(nfc_write16byte(2,DataBuffer))
		return -1;
	
	//���Ŀ�ԭʼ���뵽������Կ
	for(index=0;index<6;index++)
	{
		DataBuffer[index]=g_PN532_KeyA[index];
		DataBuffer[10+index]=g_PN532_KeyB[index];
	}
	DataBuffer[6]=0xff;//��Կ������
	DataBuffer[7]=0x07;
	DataBuffer[8]=0x80;
	DataBuffer[9]=0x69;
	if(nfc_write16byte(3,DataBuffer))
		return -1;
	
	return 0;
}	

int nfc_CreateCard_Network(uint8_t *pStationID,char *pOutRfidNumbers)
{
	uint8_t index=0;
	uint8_t DataBuffer[16];
	
	uint32_t key=RTCTime_Time_t();

	nfc_DeviceInit();
	BSP_DelayMS(1000);
	
	if(nfc_WakeUp())
		return -1;
	if(nfc_InListPassiveTarget())
		return -1;
	if(nfc_PsdVerifyKeyA((uint8_t*)g_PN532_KeyA_Default))//g_PN532_KeyA_Default
		return -1;
	
	//��������
	memset(DataBuffer,0,16);
	//������
	DataBuffer[0]='Y';
	DataBuffer[1]='D';
	if(pStationID[0]==0x00 && pStationID[1]==0x00 && pStationID[2]==0x00 && pStationID[3]==0x00)
	{
		DataBuffer[2]=0x50;//����
	}
	else
	{
		DataBuffer[2]=0x53;//����
	}
	DataBuffer[3]=0xaa;//���Գ��
	//��վID
	DataBuffer[12]=pStationID[0]+g_PN532_NFC_UID[0];//����
	DataBuffer[13]=pStationID[1]+g_PN532_NFC_UID[1];
	DataBuffer[14]=pStationID[2]+g_PN532_NFC_UID[2];
	DataBuffer[15]=pStationID[3]+g_PN532_NFC_UID[3];
	//�����Ͷ��μ���
	for(index=8;index<12;index++)
	{
		DataBuffer[index]=DataBuffer[index%4]+(uint8_t)(key>>((index%4)*8));//����
	}
	//��KEY
	for(index=4;index<8;index++)
	{
		DataBuffer[index]=(uint8_t)(key>>((index%4)*8))+g_PN532_NFC_UID[index%4];//����
	}
	//������һ�μ���
	for(index=0;index<4;index++)
	{
		DataBuffer[index]+=g_PN532_NFC_UID[index%4];//����
	}
	if(nfc_write16byte(1,DataBuffer))
		return -1;
	
	//�������㣬����
	memset(DataBuffer,0,16);
	if(nfc_write16byte(2,DataBuffer))
		return -1;
	
	//���Ŀ�ԭʼ���뵽������Կ
	for(index=0;index<6;index++)
	{
		DataBuffer[index]=g_PN532_KeyA[index];
		DataBuffer[10+index]=g_PN532_KeyB[index];
	}
	DataBuffer[6]=0xff;//��Կ������
	DataBuffer[7]=0x07;
	DataBuffer[8]=0x80;
	DataBuffer[9]=0x69;
	if(nfc_write16byte(3,DataBuffer))
		return -1;
	
	snprintf(pOutRfidNumbers,16,"%02x%02x%02x%02x%02x%02x%02x%02x",g_PN532_NFC_UID[0],g_PN532_NFC_UID[1],g_PN532_NFC_UID[2],g_PN532_NFC_UID[3],pStationID[0],pStationID[1],pStationID[2],pStationID[3]);
	return 0;
}

int nfc_CreateCard_Offline(uint8_t *pStationID,char *pOutRfidNumbers,uint32_t Money)
{
	uint8_t index=0;
	uint8_t DataBuffer[16];
	
	nfc_DeviceInit();
	BSP_DelayMS(1000);
	
	if(nfc_WakeUp())
		return -1;
	if(nfc_InListPassiveTarget())
		return -1;
	if(nfc_PsdVerifyKeyA((uint8_t*)g_PN532_KeyA_Default))//g_PN532_KeyA_Default
		return -1;
	
	//��������
	memset(DataBuffer,0,16);
	//������
	DataBuffer[0]='Y';
	DataBuffer[1]='D';
	if(pStationID[0]==0x00 && pStationID[1]==0x00 && pStationID[2]==0x00 && pStationID[3]==0x00)
	{
		DataBuffer[2]=0x51;//����
	}
	else
	{
		DataBuffer[2]=0x54;//����
	}
	DataBuffer[3]=0xaa;//���Գ��
	//��վID
	DataBuffer[12]=pStationID[0]+g_PN532_NFC_UID[0];//����
	DataBuffer[13]=pStationID[1]+g_PN532_NFC_UID[1];
	DataBuffer[14]=pStationID[2]+g_PN532_NFC_UID[2];
	DataBuffer[15]=pStationID[3]+g_PN532_NFC_UID[3];
	//�����μ���
	for(index=8;index<12;index++)
	{
		DataBuffer[index]=(uint8_t)(Money>>((index%4)*8))+pStationID[index%4];//����
	}
	//���һ�μ���
	for(index=4;index<8;index++)
	{
		DataBuffer[index]=(uint8_t)(Money>>((index%4)*8))+g_PN532_NFC_UID[index%4];//����
	}
	//������һ�μ���
	for(index=0;index<4;index++)
	{
		DataBuffer[index]+=g_PN532_NFC_UID[index%4];//����
	}
	if(nfc_write16byte(1,DataBuffer))
		return -1;
	
	//�������㣬����
	memset(DataBuffer,0,16);
	if(nfc_write16byte(2,DataBuffer))
		return -1;
	
	//���Ŀ�ԭʼ���뵽������Կ
	for(index=0;index<6;index++)
	{
		DataBuffer[index]=g_PN532_KeyA[index];
		DataBuffer[10+index]=g_PN532_KeyB[index];
	}
	DataBuffer[6]=0xff;//��Կ������
	DataBuffer[7]=0x07;
	DataBuffer[8]=0x80;
	DataBuffer[9]=0x69;
	if(nfc_write16byte(3,DataBuffer))
		return -1;
	
	snprintf(pOutRfidNumbers,16,"%02x%02x%02x%02x%02x%02x%02x%02x",g_PN532_NFC_UID[0],g_PN532_NFC_UID[1],g_PN532_NFC_UID[2],g_PN532_NFC_UID[3],pStationID[0],pStationID[1],pStationID[2],pStationID[3]);
	
	return 0;
}


int nfc_CreateCard_SelfUsed(char *DeviceSN)
{
	uint8_t index=0;
	uint8_t DataBuffer[17];
	
	uint32_t key=RTCTime_Time_t();//time();

	nfc_DeviceInit();
	BSP_DelayMS(1000);
	
	if(nfc_WakeUp())
		return -1;
	if(nfc_InListPassiveTarget())
		return -1;
	if(nfc_PsdVerifyKeyA((uint8_t*)g_PN532_KeyA_Default))//g_PN532_KeyA_Default
		return -1;
	
	//��������
	memset(DataBuffer,0,17);
	//������
	DataBuffer[0]='Y';
	DataBuffer[1]='D';
	DataBuffer[2]=0x55;//����
	DataBuffer[3]=0xaa;//���Գ��
	//�����Ͷ��μ���
	for(index=8;index<12;index++)
	{
		DataBuffer[index]=DataBuffer[index%4]+(uint8_t)(key>>((index%4)*8));//����
	}
	//��KEY
	for(index=4;index<8;index++)
	{
		DataBuffer[index]=(uint8_t)(key>>((index%4)*8))+g_PN532_NFC_UID[index%4];//����
	}
	//������һ�μ���
	for(index=0;index<4;index++)
	{
		DataBuffer[index]+=g_PN532_NFC_UID[index%4];//����
	}
	if(nfc_write16byte(1,DataBuffer))
		return -1;
	
	//��������
	memset(DataBuffer,0,16);
	strncpy((char*)DataBuffer,DeviceSN,16);//����
	if(nfc_write16byte(2,DataBuffer))
		return -1;
	
	//���Ŀ�ԭʼ���뵽������Կ
	for(index=0;index<6;index++)
	{
		DataBuffer[index]=g_PN532_KeyA[index];
		DataBuffer[10+index]=g_PN532_KeyB[index];
	}
	DataBuffer[6]=0xff;//��Կ������
	DataBuffer[7]=0x07;
	DataBuffer[8]=0x80;
	DataBuffer[9]=0x69;
	if(nfc_write16byte(3,DataBuffer))
		return -1;
	
	return 0;
}

