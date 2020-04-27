#-------------------------------------------------
#
# Project created by QtCreator 2020-03-01T21:10:48
#
#-------------------------------------------------

QT       += core gui serialport network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NfcPn532Card
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    corpmanagewidget.cpp \
    corpnetworkwidget.cpp \
    corpofflinewidget.cpp \
        main.cpp \
        dialog.cpp \
    mainwindow.cpp \
     nfcpn532api.cpp \
    startstopwidget.cpp \
    stationmanagewidget.cpp \
    stationnetworkwidget.cpp \
    stationofflinewidget.cpp \
    stationsinglewidget.cpp

HEADERS += \
    corpmanagewidget.h \
    corpnetworkwidget.h \
    corpofflinewidget.h \
        dialog.h \
    mainwindow.h \
        nfcpn532api.h \
    startstopwidget.h \
    stationmanagewidget.h \
    stationnetworkwidget.h \
    stationofflinewidget.h \
    stationsinglewidget.h \
    utils.h

FORMS += \
        corpmanagewidget.ui \
        corpnetworkwidget.ui \
        corpofflinewidget.ui \
        dialog.ui \
        startstopwidget.ui \
        stationmanagewidget.ui \
        stationnetworkwidget.ui \
        stationofflinewidget.ui \
        stationsinglewidget.ui
RC_FILE=icon.rc
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

