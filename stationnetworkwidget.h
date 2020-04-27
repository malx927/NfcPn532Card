#ifndef STATIONNETWORKWIDGET_H
#define STATIONNETWORKWIDGET_H

#include <QWidget>

namespace Ui {
class StationNetworkWidget;
}

class StationNetworkWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StationNetworkWidget(QWidget *parent = nullptr);
    ~StationNetworkWidget();

signals:
    void sig_station_network_write(QString cType, QString stationId);

public slots:
    void setBtnEnable(bool flag);

private slots:
    void on_stNetworkButton_clicked();

private:
    Ui::StationNetworkWidget *ui;
    QString m_card_type;
};

#endif // STATIONNETWORKWIDGET_H