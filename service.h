#ifndef SERVICE_H
#define SERVICE_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QTableWidget>
class service
{

private:
    int id_service;
    QString nom_service;
    double montant;
    QString horaire;
    int capacite;
    QString status_service;
    QString type_service;

public:
    service();
    service(int id ,QString n,double m,QString h,int ca,QString s,QString ts);

    //getters//
    int getid()  {return id_service;}
    QString getnom_service(){return nom_service;}
    double getmontant(){return montant;}
     QString gethoraire(){return horaire;}
    int getcapacite(){return capacite;}
    QString getstatus(){return status_service;}
    QString gettype_service(){return type_service;}
    //setters//
    void setid(int id){id_service=id;}
    void setnom(QString n){nom_service=n;}
    void settype(QString ts){type_service=ts;}
    void setcapacite(int ca){capacite=ca;}
    void sethoraire(QString  h){horaire=h;}
    void setstatus (QString s){status_service=s;}
    void setmontant(double m){montant=m;}


    bool ajoute_service();
    QSqlQueryModel* affiche();
    bool recherch_id(int id_service);
    QSqlQueryModel* affiche_id(int id_service);
    bool supprime_service(int id_service);
    bool charge_donner(int id_service);
    bool update_service(int id_service);






};

#endif // SERVICE_H
