#include "equipement.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

equipement::equipement()
{
    ID = "";
    NOM = "";
    PRIX = "";
    TYPE = "";
    ETAT = "";
    QUANTITE = "";
}

equipement::equipement(QString ID, QString NOM, QString PRIX, QString TYPE, QString ETAT, QString QUANTITE)
{
    this->ID = ID;
    this->NOM = NOM;
    this->PRIX = PRIX;
    this->TYPE = TYPE;
    this->ETAT = ETAT;
    this->QUANTITE = QUANTITE;
}

bool equipement::ajouter_EQUIPEMENT()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EQUIPEMENT (ID, NOM, PRIX, TYPE, ETAT, QUANTITE) "
                  "VALUES (:ID, :NOM, :PRIX, :TYPE, :ETAT, :QUANTITE)");

    query.bindValue(":ID", ID);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRIX", PRIX);
    query.bindValue(":TYPE", TYPE);
    query.bindValue(":ETAT", ETAT);
    query.bindValue(":QUANTITE", QUANTITE);

    if (query.exec()) {
        QMessageBox::information(nullptr, QObject::tr("Succès"),
                                 QObject::tr("L'équipement a été ajouté avec succès."));
        return true;
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Échec de l'ajout : %1").arg(query.lastError().text()));
        return false;
    }
}

QSqlQueryModel* equipement::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT ID, NOM, PRIX, TYPE, ETAT, QUANTITE FROM EQUIPEMENT");

    // Définir les en-têtes de colonnes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("QUANTITE"));

    return model;
}

bool equipement::modifier_EQUIPEMENT()
{
    QSqlQuery query;
    query.prepare("UPDATE EQUIPEMENT SET NOM = :NOM, PRIX = :PRIX, TYPE = :TYPE, "
                  "ETAT = :ETAT, QUANTITE = :QUANTITE WHERE ID = :ID");

    query.bindValue(":ID", ID);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRIX", PRIX);
    query.bindValue(":TYPE", TYPE);
    query.bindValue(":ETAT", ETAT);
    query.bindValue(":QUANTITE", QUANTITE);

    if (query.exec()) {
        QMessageBox::information(nullptr, QObject::tr("Succès"),
                                 QObject::tr("L'équipement a été modifié avec succès."));
        return true;
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Échec de la modification : %1").arg(query.lastError().text()));
        return false;
    }
}

bool equipement::supprimer_EQUIPEMENT(const QString &id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EQUIPEMENT WHERE ID = :ID");
    query.bindValue(":ID", id);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Erreur de suppression : " << query.lastError();
        return false;
    }
}
QSqlQueryModel* equipement::fillEquipement(QString id)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM EQUIPEMENT WHERE ID = '" + id + "'");

    if (model->lastError().isValid()) {
        delete model;
        return nullptr;
    }

    return model;
}
