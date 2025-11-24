#include "arduino.h"
#include <QDebug>

Arduino::Arduino()
{
    serial = new QSerialPort;
    arduino_port_name = "";
    arduino_is_available = false;

    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        if(info.hasVendorIdentifier() && info.hasProductIdentifier())
        {
            if(info.vendorIdentifier() == arduino_uno_vendor_id &&
                info.productIdentifier() == arduino_uno_product_id)
            {
                arduino_port_name = info.portName();
                arduino_is_available = true;
            }
        }
    }
}

int Arduino::connect_arduino()
{
    if(arduino_is_available)
    {
        serial->setPortName(arduino_port_name);
        if(serial->open(QSerialPort::ReadWrite))
        {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            return 1;
        }
        return -1;
    }
    return -2;
}

int Arduino::close_arduino()
{
    if(serial->isOpen()) {
        serial->close();
        return 1;
    }
    return -1;
}

int Arduino::write_to_arduino(const QByteArray &data)
{
    if(serial->isWritable()) {
        return serial->write(data);
    }
    return -1;
}

QByteArray Arduino::read_from_arduino()
{
    if(serial->isReadable()) {
        return serial->readAll();
    }
    return "";
}

QSerialPort* Arduino::getserial()
{
    return serial;
}
