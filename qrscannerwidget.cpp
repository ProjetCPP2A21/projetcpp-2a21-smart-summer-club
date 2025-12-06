#include "qrscannerwidget.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>

QRScannerWidget::QRScannerWidget(QWidget *parent) : QWidget(parent)
{
    videoLabel = new QLabel(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(videoLabel);
    setLayout(layout);

    // Ouvrir caméra
    cap.open(0);
    if(!cap.isOpened()) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir la caméra !");
        return;
    }

    //connectToDatabase();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QRScannerWidget::captureFrame);
    timer->start(30); // ~30 fps
}

QRScannerWidget::~QRScannerWidget()
{
    cap.release();
    db.close();
}

/*void QRScannerWidget::connectToDatabase()
{
    db = QSqlDatabase::addDatabase("QOCI"); // Driver Oracle
    db.setHostName("localhost");             // Modifier si nécessaire
    db.setDatabaseName("XE");                // Nom du service Oracle
    db.setUserName("username");
    db.setPassword("password");

    if(!db.open()){
        QMessageBox::critical(this, "Erreur BD", db.lastError().text());
    }
}*/

bool QRScannerWidget::verifierFormateur(const QString &idFormateur)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM FORMATEUR WHERE IDFORMATEUR = :id");
    query.bindValue(":id", idFormateur);
    /*if(!query.exec()) {
        qDebug() << "Erreur SQL:" << query.lastError().text();
        return false;
    }*/

    if(query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }
    return false;
}

void QRScannerWidget::captureFrame()
{
    cv::Mat frame;
    cap >> frame;
    if(frame.empty()) return;

    // Détecter QR code
    cv::QRCodeDetector qrDecoder;
    std::string data = qrDecoder.detectAndDecode(frame);

    if(!data.empty()) {
        QString idFormateur = QString::fromStdString(data);
        if(verifierFormateur(idFormateur)){
            qDebug() << "Formateur trouvé:" << idFormateur;
        } else {
            qDebug() << "Formateur non trouvé:" << idFormateur;
        }
    }

    // Convertir cv::Mat -> QImage
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    QImage qimg(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    videoLabel->setPixmap(QPixmap::fromImage(qimg).scaled(videoLabel->size(), Qt::KeepAspectRatio));
}
