#include "stationmanagewidget.h"
#include "ui_stationmanagewidget.h"
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDebug>

StationManageWidget::StationManageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StationManageWidget)
{
    ui->setupUi(this);
    m_card_type = "52";

    createModel();
    createView();


    ui->dateEditStopDate->setDate(QDate::currentDate());

}

StationManageWidget::~StationManageWidget()
{
    delete ui;
}

QSqlTableModel *StationManageWidget::getModel()
{
    return tableModel;
}

void StationManageWidget::createModel()
{
    tableModel = new QSqlTableModel(this);
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel->setTable("cards");
    tableModel->select();
    QString strWhere = QString("type_id='%1'").arg(m_card_type);
    tableModel->setFilter(strWhere);
    tableModel->setSort(tableModel->fieldIndex("create_time"), Qt::DescendingOrder);

    tableModel->removeColumn(tableModel->fieldIndex("card_num"));
    tableModel->removeColumn(tableModel->fieldIndex("money"));
    tableModel->removeColumn(tableModel->fieldIndex("device"));
    tableModel->removeColumn(tableModel->fieldIndex("type_id"));

    tableModel->setHeaderData(tableModel->fieldIndex("id"), Qt::Horizontal, "ID");
    tableModel->setHeaderData(tableModel->fieldIndex("type_id"), Qt::Horizontal, QStringLiteral("类型编号"));
    tableModel->setHeaderData(tableModel->fieldIndex("card_type"), Qt::Horizontal, QStringLiteral("类型名称"));
    tableModel->setHeaderData(tableModel->fieldIndex("end_date"), Qt::Horizontal, QStringLiteral("有效截止时间"));
    tableModel->setHeaderData(tableModel->fieldIndex("create_time"), Qt::Horizontal, QStringLiteral("创建时间"));
    tableModel->setHeaderData(tableModel->fieldIndex("station"), Qt::Horizontal, QStringLiteral("充电站ID"));
    tableModel->setHeaderData(tableModel->fieldIndex("username"), Qt::Horizontal, QStringLiteral("操作人"));
}

void StationManageWidget::createView()
{
    ui->tableView->setSortingEnabled(true);
//    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background:lightgray;}");
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setShowGrid(true);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->resizeColumnsToContents();

    ui->tableView->setModel( tableModel );
    ui->tableView->hideColumn(0);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
