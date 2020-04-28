#ifndef STATIONOFFLINEWIDGET_H
#define STATIONOFFLINEWIDGET_H

#include <QWidget>
class QSqlTableModel;

namespace Ui {
class StationOfflineWidget;
}

class StationOfflineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StationOfflineWidget(QWidget *parent = nullptr);
    ~StationOfflineWidget();
    QSqlTableModel* getModel();
    void getTotals();
private:
    void createModel();
    void createView();

signals:
    void sig_station_offline_write(QString cType, QString stationId, int nMoney);
    void sig_corp_offline_read(QString cType);
    void sig_corp_offline_clear(QString cType);
    void sig_corp_offline_recharge(QString cType, int money);

public slots:
    void setBtnEnable(bool flag);

private slots:
    void on_stOfflineButton_clicked();

    void on_clearMoneyButton_clicked();

    void on_rechargeButton_clicked();

    void on_readButton_clicked();

private:
    Ui::StationOfflineWidget *ui;
    QString m_card_type;
    QSqlTableModel* tableModel;
};

#endif // STATIONOFFLINEWIDGET_H
