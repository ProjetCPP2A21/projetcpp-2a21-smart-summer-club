#include "arduino.h"

#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QString>
#include <QByteArray>


Arduino::Arduino() {
    data = "";
    arduino_port_name = "";
    arduino_is_available = false;
    serial = new QSerialPort(); // <--- CRUCIAL : Initialisation de la mémoire ici
}


QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *Arduino::getserial()
{
    return serial;
}

int Arduino::connect_arduino()
{
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
        if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
            if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier() == arduino_uno_product_id) {
                arduino_is_available = true;
                arduino_port_name=serial_port_info.portName();
            }
        }
    }
    qDebug() << "arduino_port_name is :" << arduino_port_name;
    if(arduino_is_available){
        serial->setPortName(arduino_port_name);

        // --- MODIFICATION ICI ---
        if(serial->open(QSerialPort::ReadWrite)){
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            qDebug() << " connection  avec succes" << arduino_port_name;
            QMessageBox::information(nullptr, " Arduino",
                                     "connection avec succes " + arduino_port_name);
            return 0;
        }

        // AFFICHE LA VRAIE ERREUR
        qDebug() << "ERREUR CRITIQUE :" << serial->errorString();

        return 1;
    }
    return -1;
}

void Arduino::write_to_arduino(QByteArray d)
{
    if (serial->isOpen() && serial->isWritable())
    {
        serial->write(d);
    }
    else
    {
        qDebug() << "Impossible d'écrire vers Arduino !";
    }
}

QByteArray Arduino::read_from_arduino()
{
    static QByteArray buffer;

    if (serial->isReadable()) {
        buffer.append(serial->readAll());
    }

    int newlineIndex = buffer.indexOf('\n');
    if (newlineIndex != -1) {
        QByteArray line = buffer.left(newlineIndex + 1);
        buffer.remove(0, newlineIndex + 1);
        return line;
    }

    return QByteArray();
}




int Arduino::close_arduino()
{
    if(serial->isOpen()){
        serial->close();
        return 0;
    }
    return 1;
}

Arduino::~Arduino() {
    if (serial->isOpen()) serial->close();
    delete serial;
}


#include "arduino.h"

#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QString>
#include <QByteArray>

// ... code existant ...

// Nouvelle méthode : un bip court
void Arduino::buzzerShortBeep()
{
    if (serial->isOpen() && serial->isWritable())
    {
        QByteArray command = "B1\n"; // B1 = bip court (200ms)
        serial->write(command);
        qDebug() << "[BUZZER] Commande envoyée : B1 (bip court)";
    }
    else
    {
        qDebug() << "[BUZZER] Impossible d'envoyer commande !";
    }
}

// Nouvelle méthode : trois bips successifs
void Arduino::buzzerThreeBeeps()
{
    if (serial->isOpen() && serial->isWritable())
    {
        QByteArray command = "B3\n"; // B3 = trois bips
        serial->write(command);
        qDebug() << "[BUZZER] Commande envoyée : B3 (trois bips)";
    }
    else
    {
        qDebug() << "[BUZZER] Impossible d'envoyer commande !";
    }
}

// ... reste du code existant ...
