#include "sms.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QByteArray>
#include <QDebug>

SmsSender::SmsSender(QObject *parent)
    : QObject(parent), manager(new QNetworkAccessManager(this))
{
}

void SmsSender::sendSms(const QString &to, const QString &body)
{
    QString accountSid = "";
    QString authToken = ""; // Remplacer par ton vrai token !

    QString url = "https://api.twilio.com/2010-04-01/Accounts/" + accountSid + "/Messages.json";

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // AUTH BASIC (AccountSID:AuthToken)
    QByteArray auth = (accountSid + ":" + authToken).toUtf8().toBase64();
    request.setRawHeader("Authorization", "Basic " + auth);

    // PARAMETERS
    QUrlQuery params;
    params.addQueryItem("To", to);
    params.addQueryItem("MessagingServiceSid", "MG2e672a010ce89c2bba7af430bdb3d0bc");
    params.addQueryItem("Body", body);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    QNetworkReply *reply = manager->post(request, data);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            emit smsSent();
        } else {
            emit smsError(reply->errorString());
        }
        reply->deleteLater();
    });
}
