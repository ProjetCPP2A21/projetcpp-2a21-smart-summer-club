#include "arduino.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QString>
#include <QByteArray>

Arduino::Arduino() {
    serial = new QSerialPort();
    arduino_is_available = "";
}

Arduino::~Arduino() {
    if (serial->isOpen()) serial->close();
    delete serial;
}

QString Arduino::getarduino_port_name() {
    return arduino_port_name;
}

QSerialPort* Arduino::getserial() {
    return serial;
}

int Arduino::connect_arduino()
{
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
            if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier()
                                                                                    == arduino_uno_product_id)
            {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
            }
        }
    }

    qDebug() << "arduino_port_name is :" << arduino_port_name;

    if(arduino_is_available) { // configuration de la communication ( débit... )
        serial->setPortName(arduino_port_name);
        if(serial->open(QSerialPort::ReadWrite)){
            serial->setBaudRate(QSerialPort::Baud9600); // débit : 9600 bits/s
            serial->setDataBits(QSerialPort::Data8); // longueur des données : 8 bits,
            serial->setParity(QSerialPort::NoParity); // 1 bit de parité optionnel
            serial->setStopBits(QSerialPort::OneStop); // Nombre de bits de stop : 1
            serial->setFlowControl(QSerialPort::NoFlowControl);

            return 0; // Succès
        }
        return 1;   // port trouvé mais pas ouvert
    }

    return 1; // Échec
}

int Arduino::close_arduino()
{
    if(serial->isOpen()){
        serial->close();
        return 0; // Retourne 0 en cas de succès de la fermeture
    }
    return 1; // Retourne 1 si le port n'était pas ouvert
}

QByteArray Arduino::read_from_arduino()
{
    if (serial->isOpen() && serial->isReadable())
    {
        data = serial->readAll();
        return data;
    }
    return QByteArray();
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

void Arduino::handleReadyRead()
{
    QByteArray ba = serial->readAll();
    QString msg = QString::fromUtf8(ba).trimmed();

    if (!msg.isEmpty())
        emit dataReceived(msg); // envoie vers interface_formateur
}
