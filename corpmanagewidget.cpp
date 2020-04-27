#include "corpmanagewidget.h"
#include "ui_corpmanagewidget.h"

CorpManageWidget::CorpManageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CorpManageWidget)
{
    ui->setupUi(this);
}

CorpManageWidget::~CorpManageWidget()
{
    delete ui;
}
