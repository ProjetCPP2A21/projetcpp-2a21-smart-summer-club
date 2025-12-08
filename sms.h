#ifndef SMS_H
#define SMS_H

#include <QObject>
#include <QNetworkAccessManager>

class SmsSender : public QObject
{
    Q_OBJECT

public:
    explicit SmsSender(QObject *parent = nullptr);
    void sendSms(const QString &to, const QString &body);

signals:
    void smsSent();
    void smsError(QString error);

private:
    QNetworkAccessManager *manager;
};

#endif // SMS_H

