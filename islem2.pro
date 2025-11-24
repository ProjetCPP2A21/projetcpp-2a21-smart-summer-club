QT       += core gui network
QT+= sql
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    connection.cpp \
    formation2.cpp \
    main.cpp \
    formation.cpp \
    statistic.cpp \
    calendardialog.cpp \
    sendgridclient.cpp

HEADERS += \
    arduino.h \
    connection.h \
    formation.h \
    formation2.h \
    statistic.h \
    calendardialog.h \
    sendgridclient.h

FORMS += \
    formation.ui \
    statistic.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressource.qrc
