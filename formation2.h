#ifndef FORMATION2_H
#define FORMATION2_H
#include<QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMainWindow>
#include <QTableView>



class formation2
{
    QString nom, type, horaire, lieu;
    QDate dateformation;
    int id, duree, capacite, tarif, id_formateur;
    QString m_lastError;
public:
    //Constructeurs
    formation2();
    formation2(int id, QString nom, QString type, QString horaire, QDate dateformation,
               int duree, QString lieu, int capacite, int tarif, int id_formateur );



    //Getters
    int getId(){return id;}
    QString getNom(){return nom;}
    QString getType(){return type;}
    QString getHoraire(){return horaire;}
    QDate getDateFormation(){return dateformation;}
    int getDuree(){return duree;}
    QString getLieu(){return lieu;}
    int getCapacite(){return capacite;}
    int getTarif(){return tarif;}
    int getid_formateur(){return id_formateur;}


    //Setters
    void setId(int id){this->id=id;}
    void setNom(QString n){nom=n;}
    void setType(QString t){type=t;}
    void setHoraire(QString h){this->horaire=h;}
    void setDateFormation(const QDate &d){this->dateformation=d;}
    void setDuree(int d){this->duree=d;}
    void setLieu(QString l){lieu=l;}
    void setCapacite(int c){this->capacite=c;}
    void setTarif(int T){this->tarif=T;}
    void setid_formateur(int id2){this->id_formateur=id2;}



    //fonctionnalités de base(CRUD)
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int id);
    bool modifier(int id, QString nom, QString type, QString horaire, QDate dateformation,
                  int duree, QString lieu, int capacite, int tarif,int id_formateur);
    QSqlQueryModel* trier_par_horaire();
    QSqlQueryModel* rechercherParNom(const QString &nom);
    bool exporterDoc(QSqlQueryModel *model, QString cheminFichier);
    QString lastError() const { return m_lastError; }
    //  Fonction d’exportation vers Word
    //void exporterWord(QSqlQueryModel* model);








};

#endif // FORMATION2_H
