#ifndef ARDUINO_MM_H
#define ARDUINO_MM_H

#include <QtSerialPort/QSerialPort>
#include <QString>

class ArduinoMM {
public:
    explicit ArduinoMM(const QString& portName);
    ~ArduinoMM();

    void ouvrirPorte();
    void fermerPorte();
    bool estConnecte() const;

private:
    QSerialPort arduino;
};

#endif // ARDUINO_MM_H
