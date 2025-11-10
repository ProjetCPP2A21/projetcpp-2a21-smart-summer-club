#include "app.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <QDebug>  // For console output
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection& c = Connection::createInstance() ;
    bool test = c.createconnect();
    app w;

    qDebug() << "=== APPLICATION STARTED ===";



    if (test) {
        qDebug() << "Showing main window...";
        w.show();
        QMessageBox::information(nullptr, "Success", "Database connected!");
        qDebug() << "Main window displayed successfully";
    } else {
        qDebug() << "Database connection failed - starting without DB";
        w.show();  // Still show the window even if DB fails
        QMessageBox::critical(nullptr, "Error", "Connection failed!");
    }

    qDebug() << "Application running...";
    return a.exec();
}
