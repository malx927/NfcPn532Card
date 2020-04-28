#include "startstopwidget.h"
#include "ui_startstopwidget.h"
#include <QSqlTableModel>
#include <QHeaderView>
#include <QDebug>

StartStopWidget::StartStopWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartStopWidget)
{
    ui->setupUi(this);
    m_card_type = "5a";
    ui->dateEditStopDate->setDate(QDate::currentDate());
    createModel();
    createView();
}

StartStopWidget::~StartStopWidget()
{
    delete ui;
}

QSqlTableModel *StartStopWidget::getModel()
{
    return tableModel;
}

void StartStopWidget::createModel()
{
    tableModel = new QSqlTableModel(this);
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel->setTable("cards");
    tableModel->select();
    QString strWhere = QString("type_id='%1'").arg(m_card_type);
    tableModel->setFilter(strWhere);
    tableModel->setSort(tableModel->fieldIndex("create_time"), Qt::DescendingOrder);
//    qDebug() << tableModel->rowCount();
    tableModel->removeColumn(tableModel->fieldIndex("card_num"));
    tableModel->removeColumn(tableModel->fieldIndex("station"));
    tableModel->removeColumn(tableModel->fieldIndex("money"));
    tableModel->removeColumn(tableModel->fieldIndex("device"));
    tableModel->removeColumn(tableModel->fieldIndex("type_id"));

    tableModel->setHeaderData(tableModel->fieldIndex("id"), Qt::Horizontal, "ID");
    tableModel->setHeaderData(tableModel->fieldIndex("type_id"), Qt::Horizontal, QStringLiteral("类型编码"));
    tableModel->setHeaderData(tableModel->fieldIndex("card_type"), Qt::Horizontal, QStringLiteral("类型名称"));
    tableModel->setHeaderData(tableModel->fieldIndex("end_date"), Qt::Horizontal, QStringLiteral("有效截止时间"));
    tableModel->setHeaderData(tableModel->fieldIndex("username"), Qt::Horizontal, QStringLiteral("操作人"));
    tableModel->setHeaderData(tableModel->fieldIndex("create_time"), Qt::Horizontal, QStringLiteral("创建时间"));

}

void StartStopWidget::createView()
{
    ui->startTableView->setSortingEnabled(true);
//    ui->startTableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background:lightgray;}");
    ui->startTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->startTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->startTableView->setShowGrid(true);
    ui->startTableView->setAlternatingRowColors(true);
    ui->startTableView->resizeColumnsToContents();

    ui->startTableView->setModel( tableModel );
    ui->startTableView->hideColumn(0);
    ui->startTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


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
