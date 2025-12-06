#include "oracle_checker.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

bool verifierQRcode(const QString& idFormateur) {
    /*QSqlDatabase db = QSqlDatabase::addDatabase("QOCI");
    db.setHostName("localhost");
    db.setDatabaseName("XE"); // remplace par ton SID
    db.setUserName("username"); // remplace par ton user
    db.setPassword("password"); // remplace par ton mdp

    if (!db.open()) {
        qDebug() << "Erreur connexion Oracle:" << db.lastError().text();
        return false;
    }
*/
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM FORMATEUR WHERE IDFORMATEUR = :id");
    query.bindValue(":id", idFormateur);

    if (!query.exec()) {
        qDebug() << "Erreur requête:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }

    return false;
}
