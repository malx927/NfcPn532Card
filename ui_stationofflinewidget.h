/********************************************************************************
** Form generated from reading UI file 'stationofflinewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATIONOFFLINEWIDGET_H
#define UI_STATIONOFFLINEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StationOfflineWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditStationID;
    QLabel *label_3;
    QSpinBox *spinBoxMoney;
    QLabel *label_4;
    QPushButton *stOfflineButton;
    QPushButton *rechargeButton;
    QPushButton *clearMoneyButton;
    QPushButton *readButton;
    QSpacerItem *horizontalSpacer;
    QTableView *stOfflineTableView;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_5;
    QLabel *label_money;
    QLabel *label_6;

    void setupUi(QWidget *StationOfflineWidget)
    {
        if (StationOfflineWidget->objectName().isEmpty())
            StationOfflineWidget->setObjectName(QString::fromUtf8("StationOfflineWidget"));
        StationOfflineWidget->resize(890, 561);
        verticalLayout = new QVBoxLayout(StationOfflineWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(StationOfflineWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        lineEditStationID = new QLineEdit(StationOfflineWidget);
        lineEditStationID->setObjectName(QString::fromUtf8("lineEditStationID"));
        lineEditStationID->setMinimumSize(QSize(150, 0));
        lineEditStationID->setMaximumSize(QSize(120, 16777215));
        lineEditStationID->setMaxLength(10);

        horizontalLayout->addWidget(lineEditStationID);

        label_3 = new QLabel(StationOfflineWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        spinBoxMoney = new QSpinBox(StationOfflineWidget);
        spinBoxMoney->setObjectName(QString::fromUtf8("spinBoxMoney"));
        spinBoxMoney->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxMoney->setMaximum(999999);

        horizontalLayout->addWidget(spinBoxMoney);

        label_4 = new QLabel(StationOfflineWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);

        stOfflineButton = new QPushButton(StationOfflineWidget);
        stOfflineButton->setObjectName(QString::fromUtf8("stOfflineButton"));
        stOfflineButton->setMinimumSize(QSize(100, 30));

        horizontalLayout->addWidget(stOfflineButton);

        rechargeButton = new QPushButton(StationOfflineWidget);
        rechargeButton->setObjectName(QString::fromUtf8("rechargeButton"));
        rechargeButton->setMinimumSize(QSize(100, 30));

        horizontalLayout->addWidget(rechargeButton);

        clearMoneyButton = new QPushButton(StationOfflineWidget);
        clearMoneyButton->setObjectName(QString::fromUtf8("clearMoneyButton"));
        clearMoneyButton->setMinimumSize(QSize(100, 30));

        horizontalLayout->addWidget(clearMoneyButton);

        readButton = new QPushButton(StationOfflineWidget);
        readButton->setObjectName(QString::fromUtf8("readButton"));
        readButton->setMinimumSize(QSize(100, 30));

        horizontalLayout->addWidget(readButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        stOfflineTableView = new QTableView(StationOfflineWidget);
        stOfflineTableView->setObjectName(QString::fromUtf8("stOfflineTableView"));

        verticalLayout->addWidget(stOfflineTableView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label_5 = new QLabel(StationOfflineWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        label_money = new QLabel(StationOfflineWidget);
        label_money->setObjectName(QString::fromUtf8("label_money"));
        label_money->setMinimumSize(QSize(50, 0));
        label_money->setStyleSheet(QString::fromUtf8("color:rgb(0, 0, 255)"));
        label_money->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_money);

        label_6 = new QLabel(StationOfflineWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(StationOfflineWidget);

        QMetaObject::connectSlotsByName(StationOfflineWidget);
    } // setupUi

    void retranslateUi(QWidget *StationOfflineWidget)
    {
        StationOfflineWidget->setWindowTitle(QApplication::translate("StationOfflineWidget", "Form", nullptr));
        label->setText(QApplication::translate("StationOfflineWidget", "\345\205\205\347\224\265\347\253\231ID:", nullptr));
        lineEditStationID->setPlaceholderText(QApplication::translate("StationOfflineWidget", "\351\225\277\345\272\246\344\270\215\350\203\275\350\266\205\350\277\20710\344\275\215", nullptr));
        label_3->setText(QApplication::translate("StationOfflineWidget", "\345\205\205\345\200\274\351\207\221\351\242\235:", nullptr));
        label_4->setText(QApplication::translate("StationOfflineWidget", "\345\205\203", nullptr));
        stOfflineButton->setText(QApplication::translate("StationOfflineWidget", "\345\206\231\347\253\231\345\234\272\347\246\273\347\272\277\345\215\241", nullptr));
        rechargeButton->setText(QApplication::translate("StationOfflineWidget", "\345\215\241\345\205\205\345\200\274", nullptr));
        clearMoneyButton->setText(QApplication::translate("StationOfflineWidget", "\346\270\205\347\251\272\351\207\221\351\242\235", nullptr));
        readButton->setText(QApplication::translate("StationOfflineWidget", "\350\257\273\345\217\226\351\207\221\351\242\235", nullptr));
        label_5->setText(QApplication::translate("StationOfflineWidget", "\351\207\221\351\242\235\345\220\210\350\256\241:", nullptr));
        label_money->setText(QString());
        label_6->setText(QApplication::translate("StationOfflineWidget", "\345\205\203", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StationOfflineWidget: public Ui_StationOfflineWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATIONOFFLINEWIDGET_H
