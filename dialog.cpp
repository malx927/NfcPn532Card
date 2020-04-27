#include "dialog.h"
#include "ui_dialog.h"
#include <QSerialPortInfo>
#include<QDate>
#include <QDebug>
#include <QMessageBox>
#include <QRegExp>
#include <QValidator>
#include <stdlib.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QDateTime>
//#include "utils.h"

extern QByteArray intToByte1(int i);
extern QByteArray intToByte4(uint i);
extern QByteArray date2byte(QDate date);

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    const auto infos = QSerialPortInfo::availablePorts();
    QStringList strList;
    for (const QSerialPortInfo &info : infos)
        strList.append(info.portName());
//        strList.push_front(info.portName());

    ui->comboBox->addItems(strList);
    ui->btnWrite->setEnabled(false);

    QRegExp regx("[0-9]+$");
    QValidator* validator = new QRegExpValidator(regx, ui->lineEditStationID);
    ui->lineEditStationID->setValidator(validator);

    serial = new QSerialPort(this);

    m_card_type = "";
    ui->dateEditStopDate->setDate(QDate::currentDate());

    pn532Api = new NfcPn532Api(this);

    createSqliteDb();
    createModel();
    createView();

}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_btnOpenComm_clicked()
{
    QString portName = ui->comboBox->currentText();

    bool ret = pn532Api->nfc_DeviceInit(portName);

    if(ret){
        ui->label_comm_state->setText("串口打开成功!");
        ui->btnWrite->setEnabled(true);
    }
    else {
        ui->label_comm_state->setText("串口打开失败!");
    }
}

void Dialog::readData()
{

}

void Dialog::handleError(QSerialPort::SerialPortError error)
{
    qDebug() << serial->errorString();
}

void Dialog::on_radioStartStop_toggled(bool checked)
{
//    qDebug() << "on_radioStartStop_toggled" << checked;
    if(checked){
        m_card_type = "5a";
        setState();
    }
}

void Dialog::on_radioCorpNetwork_toggled(bool checked)
{
//    qDebug() << "on_radioCorpNetwork_toggled" << checked;
    if(checked){
        m_card_type = "50";
        setState();
    }
}

void Dialog::on_radioCorpOffline_toggled(bool checked)
{
//    qDebug() << "on_radioCorpOffline_toggled" << checked;
    if(checked){
        m_card_type = "51";
        setState();
    }
}

void Dialog::on_radioStationManage_toggled(bool checked)
{
//    qDebug() << "on_radioStationManage_toggled" << checked;
    if(checked){
        m_card_type = "52";
        setState();
    }
}

void Dialog::on_radioStationNetwork_toggled(bool checked)
{
//    qDebug() << "on_radioStationNetwork_toggled" << checked;
    if(checked){
        m_card_type = "53";
        setState();
    }
}

void Dialog::on_radioStationOffline_toggled(bool checked)
{
//    qDebug() << "on_radioStationOffline_toggled" << checked;
    if(checked){
        m_card_type = "54";
        setState();
    }
}

void Dialog::on_radioSingleDevice_toggled(bool checked)
{
//    qDebug() << "on_radioSingleDevice_toggled" << checked;
    if(checked){
        m_card_type = "55";
        setState();
    }
}

void Dialog::setState()
{
    if(m_card_type == "5a") /*启停卡*/
    {
        ui->lineEditStationID->setEnabled(false);
        ui->dateEditStopDate->setEnabled(true);
        ui->spinBoxMoney->setEnabled(false);
        ui->lineEditDeviceSN->setEnabled(false);
    }
    else if(m_card_type=="50")
    {
        ui->lineEditStationID->setEnabled(false);
        ui->dateEditStopDate->setEnabled(false);
        ui->spinBoxMoney->setEnabled(false);
        ui->lineEditDeviceSN->setEnabled(false);
    }
    else if(m_card_type=="51")
    {
        ui->lineEditStationID->setEnabled(false);
        ui->dateEditStopDate->setEnabled(false);
        ui->spinBoxMoney->setEnabled(true);
        ui->lineEditDeviceSN->setEnabled(false);
    }
    else if(m_card_type=="52")
    {
        ui->lineEditStationID->setEnabled(true);
        ui->dateEditStopDate->setEnabled(true);
        ui->spinBoxMoney->setEnabled(false);
        ui->lineEditDeviceSN->setEnabled(false);
    }
    else if(m_card_type=="53")
    {
        ui->lineEditStationID->setEnabled(true);
        ui->dateEditStopDate->setEnabled(false);
        ui->spinBoxMoney->setEnabled(false);
        ui->lineEditDeviceSN->setEnabled(false);
    }
    else if(m_card_type=="54")
    {
        ui->lineEditStationID->setEnabled(true);
        ui->dateEditStopDate->setEnabled(false);
        ui->spinBoxMoney->setEnabled(true);
        ui->lineEditDeviceSN->setEnabled(false);
    }
    else if(m_card_type=="55")
    {
        ui->lineEditStationID->setEnabled(false);
        ui->dateEditStopDate->setEnabled(false);
        ui->spinBoxMoney->setEnabled(false);
        ui->lineEditDeviceSN->setEnabled(true);
    }
}

void Dialog::on_btnClose_clicked()
{
    this->close();
}

void Dialog::on_btnWrite_clicked()
{
    if(m_card_type.isEmpty()){
        QMessageBox::information(this, "创建卡提示:", "请选择制卡类型");
        return;
    }

    if(m_card_type == "5a") /*启停卡*/
    {
        //站场id为空，取截至时间
        uint8_t StationID[4] = {0};
        char StopDate[4] = {0};
        QDate endDate = ui->dateEditStopDate->date();
        QByteArray arr = date2byte(endDate);
        strcpy(StopDate, arr.data());
        qDebug() << QString(StopDate);
        int ret = pn532Api->nfc_CreateCard_Manage(StationID, (uint8_t*)StopDate);
        if(ret == 0){
            QMessageBox::information(this, "创建卡提示:", "创建启动卡成功!");
        }
        else{
            QMessageBox::critical(this, "创建卡提示:", "创建启动卡失败!");
        }

    }
    else if(m_card_type=="50")  /*公司网络卡f61a6a010000000|76a46c010000000*/
    {
        uint8_t StationID[4] = {0};
        char OutRfidNumbers[64];
        memset(OutRfidNumbers, 0, 64);

        int ret = pn532Api->nfc_CreateCard_Network(StationID, OutRfidNumbers);
        qDebug() << "公司网络卡号:" << QString(OutRfidNumbers);

        if(ret == 0){
            auto cur_time = QDateTime::currentDateTime();
            insertData(QString(OutRfidNumbers), QStringLiteral("公司网络卡"), cur_time);

            QMessageBox::information(this, "创建卡提示:", "创建公司网络卡成功!");
        }
        else{
            QMessageBox::critical(this, "创建卡提示:", "创建公司网络卡失败!");
        }
    }
    else if(m_card_type=="51")  /*公司离线卡c61f78050000000*/
    {
        uint8_t StationID[4] = {0};

        char OutRfidNumbers[64];
        memset(OutRfidNumbers, 0, 64);

        int money = ui->spinBoxMoney->value();
        if(money == 0)
        {
            QMessageBox::warning(this, "提示:", "离线卡金额");
            ui->spinBoxMoney->setFocus();
            return;
        }

        int ret = pn532Api->nfc_CreateCard_Offline(StationID, OutRfidNumbers, (uint32_t)money);

        qDebug() << "公司离线卡:" <<QString(OutRfidNumbers);

        if(ret == 0){
            auto cur_time = QDateTime::currentDateTime();
            insertData(QString(OutRfidNumbers), QStringLiteral("公司离线卡"), cur_time);

            QMessageBox::information(this, "创建卡提示:", "创建公司离线卡成功!");
        }
        else{
            QMessageBox::critical(this, "创建卡提示:", "创建公司离线卡失败!");
        }

    }
    else if(m_card_type=="52")  /*场站管理卡*/
    {
        //站场id，取截至时间
        uint8_t StationID[4] = {0};
        char StopDate[4] = {0};

        QString strStationID = ui->lineEditStationID->text();
        if(strStationID.isEmpty())
        {
            QMessageBox::warning(this, "提示:", "充电站ID不能为空");
            ui->lineEditStationID->setFocus();
            return;
        }
        bool ok;
        uint u_station_id = strStationID.toUInt(&ok);
        QByteArray arrStationID = intToByte4(u_station_id);
        strcpy((char*)StationID, arrStationID.data());

        QDate endDate = ui->dateEditStopDate->date();
        QByteArray arr = date2byte(endDate);
        strcpy(StopDate, arr.data());

        qDebug() << QString(StopDate) << QString((char*)StationID) << ok;

        int ret = pn532Api->nfc_CreateCard_Manage(StationID, (uint8_t*)StopDate);
        if(ret == 0){
            QMessageBox::information(this, "创建卡提示:", "创建场站管理卡成功!");
        }
        else{
            QMessageBox::critical(this, "创建卡提示:", "创建场站管理卡失败!");
        }
    }
    else if(m_card_type=="53")  /*场站网络卡*/
    {
        uint8_t StationID[4] = {0};
        char OutRfidNumbers[64];
        memset(OutRfidNumbers, 0, 64);


        QString strStationID = ui->lineEditStationID->text();
        if(strStationID.isEmpty())
        {
            QMessageBox::warning(this, "提示:", "充电站ID不能为空");
            ui->lineEditStationID->setFocus();
            return;
        }
        bool ok;
        uint u_station_id = strStationID.toUInt(&ok);
        QByteArray arrStationID = intToByte4(u_station_id);
        strcpy((char*)StationID, arrStationID.data());

        int ret = pn532Api->nfc_CreateCard_Network(StationID, OutRfidNumbers);
        qDebug() << QString(OutRfidNumbers);

        if(ret == 0){
            auto cur_time = QDateTime::currentDateTime();
            insertData(QString(OutRfidNumbers), QStringLiteral("场站网络卡"), cur_time, strStationID);

            QMessageBox::information(this, "创建卡提示:", "创建场站网络卡成功!");
        }
        else{
            QMessageBox::critical(this, "创建卡提示:", "创建场站网络卡失败!");
        }
    }
    else if(m_card_type=="54")  /*场站离线卡*/
    {
        uint8_t StationID[4] = {0};

        char OutRfidNumbers[64];
        memset(OutRfidNumbers, 0, 64);

        QString strStationID = ui->lineEditStationID->text();
        if(strStationID.isEmpty())
        {
            QMessageBox::warning(this, "提示:", "充电站ID不能为空");
            ui->lineEditStationID->setFocus();
            return;
        }
        bool ok;
        uint u_station_id = strStationID.toUInt(&ok);
        QByteArray arrStationID = intToByte4(u_station_id);
        strcpy((char*)StationID, arrStationID.data());

        int money = ui->spinBoxMoney->value();
        if(money == 0)
        {
            QMessageBox::warning(this, "提示:", "充电站ID不能为空");
            ui->spinBoxMoney->setFocus();
            return;
        }

        int ret = pn532Api->nfc_CreateCard_Offline(StationID, OutRfidNumbers, (uint32_t)money);

        qDebug() << QString(OutRfidNumbers);

        if(ret == 0){
            auto cur_time = QDateTime::currentDateTime();
            insertData(QString(OutRfidNumbers), QStringLiteral("场站离线卡"), cur_time, strStationID);

            QMessageBox::information(this, "创建卡提示:", "创建场站离线卡成功!");
        }
        else{
            QMessageBox::critical(this, "创建卡提示:", "创建场站离线卡失败!");
        }
    }
    else if(m_card_type=="55")  /*单桩启停卡*/
    {
         QString device_sn = ui->lineEditDeviceSN->text();
         if(device_sn.isEmpty()){
             QMessageBox::warning(this, "提示:", "设置充电桩SN编号");
             ui->lineEditDeviceSN->setFocus();
             return;
         }
         QByteArray arr = device_sn.toUtf8();
         int ret = pn532Api->nfc_CreateCard_SelfUsed(arr.data());

         if(ret == 0){
             QMessageBox::information(this, "创建卡提示:", "创建单桩启停卡成功!");
         }
         else{
             QMessageBox::critical(this, "创建卡提示:", "创建单桩启停卡失败!");
         }
    }
}

bool Dialog::createSqliteDb()
{

    QSqlDatabase sqlitedb = QSqlDatabase::addDatabase("QSQLITE");

    sqlitedb.setDatabaseName("cards.db");

    if( !sqlitedb.open() )
    {
        QMessageBox::warning(this,"数据库sqlite提示信息:",sqlitedb.lastError().text());
        qDebug() << sqlitedb.lastError().text() ;
        return false;
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
                         " card_type varchar(32),"
                         " create_time datetime,"
                         " station varchar(12)"
                         " );"
                      );
        qDebug() << query.lastError().text()  << query.lastQuery();
//        QSqlQuery q;
//        q.exec("INSERT INTO cards('card_num', 'card_type', 'create_time') VALUES('123456', 'AAAAAA', '2020-09-02 00:00:00')");

    }

    return true;
}

void Dialog::createModel()
{
    tableModel = new QSqlTableModel(this);
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel->setTable("cards");
    tableModel->select();
//    tableModel->removeColumn(0);

    tableModel->setHeaderData(0, Qt::Horizontal, "ID");
    tableModel->setHeaderData(1, Qt::Horizontal, QStringLiteral("卡号"));
    tableModel->setHeaderData(2, Qt::Horizontal, QStringLiteral("类型"));
    tableModel->setHeaderData(3, Qt::Horizontal, QStringLiteral("创建时间"));
    tableModel->setHeaderData(4, Qt::Horizontal, QStringLiteral("充电站ID"));

}

void Dialog::createView()
{

    ui->tableView->setSortingEnabled(true);
//    ui->tableView->horizontalHeader()->setBackgroundRole(QPalette::Background);
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background:lightgray;}");
//    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(225,225,225)};");
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setShowGrid(true);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->resizeColumnsToContents();

    ui->tableView->setModel( tableModel );
    ui->tableView->hideColumn(0);
    ui->tableView->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
    ui->tableView->resizeColumnToContents(1);
    ui->tableView->resizeColumnToContents(2);
    ui->tableView->resizeColumnToContents(4);


    ui->tableView->sortByColumn(3, Qt::DescendingOrder);
    //    ui->tableView->verticalHeader()->hide();
}

void Dialog::insertData(QString card, QString type, QDateTime dTime, QString stationid)
{
    QSqlQuery query;
    query.prepare("INSERT INTO cards(card_num, card_type, create_time, station) VALUES(?,?,?,?)");
    query.addBindValue( card );
    query.addBindValue( type );
    query.addBindValue( dTime );
    query.addBindValue( stationid );
    if( !query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
    }
    else
    {
       tableModel->select();
    }
}
