#include "mainwindow.h"

#include "connexion.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
        MainWindow  w;
        connexion c;
        bool test = c.createconnect();

          if (test)
          {
              w.show();


               QMessageBox::information(nullptr, QObject::tr("Connexion réussie"),
                                       QObject::tr("Bonjour, connexion avec succès."));
          }
          else
          {
              QMessageBox::critical(nullptr, QObject::tr("Base de données non ouverte"),
                                    QObject::tr("Échec de la connexion.\n"
                                                "Cliquez sur Annuler pour quitter."),
                                    QMessageBox::Cancel);
          }

    return a.exec();
}
