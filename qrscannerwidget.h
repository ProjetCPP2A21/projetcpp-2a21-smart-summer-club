#ifndef QRSCANNERWIDGET_H
#define QRSCANNERWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <opencv2/opencv.hpp>

class QRScannerWidget : public QWidget
{
    Q_OBJECT
public:
    QRScannerWidget(QWidget *parent = nullptr);
    ~QRScannerWidget();

private slots:
    void captureFrame();

private:
    QTimer *timer;
    QLabel *videoLabel;
    cv::VideoCapture cap;

    QSqlDatabase db;

    //void connectToDatabase();
    bool verifierFormateur(const QString &idFormateur);
};

#endif // QRSCANNERWIDGET_H
