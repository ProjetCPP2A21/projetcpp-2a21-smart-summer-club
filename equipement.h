#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>

class equipement
{
private:
    QString ID, NOM, PRIX, TYPE, ETAT, QUANTITE;

public:
    // Constructeurs
    equipement();
    equipement(QString ID, QString NOM, QString PRIX, QString TYPE, QString ETAT, QString QUANTITE);

    // Getters
    QString getID() { return ID; }
    QString getNom() { return NOM; }
    QString getPrix() { return PRIX; }
    QString getType() { return TYPE; }
    QString getEtat() { return ETAT; }
    QString getQuantite() { return QUANTITE; }

    // Setters
    void setID(QString ID_p) { this->ID = ID_p; }
    void setNom(QString NOM_p) { this->NOM = NOM_p; }
    void setPrix(QString PRIX_p) { this->PRIX = PRIX_p; }
    void setType(QString TYPE_p) { this->TYPE = TYPE_p; }
    void setEtat(QString ETAT_p) { this->ETAT = ETAT_p; }
    void setQuantite(QString QUANTITE_p) { this->QUANTITE = QUANTITE_p; }

    // Méthodes CRUD
    bool ajouter_EQUIPEMENT();
    QSqlQueryModel* afficher();
    bool modifier_EQUIPEMENT();
    bool supprimer_EQUIPEMENT(const QString &id);
    void clearFieldsEquipement();
    QSqlQueryModel* fillEquipement(QString id);


};

#endif // EQUIPEMENTC_H
