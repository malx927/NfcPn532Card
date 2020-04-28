#ifndef CORPOFFLINEWIDGET_H
#define CORPOFFLINEWIDGET_H

#include <QWidget>
class QSqlTableModel;

namespace Ui {
class CorpOfflineWidget;
}

class CorpOfflineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CorpOfflineWidget(QWidget *parent = nullptr);
    ~CorpOfflineWidget();

    QSqlTableModel* getModel();
    void getTotals();

private:
    void createModel();
    void createView();

signals:
    void sig_corp_offline_write(QString cType, int value);

public slots:
    void setBtnEnable(bool flag);

private slots:
    void on_offlineButton_clicked();

    void on_clearMoneyButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::CorpOfflineWidget *ui;
    QString m_card_type;
    QSqlTableModel* tableModel;
};

#endif // CORPOFFLINEWIDGET_H
