#include "connection.h"
#include <QDebug>
Connection::Connection()
{
    db = QSqlDatabase::addDatabase("QODBC");
}

Connection::~Connection() {
    if (db.isOpen())
        db.close();
}

Connection& Connection::createInstance() {
    static Connection instance;
    return instance;
}

bool Connection::createconnect()
{
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("app_educamp");
    db.setUserName("smartclub");
    db.setPassword("educamp");

    qDebug() << "=== DATABASE CONNECTION DEBUG ===";
    qDebug() << "Driver:" << db.driverName();
    qDebug() << "Database name:" << db.databaseName();
    qDebug() << "Username:" << db.userName();
    qDebug() << "Connection options:" << db.connectOptions();

    if (db.open()) {
        test = true;
        qDebug() << "✅ SUCCESS: Database connected!";
        qDebug() << "Database is valid:" << db.isValid();
        qDebug() << "Database is open:" << db.isOpen();
    } else {
        qDebug() << "❌ FAILED: Database connection error!";
        qDebug() << "Error details:" << db.lastError().text();
        qDebug() << "Error database text:" << db.lastError().databaseText();
        qDebug() << "Error driver text:" << db.lastError().driverText();
    }
    qDebug() << "=================================";

    return test;
}
