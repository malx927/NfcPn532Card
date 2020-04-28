#include "stationofflinewidget.h"
#include "ui_stationofflinewidget.h"
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDebug>

StationOfflineWidget::StationOfflineWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StationOfflineWidget)
{
    ui->setupUi(this);

    m_card_type = "54";

    createModel();
    createView();

}

StationOfflineWidget::~StationOfflineWidget()
{
    delete ui;
}

QSqlTableModel *StationOfflineWidget::getModel()
{
    return tableModel;
}

void StationOfflineWidget::createModel()
{
    tableModel = new QSqlTableModel(this);
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel->setTable("cards");
    tableModel->select();
    QString strWhere = QString("type_id='%1'").arg(m_card_type);
    tableModel->setFilter(strWhere);
    tableModel->setSort(tableModel->fieldIndex("create_time"), Qt::DescendingOrder);

    tableModel->removeColumn(tableModel->fieldIndex("end_date"));
    tableModel->removeColumn(tableModel->fieldIndex("device"));
    tableModel->removeColumn(tableModel->fieldIndex("type_id"));

    tableModel->setHeaderData(tableModel->fieldIndex("id"), Qt::Horizontal, "ID");
    tableModel->setHeaderData(tableModel->fieldIndex("card_num"), Qt::Horizontal, QStringLiteral("卡号"));
    tableModel->setHeaderData(tableModel->fieldIndex("type_id"), Qt::Horizontal, QStringLiteral("类型编号"));
    tableModel->setHeaderData(tableModel->fieldIndex("card_type"), Qt::Horizontal, QStringLiteral("类型名称"));
    tableModel->setHeaderData(tableModel->fieldIndex("station"), Qt::Horizontal, QStringLiteral("充电站ID"));
    tableModel->setHeaderData(tableModel->fieldIndex("money"), Qt::Horizontal, QStringLiteral("金额"));
    tableModel->setHeaderData(tableModel->fieldIndex("create_time"), Qt::Horizontal, QStringLiteral("创建时间"));
    tableModel->setHeaderData(tableModel->fieldIndex("username"), Qt::Horizontal, QStringLiteral("操作人"));
}

void StationOfflineWidget::createView()
{
    ui->stOfflineTableView->setSortingEnabled(true);
//    ui->stOfflineTableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background:lightgray;}");
    ui->stOfflineTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->stOfflineTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->stOfflineTableView->setShowGrid(true);
    ui->stOfflineTableView->setAlternatingRowColors(true);
    ui->stOfflineTableView->resizeColumnsToContents();

    ui->stOfflineTableView->setModel( tableModel );
    ui->stOfflineTableView->hideColumn(0);
    ui->stOfflineTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void StationOfflineWidget::setBtnEnable(bool flag)
{
    ui->stOfflineButton->setEnabled(flag);
    ui->clearMoneyButton->setEnabled(flag);
}

void StationOfflineWidget::on_stOfflineButton_clicked()
{

    QString strStationID = ui->lineEditStationID->text();
    if(strStationID.isEmpty())
    {
        QMessageBox::warning(this, "提示:", "充电站ID不能为空");
        ui->lineEditStationID->setFocus();
        return;
    }

    int money = ui->spinBoxMoney->value();
    if(money == 0)
    {
        QMessageBox::warning(this, "提示:", "充值金额不能为空");
        ui->spinBoxMoney->setFocus();
        return;
    }
    emit sig_station_offline_write(m_card_type, strStationID, money);
}

void StationOfflineWidget::on_clearMoneyButton_clicked()
{

}
