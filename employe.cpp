#include "employe.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

// Constructeur
employe::employe(int id, QString nom, QString prenom, QString poste, int cin, int num,
                 QDate dateembauche, QString email, QString mdp)
{
    this->id = id;
    this->nom = nom;
    this->prenom = prenom;
    this->poste = poste;
    this->cin = cin;
    this->num = num;
    this->dateembauche = dateembauche;
    this->email = email;
    this->mdp = mdp;
}

// ✅ Ajouter un employé
bool employe::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYE "
                  "(ID_EMPLOYE, NOM, PRENOM, cin , mot_de_passe,poste, NUM, EMAIL, DATEEMBAUCHE) "
                  "VALUES (:id, :nom, :prenom, :cin, :mdp, :poste, :num,:email,:dateembauche)");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":cin", cin);
    query.bindValue(":num", num);
    query.bindValue(":email", email);
    query.bindValue(":mdp", mdp);
    query.bindValue(":dateembauche", dateembauche);

    if (!query.exec()) {
        qDebug() << "❌ Erreur ajout :" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur SQL", "Échec d'ajout : " + query.lastError().text());
        return false;
    }

    qDebug() << "✅ Ajout réussi pour :" << nom << prenom;
    return true;
}

// ✅ Afficher
QSqlQueryModel* employe::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYE");

    if (model->lastError().isValid())
        qDebug() << "❌ Erreur affichage :" << model->lastError().text();

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Employé"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("mot_de_passe"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("poste"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("numero"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("email"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("dateembauche"));

    return model;
}

// ✅ Supprimer
bool employe::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYE WHERE ID_EMPLOYE = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "❌ Erreur suppression :" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur SQL", "Échec suppression : " + query.lastError().text());
        return false;
    }

    qDebug() << "✅ Suppression réussie pour ID :" << id;
    return true;
}

// ✅ Modifier
bool employe::modifier(int id)
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYE SET "
                  "NOM = :nom, PRENOM = :prenom, POSTE = :poste, EMAIL = :email, "
                  "MDP = :mdp, CIN = :cin, NUM = :num, DATEEMBAUCHE = :dateembauche "
                  "WHERE ID_EMPLOYE = :id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":email", email);
    query.bindValue(":mdp", mdp);
    query.bindValue(":cin", cin);
    query.bindValue(":num", num);
    query.bindValue(":dateembauche", dateembauche);

    if (!query.exec()) {
        qDebug() << "❌ Erreur modification :" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur SQL", "Échec modification : " + query.lastError().text());
        return false;
    }

    qDebug() << "✅ Modification réussie pour ID :" << id;
    return true;
}

QSqlQueryModel* employe::fill(int id)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    // 1. Prepare + bind → avoids SQL-injection and works with every DB driver
    QSqlQuery q;
    q.prepare("SELECT ID_EMPLOYE, NOM, PRENOM, POSTE, CIN, NUM, EMAIL, MDP, DATEEMBAUCHE "
              "FROM EMPLOYE WHERE ID_EMPLOYE = :id");
    q.bindValue(":id", id);

    if (!q.exec()) {
        qCritical() << "fill() query failed:" << q.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(std::move(q));   // move the executed query into the model
    return model;
}
