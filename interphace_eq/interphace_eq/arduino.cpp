#include "arduino.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>

Arduino::Arduino(QObject *parent)
    : QObject(parent)
    , m_moteurActive(false)
    , m_serial(new QSerialPort(this))
{
    qDebug() << "[ARDUINO] Initialisation...";

    // Chercher Arduino automatiquement
    trouverArduino();

    // Connecter les signaux série
    connect(m_serial, &QSerialPort::readyRead, this, &Arduino::lireDonneesArduino);
}

void Arduino::trouverArduino() {
    QStringList portsTrouves;

    foreach(const QSerialPortInfo &port, QSerialPortInfo::availablePorts()) {
        QString infoPort = port.portName() + " - " + port.description();
        portsTrouves << infoPort;

        qDebug() << "[ARDUINO] Port disponible:" << infoPort;

        // Détecter Arduino
        if (port.description().contains("Arduino", Qt::CaseInsensitive) ||
            port.manufacturer().contains("Arduino", Qt::CaseInsensitive) ||
            port.description().contains("USB Serial", Qt::CaseInsensitive)) {

            m_portArduino = port.portName();
            qDebug() << "[ARDUINO] Arduino détecté sur:" << m_portArduino;
            break;
        }
    }

    if (m_portArduino.isEmpty() && !portsTrouves.isEmpty()) {
        // Prendre le premier port
        m_portArduino = portsTrouves.first().split(" - ").first();
        qDebug() << "[ARDUINO] Utilisation du port:" << m_portArduino;
    }
}

bool Arduino::connecterArduino() {
    if (m_portArduino.isEmpty()) {
        qDebug() << "[ARDUINO] Aucun port trouvé";
        return false;
    }

    m_serial->setPortName(m_portArduino);
    m_serial->setBaudRate(QSerialPort::Baud9600);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);

    if (m_serial->open(QIODevice::ReadWrite)) {
        qDebug() << "[ARDUINO] Connecté à" << m_portArduino;
        emit messageInfo("✅ Arduino connecté: " + m_portArduino);
        return true;
    } else {
        qDebug() << "[ARDUINO] Erreur connexion:" << m_serial->errorString();
        emit messageInfo("❌ Erreur connexion Arduino");
        return false;
    }
}

void Arduino::verifierID(const QString &id) {
    QString idTrimmed = id.trimmed();

    if (idTrimmed.isEmpty()) {
        emit etatChanged(false, "❌ ID vide");
        return;
    }

    // Vérifier si numérique
    bool ok;
    idTrimmed.toInt(&ok);

    if (!ok) {
        emit etatChanged(false, "❌ ID non numérique");
        return;
    }

    // Vérifier dans la BDD
    if (!verifierIDDansBDD(idTrimmed)) {
        emit etatChanged(false, "❌ ID inexistant");
        return;
    }

    // ID valide - Envoyer commande à Arduino
    if (m_serial->isOpen()) {
        QString commande = "START " + idTrimmed + "\n";
        m_serial->write(commande.toUtf8());
        m_serial->flush();

        qDebug() << "[ARDUINO] Commande envoyée:" << commande.trimmed();

        // Simuler réponse positive (en attendant la vraie réponse)
        m_moteurActive = true;
        QString message = QString("✅ ID %1 valide\nMoteur en marche!").arg(idTrimmed);
        emit etatChanged(true, message);

    } else {
        // Simulation si Arduino non connecté
        qDebug() << "[ARDUINO] Simulation - ID valide";
        m_moteurActive = true;
        QString message = QString("✅ ID %1 valide (simulation)\nMoteur virtuel en marche").arg(idTrimmed);
        emit etatChanged(true, message);
    }
}

void Arduino::arreterMoteur() {
    if (m_serial->isOpen() && m_moteurActive) {
        m_serial->write("STOP\n");
        m_serial->flush();
        qDebug() << "[ARDUINO] Commande STOP envoyée";
    }

    m_moteurActive = false;
    emit etatChanged(false, "⏹️ Moteur arrêté");
}

void Arduino::lireDonneesArduino() {
    if (m_serial->canReadLine()) {
        QByteArray data = m_serial->readLine();
        QString message = QString::fromUtf8(data).trimmed();

        qDebug() << "[ARDUINO] Reçu:" << message;
        emit messageInfo("Arduino: " + message);

        // Détecter état du moteur
        if (message.contains("MOTEUR EN MARCHE")) {
            m_moteurActive = true;
        } else if (message.contains("MOTEUR ARRETE")) {
            m_moteurActive = false;
        }
    }
}

bool Arduino::verifierIDDansBDD(const QString &id) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EQUIPEMENT WHERE ID = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "[ARDUINO] Erreur BDD:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        return query.value(0).toInt() > 0;
    }

    return false;
}
