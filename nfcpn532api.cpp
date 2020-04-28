#include "nfcpn532api.h"

#include <QDateTime>
#include <QDebug>

uint8_t g_PN532_NFC_UID[4]; //存储 UID
uint8_t g_PN532_SequenceLength=0;//卡的序列号长度
uint8_t g_PN532_Sequence[10];//卡的序列号
uint8_t g_PN532_NFC_Type;//卡的类型，04-S50,02-S70,44-UL卡
const uint8_t g_PN532_KeyA_Default[6]={0xff,0xff,0xff,0xff,0xff,0xff};
const uint8_t g_PN532_KeyA[6]= {0xaa,0x55,0x7e,0xe7,0xaa,0x55};
const uint8_t g_PN532_KeyB[6]= {'1','3','5','3','6','9'};


NfcPn532Api::NfcPn532Api(QObject *parent) : QObject(parent)
{
    serial = new QSerialPort(this);
    is_wakeup = false;
}

//往USART1，发送 length长度的数据data
void NfcPn532Api::PN532_SendData(const char *data, qint64 length)
{
    serial->write(data, length);
//    qDebug() << "PN532_SendData:" << nums;
}

void NfcPn532Api::PN532_CleanBuffer(void)
{
    serial->clear();
}

bool NfcPn532Api::nfc_DeviceInit(QString& portName)
{
    qDebug() << "nfc_DeviceInit" << portName;
    if(serial->isOpen())
    {
        serial->close();
    }
    mPortName = portName;

    serial->setPortName(portName);
    //打开串口
    bool ret = serial->open(QIODevice::ReadWrite);
    //设置波特率
    serial->setBaudRate(QSerialPort::Baud115200);
    //设置数据为
    serial->setDataBits(QSerialPort::Data8);
    //设置校验位
    serial->setParity(QSerialPort::NoParity);
    //设置停止为
    serial->setStopBits(QSerialPort::OneStop);

    return ret;
}

//55 55 00 00 00 00 00 00 00 00 00 00 00 00 00 00 FF 03 FD D4 14 01 17 00
int NfcPn532Api::nfc_WakeUp(void)
{
    uint8_t data[24];
    uint8_t CheckCode=0; //数据校验码
    uint8_t temp=0;
    uint8_t count=0;

    if(is_wakeup) return 0;

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
    data[17]=0x03; //包 长度
    data[18]=0xFD; //包 长度 校验  0x100-data[3]
    data[19]=0xD4; //命令标识码
    data[20]=0x14; //命令标识码
    data[21]=0x01;
    data[22]=0x17; //数据 校验   0x100-
    data[23]=0x00;

    PN532_CleanBuffer();
    PN532_SendData((const char*)data,24);//往串口，发送 length长度的数据data

    QByteArray arrData = readData();
    qDebug() << "nfc_WakeUp"  << arrData;
    //00 00 FF 00 FF 00 00 00 FF 02 FE D5 15 16 00
    if(arrData.count() >= 15){
        temp=0;
        for(count=11;count<13;count++)
        {
            temp += (uint8_t)(arrData.at(count));
        }

        CheckCode= 0x100 - temp;

        uint8_t u_check = (uint8_t)(arrData.at(13));

        if(CheckCode==u_check)
        {
            is_wakeup = true;
            return 0;
        }
        return -1;
    }

    return -1;
}

//配置 106 kbps type A (ISO/IEC14443 Type A),
//00 00 FF 04 FC D4 4A 01 00 E1 00
int NfcPn532Api::nfc_InListPassiveTarget(void)
{
    uint8_t data[11];
    uint8_t CheckCode=0; //数据校验码
    uint8_t temp=0;
    uint8_t index=0;

    data[0]=0x00;
    data[1]=0x00;
    data[2]=0xFF;
    data[3]=0x04; //包 长度
    data[4]=0xFC; //包 长度 校验  0x100-data[3]
    data[5]=0xD4; //命令标识码
    data[6]=0x4A; //命令标识码
    data[7]=0x01;
    data[8]=0x00;
    data[9]=0xE1; //数据 校验   0x100-
    data[10]=0x00;

    PN532_CleanBuffer();
    PN532_SendData((const char*)data, 11);

    QByteArray arrData = readData();

    qDebug() << "nfc_InListPassiveTarget:" << arrData.toHex();
    QByteArray arrData1 = readData();
    qDebug() << "nfc_InListPassiveTarget:" << arrData1.toHex();
    arrData.append(arrData1);
    qDebug() << "nfc_InListPassiveTarget:" << arrData1.count();
    if(arrData.count()>=25)
    {
        temp=0;
        for(index=11;index<23;index++)
        {
            temp+=(uint8_t)(arrData.at(index));
        }

        CheckCode=0x100 - temp;

        uint8_t u_check = (uint8_t)(arrData.at(23));

        if(CheckCode==u_check)
        {
            if((arrData.at(15)&0xc0) == 0x00)
            {
                g_PN532_SequenceLength=4;//卡的序列号长度=4个字节
            }
            else if((arrData.at(15)&0xc0) == 0x40)
            {
                g_PN532_SequenceLength=7;//卡的序列号长度=7个字节
            }
            else if((arrData.at(15)&0xc0) == 0x80)
            {
                g_PN532_SequenceLength=10;//卡的序列号长度=10个字节
            }

            if(arrData.at(16)==0x04)
            {
                g_PN532_NFC_Type=0x04;//Mifare S50卡
            }
            else if(arrData.at(16)==0x02)
            {
                g_PN532_NFC_Type=0x02;//Mifare S70卡
            }
            else
            {
                g_PN532_NFC_Type=0x44;//Mifare UltraLight卡
                return -1;
            }

            g_PN532_NFC_UID[0]  = (uint8_t)arrData.at(19);
            g_PN532_NFC_UID[1]  = (uint8_t)arrData.at(20);
            g_PN532_NFC_UID[2]  = (uint8_t)arrData.at(21);
            g_PN532_NFC_UID[3]  = (uint8_t)arrData.at(22);
            return 0;
        }
    }

    memset(g_PN532_NFC_UID,0,4);
    return -1;
}

// 密码授权，nBlock=3 验证KeyA
//00 00 FF 0F F1 D4 40 01 60 03 FF FF FF FF FF FF UID1 UID2 UID3 UID4 2A 00
//00 00 FF 0F F1 D4 40 01 60 03 FF FF FF FF FF FF 94 8A 3B 0B 2A 00
int NfcPn532Api::nfc_PsdVerifyKeyA(uint8_t *pKeyA_6Byte)
{
    uint8_t data[22];
    uint8_t temp=0;
    uint8_t index=0;
    uint8_t CheckCode=0; //数据校验码

    data[0]=0x00;
    data[1]=0x00;
    data[2]=0xFF;
    data[3]=0x0F; //包 长度
    data[4]=0xF1; //包 长度 校验  0x100-data[3]
    data[5]=0xD4; //命令标识码
    data[6]=0x40; //命令标识码
    data[7]=0x01;
    data[8]=0x60;//验证KEYA，验证KEYB为0x61
    data[9]=0x03;
    data[10]=pKeyA_6Byte[0]; //KEY A 密码 FF FF FF FF FF FF
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
    data[20]=0x100 - temp;   //数据 校验   0x100-
    data[21]=0x00;

    PN532_CleanBuffer();
    PN532_SendData((const char*)data, 22);

    QByteArray arrData = readData();
    qDebug() << "nfc_PsdVerifyKeyA:"<< arrData.toHex() << arrData.count();
    QByteArray arrData1 = readData();
    qDebug() << "nfc_PsdVerifyKeyA:"<< arrData1.toHex() << arrData1.count();
    if(arrData1.length() > 0)
    {
        arrData.append(arrData1);
    }
    if(arrData.count() >= 0x010)
    {
        temp=0;
        for(index=11;index<14;index++)
        {
            temp+=(uint8_t)(arrData.at(index));
        }

        CheckCode=0x100 - temp;

        uint8_t u_check = (uint8_t)arrData.at(14);

        qDebug() << CheckCode << u_check;
        if(CheckCode == u_check)
        {
            if(arrData.at(13)==0x00)
            {
                qDebug() << "Leave nfc_PsdVerifyKeyA 0";
                return 0;
            }
        }
        return -1;
    }
    qDebug() << "Leave nfc_PsdVerifyKeyA -1";
    return -1;
}

//默认 读 02区的16个字节
//00 00 FF 05 FB D4 40 01 30 02 B9 00
int NfcPn532Api::nfc_read16byte(uint8_t nPageNumber,uint8_t *pBuff)
{
    uint8_t data[12];
    uint8_t temp=0;
    uint8_t index;
    uint8_t CheckCode=0; //数据校验码

    data[0]=0x00;
    data[1]=0x00;
    data[2]=0xFF;
    data[3]=0x05; //包 长度
    data[4]=0xFB; //包 长度 校验  0x100-data[3]
    data[5]=0xD4; //命令标识码
    data[6]=0x40; //命令标识码
    data[7]=0x01;
    data[8]=0x30;
    data[9]=nPageNumber; //读第二块的16字节数据
    data[10]=0xB9; //数据校验
    data[11]=0x00;
    temp=0;
    for(index=5;index<10;index++)
    {
        temp+=data[index];
    }
    data[10]=0x100-temp;

    PN532_CleanBuffer();
    PN532_SendData((const char*)data, 12);

    QByteArray arrData = readData();

    if(arrData.count() >= 0x20)
    {
        temp=0;
        for(index=11;index<30;index++)
        {
            temp += (uint8_t)(arrData.at(index));
        }
        CheckCode= 0x100 - temp;

        uint8_t u_check = (uint8_t)arrData.at(30);

        if(CheckCode == u_check && arrData.at(13) == 0x00)
        {
            for(index=0;index<16;index++)
            {
                pBuff[index]=(uint8_t)arrData.at(14+index);
            }
            return 0;
        }
    }

    return -1;
}



//默认往 02区写 16个字节的第一个字节
//00 00 FF 15 EB D4 40 01 A0 02 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F D1 00
int NfcPn532Api::nfc_write16byte(uint8_t nPageNumber,uint8_t *pBuff)
{
    uint8_t data[28];
    uint8_t temp=0;
    uint8_t index;
    uint8_t CheckCode=0;

    data[0]=0x00;
    data[1]=0x00;
    data[2]=0xFF;
    data[3]=0x15; //包 长度
    data[4]=0xEB; //包 长度 校验  0x100-data[3]
    data[5]=0xD4; //命令标识码
    data[6]=0x40; //命令标识码
    data[7]=0x01; //读写大于6字节 就置1，看手册
    data[8]=0xA0; //写
    data[9]=nPageNumber; //写第二块的16字节数据
    for(index=0;index<16;index++)
    {
        data[10+index]=pBuff[index]; //第 1 字节 数据
    }

    temp=0;
    for(index=5;index<26;index++)
    {
        temp+=data[index];
    }

    data[26]=0x100-temp; //数据 校验码
    data[27]=0x00;

    PN532_CleanBuffer();
    PN532_SendData((const char*)data, 28);

    QByteArray arrData = readData();

    //00 00 FF 00 FF 00 00 00 FF 03 FD D5 41 00 EA 00
    if(arrData.count() >=0x10)
    {
        temp=0;
        for(index=11; index<14; index++)
        {
            temp+=arrData.at(index);
        }

        CheckCode=0x100 - temp;

        uint8_t u_check = (uint8_t)arrData.at(14);

        if(CheckCode==u_check)
        {
            if(arrData.at(13)==0x00)
            {
                return 0;
            }
        }
        return -1;
    }

    return -1;
}

/*page 0:NULL
 *Page 1:卡标识加密(卡标识与UUID的累加和4byte),金额加密(RMB*100与UUID的累加和4byte),场站ID值(卡标识与UUID的累加和4byte)，异常卡识别(1字节)
 *Page 2:device SN(16byte)
 *Page 3:卡密钥区
 *说明:卡标识4字节，公司标识固定为2字节“YD”，
                   卡类型固定为1字节：0x5a:起停卡，0x50:公司网络卡，0x51:公司离线卡，0x52:场站管理卡，0x53:场站网络卡，0x54:场站离线卡，0x55：单桩启停卡，
                   卡标记固定为1字节：此针对离线计量卡，0xaa:可以启动充电，0xa0:正在充电，或有帐单未结帐
       金额1加密(RMB*100与UUID的累加和4byte)，此针对离线计量卡为卡余额， 针对其他卡，此值是4字节的随机KEY。
       金额2加密(RMB*100与场站ID的累加和4byte)，此针对离线计量卡为卡余额，针对其他卡，此值是卡标识区与随机KEY的二次加密校验,
       场站ID值(4byte,与UUID的累加和),此针对离线计量卡，此值既是金额2加密值，也是场站的ID值，公司自有场站固定为0x00000000;
       device SN(16byte)，离线计量时，此值为正在充电或未结算的设备SN，个人单桩是匹配的桩SN，对于管理卡，此为有效期截止日期
 */

//4字节时间值：0字节*100+1字节=年，2字节月，3字节日
int NfcPn532Api::nfc_CreateCard_Manage(uint8_t *pStationID,uint8_t *StopDate)
{
    qDebug() << "Enter nfc_CreateCard_Manage";
    uint8_t index=0;
    uint8_t DataBuffer[16];

    uint32_t key=(uint32_t)QDateTime::currentDateTime().toMSecsSinceEpoch();
    qDebug() << key;

    if(nfc_WakeUp())
    {
        qDebug() << "nfc_wakeup error";
        return -1;
    }
    if(nfc_InListPassiveTarget())
    {
        qDebug() << "nfc_InListPassiveTarget error";
        return -1;
    }

//    g_PN532_KeyA

    if(nfc_PsdVerifyKeyA((uint8_t*)g_PN532_KeyA_Default))//g_PN532_KeyA_Default
    {
        qDebug() << "nfc_PsdVerifyKeyA error";
        return -1;
    }
    //数据清零
    memset(DataBuffer,0,16);
    //卡类型
    DataBuffer[0]='Y';
    DataBuffer[1]='D';
    if(pStationID[0]==0x00 && pStationID[1]==0x00 && pStationID[2]==0x00 && pStationID[3]==0x00)
    {
        DataBuffer[2]=0x5a;//类型
    }
    else
    {
        DataBuffer[2]=0x52;//类型
    }
    DataBuffer[3]=0xaa;//可以充电
    //场站ID
    DataBuffer[12]=pStationID[0]+g_PN532_NFC_UID[0];//加密
    DataBuffer[13]=pStationID[1]+g_PN532_NFC_UID[1];
    DataBuffer[14]=pStationID[2]+g_PN532_NFC_UID[2];
    DataBuffer[15]=pStationID[3]+g_PN532_NFC_UID[3];
    //卡类型二次加密
    for(index=8;index<12;index++)
    {
        DataBuffer[index]=DataBuffer[index%4]+(uint8_t)(key>>((index%4)*8));//加密
    }
    //卡KEY
    for(index=4;index<8;index++)
    {
        DataBuffer[index]=(uint8_t)(key>>((index%4)*8))+g_PN532_NFC_UID[index%4];//加密
    }
    //卡类型一次加密
    for(index=0;index<4;index++)
    {
        DataBuffer[index]+=g_PN532_NFC_UID[index%4];//加密
    }
    if(nfc_write16byte(1,DataBuffer))
    {
        qDebug() << "nfc_CreateCard_Manage:1:fc_write16byte";
        return -1;
    }
    //数据清零
    memset(DataBuffer,0,16);
    for(index=0;index<4;index++)
    {
        DataBuffer[index]=StopDate[index]+g_PN532_NFC_UID[index%4];//加密
    }
    if(nfc_write16byte(2,DataBuffer))
    {
        qDebug() << "nfc_CreateCard_Manage:2:fc_write16byte";
       return -1;
    }


    //更改卡原始密码到自有密钥
    for(index=0;index<6;index++)
    {
        DataBuffer[index]=g_PN532_KeyA[index];
        DataBuffer[10+index]=g_PN532_KeyB[index];
    }
    DataBuffer[6]=0xff;//密钥控制字
    DataBuffer[7]=0x07;
    DataBuffer[8]=0x80;
    DataBuffer[9]=0x69;
    if(nfc_write16byte(3,DataBuffer))
    {
        qDebug() << "nfc_CreateCard_Manage:3:fc_write16byte";
       return -1;
    }
    qDebug() << "Leave nfc_CreateCard_Manage";
    return 0;
}

int NfcPn532Api::nfc_CreateCard_Network(uint8_t *pStationID,char *pOutRfidNumbers)
{
    qDebug() << "Enter nfc_CreateCard_Network";
    uint8_t index=0;
    uint8_t DataBuffer[16];

    uint32_t key=(uint32_t)QDateTime::currentDateTime().toMSecsSinceEpoch();

    if(nfc_WakeUp())
    {
        qDebug() << "nfc_WakeUp error!";
        return -1;
    }
    if(nfc_InListPassiveTarget())
    {
        qDebug() << "nfc_InListPassiveTarget error!";
        return -1;
    }

    if(nfc_PsdVerifyKeyA((uint8_t*)g_PN532_KeyA_Default))//g_PN532_KeyA_Default
     {
        qDebug() << "nfc_PsdVerifyKeyA error!";
        return -1;
     }

    //数据清零
    memset(DataBuffer,0,16);
    //卡类型
    DataBuffer[0]='Y';
    DataBuffer[1]='D';
    if(pStationID[0]==0x00 && pStationID[1]==0x00 && pStationID[2]==0x00 && pStationID[3]==0x00)
    {
        DataBuffer[2]=0x50;//类型
    }
    else
    {
        DataBuffer[2]=0x53;//类型
    }
    DataBuffer[3]=0xaa;//可以充电
    //场站ID
    DataBuffer[12]=pStationID[0]+g_PN532_NFC_UID[0];//加密
    DataBuffer[13]=pStationID[1]+g_PN532_NFC_UID[1];
    DataBuffer[14]=pStationID[2]+g_PN532_NFC_UID[2];
    DataBuffer[15]=pStationID[3]+g_PN532_NFC_UID[3];
    //卡类型二次加密
    for(index=8;index<12;index++)
    {
        DataBuffer[index]=DataBuffer[index%4]+(uint8_t)(key>>((index%4)*8));//加密
    }
    //卡KEY
    for(index=4;index<8;index++)
    {
        DataBuffer[index]=(uint8_t)(key>>((index%4)*8))+g_PN532_NFC_UID[index%4];//加密
    }
    //卡类型一次加密
    for(index=0;index<4;index++)
    {
        DataBuffer[index]+=g_PN532_NFC_UID[index%4];//加密
    }
    if(nfc_write16byte(1,DataBuffer))
        return -1;

    //数据清零，无用
    memset(DataBuffer,0,16);
    if(nfc_write16byte(2,DataBuffer))
        return -1;

    //更改卡原始密码到自有密钥
    for(index=0;index<6;index++)
    {
        DataBuffer[index]=g_PN532_KeyA[index];
        DataBuffer[10+index]=g_PN532_KeyB[index];
    }
    DataBuffer[6]=0xff;//密钥控制字
    DataBuffer[7]=0x07;
    DataBuffer[8]=0x80;
    DataBuffer[9]=0x69;
    if(nfc_write16byte(3,DataBuffer))
        return -1;

    snprintf(pOutRfidNumbers,16,"%02x%02x%02x%02x%02x%02x%02x%02x",g_PN532_NFC_UID[0],g_PN532_NFC_UID[1],g_PN532_NFC_UID[2],g_PN532_NFC_UID[3],pStationID[0],pStationID[1],pStationID[2],pStationID[3]);
    qDebug() << "Leave nfc_CreateCard_Network";
    return 0;
}

int NfcPn532Api::nfc_CreateCard_Offline(uint8_t *pStationID,char *pOutRfidNumbers,uint32_t Money)
{
    qDebug() << "Enter nfc_CreateCard_Offline";
    uint8_t index=0;
    uint8_t DataBuffer[16];

    if(nfc_WakeUp())
    {
        qDebug() << "nfc_WakeUp error!";
        return -1;
    }
    if(nfc_InListPassiveTarget())
    {
        qDebug() << "nfc_InListPassiveTarget error!";
        return -1;
    }
    if(nfc_PsdVerifyKeyA((uint8_t*)g_PN532_KeyA_Default))//g_PN532_KeyA_Default
    {
        qDebug() << "nfc_PsdVerifyKeyA error!";
        return -1;
    }

    //数据清零
    memset(DataBuffer,0,16);
    //卡类型
    DataBuffer[0]='Y';
    DataBuffer[1]='D';
    if(pStationID[0]==0x00 && pStationID[1]==0x00 && pStationID[2]==0x00 && pStationID[3]==0x00)
    {
        DataBuffer[2]=0x51;//类型
    }
    else
    {
        DataBuffer[2]=0x54;//类型
    }
    DataBuffer[3]=0xaa;//可以充电
    //场站ID
    DataBuffer[12]=pStationID[0]+g_PN532_NFC_UID[0];//加密
    DataBuffer[13]=pStationID[1]+g_PN532_NFC_UID[1];
    DataBuffer[14]=pStationID[2]+g_PN532_NFC_UID[2];
    DataBuffer[15]=pStationID[3]+g_PN532_NFC_UID[3];
    //金额二次加密
    for(index=8;index<12;index++)
    {
        DataBuffer[index]=(uint8_t)(Money>>((index%4)*8))+pStationID[index%4];//加密
    }
    //金额一次加密
    for(index=4;index<8;index++)
    {
        DataBuffer[index]=(uint8_t)(Money>>((index%4)*8))+g_PN532_NFC_UID[index%4];//加密
    }
    //卡类型一次加密
    for(index=0;index<4;index++)
    {
        DataBuffer[index]+=g_PN532_NFC_UID[index%4];//加密
    }
    if(nfc_write16byte(1,DataBuffer))
        return -1;

    //数据清零，无用
    memset(DataBuffer,0,16);
    if(nfc_write16byte(2,DataBuffer))
        return -1;

    //更改卡原始密码到自有密钥
    for(index=0;index<6;index++)
    {
        DataBuffer[index]=g_PN532_KeyA[index];
        DataBuffer[10+index]=g_PN532_KeyB[index];
    }
    DataBuffer[6]=0xff;//密钥控制字
    DataBuffer[7]=0x07;
    DataBuffer[8]=0x80;
    DataBuffer[9]=0x69;
    if(nfc_write16byte(3,DataBuffer))
        return -1;

    snprintf(pOutRfidNumbers,16,"%02x%02x%02x%02x%02x%02x%02x%02x",g_PN532_NFC_UID[0],g_PN532_NFC_UID[1],g_PN532_NFC_UID[2],g_PN532_NFC_UID[3],pStationID[0],pStationID[1],pStationID[2],pStationID[3]);
    qDebug() << "Leave nfc_CreateCard_Offline";
    return 0;
}


int NfcPn532Api::nfc_CreateCard_SelfUsed(char *DeviceSN)
{
    qDebug() << "Enter nfc_CreateCard_SelfUsed";

    uint8_t index=0;
    uint8_t DataBuffer[17];

    uint32_t key=(uint32_t)QDateTime::currentDateTime().toMSecsSinceEpoch();

    if(nfc_WakeUp())
     {
        qDebug() << "nfc_WakeUp error!";
        return -1;
     }
    if(nfc_InListPassiveTarget())
    {
        qDebug() << "nfc_InListPassiveTarget error!";
        return -1;
    }

    if(nfc_PsdVerifyKeyA((uint8_t*)g_PN532_KeyA_Default))//g_PN532_KeyA_Default
    {
        qDebug() << "nfc_PsdVerifyKeyA error!";
        return -1;
    }

    //数据清零
    memset(DataBuffer,0,17);
    //卡类型
    DataBuffer[0]='Y';
    DataBuffer[1]='D';
    DataBuffer[2]=0x55;//类型
    DataBuffer[3]=0xaa;//可以充电
    //卡类型二次加密
    for(index=8;index<12;index++)
    {
        DataBuffer[index]=DataBuffer[index%4]+(uint8_t)(key>>((index%4)*8));//加密
    }
    //卡KEY
    for(index=4;index<8;index++)
    {
        DataBuffer[index]=(uint8_t)(key>>((index%4)*8))+g_PN532_NFC_UID[index%4];//加密
    }
    //卡类型一次加密
    for(index=0;index<4;index++)
    {
        DataBuffer[index]+=g_PN532_NFC_UID[index%4];//加密
    }
    if(nfc_write16byte(1,DataBuffer))
        return -1;

    //数据清零
    memset(DataBuffer,0,16);
    strncpy((char*)DataBuffer,DeviceSN,16);//明文
    if(nfc_write16byte(2,DataBuffer))
        return -1;

    //更改卡原始密码到自有密钥
    for(index=0;index<6;index++)
    {
        DataBuffer[index]=g_PN532_KeyA[index];
        DataBuffer[10+index]=g_PN532_KeyB[index];
    }
    DataBuffer[6]=0xff;//密钥控制字
    DataBuffer[7]=0x07;
    DataBuffer[8]=0x80;
    DataBuffer[9]=0x69;
    if(nfc_write16byte(3,DataBuffer))
        return -1;
    qDebug() << "Leave nfc_CreateCard_SelfUsed";
    return 0;
}

int NfcPn532Api::nfc_ClearCard_offline()
{
    qDebug() << "Enter nfc_ClearCard_offline";
    uint8_t index=0;
    uint8_t DataBuffer[17];

    if(nfc_WakeUp())
    {
        qDebug() << "nfc_WakeUp error!";
        return -1;
    }
    if(nfc_InListPassiveTarget())
    {
        qDebug() << "nfc_InListPassiveTarget error!";
        return -1;
    }
    if(nfc_PsdVerifyKeyA((uint8_t*)g_PN532_KeyA))//g_PN532_KeyA_Default
    {
        qDebug() << "nfc_PsdVerifyKeyA error!";
        return -1;
    }

    //数据清零
    memset(DataBuffer,0,17);

    if(nfc_read16byte(1,DataBuffer))
    {
        qDebug() << "nfc_read16byte error!";
        return -1;
    }

    if((DataBuffer[2]-g_PN532_NFC_UID[2])==0x51 || (DataBuffer[2]-g_PN532_NFC_UID[2])==0x54)
    {
        //金额清零
        for(index=4;index<12;index++)
        {
            DataBuffer[index]=(uint8_t)0;//清零
        }

        if(nfc_write16byte(1,DataBuffer))
            return -1;
    }
    else
    {
        qDebug() << "card type error!";
        return -1;
    }

    qDebug() << "Leave nfc_ClearCard_offline";
    return 0;
}

float NfcPn532Api::nfc_ReadCard_offline()
{
    qDebug() << "Enter nfc_ReadCard_offline";

    uint8_t DataBuffer[17];

    if(nfc_WakeUp())
    {
        qDebug() << "nfc_WakeUp error!";
        return -1;
    }
    if(nfc_InListPassiveTarget())
    {
        qDebug() << "nfc_InListPassiveTarget error!";
        return -1;
    }
    if(nfc_PsdVerifyKeyA((uint8_t*)g_PN532_KeyA))//g_PN532_KeyA_Default
    {
        qDebug() << "nfc_PsdVerifyKeyA error!";
        return -1;
    }

    //数据清零
    memset(DataBuffer,0,17);

    if(nfc_read16byte(1,DataBuffer))
    {
        qDebug() << "nfc_read16byte error!";
        return -1;
    }

    if((DataBuffer[2]-g_PN532_NFC_UID[2])==0x51 || (DataBuffer[2]-g_PN532_NFC_UID[2])==0x54)
    {
        //判断金额是否相符
        if(((uint8_t)(DataBuffer[8]-(DataBuffer[12]-g_PN532_NFC_UID[0]))!=(uint8_t)(DataBuffer[4]-g_PN532_NFC_UID[0])) ||
             ((uint8_t)(DataBuffer[9]-(DataBuffer[13]-g_PN532_NFC_UID[1]))!=(uint8_t)(DataBuffer[5]-g_PN532_NFC_UID[1])) ||
           ((uint8_t)(DataBuffer[10]-(DataBuffer[14]-g_PN532_NFC_UID[2]))!=(uint8_t)(DataBuffer[6]-g_PN532_NFC_UID[2]))||
           ((uint8_t)(DataBuffer[11]-(DataBuffer[15]-g_PN532_NFC_UID[3]))!=(uint8_t)(DataBuffer[7]-g_PN532_NFC_UID[3])))
        {
            qDebug() << "card money  defferent error!";
            return -1;
        }

        //判断余额是否充足
        int balance=((uint8_t)(DataBuffer[4]-g_PN532_NFC_UID[0])>>0) |((uint8_t)(DataBuffer[5]-g_PN532_NFC_UID[1])<<8) | ((uint8_t)(DataBuffer[6]-g_PN532_NFC_UID[2])<<16) | ((uint8_t)(DataBuffer[7]-g_PN532_NFC_UID[3])<<24) ;
        return balance*1.0/100 ;
    }
    else
    {
        qDebug() << "card type error!";
        return -1;
    }

    qDebug() << "Leave nfc_ReadCard_offline";
    return 0;
}

QByteArray NfcPn532Api::readData()
{
    QByteArray responseData;
    if (serial->waitForReadyRead(3000)){
        responseData = serial->readAll();
        while (serial->waitForReadyRead(10))
            responseData += serial->readAll();

        return responseData;
    }
    return responseData;
}

