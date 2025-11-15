#include "service.h"
#include<QString>
#include<QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include<QSqlQueryModel>
#include <QTableView>
#include  "ui_mainwindow.h"
#include <QPrinter>
#include<QTextDocument>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QAbstractItemModel>
#include <QtCharts/QValueAxis>
#include <QColorAxis>
service::service()
{

}

service::service(int id ,QString n,double m,QString h,int ca,QString s,QString ts) {
    id_service=id;
    nom_service=n;
    montant=m;
    horaire=h;
    capacite=ca;
    status_service=s;
    type_service=ts;

}


bool service::ajoute_service()
{

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Connexion à la base non ouverte.";

        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO service (id_service, nom_service, montant, horaire, capacite, status_service, type_service) "
                  "VALUES (:id_service, :nom_service, :montant, :horaire, :capacite, :status_service, :type_service)");

    query.bindValue(":id_service", id_service);
    query.bindValue(":nom_service", nom_service);
    query.bindValue(":montant", montant);
    query.bindValue(":horaire", horaire);
    query.bindValue(":capacite", capacite);
    query.bindValue(":status_service", status_service);
    query.bindValue(":type_service", type_service);

    return query.exec();
}

QSqlQueryModel* service::affiche()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM service");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_service"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_service"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("horaire"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("capacité"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("status_service"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("type_service"));

    return model;
}


bool service::supprime_service(int id_service)
{
    if (id_service < 0  ) {
        QMessageBox::critical(nullptr, "Erreur", "ID service vide !");
        return false;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM service WHERE id_service = :id");
    query.bindValue(":id", id_service);
    return query.exec();
}

bool service::recherch_id(int id_service)
{
    if (id_service < 0) {
        QMessageBox::critical(nullptr, "Erreur", "ID service vide !");
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM service WHERE id_service = :id");
    query.bindValue(":id", id_service);
    if (!query.exec()) {
        qDebug() << "Erreur SQL:" << query.lastError().text();
        return false;
    }

    return query.next();
}

//return query.exec();


QSqlQueryModel* service::affiche_id(int id_service)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM service WHERE id_service = :id");
    query.bindValue(":id", id_service);
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
        return nullptr;
    }
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_service"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_service"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("horaire"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("capacité"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("status_service"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("type_service"));

    return model;
}

bool service::charge_donner(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM service WHERE id_service = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur SQL :" << query.lastError().text();
        return false;
    }

    if (query.next()) {

        id_service = query.value("id_service").toInt();
        nom_service = query.value("nom_service").toString();
        montant = query.value("montant").toDouble();
        horaire = query.value("horaire").toString();
        capacite = query.value("capacite").toInt();
        status_service = query.value("status_service").toString();
        type_service = query.value("type_service").toString();
        return true;
    }

    qDebug() << "Aucun service trouvé pour ID :" << id;
    return false;
}
bool service::update_service(int id_service)
{
    QSqlQuery query;
    query.prepare("UPDATE service SET nom_service = :nom, montant = :montant, horaire = :horaire, capacite = :capacite, status_service = :status, type_service = :type WHERE id_service = :id");
    query.bindValue(":id", id_service);
    query.bindValue(":nom", nom_service);
    query.bindValue(":montant", montant);
    query.bindValue(":horaire", horaire);
    query.bindValue(":capacite", capacite);
    query.bindValue(":status", status_service);
    query.bindValue(":type", type_service);

    return query.exec();

}
QSqlQueryModel* service:: tri_capacite()
{

    QSqlQuery query;
    query.prepare("select * from service ORDER BY capacite desc");
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
        return nullptr;
    }
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_service"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_service"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("horaire"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("capacité"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("status_service"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("type_service"));

    return model;
}
///exportation en pdf///
void service::export_pdf(QTableView  *view,const QString &filename)
{
    QAbstractItemModel *model = view->model();
    QString html;
    html += "<h2 style='color:blue;'>Liste des services</h2>";
    html += "<table border='1' cellspacing='0' cellpadding='5'>";

    // En-têtes
    html += "<tr>";
    for (int col = 0; col < model->columnCount(); ++col) {
        html += "<th>" + model->headerData(col, Qt::Horizontal).toString() + "</th>";
    }
    html += "</tr>";

    // Lignes
    for (int row = 0; row < model->rowCount(); ++row) {
        html += "<tr>";
        for (int col = 0; col < model->columnCount(); ++col) {
            QString data = model->data(model->index(row, col)).toString();
            html += "<td>" + data + "</td>";
        }
        html += "</tr>";
    }
    html += "</table>";

    QTextDocument doc;
    doc.setHtml(html);

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filename);

    doc.print(&printer);

}
void  service::statistic_capacite(QTableView *view)
{

    /* QAbstractItemModel *model = view->model();

    // Exemple : histogramme de capacité par service
    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Capacité");

    QStringList categories;
    for (int row = 0; row < model->rowCount(); ++row) {
        QString sante = model->data(model->index(row, 0)).toString(); // nom service
        bool ok;
        double capacity = model->data(model->index(row, 1)).toDouble(&ok); // capacité
        if (ok) {
            *set << capacity;
            categories << sante;
        }
    }
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistique de capacité par service");
    chart->createDefaultAxes();

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->setAxisX(axisX, series);

    // Afficher le graphique dans une fenêtre
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(600, 400);
    chartView->show();*/


    // Exemple : histogramme de capacité par service
    QAbstractItemModel *model = view->model();

    // Créer la série et le set
    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Capacité");

    QStringList categories;
    for (int row = 0; row < model->rowCount(); ++row) {
        QString serviceName = model->data(model->index(row, 6)).toString(); // nom service
        bool ok;
        double capacity = model->data(model->index(row, 4)).toDouble(&ok); // capacité (colonne 2)
        qDebug() << "Service:" << serviceName << "Capacité:" << capacity << "ok:" << ok;
        if (ok) {
            *set << capacity;
            categories << serviceName;
        }
    }


    // Vérifier s'il y a des données
    if (set->count() == 0) {
        qDebug() << "Aucune donnée valide pour le graphique.";
        return;
    }

    // Ajouter le set à la série
    series->append(set);

    // Créer le graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistique de capacité par service");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Axe X : catégories
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Service");
    chart->setAxisX(axisX, series);

    // Axe Y : valeurs
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Capacité");
    chart->setAxisY(axisY, series);

    // Afficher le graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setWindowTitle("Statistique de capacité");
    chartView->resize(700, 500);
    //set->setColor(Qt::orange);   // couleur principale des barres
    set->setLabelColor(Qt::red);
    chartView->show();


}




