#ifndef STARTSTOPWIDGET_H
#define STARTSTOPWIDGET_H

#include <QWidget>
#include <QDate>

namespace Ui {
class StartStopWidget;
}

class StartStopWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StartStopWidget(QWidget *parent = nullptr);
    ~StartStopWidget();

signals:
    void sig_start_stop_write(QString cType, QDate date);

public slots:
    void setBtnEnable(bool flag);

private slots:
    void on_startStopButton_clicked();

private:
    Ui::StartStopWidget *ui;
    QString m_card_type;
};

#endif // STARTSTOPWIDGET_H
