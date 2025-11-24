#include "connection.h"
#include <QSqlDatabase>

connection* connection::p_instance = nullptr;

connection::connection()
{

}
connection* connection::instance()
{
    if(p_instance == nullptr){
        p_instance = new connection();
    }
    return p_instance;
}

bool connection::createconnect()
{bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("app_educamp");//inserer le nom de la source de données
    db.setUserName("smartclub");//inserer nom de l'utilisateur
    db.setPassword("educamp");//inserer mot de passe de cet utilisateur

    if (db.open())
        test=true;





    return  test;
}
connection::~connection()
{
    QSqlDatabase db = QSqlDatabase::database();
    if(db.isOpen()){
        db.close();
    }
}

