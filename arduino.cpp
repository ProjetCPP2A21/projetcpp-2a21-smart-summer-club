#include "arduino.h"
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QString>
#include <QByteArray>
#include <QMessageBox>

Arduino::Arduino() {
    data = "";
    arduino_port_name = "";
    arduino_is_available = false;
    //arduino_is_available = "";
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

Arduino::~Arduino() {
    if (serial->isOpen()) serial->close();
    delete serial;
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
                //arduino_port_name = "COM6";
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

/*            connect(serial, &QSerialPort::readyRead,
                    this, &Arduino::handleReadyRead);*/
            qDebug() << " connection  avec succes" << arduino_port_name;
            QMessageBox::critical(nullptr, " Arduino",
                                  "connection avec succes " + arduino_port_name);
            return -0;

            return 0; // Succès
        }
        // AFFICHE LA VRAIE ERREUR
        qDebug() << "ERREUR CRITIQUE :" << serial->errorString();
        return 1;   // port trouvé mais pas ouvert
    }

    return 1; // Échec
}


int Arduino::close_arduino()
{
    if(serial->isOpen()){
        serial->close();
        return 0;
    }
    return 1;
}


QByteArray Arduino::read_from_arduino()
{
    if (serial->isOpen() && serial->isReadable())
    {
        data = serial->readAll();
        return data;
    }
    return QByteArray();
    //return "";
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
/*void Arduino::write_to_arduino(QByteArray d)
{
    if(serial->isWritable()){
        serial->write(d);
        // Envoyer des données vers Arduino
    } else {
        qDebug() << "Erreur : Impossible d'écrire sur le port série !";
    }
}
*/
/*void Arduino::handleReadyRead()
{
    QByteArray ba = serial->readAll();
    QString msg = QString::fromUtf8(ba).trimmed();

    if (!msg.isEmpty())
        emit dataReceived(msg); // envoie vers interface_formateur
}*/

void Arduino::handleReadyRead()
{
    /* QByteArray ba = serial->readAll();
    QString msg = QString::fromUtf8(ba).trimmed();

    if (!msg.isEmpty())
        emit dataReceived(msg); // envoie vers interface_formateur*/
    static QString buffer;
    buffer += serial->readAll();

    int pos;
    while ((pos = buffer.indexOf('\n')) != -1) {
        QString ligne = buffer.left(pos).trimmed();
        buffer.remove(0, pos+1);

        if (!ligne.isEmpty())
            emit dataReceived(ligne);
    }
}


