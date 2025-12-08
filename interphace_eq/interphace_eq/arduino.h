#ifndef ARDUINO_H
#define ARDUINO_H

#include <QObject>
#include <QString>
#include <QSerialPort>

class Arduino : public QObject
{
    Q_OBJECT

public:
    explicit Arduino(QObject *parent = nullptr);

    // Méthodes principales
    void verifierID(const QString &id);
    void arreterMoteur();
    bool connecterArduino();

    // Getters
    bool moteurEnMarche() const { return m_moteurActive; }

signals:
    void etatChanged(bool moteurActif, const QString &message);
    void messageInfo(const QString &message);

private slots:
    void lireDonneesArduino();

private:
    bool m_moteurActive;
    QSerialPort *m_serial;
    QString m_portArduino;

    bool verifierIDDansBDD(const QString &id);
    void trouverArduino();
};

#endif // ARDUINO_H
