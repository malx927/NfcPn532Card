/********************************************************************************
** Form generated from reading UI file 'startstopwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTSTOPWIDGET_H
#define UI_STARTSTOPWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartStopWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QDateEdit *dateEditStopDate;
    QPushButton *startStopButton;
    QSpacerItem *horizontalSpacer;
    QTableView *startTableView;

    void setupUi(QWidget *StartStopWidget)
    {
        if (StartStopWidget->objectName().isEmpty())
            StartStopWidget->setObjectName(QString::fromUtf8("StartStopWidget"));
        StartStopWidget->resize(898, 612);
        verticalLayout = new QVBoxLayout(StartStopWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(StartStopWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        dateEditStopDate = new QDateEdit(StartStopWidget);
        dateEditStopDate->setObjectName(QString::fromUtf8("dateEditStopDate"));
        dateEditStopDate->setCurrentSection(QDateTimeEdit::YearSection);
        dateEditStopDate->setCalendarPopup(true);

        horizontalLayout->addWidget(dateEditStopDate);

        startStopButton = new QPushButton(StartStopWidget);
        startStopButton->setObjectName(QString::fromUtf8("startStopButton"));
        startStopButton->setMinimumSize(QSize(100, 30));

        horizontalLayout->addWidget(startStopButton);


        horizontalLayout_2->addLayout(horizontalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        startTableView = new QTableView(StartStopWidget);
        startTableView->setObjectName(QString::fromUtf8("startTableView"));

        verticalLayout->addWidget(startTableView);


        retranslateUi(StartStopWidget);

        QMetaObject::connectSlotsByName(StartStopWidget);
    } // setupUi

    void retranslateUi(QWidget *StartStopWidget)
    {
        StartStopWidget->setWindowTitle(QApplication::translate("StartStopWidget", "Form", nullptr));
        label_2->setText(QApplication::translate("StartStopWidget", "\346\234\211\346\225\210\346\234\237\346\210\252\346\255\242\346\227\245\346\234\237\357\274\232", nullptr));
        dateEditStopDate->setDisplayFormat(QApplication::translate("StartStopWidget", "yyyy-MM-dd", nullptr));
        startStopButton->setText(QApplication::translate("StartStopWidget", "\345\206\231\345\220\257\345\201\234\345\215\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartStopWidget: public Ui_StartStopWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTSTOPWIDGET_H
