#ifndef QR_READER_H
#define QR_READER_H

#include <QImage>
#include <QString>

class QrReader
{
public:
    QrReader();
    QString lireQRCode(const QImage& frame);
};

#endif // QR_READER_H
