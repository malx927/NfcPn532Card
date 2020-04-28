#include "stationsinglewidget.h"
#include "ui_stationsinglewidget.h"
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDebug>

StationSingleWidget::StationSingleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StationSingleWidget)
{
    ui->setupUi(this);

    m_card_type = "55";

    createModel();
    createView();

}

StationSingleWidget::~StationSingleWidget()
{
    delete ui;
}

QSqlTableModel *StationSingleWidget::getModel()
{
    return tableModel;
}

void StationSingleWidget::createModel()
{
    tableModel = new QSqlTableModel(this);
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel->setTable("cards");
    tableModel->select();
    QString strWhere = QString("type_id='%1'").arg(m_card_type);
    tableModel->setFilter(strWhere);
    tableModel->setSort(tableModel->fieldIndex("create_time"), Qt::DescendingOrder);

    tableModel->removeColumn(tableModel->fieldIndex("card_num"));
    tableModel->removeColumn(tableModel->fieldIndex("station"));
    tableModel->removeColumn(tableModel->fieldIndex("money"));
    tableModel->removeColumn(tableModel->fieldIndex("end_date"));
    tableModel->removeColumn(tableModel->fieldIndex("type_id"));

    tableModel->setHeaderData(tableModel->fieldIndex("id"), Qt::Horizontal, "ID");
    tableModel->setHeaderData(tableModel->fieldIndex("type_id"), Qt::Horizontal, QStringLiteral("类型编号"));
    tableModel->setHeaderData(tableModel->fieldIndex("card_type"), Qt::Horizontal, QStringLiteral("类型名称"));
    tableModel->setHeaderData(tableModel->fieldIndex("create_time"), Qt::Horizontal, QStringLiteral("创建时间"));
    tableModel->setHeaderData(tableModel->fieldIndex("device"), Qt::Horizontal, QStringLiteral("充电桩"));
    tableModel->setHeaderData(tableModel->fieldIndex("username"), Qt::Horizontal, QStringLiteral("操作人"));

}

void StationSingleWidget::createView()
{
    ui->singleTableView->setSortingEnabled(true);
//    ui->singleTableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background:lightgray;}");
    ui->singleTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->singleTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->singleTableView->setShowGrid(true);
    ui->singleTableView->setAlternatingRowColors(true);
    ui->singleTableView->resizeColumnsToContents();
    ui->singleTableView->setModel( tableModel );
    ui->singleTableView->hideColumn(0);
    ui->singleTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
