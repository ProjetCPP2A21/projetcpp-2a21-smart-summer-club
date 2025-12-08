#include "connexion.h"

connexion::connexion()
{

}
bool connexion::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("app_educamp");
db.setUserName("smartclub");
db.setPassword("educamp");
if(db.open())
    test=true;


return test;
}
