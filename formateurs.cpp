#include "formateurs.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QObject>
#include <QTableView>
#include <QSqlError>

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
        query.prepare("INSERT INTO FORMATEUR(IDFORMATEUR,NOM,PRENOM,SEXE,CONTACT,DATE_EMBAUCHE,SPECIALITE,NB_HEURES_PREVUES,SALAIRE)" "VALUES(:Id,:Nom,:Prenom,:Sexe,:Contact,:Date,:Specialite,:HeuresPrevues,:Salaire)");
        query.bindValue(":Id",IdF);
        query.bindValue(":Nom",NomFormateur);
        query.bindValue(":Prenom",PrenomFormateur);
        query.bindValue(":Sexe",SexeFormateur);
        query.bindValue(":Contact",ContactFormateur);
        query.bindValue(":Date",DateEmbauche);
        query.bindValue(":Specialite",SpecialiteFormateur);
        query.bindValue(":HeuresPrevues",HeuresPrevuesFormateur);
        query.bindValue(":Salaire",SalaireFormateur);
        //return query.exec();
        if (!query.exec()) {
            qDebug() << "Erreur SQL:" << query.lastError().text();
            return false;
        }
        return true;
    }




QSqlQueryModel * Formateur :: afficher()
    {
        QSqlQueryModel * model=new QSqlQueryModel();
        model ->setQuery("SELECT * FROM FORMATEUR");

        model -> setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
        model -> setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
        model -> setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
        model -> setHeaderData(3,Qt::Horizontal,QObject::tr("SEXE"));
        model -> setHeaderData(4,Qt::Horizontal,QObject::tr("CONTACT"));
        model -> setHeaderData(5,Qt::Horizontal,QObject::tr("DATE"));
        model -> setHeaderData(6,Qt::Horizontal,QObject::tr("SPECIALITE"));
        model -> setHeaderData(7,Qt::Horizontal,QObject::tr("HEURES_PREVUES"));
        model -> setHeaderData(8,Qt::Horizontal,QObject::tr("SALAIRE"));

        return model;
    }


    // NE FONCTIONNE PAS CORRECTEMENT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    bool Formateur :: supprimer(int id){
        QSqlQuery query;
        QString IdF = QString :: number(id);
        query.prepare("DELETE FROM FORMATEUR WHERE IDFORMATEUR = :id;");
        query.bindValue(":id",IdF);
        return query.exec();
    }



bool Formateur :: recherche(int id){
        QSqlQuery query;
        QString IdF = QString :: number(id);
        query.prepare("SELECT * FROM FORMATEUR WHERE IDFORMATEUR = :id");
        query.bindValue(":id",IdF);
        if (query.exec()) {
            if (query.next()) { // formateur trouvé
                this->NomFormateur = query.value("NOM").toString();
                this->PrenomFormateur = query.value("PRENOM").toString();
                this->SexeFormateur = query.value("SEXE").toString();
                this->ContactFormateur = query.value("CONTACT").toString();
                this->SpecialiteFormateur = query.value("SPECIALITE").toString();
                //float salaire = query.value("SALAIRE").toFloat();
                //date = query.value("DATE_EMBAUCHE");
                //heures = query.value("NB_HEURES_PREVUES");
                return true;
            }
        }
        return false;
    }

    bool Formateur::modifier(){
        QSqlQuery query;
        QString IdF = QString ::number(IdFormateur);
        query.prepare("UPDATE FORMATEUR SET "
                      "NOM= :Nom, "
                      "PRENOM= :Prenom, "
                      "SEXE= :Sexe, "
                      "CONTACT= :Contact, "
                      "DATE_EMBAUCHE= :Date, "
                      "SPECIALITE= :Specialite, "
                      "NB_HEURES_PREVUES= :HeuresPrevues, "
                      "SALAIRE= :Salaire "
                      "WHERE IDFORMATEUR = :Id");
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
