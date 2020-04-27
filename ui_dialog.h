/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QComboBox *comboBox;
    QPushButton *btnOpenComm;
    QLabel *label_comm_state;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioStartStop;
    QRadioButton *radioCorpNetwork;
    QRadioButton *radioCorpOffline;
    QRadioButton *radioStationManage;
    QRadioButton *radioStationNetwork;
    QRadioButton *radioStationOffline;
    QRadioButton *radioSingleDevice;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditStationID;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDateEdit *dateEditStopDate;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpinBox *spinBoxMoney;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QLineEdit *lineEditDeviceSN;
    QSpacerItem *verticalSpacer;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *btnWrite;
    QPushButton *btnClose;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(1045, 568);
        verticalLayout_3 = new QVBoxLayout(Dialog);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(20, 10, -1, 10);
        label_6 = new QLabel(Dialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(label_6);

        comboBox = new QComboBox(Dialog);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMinimumSize(QSize(100, 0));

        horizontalLayout_7->addWidget(comboBox);

        btnOpenComm = new QPushButton(Dialog);
        btnOpenComm->setObjectName(QString::fromUtf8("btnOpenComm"));

        horizontalLayout_7->addWidget(btnOpenComm);

        label_comm_state = new QLabel(Dialog);
        label_comm_state->setObjectName(QString::fromUtf8("label_comm_state"));
        label_comm_state->setMinimumSize(QSize(200, 0));

        horizontalLayout_7->addWidget(label_comm_state);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_7);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(15);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(30, 20, 20, 20);
        radioStartStop = new QRadioButton(groupBox);
        radioStartStop->setObjectName(QString::fromUtf8("radioStartStop"));

        verticalLayout->addWidget(radioStartStop);

        radioCorpNetwork = new QRadioButton(groupBox);
        radioCorpNetwork->setObjectName(QString::fromUtf8("radioCorpNetwork"));

        verticalLayout->addWidget(radioCorpNetwork);

        radioCorpOffline = new QRadioButton(groupBox);
        radioCorpOffline->setObjectName(QString::fromUtf8("radioCorpOffline"));

        verticalLayout->addWidget(radioCorpOffline);

        radioStationManage = new QRadioButton(groupBox);
        radioStationManage->setObjectName(QString::fromUtf8("radioStationManage"));

        verticalLayout->addWidget(radioStationManage);

        radioStationNetwork = new QRadioButton(groupBox);
        radioStationNetwork->setObjectName(QString::fromUtf8("radioStationNetwork"));

        verticalLayout->addWidget(radioStationNetwork);

        radioStationOffline = new QRadioButton(groupBox);
        radioStationOffline->setObjectName(QString::fromUtf8("radioStationOffline"));

        verticalLayout->addWidget(radioStationOffline);

        radioSingleDevice = new QRadioButton(groupBox);
        radioSingleDevice->setObjectName(QString::fromUtf8("radioSingleDevice"));

        verticalLayout->addWidget(radioSingleDevice);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout_5->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Dialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(20);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(20, 20, 20, 20);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        lineEditStationID = new QLineEdit(groupBox_2);
        lineEditStationID->setObjectName(QString::fromUtf8("lineEditStationID"));
        lineEditStationID->setMaxLength(10);

        horizontalLayout->addWidget(lineEditStationID);

        horizontalLayout->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        dateEditStopDate = new QDateEdit(groupBox_2);
        dateEditStopDate->setObjectName(QString::fromUtf8("dateEditStopDate"));
        dateEditStopDate->setCurrentSection(QDateTimeEdit::YearSection);
        dateEditStopDate->setCalendarPopup(true);

        horizontalLayout_2->addWidget(dateEditStopDate);

        horizontalLayout_2->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        spinBoxMoney = new QSpinBox(groupBox_2);
        spinBoxMoney->setObjectName(QString::fromUtf8("spinBoxMoney"));
        spinBoxMoney->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxMoney->setMaximum(999999);

        horizontalLayout_3->addWidget(spinBoxMoney);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_3->addWidget(label_4);

        horizontalLayout_3->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_4->addWidget(label_5);

        lineEditDeviceSN = new QLineEdit(groupBox_2);
        lineEditDeviceSN->setObjectName(QString::fromUtf8("lineEditDeviceSN"));
        lineEditDeviceSN->setMaxLength(16);

        horizontalLayout_4->addWidget(lineEditDeviceSN);

        horizontalLayout_4->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_5->addWidget(groupBox_2);

        tableView = new QTableView(Dialog);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        horizontalLayout_5->addWidget(tableView);

        horizontalLayout_5->setStretch(2, 1);

        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(60);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_6->setContentsMargins(20, 20, 20, 20);
        btnWrite = new QPushButton(Dialog);
        btnWrite->setObjectName(QString::fromUtf8("btnWrite"));

        horizontalLayout_6->addWidget(btnWrite);

        btnClose = new QPushButton(Dialog);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));

        horizontalLayout_6->addWidget(btnClose);


        verticalLayout_3->addLayout(horizontalLayout_6);


        retranslateUi(Dialog);

        btnClose->setDefault(true);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "\344\272\232\347\224\265\346\226\260\350\203\275\346\272\220\345\206\231\345\215\241\347\250\213\345\272\217-NFC_Pn532", nullptr));
        label_6->setText(QApplication::translate("Dialog", "\344\270\262\345\217\243\345\217\267:", nullptr));
        btnOpenComm->setText(QApplication::translate("Dialog", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        label_comm_state->setText(QString());
        groupBox->setTitle(QApplication::translate("Dialog", "\345\215\241\347\261\273\345\236\213", nullptr));
        radioStartStop->setText(QApplication::translate("Dialog", "\350\265\267\345\201\234\345\215\241", nullptr));
        radioCorpNetwork->setText(QApplication::translate("Dialog", "\345\205\254\345\217\270\347\275\221\347\273\234\345\215\241", nullptr));
        radioCorpOffline->setText(QApplication::translate("Dialog", "\345\205\254\345\217\270\347\246\273\347\272\277\345\215\241", nullptr));
        radioStationManage->setText(QApplication::translate("Dialog", "\345\234\272\347\253\231\347\256\241\347\220\206\345\215\241", nullptr));
        radioStationNetwork->setText(QApplication::translate("Dialog", "\345\234\272\347\253\231\347\275\221\347\273\234\345\215\241", nullptr));
        radioStationOffline->setText(QApplication::translate("Dialog", "\345\234\272\347\253\231\347\246\273\347\272\277\345\215\241", nullptr));
        radioSingleDevice->setText(QApplication::translate("Dialog", "\345\215\225\346\241\251\345\220\257\345\201\234\345\215\241", nullptr));
        groupBox_2->setTitle(QApplication::translate("Dialog", "\345\215\241\345\217\202\346\225\260", nullptr));
        label->setText(QApplication::translate("Dialog", "\345\205\205\347\224\265\347\253\231ID:", nullptr));
        lineEditStationID->setPlaceholderText(QApplication::translate("Dialog", "\351\225\277\345\272\246\344\270\215\350\203\275\350\266\205\350\277\20710\344\275\215", nullptr));
        label_2->setText(QApplication::translate("Dialog", "\346\234\211\346\225\210\346\234\237\346\210\252\346\255\242\346\227\245\346\234\237\357\274\232", nullptr));
        dateEditStopDate->setDisplayFormat(QApplication::translate("Dialog", "yyyy-MM-dd", nullptr));
        label_3->setText(QApplication::translate("Dialog", "\345\205\205\345\200\274\351\207\221\351\242\235:", nullptr));
        label_4->setText(QApplication::translate("Dialog", "\345\205\203", nullptr));
        label_5->setText(QApplication::translate("Dialog", "\345\205\205\347\224\265\346\241\251SN:", nullptr));
        lineEditDeviceSN->setPlaceholderText(QApplication::translate("Dialog", "\351\225\277\345\272\246\344\270\215\350\203\275\350\266\205\350\277\20716\344\275\215", nullptr));
        btnWrite->setText(QApplication::translate("Dialog", "\345\206\231\345\215\241", nullptr));
        btnClose->setText(QApplication::translate("Dialog", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
