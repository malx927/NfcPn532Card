#include "stationsinglewidget.h"
#include "ui_stationsinglewidget.h"
#include <QMessageBox>

StationSingleWidget::StationSingleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StationSingleWidget)
{
    ui->setupUi(this);
    m_card_type = "55";
}

StationSingleWidget::~StationSingleWidget()
{
    delete ui;
}

void StationSingleWidget::setBtnEnable(bool flag)
{
    ui->singeButton->setEnabled(flag);
}

void StationSingleWidget::on_singeButton_clicked()
{
    QString device_sn = ui->lineEditDeviceSN->text();
    if(device_sn.isEmpty()){
        QMessageBox::warning(this, "提示:", "设置充电桩SN编号");
        ui->lineEditDeviceSN->setFocus();
        return;
    }
    emit sig_station_single_write(m_card_type, device_sn);
}
