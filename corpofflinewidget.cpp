#include "corpofflinewidget.h"
#include "ui_corpofflinewidget.h"
#include <QMessageBox>

CorpOfflineWidget::CorpOfflineWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CorpOfflineWidget)
{
    ui->setupUi(this);
     m_card_type = "51";
}

CorpOfflineWidget::~CorpOfflineWidget()
{
    delete ui;
}

void CorpOfflineWidget::setBtnEnable(bool flag)
{
    ui->offlineButton->setEnabled(flag);
    ui->clearMoneyButton->setEnabled(flag);
}

void CorpOfflineWidget::on_offlineButton_clicked()
{
    int money = ui->spinBoxMoney->value();
    if(money == 0)
    {
        QMessageBox::warning(this, "提示:", "离线卡金额");
        ui->spinBoxMoney->setFocus();
        return;
    }
    emit sig_corp_offline_write(m_card_type, money);
}

void CorpOfflineWidget::on_clearMoneyButton_clicked()
{

}
