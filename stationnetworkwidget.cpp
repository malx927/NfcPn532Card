#include "stationnetworkwidget.h"
#include "ui_stationnetworkwidget.h"
#include <QMessageBox>

StationNetworkWidget::StationNetworkWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StationNetworkWidget)
{
    ui->setupUi(this);
    m_card_type = "53";
}

StationNetworkWidget::~StationNetworkWidget()
{
    delete ui;
}

void StationNetworkWidget::setBtnEnable(bool flag)
{
    ui->stNetworkButton->setEnabled(flag);
}

void StationNetworkWidget::on_stNetworkButton_clicked()
{

    QString strStationID = ui->lineEditStationID->text();
    if(strStationID.isEmpty())
    {
        QMessageBox::warning(this, "提示:", "充电站ID不能为空");
        ui->lineEditStationID->setFocus();
        return;
    }
    emit sig_station_network_write(m_card_type, strStationID);
}
