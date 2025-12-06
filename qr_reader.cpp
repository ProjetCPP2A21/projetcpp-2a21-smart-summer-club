#include "qr_reader.h"
#include <ZXing/ReadBarcode.h>
#include <ZXing/BarcodeFormat.h>
#include <ZXing/DecodeHints.h>
#include <ZXing/QtZXing.h>
#include <QDebug>

QrReader::QrReader() {}

QString QrReader::lireQRCode(const QImage& frame)
{
    if (frame.isNull()) {
        qDebug() << "Image QR vide";
        return "";
    }

    ZXing::ImageView iv = ZXing::Qt::ReadImage(frame);

    ZXing::DecodeHints hints;
    hints.setFormats(ZXing::BarcodeFormat::QR_CODE);

    //auto result = ZXing::ReadBarcode(iv, hints);

    QString result = QString::fromStdString(
        ZXing::ReadBarcode(image, ZXing::BarcodeFormat::QR_CODE)
        );
    if (!result.isValid())
        return "";

    QString code = QString::fromStdString(result.text()).trimmed();
    qDebug() << "QR détecté :" << code;

    return code;
}
