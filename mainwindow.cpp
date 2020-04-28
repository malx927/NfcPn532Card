#include "mainwindow.h"
#include <QToolBar>
#include <QAction>
#include <QStackedWidget>
#include <QActionGroup>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QValidator>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QByteArray>
#include <QMessageBox>
#include "startstopwidget.h"
#include "corpnetworkwidget.h"
#include "corpofflinewidget.h"
#include "stationmanagewidget.h"
#include "stationnetworkwidget.h"
#include "stationofflinewidget.h"
#include "stationsinglewidget.h"
#include "utils.h"
#include <QDebug>

//extern QByteArray intToByte1(int i);
//extern QByteArray intToByte4(uint i);
//extern QByteArray date2byte(QDate date);

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    createAction();
    createToolbar();
    createSqliteDb();
    showPanel();

    const auto infos = QSerialPortInfo::availablePorts();
    QStringList strList;
    for (const QSerialPortInfo &info : infos)
        strList.append(info.portName());

    comboBox->addItems(strList);

    serial = new QSerialPort(this);

    pn532Api = new NfcPn532Api(this);


    setButtionState(false);
}

void MainWindow::createAction()
{
    actionGroup = new QActionGroup(this);

    startStopAction = new QAction("启停卡",this);
    startStopAction->setCheckable(true);
    startStopAction->setIcon(QIcon(":/image/start_stop.png"));
    startStopAction->setStatusTip("启停卡");
    actionGroup->addAction(startStopAction);

    corpNetworkAction = new QAction("公司网络卡",this);
    corpNetworkAction->setCheckable(true);
    corpNetworkAction->setIcon(QIcon(":/image/corp_network.png"));
    corpNetworkAction->setStatusTip("公司网络卡");
    actionGroup->addAction(corpNetworkAction);

    corpOfflineAction = new QAction("公司离线卡",this);
    corpOfflineAction->setCheckable(true);
    corpOfflineAction->setIcon(QIcon(":/image/corp_offline.png"));
    corpOfflineAction->setStatusTip("公司离线卡");
    actionGroup->addAction(corpOfflineAction);

    stationManageAction = new QAction("站场管理卡",this);
    stationManageAction->setCheckable(true);
    stationManageAction->setIcon(QIcon(":/image/station_manage.png"));
    stationManageAction->setStatusTip("站场管理卡");
    actionGroup->addAction(stationManageAction);

    stationNetworkAction = new QAction("站场网络卡",this);
    stationNetworkAction->setCheckable(true);
    stationNetworkAction->setIcon(QIcon(":/image/station_network.png"));
    stationNetworkAction->setStatusTip("站场网络卡");
    actionGroup->addAction(stationNetworkAction);

    stationOfflineAction = new QAction("站场离线卡",this);
    stationOfflineAction->setCheckable(true);
    stationOfflineAction->setIcon(QIcon(":/image/station_offline.png"));
    stationOfflineAction->setStatusTip("站场离线卡");
    actionGroup->addAction(stationOfflineAction);

    singleDeviceAction = new QAction("单桩启停卡",this);
    singleDeviceAction->setCheckable(true);
    singleDeviceAction->setIcon(QIcon(":/image/single_device.png"));
    singleDeviceAction->setStatusTip("单桩启停卡");
    actionGroup->addAction(singleDeviceAction);

}

void MainWindow::createToolbar()
{
    this->setContextMenuPolicy(Qt::NoContextMenu);
    toolBar = addToolBar("工具栏");
    toolBar->setIconSize(QSize(32,32));
    toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    comboBox = new QComboBox(this);
    comboBox->setMinimumWidth(80);
    comboBox->setMinimumHeight(25);
    openButton = new QPushButton("打开串口",this);
    openButton->setFixedSize(QSize(80,28));

    QLabel *label = new QLabel("串口号:");
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setSpacing(10);
    layout->addWidget(label);
    layout->addWidget(comboBox);
    layout->addWidget(openButton);
    QWidget* widget = new QWidget(toolBar);
    widget->setLayout(layout);
    toolBar->addWidget(widget);

    toolBar->addSeparator();
    toolBar->addAction(startStopAction);
    toolBar->addAction(corpNetworkAction);
    toolBar->addAction(corpOfflineAction);
    toolBar->addAction(stationManageAction);
    toolBar->addAction(stationNetworkAction);
    toolBar->addAction(stationOfflineAction);
    toolBar->addAction(singleDeviceAction);

}

void MainWindow::showPanel()
{

    startStopAction->setChecked(true);
    stackedWidget = new QStackedWidget(this);

    startStopWidget = new StartStopWidget(stackedWidget);
    networkWidget = new CorpNetworkWidget(stackedWidget);
    offlineWidget = new CorpOfflineWidget(stackedWidget);

    stManageWidget = new StationManageWidget(stackedWidget);
    stNetworkWidget = new StationNetworkWidget(stackedWidget);
    stOfflineWidget = new StationOfflineWidget(stackedWidget);
    stSingleWidget = new StationSingleWidget(stackedWidget);

    stackedWidget->addWidget(startStopWidget);
    stackedWidget->addWidget(networkWidget);
    stackedWidget->addWidget(offlineWidget);
    stackedWidget->addWidget(stManageWidget);
    stackedWidget->addWidget(stNetworkWidget);
    stackedWidget->addWidget(stOfflineWidget);
    stackedWidget->addWidget(stSingleWidget);

    setCentralWidget(stackedWidget);
    stackedWidget->setCurrentWidget(startStopWidget);

    connect(startStopAction, &QAction::triggered, this, &MainWindow::slot_start_stop);
    connect(corpNetworkAction, &QAction::triggered, this, &MainWindow::slot_corp_network);
    connect(corpOfflineAction, &QAction::triggered, this, &MainWindow::slot_corp_offline);
    connect(stationManageAction, &QAction::triggered, this, &MainWindow::slot_station_manage);
    connect(stationNetworkAction, &QAction::triggered, this, &MainWindow::slot_station_network);
    connect(stationOfflineAction, &QAction::triggered, this, &MainWindow::slot_station_offline);
    connect(singleDeviceAction, &QAction::triggered, this, &MainWindow::slot_station_single);

    connect(openButton, &QPushButton::clicked, this, &MainWindow::openComm);

    connect(startStopWidget, &StartStopWidget::sig_start_stop_write, this, &MainWindow::slot_start_stop_write);
    connect(networkWidget, &CorpNetworkWidget::sig_corp_network_write, this, &MainWindow::slot_corp_network_write);
    connect(offlineWidget, &CorpOfflineWidget::sig_corp_offline_write, this, &MainWindow::slot_corp_offline_write);
    connect(stManageWidget, &StationManageWidget::sig_station_manage_write, this, &MainWindow::slot_station_manage_write);
    connect(stNetworkWidget, &StationNetworkWidget::sig_station_network_write, this, &MainWindow::slot_station_network_write);
    connect(stOfflineWidget, &StationOfflineWidget::sig_station_offline_write, this, &MainWindow::slot_station_offline_write);
    connect(stSingleWidget, &StationSingleWidget::sig_station_single_write, this, &MainWindow::slot_station_single_write);

}

void MainWindow::addWidget()
{

}

void MainWindow::createSqliteDb()
{
    QSqlDatabase sqlitedb = QSqlDatabase::addDatabase("QSQLITE");

    sqlitedb.setDatabaseName("cards.db");

    if( !sqlitedb.open() )
    {
        QMessageBox::warning(this,"数据库sqlite提示信息:",sqlitedb.lastError().text());
        qDebug() << sqlitedb.lastError().text() ;
        return ;
    }
    else
    {
         qDebug() << "数据库创建成功";
    }

    if ( !sqlitedb.tables().contains( "cards" ) )       ////创建表
    {

        QSqlQuery query = sqlitedb.exec( "create table cards("
                         " id integer primary key AUTOINCREMENT, "
                         " card_num varchar(64),"
                         " type_id integer,"
                         " card_type varchar(32),"
                         " end_date date,"
                         " station varchar(12),"
                         " device varchar(24),"
                         " money float,"
                         " create_time datetime,"
                         " username varchar(24)"

                         " );"
                      );
        qDebug() << query.lastError().text()  << query.lastQuery();
//        QSqlQuery q;
//        q.exec("INSERT INTO cards('card_num', 'card_type', 'create_time') VALUES('123456', 'AAAAAA', '2020-09-02 00:00:00')");

    }

}

void MainWindow::setButtionState(bool flag)
{
    startStopWidget->setBtnEnable(flag);
    networkWidget->setBtnEnable(flag);
    offlineWidget->setBtnEnable(flag);
    stManageWidget->setBtnEnable(flag);
    stNetworkWidget->setBtnEnable(flag);
    stOfflineWidget->setBtnEnable(flag);
    stSingleWidget->setBtnEnable(flag);
}

void MainWindow::openComm()
{
    QString portName = comboBox->currentText();

    bool ret = pn532Api->nfc_DeviceInit(portName);

    if(ret){
        setButtionState(ret);
        QMessageBox::warning(this,"提示信息:", "串口打开成功");
    }
    else {
        setButtionState(ret);
        QMessageBox::warning(this,"提示信息:", "串口打开失败");
    }

}

void MainWindow::slot_start_stop()
{
    stackedWidget->setCurrentWidget(startStopWidget);
}

void MainWindow::slot_corp_network()
{

    stackedWidget->setCurrentWidget(networkWidget);
}

void MainWindow::slot_corp_offline()
{
    stackedWidget->setCurrentWidget(offlineWidget);
}

void MainWindow::slot_station_manage()
{
    stackedWidget->setCurrentWidget(stManageWidget);
}

void MainWindow::slot_station_network()
{
    stackedWidget->setCurrentWidget(stNetworkWidget);
}

void MainWindow::slot_station_offline()
{
    stackedWidget->setCurrentWidget(stOfflineWidget);
}

void MainWindow::slot_station_single()
{
    stackedWidget->setCurrentWidget(stSingleWidget);
}

void MainWindow::slot_start_stop_write(QString cType, QDate date)
{
    if(cType == "5a") /*启停卡*/
    {
        //站场id为空，取截至时间
        uint8_t StationID[4] = {0};
        char StopDate[4] = {0};
        QDate endDate = date;
        QByteArray arr = date2byte(endDate);
        strcpy(StopDate, arr.data());
        qDebug() << QString(StopDate);
        int ret = pn532Api->nfc_CreateCard_Manage(StationID, (uint8_t*)StopDate);
//        insertData(cType, "启停卡", endDate);
        if(ret == 0){
            insertData(cType, "启停卡", endDate);
            QMessageBox::information(this, "创建卡提示:", "创建启动卡成功!");
        }
        else{
            QMessageBox::critical(this, "创建卡提示:", "创建启动卡失败!");
        }

    }
}

void MainWindow::slot_corp_network_write(QString cType)
{
    if(cType == "50")  /*公司网络卡f61a6a010000000|76a46c010000000*/
    {
        uint8_t StationID[4] = {0};
        char OutRfidNumbers[64];
        memset(OutRfidNumbers, 0, 64);

        int ret = pn532Api->nfc_CreateCard_Network(StationID, OutRfidNumbers);
        qDebug() << "公司网络卡号:" << QString(OutRfidNumbers);
//        auto cur_time = QDate::currentDate();
//        insertData(cType, QStringLiteral("公司网络卡"), cur_time, QString(OutRfidNumbers));
        if(ret == 0){
            auto cur_time = QDate::currentDate();
            insertData(cType, QStringLiteral("公司网络卡"), cur_time, QString(OutRfidNumbers));

            QMessageBox::information(this, "创建卡提示:", "创建公司网络卡成功!");
        }
        else{
            QMessageBox::critical(this, "创建卡提示:", "创建公司网络卡失败!");
        }
    }
}

void MainWindow::slot_corp_offline_write(QString cType, int value)
{
   if(cType == "51")  /*公司离线卡c61f78050000000*/
    {
        uint8_t StationID[4] = {0};

        char OutRfidNumbers[64];
        memset(OutRfidNumbers, 0, 64);

        int money = value * 100;

        int ret = pn532Api->nfc_CreateCard_Offline(StationID, OutRfidNumbers, (uint32_t)money);

        qDebug() << "公司离线卡:" <<QString(OutRfidNumbers);
//        auto cur_time = QDate::currentDate();
//        insertData(cType, QStringLiteral("公司离线卡"), cur_time, QString(OutRfidNumbers), QString(), money);

        if(ret == 0){
            auto cur_time = QDate::currentDate();
            insertData(cType, QStringLiteral("公司离线卡"), cur_time, QString(OutRfidNumbers), QString(), value);

            QMessageBox::information(this, "创建卡提示:", "创建公司离线卡成功!");
        }
        else{
            QMessageBox::critical(this, "创建卡提示:", "创建公司离线卡失败!");
        }

    }
}

void MainWindow::slot_station_manage_write(QString cType, QString stationId, QDate date)
{
    if(cType == "52")  /*场站管理卡*/
    {
        //站场id，取截至时间
        uint8_t StationID[4] = {0};
        char StopDate[4] = {0};

        QString strStationID = stationId;

        bool ok;
        uint u_station_id = strStationID.toUInt(&ok);
        QByteArray arrStationID = intToByte4(u_station_id);
        strcpy((char*)StationID, arrStationID.data());

        QDate endDate = date;
        QByteArray arr = date2byte(endDate);
        strcpy(StopDate, arr.data());

        qDebug() << QString(StopDate) << QString((char*)StationID) << ok;

        int ret = pn532Api->nfc_CreateCard_Manage(StationID, (uint8_t*)StopDate);

        if(ret == 0){
            insertData(cType, "场站管理卡", endDate, QString(), strStationID);
            QMessageBox::information(this, "创建卡提示:", "创建场站管理卡成功!");
        }
        else{
            QMessageBox::critical(this, "创建卡提示:", "创建场站管理卡失败!");
        }
    }
}

void MainWindow::slot_station_network_write(QString cType, QString stationId)
{
    if(cType == "53")  /*场站网络卡*/
    {
        uint8_t StationID[4] = {0};
        char OutRfidNumbers[64];
        memset(OutRfidNumbers, 0, 64);


        QString strStationID = stationId;

        bool ok;
        uint u_station_id = strStationID.toUInt(&ok);
        QByteArray arrStationID = intToByte4(u_station_id);
        strcpy((char*)StationID, arrStationID.data());

        int ret = pn532Api->nfc_CreateCard_Network(StationID, OutRfidNumbers);
        qDebug() << QString(OutRfidNumbers);
//        auto cur_time = QDate::currentDate();

        if(ret == 0){
            auto cur_time = QDate::currentDate();
            insertData(cType, QStringLiteral("场站网络卡"), cur_time, QString(OutRfidNumbers), strStationID);
//            insertData(QString(OutRfidNumbers), QStringLiteral("场站网络卡"), cur_time, strStationID);

            QMessageBox::information(this, "创建卡提示:", "创建场站网络卡成功!");
        }
        else{
            QMessageBox::critical(this, "创建卡提示:", "创建场站网络卡失败!");
        }
    }
}

void MainWindow::slot_station_offline_write(QString cType, QString stationId, int nMoney)
{
    if(cType == "54")  /*场站离线卡*/
    {
        uint8_t StationID[4] = {0};

        char OutRfidNumbers[64];
        memset(OutRfidNumbers, 0, 64);

        QString strStationID = stationId;

        bool ok;
        uint u_station_id = strStationID.toUInt(&ok);
        QByteArray arrStationID = intToByte4(u_station_id);
        strcpy((char*)StationID, arrStationID.data());

        int money = nMoney * 100;

        int ret = pn532Api->nfc_CreateCard_Offline(StationID, OutRfidNumbers, (uint32_t)money);

        qDebug() << QString(OutRfidNumbers);
//        auto cur_time = QDate::currentDate();
//        insertData(cType, QStringLiteral("场站离线卡"), cur_time, QString(OutRfidNumbers), strStationID, money);

        if(ret == 0){
            auto cur_time = QDate::currentDate();
            insertData(cType, QStringLiteral("场站离线卡"), cur_time, QString(OutRfidNumbers), strStationID, nMoney);
            QMessageBox::information(this, "创建卡提示:", "创建场站离线卡成功!");
        }
        else{
            QMessageBox::critical(this, "创建卡提示:", "创建场站离线卡失败!");
        }
    }
}

void MainWindow::slot_station_single_write(QString cType, QString deviceSN)
{
    if(cType=="55")  /*单桩启停卡*/
    {
         QString device_sn = deviceSN;

         QByteArray arr = device_sn.toUtf8();
         int ret = pn532Api->nfc_CreateCard_SelfUsed(arr.data());

         if(ret == 0){
             auto cur_date = QDate::currentDate();
             insertData(cType, "单桩启停卡", cur_date, QString(), QString(), 0, device_sn);
             QMessageBox::information(this, "创建卡提示:", "创建单桩启停卡成功!");
         }
         else{
             QMessageBox::critical(this, "创建卡提示:", "创建单桩启停卡失败!");
         }
    }
}

void MainWindow::slot_card_money_clear(QString cType)
{
    if(cType == "54" || cType == "51")
    {
        int ret = pn532Api->nfc_ClearCard_offline();
        if(ret == 0){
            QMessageBox::information(this, "卡金额清零:", "卡清零成功!");
        }
        else{
            QMessageBox::critical(this, "卡金额清零:", "卡清零失败!");
        }
    }
}

void MainWindow::slot_card_read_money(QString cType)
{
    if(cType == "54" || cType == "51")
    {
        int ret = pn532Api->nfc_ReadCard_offline();
        if(ret >= 0)
        {
            QMessageBox::information(this, "卡金额:", QString("%1元").arg(ret));
        }
        else
        {
            QMessageBox::critical(this, "卡金额清零:", "卡清零失败!");
        }
    }
}

void MainWindow::insertData(QString type, QString type_name, QDate dTime, QString card, QString stationid, int money, QString device_sn)
{
    QSqlQuery query;
    query.prepare("INSERT INTO cards(card_num, type_id, card_type, end_date, create_time, station, device, money,username) VALUES(?,?,?,?,?,?,?,?,?)");
    query.addBindValue( card );
    query.addBindValue( type );
    query.addBindValue( type_name );
    query.addBindValue( dTime );
    query.addBindValue( QDateTime::currentDateTime() );
    query.addBindValue( stationid );
    query.addBindValue( device_sn );
    query.addBindValue( money );
    query.addBindValue( "" );


    if( !query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        return;
    }

    if(type == "5a")
    {
        startStopWidget->getModel()->select();
    }
    else if(type == "50")
    {
        networkWidget->getModel()->select();
    }
    else if(type == "51")
    {
        offlineWidget->getModel()->select();
        offlineWidget->getTotals();
    }
    else if(type == "52")
    {
        stManageWidget->getModel()->select();
    }
    else if(type == "53")
    {
        stNetworkWidget->getModel()->select();
    }
    else if(type == "54")
    {
        stOfflineWidget->getModel()->select();
        stOfflineWidget->getTotals();
    }
    else if(type == "55")
    {
        stSingleWidget->getModel()->select();
    }

}
