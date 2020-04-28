#include "corpnetworkwidget.h"
#include "ui_corpnetworkwidget.h"
#include <QSqlTableModel>
#include <QDebug>

CorpNetworkWidget::CorpNetworkWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CorpNetworkWidget)
{
    ui->setupUi(this);

    m_card_type = "50";

    createModel();
    createView();

}

CorpNetworkWidget::~CorpNetworkWidget()
{
    delete ui;
}

QSqlTableModel *CorpNetworkWidget::getModel()
{
    return  tableModel;
}

void CorpNetworkWidget::createModel()
{
    tableModel = new QSqlTableModel(this);
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel->setTable("cards");
    tableModel->select();
    QString strWhere = QString("type_id='%1'").arg(m_card_type);
    tableModel->setFilter(strWhere);
    tableModel->setSort(tableModel->fieldIndex("create_time"), Qt::DescendingOrder);

    tableModel->removeColumn(tableModel->fieldIndex("end_date"));
    tableModel->removeColumn(tableModel->fieldIndex("station"));
    tableModel->removeColumn(tableModel->fieldIndex("money"));
    tableModel->removeColumn(tableModel->fieldIndex("device"));
    tableModel->removeColumn(tableModel->fieldIndex("type_id"));

    tableModel->setHeaderData(tableModel->fieldIndex("id"), Qt::Horizontal, "ID");
    tableModel->setHeaderData(tableModel->fieldIndex("card_num"), Qt::Horizontal, QStringLiteral("卡号"));
    tableModel->setHeaderData(tableModel->fieldIndex("type_id"), Qt::Horizontal, QStringLiteral("类型编号"));
    tableModel->setHeaderData(tableModel->fieldIndex("card_type"), Qt::Horizontal, QStringLiteral("类型名称"));
    tableModel->setHeaderData(tableModel->fieldIndex("create_time"), Qt::Horizontal, QStringLiteral("创建时间"));
    tableModel->setHeaderData(tableModel->fieldIndex("username"), Qt::Horizontal, QStringLiteral("操作人"));

}

void CorpNetworkWidget::createView()
{
    ui->networkTableView->setSortingEnabled(true);
//    ui->networkTableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background:lightgray;}");
    ui->networkTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->networkTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->networkTableView->setShowGrid(true);
    ui->networkTableView->setAlternatingRowColors(true);
    ui->networkTableView->resizeColumnsToContents();

    ui->networkTableView->setModel( tableModel );
    ui->networkTableView->hideColumn(0);
    ui->networkTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void CorpNetworkWidget::setBtnEnable(bool flag)
{
    ui->corpNetButton->setEnabled(flag);
}

void CorpNetworkWidget::on_corpNetButton_clicked()
{
    emit sig_corp_network_write(m_card_type);
}
