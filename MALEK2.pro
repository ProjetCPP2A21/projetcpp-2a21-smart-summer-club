QT       += core gui sql
QT += sql
QT += core gui sql charts
QT += charts sql
QT += printsupport
QT += widgets printsupport
QT += charts
QT += network
QT += serialport




QT       += core gui sql
QT += sql
QT += core
QT += charts
QT += core gui widgets sql charts
QT += core gui network widgets

CONFIG += c++17

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


SOURCES += qrcodegen.cpp \
    arduino.cpp \
    sms.cpp
HEADERS += qrcodegen.hpp \
    arduino.h \
    sms.h



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    apprenant.cpp \
    calendardialog.cpp \
    connection.cpp \
    employe.cpp \
    equipement.cpp \
    formateurs.cpp \
    formation2.cpp \
    interface_formateur.cpp \
    main.cpp \
    mainwindow.cpp \
    sendgridclient.cpp \
    service.cpp \
    statistic.cpp \
    statisticsdialog.cpp

HEADERS += \
    apprenant.h \
    calendardialog.h \
    connection.h \
    employe.h \
    equipement.h \
    formateurs.h \
    formation2.h \
    interface_formateur.h \
    mainwindow.h \
    sendgridclient.h \
    service.h \
    statistic.h \
    statisticsdialog.h

FORMS += \
    interface_formateur.ui \
    mainwindow.ui \
    statistic.ui \
    statisticsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

DISTFILES += \
    Untitled-1.png
