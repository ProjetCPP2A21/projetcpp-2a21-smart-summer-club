#ifndef FORMATION2_H
#define FORMATION2_H
#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class formation2
{
    QString  nom , type ,lieu;
    int id, horaire,duree,capacite,tarif;
public:
    //Constructeurs
    formation2();
    formation2(int,QString,QString,int,int,QString,int,int);


    //Getters
    int getId(){return id;}
    QString getNom(){return nom;}
    QString getType(){return type;}
    int getHoraire(){return horaire;}
    int getDuree(){return duree;}
    QString getLieu(){return lieu;}
    int getCapacite(){return capacite;}
    int getTarif(){return tarif;}

    //Setters
    void setId(int id){this->id=id;}
    void setNom(QString n){nom=n;}
    void setType(QString t){type=t;}
    void setHoraire(int h){this->horaire=h;}
    void setDuree(int d){this->duree=d;}
    void setLieu(QString l){lieu=l;}
    void setCapacite(int c){this->capacite=c;}
    void setTarif(int T){this->tarif=T;}


    //fonctionnalités de base(CRUD)
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);







};

#endif // FORMATION2_H
