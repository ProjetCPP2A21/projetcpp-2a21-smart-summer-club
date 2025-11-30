#include "sendgridclient.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QUrl>
#include <QDebug>

SendGridClient::SendGridClient() = default;

void SendGridClient::configure(const QString &apiKey,
                               const QString &fromEmail,
                               const QString &fromName,
                               const QStringList &toEmails)
{
    m_apiKey = apiKey.trimmed();
    m_fromEmail = fromEmail.trimmed();
    m_fromName = fromName.trimmed();
    m_toEmails = toEmails;
}

bool SendGridClient::isConfigured() const
{
    return !m_apiKey.isEmpty() &&
           !m_fromEmail.isEmpty() &&
           !m_toEmails.isEmpty();
}

bool SendGridClient::sendFormationCreatedEmail(const QString &nom,
                                               const QString &type,
                                               const QString &horaire,
                                               const QString &lieu,
                                               const QDate &dateFormation,
                                               int capacite,
                                               int tarif,
                                               int idFormateur,
                                               int idFormation)
{
    if (!isConfigured())
    {
        m_lastError = QObject::tr("SendGrid n'est pas configuré.");
        qWarning() << m_lastError;
        return false;
    }

    QString subject = QObject::tr("Nouvelle formation ajoutée : %1").arg(nom);
    QString textBody = QObject::tr(
                           "Une nouvelle formation a été créée :\n"
                           "- ID : %1\n"
                           "- Nom : %2\n"
                           "- Type : %3\n"
                           "- Date : %4\n"
                           "- Horaire : %5\n"
                           "- Lieu : %6\n"
                           "- Capacité : %7\n"
                           "- Tarif : %8\n"
                           "- Formateur ID : %9\n")
                           .arg(idFormation)
                           .arg(nom)
                           .arg(type)
                           .arg(dateFormation.toString("yyyy-MM-dd"))
                           .arg(horaire)
                           .arg(lieu)
                           .arg(capacite)
                           .arg(tarif)
                           .arg(idFormateur);

    QString htmlBody = QObject::tr(
                           "<h3>Nouvelle formation ajoutée</h3>"
                           "<ul>"
                           "<li><strong>ID :</strong> %1</li>"
                           "<li><strong>Nom :</strong> %2</li>"
                           "<li><strong>Type :</strong> %3</li>"
                           "<li><strong>Date :</strong> %4</li>"
                           "<li><strong>Horaire :</strong> %5</li>"
                           "<li><strong>Lieu :</strong> %6</li>"
                           "<li><strong>Capacité :</strong> %7</li>"
                           "<li><strong>Tarif :</strong> %8</li>"
                           "<li><strong>ID Formateur :</strong> %9</li>"
                           "</ul>")
                           .arg(idFormation)
                           .arg(nom)
                           .arg(type)
                           .arg(dateFormation.toString("yyyy-MM-dd"))
                           .arg(horaire)
                           .arg(lieu)
                           .arg(capacite)
                           .arg(tarif)
                           .arg(idFormateur);

    return sendMail(subject, textBody, htmlBody);
}

bool SendGridClient::sendMail(const QString &subject, const QString &textBody, const QString &htmlBody)
{
    m_lastError.clear();

    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl("https://api.sendgrid.com/v3/mail/send"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer " + m_apiKey.toUtf8());

    QJsonArray toArray;
    for (const QString &email : m_toEmails)
    {
        const QString trimmed = email.trimmed();
        if (trimmed.isEmpty())
            continue;
        QJsonObject toObj;
        toObj["email"] = trimmed;
        toArray.append(toObj);
    }

    if (toArray.isEmpty())
    {
        m_lastError = QObject::tr("Aucun destinataire SendGrid configuré.");
        return false;
    }

    QJsonObject personalization;
    personalization["to"] = toArray;

    QJsonObject fromObj;
    fromObj["email"] = m_fromEmail;
    if (!m_fromName.isEmpty())
        fromObj["name"] = m_fromName;

    QJsonArray contentArray;
    QJsonObject textContent;
    textContent["type"] = "text/plain";
    textContent["value"] = textBody;
    contentArray.append(textContent);

    QJsonObject htmlContent;
    htmlContent["type"] = "text/html";
    htmlContent["value"] = htmlBody;
    contentArray.append(htmlContent);

    QJsonObject root;
    root["personalizations"] = QJsonArray{ personalization };
    root["from"] = fromObj;
    root["subject"] = subject;
    root["content"] = contentArray;

    QEventLoop loop;
    QNetworkReply *reply = manager.post(request, QJsonDocument(root).toJson());
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QByteArray response = reply->readAll();

    if (reply->error() != QNetworkReply::NoError)
    {
        m_lastError = reply->errorString() + " - " + QString::fromUtf8(response);
        qWarning() << "SendGrid error:" << m_lastError;
        reply->deleteLater();
        return false;
    }

    reply->deleteLater();
    return true;
}


