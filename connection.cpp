#include "connection.h"
#include <QSqlDatabase>

Connection* Connection :: p_instance = nullptr;

Connection::Connection() {}

Connection* Connection :: instance()
{
    if(p_instance == nullptr){
        p_instance = new Connection();
    }
    return p_instance;
}



bool Connection::createconnect()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("source_projet2A");//inserer le nom de la source de données
    db.setUserName("Malek");//inserer nom de l'utilisateur
    db.setPassword("loka");//inserer mot de passe de cet utilisateur

     if (db.open()){
        test=true;
        //qDebug() << "Connexion réussie à la base de données.";
    } else {
       // qDebug() << "Échec de la connexion :" << db.lastError().text();
    }
    return  test;
}

Connection :: ~Connection(){
    QSqlDatabase db = QSqlDatabase :: database();
    if(db.isOpen()){
        db.close();
    }
}

