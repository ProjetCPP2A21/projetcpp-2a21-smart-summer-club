#ifndef FORMATEURS_H
#define FORMATEURS_H
#include <QMainWindow>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include<QDate> //modif



class Formateur
{
private:
    int IdFormateur;
    QString NomFormateur;
    QString PrenomFormateur;
    QString ContactFormateur;
    QString SexeFormateur;
    QDate DateEmbauche;//Modif
    QString SpecialiteFormateur;
    float HeuresPrevuesFormateur;
    float SalaireFormateur;

public:
    // Constructeur par défaut
    Formateur();

    // Constructeur paramétré
    Formateur(int id, const QString &nom, const QString &prenom,
              const QString &sexe, const QString &contact,
              const QDate &dateEmbauche, const QString &specialite,
              float heuresPrevues, float salaire);

    // --- Getters ---
    int getIdFormateur() const;
    QString getNomFormateur() const;
    QString getPrenomFormateur() const;
    QString getContactFormateur() const;
    QString getSexeFormateur() const;
    QDate getDateEmbauche() const;//modif
    QString getSpecialiteFormateur() const;
    float getHeuresPrevuesFormateur() const;
    float getSalaireFormateur() const;

    // --- Setters ---
    void setIdFormateur(int id);
    void setNomFormateur(const QString &nom);
    void setPrenomFormateur(const QString &prenom);
    void setContactFormateur(const QString &contact);
    void setSexeFormateur(const QString &sexe);
    void setDateEmbauche(const QDate &date);//modif
    void setSpecialiteFormateur(const QString &spec);
    void setHeuresPrevuesFormateur(float heures);
    void setSalaireFormateur(float salaire);


    // --- Fonctionnalités ---
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel* Afficher_recherche(int id);
    bool supprimer(int id);
    bool recherche(int id);
    bool modifier();//06.11
    QSqlQueryModel * trierDateEmbauche();

};

#endif // FORMATEURS_H

/*#ifndef FORMATEURS_H
#define FORMATEURS_H
#include <QMainWindow>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>



class Formateur
{
private:
    int IdFormateur;
    QString NomFormateur;
    QString PrenomFormateur;
    QString ContactFormateur;
    QString SexeFormateur;
    QString DateEmbauche;
    QString SpecialiteFormateur;
    float HeuresPrevuesFormateur;
    float SalaireFormateur;

public:
    // Constructeur par défaut
    Formateur();

    // Constructeur paramétré
    Formateur(int id, const QString &nom, const QString &prenom,
              const QString &contact, const QString &sexe,
              const QString &dateEmbauche, const QString &specialite,
              float heuresPrevues, float salaire);

    // --- Getters ---
    int getIdFormateur() const;
    QString getNomFormateur() const;
    QString getPrenomFormateur() const;
    QString getContactFormateur() const;
    QString getSexeFormateur() const;
    QString getDateEmbauche() const;
    QString getSpecialiteFormateur() const;
    float getHeuresPrevuesFormateur() const;
    float getSalaireFormateur() const;

    // --- Setters ---
    void setIdFormateur(int id);
    void setNomFormateur(const QString &nom);
    void setPrenomFormateur(const QString &prenom);
    void setContactFormateur(const QString &contact);
    void setSexeFormateur(const QString &sexe);
    void setDateEmbauche(const QString &date);
    void setSpecialiteFormateur(const QString &spec);
    void setHeuresPrevuesFormateur(float heures);
    void setSalaireFormateur(float salaire);


    // --- Fonctionnalités ---
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int id);
    bool recherche(int id);
    bool modifier();//06.11

};

#endif // FORMATEURS_H
*/
