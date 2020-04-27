#include "startstopwidget.h"
#include "ui_startstopwidget.h"

StartStopWidget::StartStopWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartStopWidget)
{
    ui->setupUi(this);
    m_card_type = "5a";
    ui->dateEditStopDate->setDate(QDate::currentDate());

}

StartStopWidget::~StartStopWidget()
{
    delete ui;
}

void StartStopWidget::setBtnEnable(bool flag)
{
    ui->startStopButton->setEnabled(flag);
}

void StartStopWidget::on_startStopButton_clicked()
{
    QDate endDate = ui->dateEditStopDate->date();
    emit sig_start_stop_write(m_card_type, endDate);
}
