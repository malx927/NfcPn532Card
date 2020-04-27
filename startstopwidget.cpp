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
    createModel();
    createView();
    m_card_type = "5a";
    ui->dateEditStopDate->setDate(QDate::currentDate());

}

StartStopWidget::~StartStopWidget()
{
    delete ui;
}

void StartStopWidget::createModel()
{
    tableModel = new QSqlTableModel(this);
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel->setTable("cards");
    tableModel->select();
    qDebug() << tableModel->rowCount();
//    tableModel->removeColumn(0);

    tableModel->setHeaderData(0, Qt::Horizontal, "ID");
    tableModel->setHeaderData(1, Qt::Horizontal, QStringLiteral("卡号"));
    tableModel->setHeaderData(2, Qt::Horizontal, QStringLiteral("类型编号"));
    tableModel->setHeaderData(3, Qt::Horizontal, QStringLiteral("类型名称"));
    tableModel->setHeaderData(4, Qt::Horizontal, QStringLiteral("创建时间"));
    tableModel->setHeaderData(5, Qt::Horizontal, QStringLiteral("充电站ID"));
    tableModel->setHeaderData(6, Qt::Horizontal, QStringLiteral("金额"));
}

void StartStopWidget::createView()
{
    ui->startTableView->setSortingEnabled(true);
    ui->startTableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background:lightgray;}");
    ui->startTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->startTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->startTableView->setShowGrid(true);
    ui->startTableView->setAlternatingRowColors(true);
    ui->startTableView->resizeColumnsToContents();

    ui->startTableView->setModel( tableModel );
    ui->startTableView->hideColumn(0);
    ui->startTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->startTableView->resizeColumnToContents(1);
//    ui->startTableView->resizeColumnToContents(2);
//    ui->startTableView->resizeColumnToContents(4);


//    ui->startTableView->sortByColumn(3, Qt::DescendingOrder);

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
