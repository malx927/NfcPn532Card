#include "dialog.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Dialog w;
//    w.show();
    MainWindow w;
    w.setMinimumHeight(600);
    w.showNormal();

    return a.exec();
}
