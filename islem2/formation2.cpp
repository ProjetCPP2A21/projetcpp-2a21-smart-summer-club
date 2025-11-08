#include "formation2.h"
#include <QSqlQueryModel>
#include <QSqlDatabase>


//constructeur par defaut
formation2::formation2() {}
//constructeur paramétré
formation2::formation2(int id,QString nom,QString type,int horaire,int duree,QString lieu,int capacite,int tarif)
{
    this->id=id;
    this->nom=nom;
    this->type=type;
    this->horaire=horaire;
    this->duree=duree;
    this->lieu=lieu;
    this->capacite=capacite;
    this->tarif=tarif;
}
bool formation2::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(id);
    //prepare() prend la requete en parametre pour la preparer à l'execution
    query.prepare("insert into formation (id , nom , type ,horaire , duree , lieu , capacite , tarif)" "values (:id, :nom, :type, :horaire, :duree, :lieu, :capacite, :tarif)");

    //creation des variables liées
    query.bindValue(":id" ,res);
    query.bindValue(":nom" ,nom);
    query.bindValue(":type" ,type);
    query.bindValue(":horaire" ,horaire);
    query.bindValue(":duree" ,duree);
    query.bindValue(":lieu" ,lieu);
    query.bindValue(":capacite" ,capacite);
    query.bindValue(":tarif" ,tarif);

    return query.exec(); //exec() envoie la requete poue l'executer


}
