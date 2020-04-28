#ifndef CORPMANAGEWIDGET_H
#define CORPMANAGEWIDGET_H

#include <QWidget>
class QSqlTableModel;

namespace Ui {
class CorpManageWidget;
}

class CorpManageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CorpManageWidget(QWidget *parent = nullptr);
    ~CorpManageWidget();

private:
    void createModel();
    void createView();

private:
    Ui::CorpManageWidget *ui;
    QString m_card_type;
    QSqlTableModel* tableModel;
};

#endif // CORPMANAGEWIDGET_H
