/********************************************************************************
** Form generated from reading UI file 'stationnetworkwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATIONNETWORKWIDGET_H
#define UI_STATIONNETWORKWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StationNetworkWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditStationID;
    QPushButton *stNetworkButton;
    QSpacerItem *horizontalSpacer;
    QTableView *stNetworkTableView;

    void setupUi(QWidget *StationNetworkWidget)
    {
        if (StationNetworkWidget->objectName().isEmpty())
            StationNetworkWidget->setObjectName(QString::fromUtf8("StationNetworkWidget"));
        StationNetworkWidget->resize(806, 541);
        verticalLayout = new QVBoxLayout(StationNetworkWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(StationNetworkWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        lineEditStationID = new QLineEdit(StationNetworkWidget);
        lineEditStationID->setObjectName(QString::fromUtf8("lineEditStationID"));
        lineEditStationID->setMaximumSize(QSize(120, 16777215));
        lineEditStationID->setMaxLength(10);

        horizontalLayout->addWidget(lineEditStationID);

        stNetworkButton = new QPushButton(StationNetworkWidget);
        stNetworkButton->setObjectName(QString::fromUtf8("stNetworkButton"));
        stNetworkButton->setMinimumSize(QSize(100, 30));

        horizontalLayout->addWidget(stNetworkButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        stNetworkTableView = new QTableView(StationNetworkWidget);
        stNetworkTableView->setObjectName(QString::fromUtf8("stNetworkTableView"));

        verticalLayout->addWidget(stNetworkTableView);


        retranslateUi(StationNetworkWidget);

        QMetaObject::connectSlotsByName(StationNetworkWidget);
    } // setupUi

    void retranslateUi(QWidget *StationNetworkWidget)
    {
        StationNetworkWidget->setWindowTitle(QApplication::translate("StationNetworkWidget", "Form", nullptr));
        label->setText(QApplication::translate("StationNetworkWidget", "\345\205\205\347\224\265\347\253\231ID:", nullptr));
        lineEditStationID->setPlaceholderText(QApplication::translate("StationNetworkWidget", "\351\225\277\345\272\246\344\270\215\350\203\275\350\266\205\350\277\20710\344\275\215", nullptr));
        stNetworkButton->setText(QApplication::translate("StationNetworkWidget", "\345\206\231\347\253\231\345\234\272\347\275\221\347\273\234\345\215\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StationNetworkWidget: public Ui_StationNetworkWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATIONNETWORKWIDGET_H
