#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSerialPort>
#include "nfcpn532api.h"

class QSqlTableModel;
class QTableView;
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_btnOpenComm_clicked();
    void readData();
    void handleError(QSerialPort::SerialPortError error);

    void on_radioStartStop_toggled(bool checked);

    void on_radioCorpNetwork_toggled(bool checked);

    void on_radioCorpOffline_toggled(bool checked);

    void on_radioStationManage_toggled(bool checked);

    void on_radioStationNetwork_toggled(bool checked);

    void on_radioStationOffline_toggled(bool checked);

    void on_radioSingleDevice_toggled(bool checked);

    void on_btnClose_clicked();

    void on_btnWrite_clicked();

private:
    void setState();
    bool createSqliteDb();
    void createModel();
    void createView();
    void insertData(QString card, QString type, QDateTime dTime, QString stationid = QString());
private:
    Ui::Dialog *ui;
    QSerialPort *serial;
    QString m_card_type;
    NfcPn532Api *pn532Api;
    QSqlTableModel* tableModel;


};

#endif // DIALOG_H
