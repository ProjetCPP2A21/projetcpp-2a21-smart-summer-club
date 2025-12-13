#include "mainwindow.h"
#include "gestion_employe.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>
#include "apprenant.h"
#include "service.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gestion_employe g;
    Connection *c= Connection :: instance();
    bool test=c->createconnect();
    service s;
    if(test){
    g.show();

   /*QMessageBox::information(nullptr, QObject::tr("database is open"),
                                 QObject::tr("connection successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel;*/


    }
/*else{
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                              QObject::tr("connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
*/
    return a.exec();
}
