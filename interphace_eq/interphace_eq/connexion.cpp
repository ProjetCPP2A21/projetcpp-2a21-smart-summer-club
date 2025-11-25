#include "connexion.h"

connexion::connexion()
{

}
bool connexion::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projet_2A");
db.setUserName("moudhaffar");
db.setPassword("1920");
if(db.open())
    test=true;


return test;
}
