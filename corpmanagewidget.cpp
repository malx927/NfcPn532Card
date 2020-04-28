#include "corpmanagewidget.h"
#include "ui_corpmanagewidget.h"

CorpManageWidget::CorpManageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CorpManageWidget)
{
    ui->setupUi(this);
    createModel();
    createView();
}

CorpManageWidget::~CorpManageWidget()
{
    delete ui;
}

void CorpManageWidget::createModel()
{

}

void CorpManageWidget::createView()
{

}
