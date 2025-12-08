
#ifndef EQUIPEMENTC_H
#define EQUIPEMENTC_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>
#include <QTableView>

class equipementC
{
private:
    QString ID, NOM, PRIX, TYPE, ETAT, QUANTITE;
    QDate DATE_ACHAT;
    int DUREE_VIE;

public:
    // Constructeurs
    equipementC();
    equipementC(QString ID, QString NOM, QString PRIX, QString TYPE, QString ETAT, QString QUANTITE);
    equipementC(QString ID, QString NOM, QString PRIX, QString TYPE, QString ETAT, QString QUANTITE, QDate DATE_ACHAT);
    equipementC(QString ID, QString NOM, QString PRIX, QString TYPE, QString ETAT, QString QUANTITE, QDate DATE_ACHAT, int DUREE_VIE);

    // Getters
    QString getID() const { return ID; }
    QString getNom() const { return NOM; }
    QString getPrix() const { return PRIX; }
    QString getType() const { return TYPE; }
    QString getEtat() const { return ETAT; }
    QString getQuantite() const { return QUANTITE; }
    QDate getDateAchat() const { return DATE_ACHAT; }
    int getDureeVie() const { return DUREE_VIE; }

    // Setters
    void setID(QString ID_p) { this->ID = ID_p; }
    void setNom(QString NOM_p) { this->NOM = NOM_p; }
    void setPrix(QString PRIX_p) { this->PRIX = PRIX_p; }
    void setType(QString TYPE_p) { this->TYPE = TYPE_p; }
    void setEtat(QString ETAT_p) { this->ETAT = ETAT_p; }
    void setQuantite(QString QUANTITE_p) { this->QUANTITE = QUANTITE_p; }
    void setDateAchat(QDate date) { this->DATE_ACHAT = date; }
    void setDureeVie(int duree) { this->DUREE_VIE = duree; }

    // Méthodes CRUD
    bool ajouter_EQUIPEMENT();
    QSqlQueryModel* afficher();
    bool modifier_EQUIPEMENT();
    bool supprimer_EQUIPEMENT(const QString &id);
    QSqlQueryModel* fillEquipement(QString id);
    QSqlQueryModel* trierParType();
    void statistic_taux_utilisation(QTableView *view);
    void export_pdf(QTableView *view, const QString &filename);

    // Méthodes pour la fiche technique
    int calculerAge();
    int calculerDureeVieRestante();
    double calculerPourcentageUsure();
    QString obtenirStatutVie();
    QString genererFicheTechnique();
    QString obtenirRecommandation();
};

#endif // EQUIPEMENTC_H
