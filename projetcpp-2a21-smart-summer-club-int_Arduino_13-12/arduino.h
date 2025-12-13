#ifndef ARDUINO_H
#define ARDUINO_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QByteArray>
#include <QObject>

class Arduino : public QObject
{
    Q_OBJECT

public:
    Arduino();
    ~Arduino();
    int connect_arduino(); // permet de connecter le PC à Arduino
    int close_arduino(); // permet de femer la connexion
    void write_to_arduino( QByteArray ); // envoyer des données vers arduino
    QByteArray read_from_arduino();  //recevoir des données de la carte Arduino
    QSerialPort* getserial();   // accesseur
    QString getarduino_port_name();

    // Méthodes pour contrôler le buzzer via le même Arduino
    void buzzerShortBeep();      // Un bip court
    void buzzerThreeBeeps();     // Trois bips successifs

private:
    QSerialPort * serial; //Cet objet rassemble des informations (vitesse, bits de données, etc.)
    //et des fonctions (envoi, lecture de réception,...) sur ce qu'est une voie série pour Arduino.
    static const quint16 arduino_uno_vendor_id = 0x2341; // Note : J'ai corrigé 9025 en 0x2341, qui est l'ID standard d'Arduino Srl
    static const quint16 arduino_uno_product_id = 0x0043;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data;  // contenant les données lues à partir d'Arduino

};

#endif // ARDUINO_H
