#include "corpofflinewidget.h"
#include "ui_corpofflinewidget.h"
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QDebug>

CorpOfflineWidget::CorpOfflineWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CorpOfflineWidget)
{
    ui->setupUi(this);
    m_card_type = "51";

    createModel();
    createView();
    getTotals();
}

CorpOfflineWidget::~CorpOfflineWidget()
{
    delete ui;
}

QSqlTableModel *CorpOfflineWidget::getModel()
{
    return tableModel;
}

void CorpOfflineWidget::getTotals()
{
    QString sql = QString("select sum(money) from cards where type_id='%1'").arg(m_card_type);
    QSqlQuery query;
    qDebug() << "totals" << sql;
    query.exec(sql);
    int totals = 0;
    if(query.next()){
        totals = query.value(0).toInt();
    }
    qDebug() << "totals" << totals;
    ui->label_money->setText(QString::number(totals));
}

void CorpOfflineWidget::createModel()
{
    tableModel = new QSqlTableModel(this);
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel->setTable("cards");
    tableModel->select();
    QString strWhere = QString("type_id='%1'").arg(m_card_type);
    tableModel->setFilter(strWhere);
    tableModel->setSort(tableModel->fieldIndex("create_time"), Qt::DescendingOrder);

    tableModel->removeColumn(tableModel->fieldIndex("station"));
    tableModel->removeColumn(tableModel->fieldIndex("end_date"));
    tableModel->removeColumn(tableModel->fieldIndex("device"));
    tableModel->removeColumn(tableModel->fieldIndex("type_id"));

    tableModel->setHeaderData(tableModel->fieldIndex("id"), Qt::Horizontal, "ID");
    tableModel->setHeaderData(tableModel->fieldIndex("card_num"), Qt::Horizontal, QStringLiteral("卡号"));
    tableModel->setHeaderData(tableModel->fieldIndex("type_id"), Qt::Horizontal, QStringLiteral("类型编号"));
    tableModel->setHeaderData(tableModel->fieldIndex("card_type"), Qt::Horizontal, QStringLiteral("类型名称"));
    tableModel->setHeaderData(tableModel->fieldIndex("money"), Qt::Horizontal, QStringLiteral("金额"));
    tableModel->setHeaderData(tableModel->fieldIndex("create_time"), Qt::Horizontal, QStringLiteral("创建时间"));
    tableModel->setHeaderData(tableModel->fieldIndex("username"), Qt::Horizontal, QStringLiteral("操作人"));


}

void CorpOfflineWidget::createView()
{
    ui->offlineTableView->setSortingEnabled(true);
//    ui->offlineTableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background:lightgray;}");
    ui->offlineTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->offlineTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->offlineTableView->setShowGrid(true);
    ui->offlineTableView->setAlternatingRowColors(true);
    ui->offlineTableView->resizeColumnsToContents();

    ui->offlineTableView->setModel( tableModel );
    ui->offlineTableView->hideColumn(0);
    ui->offlineTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void CorpOfflineWidget::setBtnEnable(bool flag)
{
    ui->offlineButton->setEnabled(flag);
    ui->clearMoneyButton->setEnabled(flag);

    ui->pushButton->setEnabled(flag);
    ui->readButton->setEnabled(flag);
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
    emit sig_corp_offline_clear(m_card_type);
}

void CorpOfflineWidget::on_pushButton_clicked()
{
    int money = ui->spinBoxMoney->value();
    if(money == 0)
    {
        QMessageBox::warning(this, "提示:", "离线卡金额");
        ui->spinBoxMoney->setFocus();
        return;
    }
    emit sig_corp_offline_recharge(m_card_type, money);
}


void CorpOfflineWidget::on_readButton_clicked()
{
    emit sig_corp_offline_read(m_card_type);
}
