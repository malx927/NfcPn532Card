/********************************************************************************
** Form generated from reading UI file 'stationsinglewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATIONSINGLEWIDGET_H
#define UI_STATIONSINGLEWIDGET_H

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

class Ui_StationSingleWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_5;
    QLineEdit *lineEditDeviceSN;
    QPushButton *singeButton;
    QSpacerItem *horizontalSpacer;
    QTableView *singleTableView;

    void setupUi(QWidget *StationSingleWidget)
    {
        if (StationSingleWidget->objectName().isEmpty())
            StationSingleWidget->setObjectName(QString::fromUtf8("StationSingleWidget"));
        StationSingleWidget->resize(697, 430);
        verticalLayout = new QVBoxLayout(StationSingleWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_5 = new QLabel(StationSingleWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout->addWidget(label_5);

        lineEditDeviceSN = new QLineEdit(StationSingleWidget);
        lineEditDeviceSN->setObjectName(QString::fromUtf8("lineEditDeviceSN"));
        lineEditDeviceSN->setMaximumSize(QSize(120, 16777215));
        lineEditDeviceSN->setMaxLength(16);

        horizontalLayout->addWidget(lineEditDeviceSN);

        singeButton = new QPushButton(StationSingleWidget);
        singeButton->setObjectName(QString::fromUtf8("singeButton"));
        singeButton->setMinimumSize(QSize(100, 30));

        horizontalLayout->addWidget(singeButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        singleTableView = new QTableView(StationSingleWidget);
        singleTableView->setObjectName(QString::fromUtf8("singleTableView"));

        verticalLayout->addWidget(singleTableView);


        retranslateUi(StationSingleWidget);

        QMetaObject::connectSlotsByName(StationSingleWidget);
    } // setupUi

    void retranslateUi(QWidget *StationSingleWidget)
    {
        StationSingleWidget->setWindowTitle(QApplication::translate("StationSingleWidget", "Form", nullptr));
        label_5->setText(QApplication::translate("StationSingleWidget", "\345\205\205\347\224\265\346\241\251SN:", nullptr));
        lineEditDeviceSN->setPlaceholderText(QApplication::translate("StationSingleWidget", "\351\225\277\345\272\246\344\270\215\350\203\275\350\266\205\350\277\20716\344\275\215", nullptr));
        singeButton->setText(QApplication::translate("StationSingleWidget", "\345\206\231\345\215\225\346\241\251\345\220\257\345\201\234\345\215\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StationSingleWidget: public Ui_StationSingleWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATIONSINGLEWIDGET_H
