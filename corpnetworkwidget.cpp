#include "corpnetworkwidget.h"
#include "ui_corpnetworkwidget.h"

CorpNetworkWidget::CorpNetworkWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CorpNetworkWidget)
{
    ui->setupUi(this);
    m_card_type = "50";
}

CorpNetworkWidget::~CorpNetworkWidget()
{
    delete ui;
}

void CorpNetworkWidget::setBtnEnable(bool flag)
{
    ui->corpNetButton->setEnabled(flag);
}

void CorpNetworkWidget::on_corpNetButton_clicked()
{
    emit sig_corp_network_write(m_card_type);
}
