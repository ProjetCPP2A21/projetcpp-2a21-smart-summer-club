#ifndef APPRENANT_H
#define APPRENANT_H

#include "ui_apprenant.h"
#include <QWidget>
#include <QObject>
#include <QMainWindow>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

#include <QDialog>

namespace Ui {
class apprenant;
}

class apprenant : public QWidget
{
    Q_OBJECT
    QString nom, prenom, email;
    QDate date_naiss;
    int id_apprenant;


public:
    //constructeurs
    apprenant(){}
    apprenant(int,QString,QString,QDate,QString);
    //getters
    int getid_apprenant(){return id_apprenant;}
    QString getnom(){return nom;}
    QString getprenom(){return prenom;}
    QDate getdate_naiss(){return date_naiss;}
    QString getemail(){return email;}
    //setters
    void setid_apprenant(int id){id_apprenant=id;}
    void setnom(QString n){nom=n;}
    void setprenom(QString p){prenom=p;}
    void setdate_naiss(QDate d){date_naiss=d;}
    void setemail(QString e){email=e;}
    //fonctionnalités de base relatives à l'entité apprenant
    bool ajouter_apprenant(int id_apprenant, const QString &nom, const QString &prenom, const QDate &date_naiss, const QString &email);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);


    explicit apprenant(QWidget *parent = nullptr);
    ~apprenant();
private slots:
    void on_pushButton_AJOUTER_3_clicked();  // bouton qui ouvre interface apprenants
    void on_pushButton_18_clicked();
    void on_pushButton_ANNULER_3_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_19_clicked();
    void on_pushButton_20_clicked();
    void on_pushButton_stat_clicked();
    void on_lineEdit_RECHERCHE_2_textChanged(const QString &arg1);

private:
    Ui::apprenant *ui;
    static const QRegularExpression EMAIL_REGEX;
    apprenant *Etmp;

};

#endif // APP_H
