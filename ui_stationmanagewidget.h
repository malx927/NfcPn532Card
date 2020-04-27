/********************************************************************************
** Form generated from reading UI file 'stationmanagewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATIONMANAGEWIDGET_H
#define UI_STATIONMANAGEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
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

class Ui_StationManageWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditStationID;
    QLabel *label_2;
    QDateEdit *dateEditStopDate;
    QPushButton *stManageButton;
    QSpacerItem *horizontalSpacer;
    QTableView *tableView;

    void setupUi(QWidget *StationManageWidget)
    {
        if (StationManageWidget->objectName().isEmpty())
            StationManageWidget->setObjectName(QString::fromUtf8("StationManageWidget"));
        StationManageWidget->resize(831, 588);
        verticalLayout = new QVBoxLayout(StationManageWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(StationManageWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        lineEditStationID = new QLineEdit(StationManageWidget);
        lineEditStationID->setObjectName(QString::fromUtf8("lineEditStationID"));
        lineEditStationID->setMinimumSize(QSize(60, 0));
        lineEditStationID->setMaximumSize(QSize(120, 16777215));
        lineEditStationID->setMaxLength(10);

        horizontalLayout->addWidget(lineEditStationID);

        label_2 = new QLabel(StationManageWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        dateEditStopDate = new QDateEdit(StationManageWidget);
        dateEditStopDate->setObjectName(QString::fromUtf8("dateEditStopDate"));
        dateEditStopDate->setCurrentSection(QDateTimeEdit::YearSection);
        dateEditStopDate->setCalendarPopup(true);

        horizontalLayout->addWidget(dateEditStopDate);

        stManageButton = new QPushButton(StationManageWidget);
        stManageButton->setObjectName(QString::fromUtf8("stManageButton"));
        stManageButton->setMinimumSize(QSize(100, 30));

        horizontalLayout->addWidget(stManageButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(StationManageWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);


        retranslateUi(StationManageWidget);

        QMetaObject::connectSlotsByName(StationManageWidget);
    } // setupUi

    void retranslateUi(QWidget *StationManageWidget)
    {
        StationManageWidget->setWindowTitle(QApplication::translate("StationManageWidget", "Form", nullptr));
        label->setText(QApplication::translate("StationManageWidget", "\345\205\205\347\224\265\347\253\231ID:", nullptr));
        lineEditStationID->setPlaceholderText(QApplication::translate("StationManageWidget", "\351\225\277\345\272\246\344\270\215\350\203\275\350\266\205\350\277\20710\344\275\215", nullptr));
        label_2->setText(QApplication::translate("StationManageWidget", "\346\234\211\346\225\210\346\234\237\346\210\252\346\255\242\346\227\245\346\234\237\357\274\232", nullptr));
        dateEditStopDate->setDisplayFormat(QApplication::translate("StationManageWidget", "yyyy-MM-dd", nullptr));
        stManageButton->setText(QApplication::translate("StationManageWidget", "\347\253\231\345\234\272\347\256\241\347\220\206\345\215\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StationManageWidget: public Ui_StationManageWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATIONMANAGEWIDGET_H
