/********************************************************************************
** Form generated from reading UI file 'corpnetworkwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CORPNETWORKWIDGET_H
#define UI_CORPNETWORKWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CorpNetworkWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *corpNetButton;
    QSpacerItem *horizontalSpacer;
    QTableView *networkTableView;

    void setupUi(QWidget *CorpNetworkWidget)
    {
        if (CorpNetworkWidget->objectName().isEmpty())
            CorpNetworkWidget->setObjectName(QString::fromUtf8("CorpNetworkWidget"));
        CorpNetworkWidget->resize(739, 558);
        verticalLayout = new QVBoxLayout(CorpNetworkWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, -1, -1, -1);
        horizontalSpacer_2 = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        corpNetButton = new QPushButton(CorpNetworkWidget);
        corpNetButton->setObjectName(QString::fromUtf8("corpNetButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(corpNetButton->sizePolicy().hasHeightForWidth());
        corpNetButton->setSizePolicy(sizePolicy);
        corpNetButton->setMinimumSize(QSize(100, 30));

        horizontalLayout->addWidget(corpNetButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        networkTableView = new QTableView(CorpNetworkWidget);
        networkTableView->setObjectName(QString::fromUtf8("networkTableView"));

        verticalLayout->addWidget(networkTableView);


        retranslateUi(CorpNetworkWidget);

        QMetaObject::connectSlotsByName(CorpNetworkWidget);
    } // setupUi

    void retranslateUi(QWidget *CorpNetworkWidget)
    {
        CorpNetworkWidget->setWindowTitle(QApplication::translate("CorpNetworkWidget", "Form", nullptr));
        corpNetButton->setText(QApplication::translate("CorpNetworkWidget", "\345\206\231\345\205\254\345\217\270\347\275\221\347\273\234\345\215\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CorpNetworkWidget: public Ui_CorpNetworkWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CORPNETWORKWIDGET_H
