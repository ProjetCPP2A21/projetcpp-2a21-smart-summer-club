#include "service.h"
#include<QString>
#include<QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include<QSqlQueryModel>
#include <QTableView>
#include  "ui_mainwindow.h"
service::service()
{

}

service::service(int id ,QString n,double m,QString h,int ca,QString s,QString ts) {
    id_service=id;
    nom_service=n;
    montant=m;
    horaire=h;
    capacite=ca;
    status_service=s;
    type_service=ts;


}


bool service::ajoute_service()
{

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Connexion à la base non ouverte.";

        return false;
    }
    /*else if (id_service <= 0) {
        QMessageBox::warning(nullptr, "Saisie invalide", "L'identifiant du service doit être supérieur à zéro.");

        return false;
    }
    else if  (nom_service.isEmpty()) {
        QMessageBox::warning(nullptr, "nom service vide ", "verifie nom service.");

        return false;
    }
    if (montant<=0) {
        QMessageBox::warning(nullptr, "montant invalide ", "montant doit etre >0.");

        return false;
    }
    if (horaire.isEmpty()) {
        QMessageBox::warning(nullptr, "horaire vide  ", "verifie horaire.");

        return false;
    }
    if (capacite<0) {
        QMessageBox::warning(nullptr, "capacite vide  ", "verifie horaire.");

        return false;
    }
    if (status_service.isEmpty()) {
        QMessageBox::warning(nullptr, "status service vide  ", "verifie horaire.");

        return false;
    }

    if (type_service.isEmpty()) {
        QMessageBox::warning(nullptr, "type service   ", "verifie horaire.");

        return false;
    }*/

    QSqlQuery query;
    query.prepare("INSERT INTO service (id_service, nom_service, montant, horaire, capacite, status_service, type_service) "
                  "VALUES (:id_service, :nom_service, :montant, :horaire, :capacite, :status_service, :type_service)");

    query.bindValue(":id_service", id_service);
    query.bindValue(":nom_service", nom_service);
    query.bindValue(":montant", montant);
    query.bindValue(":horaire", horaire);
    query.bindValue(":capacite", capacite);
    query.bindValue(":status_service", status_service);
    query.bindValue(":type_service", type_service);

    return query.exec();
}
///*//
 QSqlQueryModel* service::affiche()
{
     QSqlQueryModel* model = new QSqlQueryModel();
     model->setQuery("SELECT * FROM service");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_service"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_service"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("horaire"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("capacité"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("status_service"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("type_service"));

    return model;
}


bool service::supprime_service(int id_service)
{
    if (id_service < 0  ) {
        QMessageBox::critical(nullptr, "Erreur", "ID service vide !");
        return false;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM service WHERE id_service = :id");
    query.bindValue(":id", id_service);
    return query.exec();
}

bool service::recherch_id(int id_service)
{
    if (id_service < 0) {
        QMessageBox::critical(nullptr, "Erreur", "ID service vide !");
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM service WHERE id_service = :id");
    query.bindValue(":id", id_service);
    if (!query.exec()) {
        qDebug() << "Erreur SQL:" << query.lastError().text();
        return false;
    }

    return query.next();
}

    //return query.exec();


QSqlQueryModel* service::affiche_id(int id_service)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM service WHERE id_service = :id");
    query.bindValue(":id", id_service);
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
        return nullptr; // renvoyer null si la requête échoue
    }
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_service"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_service"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("horaire"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("capacité"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("status_service"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("type_service"));

    return model;
}

bool service::charge_donner(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM service WHERE id_service = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur SQL :" << query.lastError().text();
        return false;
    }

    if (query.next()) {

        id_service = query.value("id_service").toInt();
        nom_service = query.value("nom_service").toString();
        montant = query.value("montant").toDouble();
        horaire = query.value("horaire").toString();
        capacite = query.value("capacite").toInt();
        status_service = query.value("status_service").toString();
        type_service = query.value("type_service").toString();
        return true;
    }

    qDebug() << "Aucun service trouvé pour ID :" << id;
    return false;
}
bool service::update_service(int id_service)
{
    QSqlQuery query;
    query.prepare("UPDATE service SET nom_service = :nom, montant = :montant, horaire = :horaire, capacite = :capacite, status_service = :status, type_service = :type WHERE id_service = :id");
    query.bindValue(":id", id_service);
    query.bindValue(":nom", nom_service);
    query.bindValue(":montant", montant);
    query.bindValue(":horaire", horaire);
    query.bindValue(":capacite", capacite);
    query.bindValue(":status", status_service);
    query.bindValue(":type", type_service);

    return query.exec();
}





