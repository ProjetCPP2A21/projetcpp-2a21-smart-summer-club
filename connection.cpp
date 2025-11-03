#include "connection.h"


Connection::Connection()
{
    db=QSqlDatabase::addDatabase("QODBC");
}


Connection::~Connection()
{
    if(db.isOpen())
    {db.close();}
}


Connection& Connection::createInstance(){
    static Connection instance;
    return instance;
}



bool Connection::createconnection()
{
    db.setDatabaseName("educamp");//inserer le nom de la source de données
    db.setUserName("system");//inserer nom de l'utilisateur
    db.setPassword("karim");//inserer mot de passe de cet utilisateur

    if (db.open()){
            qDebug()<<"connexion etablie";
        return true;

    }

     qDebug()<<"connexion invalide :"<<db.lastError().text();
    return false;


}
