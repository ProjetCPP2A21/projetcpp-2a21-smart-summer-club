#include "equipement.h"
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>


// --- Constructeur par défaut ---
Equipement::Equipement()
{
    id_equipement = 0;
    nom_equipement = "";
    type_equipement = "";
    prix = 0.0;
    quantite = 0;
    etat = "";
}

// --- Constructeur paramétré ---
Equipement::Equipement(int id, const QString &nom, const QString &type,
                       double p, int q, const QString &e)
{
    id_equipement = id;
    nom_equipement = nom;
    type_equipement = type;
    prix = p;
    quantite = q;
    etat = e;
}

// --- Getters ---
int Equipement::getIdE() const { return id_equipement; }
QString Equipement::getNom() const { return nom_equipement; }
QString Equipement::getType() const { return type_equipement; }
double Equipement::getPrix() const { return prix; }
int Equipement::getQuantite() const { return quantite; }
QString Equipement::getEtat() const { return etat; }

// --- Setters ---
void Equipement::setIdE(int id) { id_equipement = id; }
void Equipement::setNom(const QString &nom) { nom_equipement = nom; }
void Equipement::setType(const QString &type) { type_equipement = type; }
void Equipement::setPrix(double p) { prix = p; }
void Equipement::setQuantite(int q) { quantite = q; }
void Equipement::setEtat(const QString &e) { etat = e; }

// --- Ajouter ---
bool Equipement::ajouter()
{
    QSqlQuery query;
    QString id = QString::number(id_equipement);

    query.prepare("INSERT INTO EQUIPEMENT (ID_EQUIPEMENT, NOM, TYPE, etat, prix, quantite) "
                  "VALUES (:id, :nom, :type, :etat,:prix, :quantite)");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom_equipement);
    query.bindValue(":type", type_equipement);
    query.bindValue(":prix", prix);
    query.bindValue(":quantite", quantite);
    query.bindValue(":etat", etat);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout de l'équipement :" << query.lastError().text();
        return false;
    }
    return true;
}

// --- Afficher ---
QSqlQueryModel* Equipement::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EQUIPEMENT");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("etat"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("quantite"));

    return model;
}

// --- Supprimer ---
bool Equipement::supprimer(int id)
{
    QSqlQuery query;
    QString idE = QString::number(id);
    query.prepare("DELETE FROM EQUIPEMENT WHERE ID_EQUIPEMENT = :id");
    query.bindValue(":id", idE);
    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression :" << query.lastError().text();
        return false;
    }
    return true;
}

// --- Rechercher ---

bool Equipement::recherche_id(int id)
{
    if (id_equipement < 0) {
        QMessageBox::critical(nullptr, "Erreur", "ID equipement vide !");
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM equipement WHERE id_equipement = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Erreur SQL:" << query.lastError().text();
        return false;
    }

    return query.next();
}


// --- Modifier ---
bool Equipement::modifier()
{
    QSqlQuery query;
    QString idE = QString::number(id_equipement);

    query.prepare("UPDATE EQUIPEMENT SET "
                  "NOM = :nom, "
                  "TYPE = :type, "
                  "PRIX = :prix, "
                  "QUANTITE = :quantite, "
                  "ETAT = :etat "
                  "WHERE ID_EQUIPEMENT = :id");
    query.bindValue(":id", idE);
    query.bindValue(":nom", nom_equipement);
    query.bindValue(":type", type_equipement);
    query.bindValue(":prix", prix);
    query.bindValue(":quantite", quantite);
    query.bindValue(":etat", etat);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la modification :" << query.lastError().text();
        return false;
    }
    return true;
}
