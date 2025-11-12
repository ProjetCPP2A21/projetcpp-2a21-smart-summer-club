#include "formation2.h"
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QObject>
#include <QTableView>
#include <QSqlError>

//constructeur par defaut
formation2::formation2() {}
//constructeur paramétré
formation2::formation2(int id,QString nom,QString type,QString horaire,int duree,QString lieu,int capacite,int tarif,int id_formateur)
{
    this->id=id;
    this->nom=nom;
    this->type=type;
    this->horaire=horaire;
    this->duree=duree;
    this->lieu=lieu;
    this->capacite=capacite;
    this->tarif=tarif;
    this->id_formateur=id_formateur;
}
bool formation2::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(id);
    QString res2 = QString::number(id_formateur);

    //prepare() prend la requete en parametre pour la preparer à l'execution
    query.prepare("INSERT INTO FORMATION(ID_FORMATION,NOM,TYPE_FORMATION,HORAIRE,DUREE,LIEU,CAPACITE,TARIF,IDFORMATEUR)"
                  "VALUES (:id,:nom,:type,:horaire,:duree,:lieu,:capacite,:tarif,:id_formateur)");

    //creation des variables liées
    query.bindValue(":id" ,res);
    query.bindValue(":nom" ,nom);
    query.bindValue(":type" ,type);
    query.bindValue(":horaire" ,horaire);
    query.bindValue(":duree" ,duree);
    query.bindValue(":lieu" ,lieu);
    query.bindValue(":capacite" ,capacite);
    query.bindValue(":tarif" ,tarif);
    query.bindValue(":id_formateur" ,res2);

    return query.exec(); //exec() envoie la requete poue l'executer


}
QSqlQueryModel * formation2::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model ->setQuery("SELECT * FROM FORMATION");

    model -> setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model -> setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model -> setHeaderData(2,Qt::Horizontal,QObject::tr("TYPE"));
    model -> setHeaderData(3,Qt::Horizontal,QObject::tr("HORAIRE"));
    model -> setHeaderData(4,Qt::Horizontal,QObject::tr("DUREE"));
    model -> setHeaderData(5,Qt::Horizontal,QObject::tr("LIEU"));
    model -> setHeaderData(6,Qt::Horizontal,QObject::tr("CAPACITE"));
    model -> setHeaderData(7,Qt::Horizontal,QObject::tr("TARIF"));
    model -> setHeaderData(8,Qt::Horizontal,QObject::tr("IDFORMATEUR"));


    return model;
}
bool formation2::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM formation WHERE ID_FORMATION = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur SQL :" << query.lastError().text();
        return false;
    }

    return true;
}
bool formation2::modifier(int id,QString nom,QString type,QString horaire,int duree,QString lieu,int capacite,int tarif,int id_formateur)
{
    QSqlQuery query;
    query.prepare("UPDATE FORMATION SET ID_FORMATION = :id,NOM = :nom,TYPE_FORMATION = :type,HORAIRE = :horaire,DUREE = :duree,LIEU = :lieu,CAPACITE = :capacite,TARIF = :tarif, IDFORMATEUR = :id_formateur WHERE ID_FORMATION = :id");
    query.bindValue(":id" ,id);
    query.bindValue(":nom" ,nom);
    query.bindValue(":type" ,type);
    query.bindValue(":horaire" ,horaire);
    query.bindValue(":duree" ,duree);
    query.bindValue(":lieu" ,lieu);
    query.bindValue(":capacite" ,capacite);
    query.bindValue(":tarif" ,tarif);
    query.bindValue(":id_formateur" ,id_formateur);


    return query.exec();
}
//fonction trier selon horaire
QSqlQueryModel* formation2::trier_par_horaire()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM formation ORDER BY horaire DESC"); // tri croissant
    return model;
}
//fonction rechercher selon le nom
//bool formation2 :: recherche(QString nom){
//QSqlQuery query;
//QString IdF = QString :: number(id);
//query.prepare("SELECT * FROM FORMATEURS WHERE IDFORMATEUR = :id");
//query.bindValue(":id",IdF);
//if (query.exec()) {
// if (query.next()) { // formateur trouvé
//return true;
//}
//}
//return false;
//}//
