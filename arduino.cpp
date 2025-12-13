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
                //arduino_port_name="COM5";


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

/*int Arduino::connect_arduino()
{
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
            if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier()== arduino_uno_product_id)
            {

              arduino_port_name = serial_port_info.portName();
              arduino_is_available = true;

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

            /*   connect(serial, &QSerialPort::readyRead,
                    this, &Arduino::handleReadyRead);*//*
            qDebug() << " connection  avec succes" << arduino_port_name;
            QMessageBox::information(nullptr, " Arduino",
                                  "connection avec succes " + arduino_port_name);
            return 0; // Succès
        }
        // AFFICHE LA VRAIE ERREUR
        qDebug() << "ERREUR CRITIQUE :" << serial->errorString();
        return -1;   // port trouvé mais pas ouvert
    }

    return 1;
}*/

/*QByteArray Arduino::read_from_arduino()
{
    if(serial->isReadable()){
        data = serial->readAll(); // Lire toutes les données reçues
        return data;
    }
    return ""; // Retourner vide si rien à lire
}*/

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
// arduino sinda






/* --- ARDUINO FORMATEUR ----
 void Arduino::handleReadyRead()
{
    /* QByteArray ba = serial->readAll();
    QString msg = QString::fromUtf8(ba).trimmed();

    if (!msg.isEmpty())
        emit dataReceived(msg); // envoie vers interface_formateur*/
/*    static QString buffer;
    buffer += serial->readAll();

    int pos;
    while ((pos = buffer.indexOf('\n')) != -1) {
        QString ligne = buffer.left(pos).trimmed();
        buffer.remove(0, pos+1);

        if (!ligne.isEmpty())
            emit dataReceived(ligne);
    }
}*/

/*----------karim&amine--------------*/
/*QByteArray Arduino::read_from_arduino()
{
    {
        static QByteArray buffer;

        if (serial->isReadable()) {
            buffer.append(serial->readAll());
        }

        int newlineIndex = buffer.indexOf('\n');
        if (newlineIndex != -1) {
            QByteArray line = buffer.left(newlineIndex + 1);
            buffer.remove(0, newlineIndex + 1);
            return "";
        }

    }
}*/
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

    return QByteArray(); // IMPORTANT
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


