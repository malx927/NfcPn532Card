#ifndef STARTSTOPWIDGET_H
#define STARTSTOPWIDGET_H

#include <QWidget>
#include <QDate>
class QSqlTableModel;

namespace Ui {
class StartStopWidget;
}

class StartStopWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StartStopWidget(QWidget *parent = nullptr);
    ~StartStopWidget();
    QSqlTableModel* getModel();

signals:
    void sig_start_stop_write(QString cType, QDate date);
private:
    void createModel();
    void createView();

public slots:
    void setBtnEnable(bool flag);

private slots:
    void on_startStopButton_clicked();

private:
    Ui::StartStopWidget *ui;
    QString m_card_type;
    QSqlTableModel* tableModel;
};

#endif // STARTSTOPWIDGET_H
