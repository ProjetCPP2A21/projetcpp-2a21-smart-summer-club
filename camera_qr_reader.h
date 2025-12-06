#ifndef CAMERA_QR_READER_H
#define CAMERA_QR_READER_H

#include <QObject>
#include <QTimer>
#include <QImage>
#include <opencv2/opencv.hpp>
#include "qr_reader.h"

class CameraQRReader : public QObject
{
    Q_OBJECT

public:
    explicit CameraQRReader(QObject *parent = nullptr);
    ~CameraQRReader();

    bool startCamera(int cameraIndex = 0);
    void stopCamera();

signals:
    void frameReady(const QImage& frame);
    void qrCodeDetected(const QString& code);

private slots:
    void captureFrame();

private:
    cv::VideoCapture cap;
    QTimer timer;
    QrReader qrReader;
};

#endif // CAMERA_QR_READER_H
