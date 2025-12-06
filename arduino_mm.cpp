#include "arduino_mm.h"
#include <QDebug>

ArduinoMM::ArduinoMM(const QString& portName) {
    arduino.setPortName(portName);
    arduino.setBaudRate(QSerialPort::Baud9600);
    arduino.setDataBits(QSerialPort::Data8);
    arduino.setParity(QSerialPort::NoParity);
    arduino.setStopBits(QSerialPort::OneStop);
    arduino.setFlowControl(QSerialPort::NoFlowControl);

    if (!arduino.open(QIODevice::ReadWrite)) {
        qDebug() << "Impossible d'ouvrir le port Arduino :" << portName;
    } else {
        qDebug() << "Port Arduino ouvert :" << portName;
    }
}

ArduinoMM::~ArduinoMM() {
    if (arduino.isOpen()) arduino.close();
}

void ArduinoMM::ouvrirPorte() {
    if (arduino.isOpen()) {
        arduino.write("O");
        qDebug() << "Commande ouverture envoyée";
    }
}

void ArduinoMM::fermerPorte() {
    if (arduino.isOpen()) {
        arduino.write("F");
        qDebug() << "Commande fermeture envoyée";
    }
}

bool ArduinoMM::estConnecte() const {
    return arduino.isOpen();
}
