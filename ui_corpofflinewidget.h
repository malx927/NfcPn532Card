/********************************************************************************
** Form generated from reading UI file 'corpofflinewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CORPOFFLINEWIDGET_H
#define UI_CORPOFFLINEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CorpOfflineWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSpinBox *spinBoxMoney;
    QLabel *label_4;
    QPushButton *offlineButton;
    QPushButton *clearMoneyButton;
    QSpacerItem *horizontalSpacer;
    QTableView *offlineTableView;

    void setupUi(QWidget *CorpOfflineWidget)
    {
        if (CorpOfflineWidget->objectName().isEmpty())
            CorpOfflineWidget->setObjectName(QString::fromUtf8("CorpOfflineWidget"));
        CorpOfflineWidget->resize(626, 448);
        verticalLayout = new QVBoxLayout(CorpOfflineWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(CorpOfflineWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        spinBoxMoney = new QSpinBox(CorpOfflineWidget);
        spinBoxMoney->setObjectName(QString::fromUtf8("spinBoxMoney"));
        spinBoxMoney->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxMoney->setMaximum(999999);

        horizontalLayout->addWidget(spinBoxMoney);

        label_4 = new QLabel(CorpOfflineWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);

        offlineButton = new QPushButton(CorpOfflineWidget);
        offlineButton->setObjectName(QString::fromUtf8("offlineButton"));
        offlineButton->setMinimumSize(QSize(100, 30));

        horizontalLayout->addWidget(offlineButton);

        clearMoneyButton = new QPushButton(CorpOfflineWidget);
        clearMoneyButton->setObjectName(QString::fromUtf8("clearMoneyButton"));
        clearMoneyButton->setMinimumSize(QSize(100, 30));

        horizontalLayout->addWidget(clearMoneyButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        offlineTableView = new QTableView(CorpOfflineWidget);
        offlineTableView->setObjectName(QString::fromUtf8("offlineTableView"));

        verticalLayout->addWidget(offlineTableView);


        retranslateUi(CorpOfflineWidget);

        QMetaObject::connectSlotsByName(CorpOfflineWidget);
    } // setupUi

    void retranslateUi(QWidget *CorpOfflineWidget)
    {
        CorpOfflineWidget->setWindowTitle(QApplication::translate("CorpOfflineWidget", "Form", nullptr));
        label_3->setText(QApplication::translate("CorpOfflineWidget", "\345\205\205\345\200\274\351\207\221\351\242\235:", nullptr));
        label_4->setText(QApplication::translate("CorpOfflineWidget", "\345\205\203", nullptr));
        offlineButton->setText(QApplication::translate("CorpOfflineWidget", "\345\206\231\345\205\254\345\217\270\347\246\273\347\272\277\345\215\241", nullptr));
        clearMoneyButton->setText(QApplication::translate("CorpOfflineWidget", "\346\270\205\347\251\272\351\207\221\351\242\235", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CorpOfflineWidget: public Ui_CorpOfflineWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CORPOFFLINEWIDGET_H