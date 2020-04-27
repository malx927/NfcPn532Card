#include "stationmanagewidget.h"
#include "ui_stationmanagewidget.h"
#include <QMessageBox>

StationManageWidget::StationManageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StationManageWidget)
{
    ui->setupUi(this);
    m_card_type = "52";
    ui->dateEditStopDate->setDate(QDate::currentDate());
}

StationManageWidget::~StationManageWidget()
{
    delete ui;
}

void StationManageWidget::setBtnEnable(bool flag)
{
    ui->stManageButton->setEnabled(flag);
}

void StationManageWidget::on_stManageButton_clicked()
{
    QString strStationID = ui->lineEditStationID->text();
    if(strStationID.isEmpty())
    {
        QMessageBox::warning(this, "提示:", "充电站ID不能为空");
        ui->lineEditStationID->setFocus();
        return;
    }

    QDate endDate = ui->dateEditStopDate->date();
    emit sig_station_manage_write(m_card_type, strStationID, endDate);
}
