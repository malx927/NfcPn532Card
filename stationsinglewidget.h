#ifndef STATIONSINGLEWIDGET_H
#define STATIONSINGLEWIDGET_H

#include <QWidget>
class QSqlTableModel;

namespace Ui {
class StationSingleWidget;
}

class StationSingleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StationSingleWidget(QWidget *parent = nullptr);
    ~StationSingleWidget();

signals:
    void sig_station_single_write(QString cType, QString deviceSN);

public slots:
    void setBtnEnable(bool flag);

private slots:
    void on_singeButton_clicked();

private:
    Ui::StationSingleWidget *ui;
    QString m_card_type;
    QSqlTableModel* tableModel;
};

#endif // STATIONSINGLEWIDGET_H
