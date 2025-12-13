#include "employe.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

#include <QSerialPort>








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
// Fichier: employe.cpp

bool employe::ajouter()
{
    QSqlQuery query;

    // 1. Définition de la requête INSERT INTO
    // Assurez-vous que l'ordre des colonnes ici correspond à l'ordre dans VALUES
    // et que toutes les colonnes NOT NULL sont incluses.
    query.prepare("INSERT INTO EMPLOYE "
                  "(IDEMPLOYE, CINEMPLOYE, NOMEMPLOYE, PRENOMEMPLOYE, DATEEMBAUCHE, EMAILEMPLOYE, TELEMPLOYE, POSTEEMPLOYE, MDPEMPLOYE) "
                  "VALUES (:id, :cin, :nom, :prenom, :dateembauche, :email, :num, :poste, :mdp)");

    // 2. Association des valeurs (bindValue)
    // L'ordre des bindValue est moins critique car ils sont nommés, mais il est bon
    // de les lister dans le même ordre que les colonnes pour la lisibilité.
    query.bindValue(":id", id);
    query.bindValue(":cin", cin);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":dateembauche", dateembauche);
    query.bindValue(":email", email);
    query.bindValue(":num", num);    // TELEMPLOYER est lié à 'num' (votre variable de classe)
    query.bindValue(":poste", poste);
    query.bindValue(":mdp", mdp);

    // 3. Exécution et gestion des erreurs
    if (!query.exec()) {
        // En cas d'erreur (comme le trigger invalide ORA-04098), elle sera affichée ici.
        qDebug() << "❌ Erreur ajout (SQL) :" << query.lastError().text();
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

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID EMPLOYE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE D'EMBAUCHE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("POSTE"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("MOT DE PASSE"));


    return model;
}

// ✅ Supprimer
bool employe::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYE WHERE IDEMPLOYE = :id");
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
                  "NOMEMPLOYE = :nom, PRENOMEMPLOYE = :prenom, POSTEEMPLOYE = :poste,  CINEMPLOYE = :cin, TELEMPLOYER = :num, EMAILEMPLOYE = :email, "
                  "MDPEMPLOYE = :mdp, DATEEMBAUCHE = :dateembauche "
                  "WHERE IDEMPLOYE = :id");

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
    q.prepare("SELECT IDEMPLOYE, NOMEMPLOYE, PRENOMEMPLOYE, POSTEEMPLOYE, CINEMPLOYE, TELEMPLOYER, EMAILEMPLOYE, MDPEMPLOYE, DATEEMBAUCHE "
              "FROM EMPLOYE WHERE IDEMPLOYE = :id");
    q.bindValue(":id", id);

    if (!q.exec()) {
        qCritical() << "fill() query failed:" << q.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(std::move(q));   // move the executed query into the model
    return model;
}
//rechercher
QSqlQueryModel* employe::rechercher_email(const QString &email)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT * FROM EMPLOYE WHERE EMAILEMPLOYE LIKE :email");
    query.bindValue(":email", "%" + email + "%");

    if (!query.exec()) {
        qDebug() << "Erreur rechercher_email:" << query.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(query);
    return model;
}
//tri croissant
QSqlQueryModel* employe::trier_date_croissant()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYE ORDER BY DATEEMBAUCHE ASC");
    return model;
}

//mdp
QString employe::recuperer_mdp(int id, int cin, const QDate &dateembauche)
{
    QSqlQuery query;
    // Fetch date and mdp for the given ID and CIN
    query.prepare("SELECT DATEEMBAUCHE, MDPEMPLOYE FROM EMPLOYE WHERE IDEMPLOYE = :id AND CINEMPLOYE = :cin");
    query.bindValue(":id", id);
    query.bindValue(":cin", cin);

    if (query.exec()) {
        while (query.next()) {
            QDate dbDate = query.value(0).toDate();
            QString mdp = query.value(1).toString();

            // Robust date comparison
            if (dbDate == dateembauche) {
                return mdp;
            }
        }
    } else {
        qDebug() << "Query Execution Error:" << query.lastError().text();
    }

    return QString(); // vide si non trouvé
}

// se connecter
bool employe::seConnecter(int id, QString mdp)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYE WHERE IDEMPLOYE = :id AND MDPEMPLOYE = :mdp");
    query.bindValue(":id", id);
    query.bindValue(":mdp", mdp);

    if (query.exec()) {
        if (query.next()) {
            return true;
        }
    } else {
        qDebug() << "Erreur connexion :" << query.lastError().text();
    }
    return false;
}
void employe::rechercherArduino(QSerialPort* arduino, const QString& idText)
{
    // VOTRE FONCTION EXACTE - copier/coller
    if (idText.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur", "Veuillez entrer un ID !");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYE WHERE TRIM(IDEMPLOYE) = :id");
    query.bindValue(":id", idText.trimmed());

    bool idExiste = false;

    if (!query.exec()) {
        qDebug() << "Erreur SQL :" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur SQL", query.lastError().text());
        return;
    }

    if (query.next()) {
        idExiste = true;
        QMessageBox::information(nullptr, "Succès", "ID trouvé dans la base !");
    } else {
        QMessageBox::warning(nullptr, "Non trouvé", "ID introuvable dans la base.");
    }

    if (arduino && arduino->isOpen()) {
        QString signal = idExiste ? "1" : "0";
        QByteArray data = signal.toLatin1();
        arduino->write(data);
        arduino->flush();

        qDebug() << "Envoyé à Arduino :" << data;
    } else {
        QMessageBox::critical(nullptr, "Erreur Arduino", "Arduino n'est pas connecté !");
    }
}
QString employe::getPosteById(int id)
{
    QSqlQuery query;
    query.prepare("SELECT POSTEEMPLOYE FROM EMPLOYE WHERE IDEMPLOYE = :id");  // ✅ CORRECT
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }

    qDebug() << "❌ Erreur getPosteById:" << query.lastError().text();
    return QString();
}

