#include "connection.h"

Connection::Connection()
{
    db = QSqlDatabase::addDatabase("QODBC");
}

Connection::~Connection()
{
    if (db.isOpen())
        db.close();
}

Connection& Connection::instance()
{
    static Connection instance;
    return instance;
}

bool Connection::createConnection()
{
    db.setDatabaseName("houssem-bd");
    db.setUserName("houssem");
    db.setPassword("exokai1288");

    if (db.open()) {
        qDebug() << "Connexion établie ✅";
        return true;
    } else {
        qDebug() << "Échec de la connexion ❌:" << db.lastError().text();
        return false;
    }
}
