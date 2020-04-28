#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QDate>
#include "nfcpn532api.h"
class QStackedWidget;
class QActionGroup;
class StartStopWidget;
class CorpNetworkWidget;
class CorpOfflineWidget;
class StationManageWidget;
class StationNetworkWidget;
class StationOfflineWidget;
class StationSingleWidget;
class QPushButton;
class QValidator;
class QSerialPort;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
//    QValidator* validator;
private:
    void createAction();
    void createToolbar();
    void showPanel();
    void addWidget();
    void createSqliteDb();
    void setButtionState(bool flag);
    void insertData(QString type, QString type_name, QDate dTime, QString card=QString(""), QString stationid=QString(""), int money=0, QString device_sn=QString());
public slots:
    void openComm();
    void slot_start_stop();
    void slot_corp_network();
    void slot_corp_offline();
    void slot_station_manage();
    void slot_station_network();
    void slot_station_offline();
    void slot_station_single();

    void slot_start_stop_write(QString cType, QDate date);
    void slot_corp_network_write(QString cType);
    void slot_corp_offline_write(QString cType, int value);
    void slot_station_manage_write(QString cType, QString stationId, QDate date);
    void slot_station_network_write(QString cType, QString stationId);
    void slot_station_offline_write(QString cType, QString stationId, int nMoney);
    void slot_station_single_write(QString cType, QString deviceSN);
    void slot_card_money_clear(QString cType);
    void slot_card_read_money(QString cType);

signals:

private:
    QToolBar *toolBar;
    QActionGroup *actionGroup;
    QAction *startStopAction;
    QAction *corpNetworkAction;
    QAction *corpOfflineAction;
    QAction *stationManageAction;
    QAction *stationNetworkAction;
    QAction *stationOfflineAction;
    QAction *singleDeviceAction;
    QComboBox *comboBox;
    QPushButton* openButton;

    QStackedWidget *stackedWidget;

    StartStopWidget * startStopWidget;
    CorpNetworkWidget * networkWidget;
    CorpOfflineWidget * offlineWidget;

    StationManageWidget * stManageWidget;
    StationNetworkWidget * stNetworkWidget;
    StationOfflineWidget * stOfflineWidget;
    StationSingleWidget * stSingleWidget;

    QSerialPort *serial;
    NfcPn532Api *pn532Api;


};

#endif // MAINWINDOW_H
