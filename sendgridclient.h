#ifndef SENDGRIDCLIENT_H
#define SENDGRIDCLIENT_H

#include <QString>
#include <QStringList>
#include <QDate>

class SendGridClient
{
public:
    SendGridClient();
    //méthode publique pour donner à la classe la clé API, l’email expéditeur, le nom expéditeur, et la liste des destinataire
    void configure(const QString &apiKey,
                   const QString &fromEmail,
                   const QString &fromName,
                   const QStringList &toEmails);
    //vérifie si les infos nécessaires existent clé, from, to
    bool isConfigured() const;
    //retourne le dernier message d’erreur enregistré
    QString lastError() const { return m_lastError; }
    //prépare le contenu du mail

    bool sendFormationCreatedEmail(const QString &nom,
                                   const QString &type,
                                   const QString &horaire,
                                   const QString &lieu,
                                   const QDate &dateFormation,
                                   int capacite,
                                   int tarif,
                                   int idFormateur,
                                   int idFormation);

private:
    //Variables privées stockent la configuration
    QString m_apiKey;
    QString m_fromEmail;
    QString m_fromName;
    QStringList m_toEmails;
    QString m_lastError;
    //méthode privée qui construit le JSON et appelle SendGrid
    bool sendMail(const QString &subject, const QString &textBody, const QString &htmlBody);
};

#endif // SENDGRIDCLIENT_H

