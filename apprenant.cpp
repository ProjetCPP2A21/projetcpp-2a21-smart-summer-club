#include "apprenant.h"
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QRegularExpression>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QtCharts>

// Constructeur modifié
apprenant::apprenant(QObject *parent) : QObject(parent)
{
    // Plus d'initialisation UI ici
}

apprenant::apprenant(int id_apprenant, QString nom, QString prenom, QDate date_naiss, QString email)
{
    this->id_apprenant = id_apprenant;
    this->nom = nom;
    this->prenom = prenom;
    this->date_naiss = date_naiss;
    this->email = email;
}

apprenant::~apprenant()
{
    // Plus de delete ui
}

bool apprenant::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(id_apprenant);
    query.prepare("INSERT INTO apprenant (id, nom, prenom, date_naiss, email) "
                  "VALUES (:id_apprenant, :nom, :prenom, :date_naiss, :email)");
    query.bindValue(":id_apprenant", res);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":date_naiss", date_naiss);
    query.bindValue(":email", email);

    if (!query.exec()) {
        qDebug() << "Add failed:" << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel *apprenant::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT id_apprenant, nom, prenom, date_naiss, email FROM apprenant");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date_naiss"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));

    if (model->lastError().isValid()) {
        qDebug() << "Select failed:" << model->lastError().text();
    }
    return model;
}

bool apprenant::supprimer(int id_apprenant)
{
    QSqlQuery query;
    QString res = QString::number(id_apprenant);
    query.prepare("DELETE FROM apprenant WHERE id_apprenant = ?");
    query.addBindValue(res);

    if (!query.exec()) {
        qDebug() << "Delete failed:" << query.lastError().text();
        return false;
    }
    return true;
}

bool apprenant::ajouter_apprenant(int id_apprenant, const QString &nom, const QString &prenom, const QDate &date_naiss, const QString &email)
{
    QSqlQuery query;

    qDebug() << "=== DEBUG AJOUT ORACLE DATE ===";
    QString dateStr = date_naiss.toString("dd/MM/yyyy");
    qDebug() << "Using date format:" << dateStr;

    query.prepare("INSERT INTO apprenant (ID_APPRENANT, NOM, PRENOM, DATE_NAISS, EMAIL) "
                  "VALUES (:id, :nom, :prenom, TO_DATE(:date_naiss, 'DD/MM/YYYY'), :email)");

    query.bindValue(":id", id_apprenant);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":date_naiss", dateStr);
    query.bindValue(":email", email);

    if (query.exec()) {
        qDebug() << "SUCCESS: Added apprenant to apprenant table";
        return true;
    } else {
        qDebug() << "SQL ERROR:" << query.lastError().text();
        return false;
    }
}

bool apprenant::modifier(int id_apprenant, const QString &nom, const QString &prenom, const QDate &date_naiss, const QString &email)
{
    QSqlQuery query;
    QString dateStr = date_naiss.toString("dd/MM/yyyy");

    query.prepare("UPDATE apprenant SET NOM=:nom, PRENOM=:prenom, DATE_NAISS=TO_DATE(:date_naiss, 'DD/MM/YYYY'), EMAIL=:email WHERE ID_APPRENANT=:id");
    query.bindValue(":id", id_apprenant);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":date_naiss", dateStr);
    query.bindValue(":email", email);

    if (query.exec()) {
        qDebug() << "SUCCESS: Modified apprenant";
        return true;
    } else {
        qDebug() << "SQL ERROR:" << query.lastError().text();
        return false;
    }
}

QSqlQueryModel *apprenant::trier_par_date()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT ID_APPRENANT, NOM, PRENOM, DATE_NAISS, EMAIL FROM apprenant ORDER BY DATE_NAISS ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Naiss"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));

    return model;
}

void apprenant::exporter_vers_word()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Exporter vers Word", "liste_apprenants.doc", "Documents Word (*.doc)");

    if (fileName.isEmpty()) return;

    QSqlQueryModel *model = afficher();

    QString html;
    html += "<html><head><meta charset=\"UTF-8\"><title>Liste des Apprenants</title></head><body>";
    html += "<h1>Liste des Apprenants</h1>";
    html += "<table border='1' cellpadding='5' cellspacing='0' width='100%'>";

    // En-têtes du tableau
    html += "<tr style='background-color: #f0f0f0;'>";
    for (int col = 0; col < model->columnCount(); ++col) {
        html += "<th>" + model->headerData(col, Qt::Horizontal).toString() + "</th>";
    }
    html += "</tr>";

    // Données
    for (int row = 0; row < model->rowCount(); ++row) {
        html += "<tr>";
        for (int col = 0; col < model->columnCount(); ++col) {
            html += "<td>" + model->data(model->index(row, col)).toString() + "</td>";
        }
        html += "</tr>";
    }

    html += "</table>";
    html += "<p>Total: " + QString::number(model->rowCount()) + " apprenant</p>";
    html += "</body></html>";

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << html;
        file.close();
        QMessageBox::information(nullptr, "Succès", "Liste exportée vers:\n" + fileName);
    } else {
        QMessageBox::critical(nullptr, "Erreur", "Impossible de sauvegarder le fichier");
    }

    delete model;
}

void apprenant::statistiques_ages()
{
    QSqlQuery query;
    query.exec("SELECT DATE_NAISS FROM apprenant");

    int tranches[4] = {0}; // 0: <15, 1:15, 2:16, 3:17
    QDate aujourdhui = QDate::currentDate();

    while (query.next()) {
        QDate date_naiss = query.value(0).toDate();
        int age = aujourdhui.year() - date_naiss.year();

        if (aujourdhui < QDate(aujourdhui.year(), date_naiss.month(), date_naiss.day())) {
            age--;
        }

        if (age < 15) tranches[0]++;
        else if (age == 15) tranches[1]++;
        else if (age == 16) tranches[2]++;
        else if (age == 17) tranches[3]++;
    }

    // Créer et afficher les statistiques (version texte simple)
    QString stats = "📊 RÉPARTITION PAR TRANCHE D'ÂGE\n\n";
    QStringList labels = {"Moins de 15 ans", "15 ans", "16 ans", "17 ans"};

    int total = tranches[0] + tranches[1] + tranches[2] + tranches[3];

    for (int i = 0; i < 4; i++) {
        if (tranches[i] > 0) {
            double pourcentage = (tranches[i] * 100.0) / total;
            stats += QString("%1: %2 apprenants (%3%)\n")
                         .arg(labels[i])
                         .arg(tranches[i])
                         .arg(QString::number(pourcentage, 'f', 1));
        }
    }

    stats += QString("\n📈 Total: %1 apprenants").arg(total);

    QMessageBox::information(nullptr, "Statistiques", stats);
}
