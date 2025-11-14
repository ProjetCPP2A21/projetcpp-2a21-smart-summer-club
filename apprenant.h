#ifndef APPRENANT_H
#define APPRENANT_H

#include <QObject>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QRegularExpression>

class apprenant : public QObject
{
    Q_OBJECT

    QString nom, prenom, email;
    QDate date_naiss;
    int id_apprenant;

public:
    // Constructeurs
    apprenant(int, QString, QString, QDate, QString);  // Constructeur paramétré

    // Getters
    int getid_apprenant(){return id_apprenant;}
    QString getnom(){return nom;}
    QString getprenom(){return prenom;}
    QDate getdate_naiss(){return date_naiss;}
    QString getemail(){return email;}

    // Setters
    void setid_apprenant(int id){id_apprenant=id;}
    void setnom(QString n){nom=n;}
    void setprenom(QString p){prenom=p;}
    void setdate_naiss(QDate d){date_naiss=d;}
    void setemail(QString e){email=e;}

    // Fonctionnalités CRUD
    bool ajouter();
    bool ajouter_apprenant(int id_apprenant, const QString &nom, const QString &prenom, const QDate &date_naiss, const QString &email);
    QSqlQueryModel *afficher();
    bool supprimer(int id);
    bool modifier(int id_apprenant, const QString &nom, const QString &prenom, const QDate &date_naiss, const QString &email);

    // Méthodes pour les métiers basiques
    QSqlQueryModel *trier_par_date();
    void exporter_vers_word();
    void statistiques_ages();

    explicit apprenant(QObject *parent = nullptr);
    ~apprenant();

private:
    static const QRegularExpression EMAIL_REGEX;
};

#endif // APPRENANT_H
