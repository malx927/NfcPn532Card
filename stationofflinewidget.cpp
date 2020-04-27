#include "stationofflinewidget.h"
#include "ui_stationofflinewidget.h"
#include <QMessageBox>

StationOfflineWidget::StationOfflineWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StationOfflineWidget)
{
    ui->setupUi(this);
    m_card_type = "54";
}

StationOfflineWidget::~StationOfflineWidget()
{
    delete ui;
}

void StationOfflineWidget::setBtnEnable(bool flag)
{
    ui->stOfflineButton->setEnabled(flag);
    ui->clearMoneyButton->setEnabled(flag);
}

void StationOfflineWidget::on_stOfflineButton_clicked()
{

    QString strStationID = ui->lineEditStationID->text();
    if(strStationID.isEmpty())
    {
        QMessageBox::warning(this, "提示:", "充电站ID不能为空");
        ui->lineEditStationID->setFocus();
        return;
    }

    int money = ui->spinBoxMoney->value();
    if(money == 0)
    {
        QMessageBox::warning(this, "提示:", "充值金额不能为空");
        ui->spinBoxMoney->setFocus();
        return;
    }
    emit sig_station_offline_write(m_card_type, strStationID, money);
}

void StationOfflineWidget::on_clearMoneyButton_clicked()
{

}
