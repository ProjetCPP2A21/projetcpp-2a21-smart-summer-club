#include "formateurs.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QObject>
#include <QTableView>


    // Constructeur par défaut
Formateur :: Formateur(){
    IdFormateur = 0;     // null ??
    NomFormateur ="";
    PrenomFormateur = "";
    ContactFormateur="";
    SexeFormateur="";
    DateEmbauche="";
    SpecialiteFormateur="";
    HeuresPrevuesFormateur=00.00;
    SalaireFormateur=00.00;
};

    // Constructeur paramétré
Formateur :: Formateur(int id, const QString &nom, const QString &prenom,
              const QString &contact, const QString &sexe,
              const QString &date, const QString &specialite,
              float h, float s){


        IdFormateur = id;
        NomFormateur = nom;
        PrenomFormateur = prenom;
        ContactFormateur= contact;
        SexeFormateur= sexe;
        DateEmbauche= date;
        SpecialiteFormateur=specialite;
        HeuresPrevuesFormateur= h;
        SalaireFormateur=s;
    };

    // --- Getters ---
    int Formateur :: getIdFormateur() const {return IdFormateur;}
    QString Formateur :: getNomFormateur() const {return NomFormateur;}
    QString Formateur :: getPrenomFormateur() const {return PrenomFormateur;}
    QString Formateur :: getContactFormateur() const {return ContactFormateur;}
    QString Formateur :: getSexeFormateur() const {return SexeFormateur;}
    QString Formateur :: getDateEmbauche() const {return DateEmbauche;}
    QString Formateur :: getSpecialiteFormateur() const {return SpecialiteFormateur;}
    float Formateur :: getHeuresPrevuesFormateur() const {return HeuresPrevuesFormateur;}
    float Formateur :: getSalaireFormateur() const{return SalaireFormateur;}

    // --- Setters ---
    void Formateur :: setIdFormateur(int id){IdFormateur = id;}
    void Formateur :: setNomFormateur(const QString &nom){NomFormateur=nom;}
    void Formateur :: setPrenomFormateur(const QString &prenom){PrenomFormateur = prenom;}
    void Formateur :: setContactFormateur(const QString &contact){ContactFormateur=contact;}
    void Formateur :: setSexeFormateur(const QString &sexe){SexeFormateur= sexe;}
    void Formateur :: setDateEmbauche(const QString &date){DateEmbauche = date;}
    void Formateur :: setSpecialiteFormateur(const QString &spec){SpecialiteFormateur = spec;}
    void Formateur :: setHeuresPrevuesFormateur(float heures){HeuresPrevuesFormateur= heures;}
    void Formateur :: setSalaireFormateur(float salaire){SalaireFormateur=salaire;}

//30.10

    bool Formateur :: ajouter()
    {
        QSqlQuery query;
        QString IdF = QString ::number(IdFormateur);
        query.prepare("INSERT INTO FORMATEURS(IDFORMATEUR,NOM,PRENOM,SEXE,CONTACT,DATE_EMBAUCHE,SPECIALITE,NB_HEURES_PREVUES,SALAIRE)" "VALUES(:Id,:Nom,:Prenom,:Sexe,:Contact,:Date,:Specialite,:HeuresPrevues,:Salaire)");
        query.bindValue(":Id",IdF);
        query.bindValue(":Nom",NomFormateur);
        query.bindValue(":Prenom",PrenomFormateur);
        query.bindValue(":Sexe",SexeFormateur);
        query.bindValue(":Contact",ContactFormateur);
        query.bindValue(":Date",DateEmbauche);
        query.bindValue(":Specialite",SpecialiteFormateur);
        query.bindValue(":HeuresPrevues",HeuresPrevuesFormateur);
        query.bindValue(":Salaire",SalaireFormateur);
        return query.exec();
    }



/*
    QSqlQueryModel * Formateur :: afficher()
    {
        QSqlQuery * model=new QSqlQueryModel();
        model ->setQuery("SELECT * FROM Formateur");
        model -> setHeaderData(0,Qt::Horizental,QObject::tr(":Id"));
        model -> setHeaderData(1,Qt::Horizental,QObject::tr(":Nom"));
        model -> setHeaderData(2,Qt::Horizental,QObject::tr(":Prenom"));
        model -> setHeaderData(3,Qt::Horizental,QObject::tr(":Sexe"));
        model -> setHeaderData(4,Qt::Horizental,QObject::tr(":Contact"));
        model -> setHeaderData(5,Qt::Horizental,QObject::tr(":Date"));
        model -> setHeaderData(6,Qt::Horizental,QObject::tr(":Specialite"));
        model -> setHeaderData(7,Qt::Horizental,QObject::tr(":HeuresPrevues"));
        model -> setHeaderData(8,Qt::Horizental,QObject::tr(":Salaire"));

        return model;
    }
*/


/*
    bool Formateur :: supprimer(int id){
        QSqlQuery query;
        QString IdF = QString :: number(id);
        query.prepare("DELETE FROM FORMATEUR WHERE IDFORMATEUR = :id");
        query.bindValue(":id",IdF);
        return query.exec();
    }
*/



// manque fonction SELECTIONNER ==> recuperation de l id pour suppression
// mehtode modifier un formateur ??
