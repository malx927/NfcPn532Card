/********************************************************************************
** Form generated from reading UI file 'corpmanagewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CORPMANAGEWIDGET_H
#define UI_CORPMANAGEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CorpManageWidget
{
public:

    void setupUi(QWidget *CorpManageWidget)
    {
        if (CorpManageWidget->objectName().isEmpty())
            CorpManageWidget->setObjectName(QString::fromUtf8("CorpManageWidget"));
        CorpManageWidget->resize(400, 300);

        retranslateUi(CorpManageWidget);

        QMetaObject::connectSlotsByName(CorpManageWidget);
    } // setupUi

    void retranslateUi(QWidget *CorpManageWidget)
    {
        CorpManageWidget->setWindowTitle(QApplication::translate("CorpManageWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CorpManageWidget: public Ui_CorpManageWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CORPMANAGEWIDGET_H
