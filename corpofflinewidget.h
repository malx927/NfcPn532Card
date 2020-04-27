#ifndef CORPOFFLINEWIDGET_H
#define CORPOFFLINEWIDGET_H

#include <QWidget>

namespace Ui {
class CorpOfflineWidget;
}

class CorpOfflineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CorpOfflineWidget(QWidget *parent = nullptr);
    ~CorpOfflineWidget();

signals:
    void sig_corp_offline_write(QString cType, int value);

public slots:
    void setBtnEnable(bool flag);

private slots:
    void on_offlineButton_clicked();

    void on_clearMoneyButton_clicked();

private:
    Ui::CorpOfflineWidget *ui;
    QString m_card_type;
};

#endif // CORPOFFLINEWIDGET_H
