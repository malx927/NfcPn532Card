#include "stationnetworkwidget.h"
#include "ui_stationnetworkwidget.h"
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDebug>

StationNetworkWidget::StationNetworkWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StationNetworkWidget)
{
    ui->setupUi(this);

    m_card_type = "53";

    createModel();
    createView();

}

StationNetworkWidget::~StationNetworkWidget()
{
    delete ui;
}

QSqlTableModel *StationNetworkWidget::getModel()
{
    return  tableModel;
}

void StationNetworkWidget::createModel()
{
    tableModel = new QSqlTableModel(this);
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel->setTable("cards");
    tableModel->select();
    QString strWhere = QString("type_id='%1'").arg(m_card_type);
    tableModel->setFilter(strWhere);

    tableModel->setSort(tableModel->fieldIndex("create_time"), Qt::DescendingOrder);
//    tableModel->removeColumn(tableModel->fieldIndex("card_num"));
    tableModel->removeColumn(tableModel->fieldIndex("end_date"));
    tableModel->removeColumn(tableModel->fieldIndex("money"));
    tableModel->removeColumn(tableModel->fieldIndex("device"));
    tableModel->removeColumn(tableModel->fieldIndex("type_id"));

    tableModel->setHeaderData(tableModel->fieldIndex("id"), Qt::Horizontal, "ID");
    tableModel->setHeaderData(tableModel->fieldIndex("card_num"), Qt::Horizontal, QStringLiteral("卡号"));
    tableModel->setHeaderData(tableModel->fieldIndex("type_id"), Qt::Horizontal, QStringLiteral("类型编号"));
    tableModel->setHeaderData(tableModel->fieldIndex("card_type"), Qt::Horizontal, QStringLiteral("类型名称"));
    tableModel->setHeaderData(tableModel->fieldIndex("create_time"), Qt::Horizontal, QStringLiteral("创建时间"));
    tableModel->setHeaderData(tableModel->fieldIndex("station"), Qt::Horizontal, QStringLiteral("充电站ID"));
    tableModel->setHeaderData(tableModel->fieldIndex("username"), Qt::Horizontal, QStringLiteral("操作人"));
}

void StationNetworkWidget::createView()
{
    ui->stNetworkTableView->setSortingEnabled(true);
//    ui->stNetworkTableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background:lightgray;}");
    ui->stNetworkTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->stNetworkTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->stNetworkTableView->setShowGrid(true);
    ui->stNetworkTableView->setAlternatingRowColors(true);
    ui->stNetworkTableView->resizeColumnsToContents();

    ui->stNetworkTableView->setModel( tableModel );
    ui->stNetworkTableView->hideColumn(0);
    ui->stNetworkTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void StationNetworkWidget::setBtnEnable(bool flag)
{
    ui->stNetworkButton->setEnabled(flag);
}

void StationNetworkWidget::on_stNetworkButton_clicked()
{

    QString strStationID = ui->lineEditStationID->text();
    if(strStationID.isEmpty())
    {
        QMessageBox::warning(this, "提示:", "充电站ID不能为空");
        ui->lineEditStationID->setFocus();
        return;
    }
    emit sig_station_network_write(m_card_type, strStationID);
}
