#ifndef STATIONMANAGEWIDGET_H
#define STATIONMANAGEWIDGET_H

#include <QWidget>
#include <QDate>

namespace Ui {
class StationManageWidget;
}

class StationManageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StationManageWidget(QWidget *parent = nullptr);
    ~StationManageWidget();

signals:
    void sig_station_manage_write(QString cType, QString stationId, QDate date);


public slots:
    void setBtnEnable(bool flag);

private slots:
    void on_stManageButton_clicked();

private:
    Ui::StationManageWidget *ui;
    QString m_card_type;
};

#endif // STATIONMANAGEWIDGET_H
