#ifndef CORPNETWORKWIDGET_H
#define CORPNETWORKWIDGET_H

#include <QWidget>

namespace Ui {
class CorpNetworkWidget;
}

class CorpNetworkWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CorpNetworkWidget(QWidget *parent = nullptr);
    ~CorpNetworkWidget();

signals:
    void sig_corp_network_write(QString cType);

public slots:
    void setBtnEnable(bool flag);

private slots:
    void on_corpNetButton_clicked();

private:
    Ui::CorpNetworkWidget *ui;
    QString m_card_type;
};

#endif // CORPNETWORKWIDGET_H
