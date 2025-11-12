#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QObject>

class Equipement
{
private:
    int id_equipement;
    QString nom_equipement;
    QString type_equipement;
    double prix;
    int quantite;
    QString etat; // Exemple : "Disponible", "En maintenance"

public:
    // --- Constructeurs ---
    Equipement();
    Equipement(int id, const QString &nom, const QString &type,
               double p, int q, const QString &etat);
    ~Equipement() {}

    // --- Getters ---
    int getIdE() const;
    QString getNom() const;
    QString getType() const;
    double getPrix() const;
    int getQuantite() const;
    QString getEtat() const;

    // --- Setters ---
    void setIdE(int id);
    void setNom(const QString &nom);
    void setType(const QString &type);
    void setPrix(double prix);
    void setQuantite(int quantite);
    void setEtat(const QString &etat);

    // --- Méthodes principales ---
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
    bool modifier();
    bool recherche_id(int id);
};

#endif // EQUIPEMENT_H

