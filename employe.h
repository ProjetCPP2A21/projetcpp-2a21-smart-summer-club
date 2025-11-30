#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QDate>

class employe
{
private:
    QString nom, prenom, poste, email, mdp;
    QDate dateembauche;  // ✅ passer de QString à QDate
    int id, cin, num;

public:
    employe() {}
    // constructeur clair et dans l'ordre logique
    employe(int id, QString nom, QString prenom, QString poste, int cin, int num,
            QDate dateembauche, QString email, QString mdp);

    // getters
    QString getnom() const { return nom; }
    QString getprenom() const { return prenom; }
    QDate getdateembauche() const { return dateembauche; } // ✅ retourne QDate
    QString getposte() const { return poste; }
    QString getemail() const { return email; }
    QString getmdp() const { return mdp; }
    int getcin() const { return cin; }
    int getnum() const { return num; }
    int getID() const { return id; }

    // setters
    void setnom(const QString &n) { nom = n; }
    void setprenom(const QString &p) { prenom = p; }
    void setdateembauche(const QDate &d) { dateembauche = d; } // ✅ setter QDate
    void setposte(const QString &po) { poste = po; }
    void setemail(const QString &e) { email = e; }
    void setmdp(const QString &m) { mdp = m; }
    void setcin(int c) { cin = c; }
    void setnum(int nm) { num = nm; }
    void setID(int i) { id = i; }

    // fonctionnalités
    bool ajouter();
    bool supprimer(int id);
    bool modifier(int id);
    QSqlQueryModel* afficher();
    QSqlQueryModel* fill(int id);
};

#endif // EMPLOYE_H
