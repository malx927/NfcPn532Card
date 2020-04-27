#ifndef CORPMANAGEWIDGET_H
#define CORPMANAGEWIDGET_H

#include <QWidget>

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
    Ui::CorpManageWidget *ui;
    QString m_card_type;
};

#endif // CORPMANAGEWIDGET_H
