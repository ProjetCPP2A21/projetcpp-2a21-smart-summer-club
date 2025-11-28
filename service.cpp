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
#include "apprenant.h"
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


    html += "<tr>";
    for (int col = 0; col < model->columnCount(); ++col) {
        html += "<th>" + model->headerData(col, Qt::Horizontal).toString() + "</th>";
    }
    html += "</tr>";


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



    QAbstractItemModel *model = view->model();


    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Capacité");

    QStringList categories;
    for (int row = 0; row < model->rowCount(); ++row) {
        QString serviceName = model->data(model->index(row, 6)).toString();
        bool ok;
        double capacity = model->data(model->index(row, 4)).toDouble(&ok);
        qDebug() << "Service:" << serviceName << "Capacité:" << capacity << "ok:" << ok;
        if (ok) {
            *set << capacity;
            categories << serviceName;
        }
    }



    if (set->count() == 0) {
        qDebug() << "Aucune donnée valide pour le graphique.";
        return;
    }


    series->append(set);


    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistique de capacité par service");
    chart->setAnimationOptions(QChart::SeriesAnimations);


    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Service");
    chart->setAxisX(axisX, series);


    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Capacité");
    chart->setAxisY(axisY, series);


    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setWindowTitle("Statistique de capacité");
    chartView->resize(700, 500);
    //set->setColor(Qt::orange);   // couleur principale des barres
    set->setLabelColor(Qt::red);
    chartView->show();


}
/*************************************/
//***********metier avances alert systeme*****************//
bool service::inscription(int id_service,int id_apprenant)
{

        QSqlQuery query;
        query.prepare("INSERT INTO beneficier (id_service, id_apprenant) VALUES (:id_service, :id_apprenant)");
        query.bindValue(":id_service", id_service);
        query.bindValue(":id_apprenant", id_apprenant);

        if (!query.exec()) {
            qDebug() << "Erreur insertion:" << query.lastError().text();
            return false;
        }


        return alert_capacite( id_service);


}

#include <QSystemTrayIcon>
#include <QIcon>

bool service::alert_capacite(int id_service)
{
    QSqlQuery req1;
    req1.prepare("SELECT capacite FROM service WHERE id_service = :id");
    req1.bindValue(":id", id_service);
    if (!req1.exec() || !req1.next()) {
        qDebug() << "Erreur récupération capacité:" << req1.lastError().text();
        return false;
    }
    int capacite = req1.value(0).toInt();


    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM beneficier WHERE id_service = :id");
    query.bindValue(":id", id_service);
    if (!query.exec() || !query.next()) {
        qDebug() << "Erreur vérification capacité:" << query.lastError().text();
        return false;
    }
    int nbInscrits = query.value(0).toInt();
    static QSystemTrayIcon trayIcon;
    if (!trayIcon.isVisible()) {
        trayIcon.setIcon(QIcon("C:/Users/karim/OneDrive/Desktop/Nouveau dossier (2)/warning.png"));
        trayIcon.show(); //
    }


    if (nbInscrits == capacite) {
        trayIcon.showMessage("Service complet",
                             "Le service d'id " + QString::number(id_service) + " est complet",
                             QSystemTrayIcon::Information);
        return false;
    }
    if (nbInscrits > capacite) {
            trayIcon.showMessage("service surecharge", "️ nombre d'inscrit  surcharge verfier  id service : "+QString::number(id_service));
            return false;
    } else if (nbInscrits >= capacite/2) {
        int placesRestantes = capacite - nbInscrits;
        trayIcon.showMessage( "Service presque complet",
                                 " Il reste " + QString::number(placesRestantes) +" place dans le service d'id : "+QString::number(id_service)+":");
    }
    return true;
}

bool service::inscription_auto(int id_apprenant)
{
    int id_service = 0;
    if (id_apprenant >= 1001 && id_apprenant <= 1009) id_service = 101;
    else if (id_apprenant >= 1010 && id_apprenant <= 1019) id_service = 102;
    else if (id_apprenant >= 1020 && id_apprenant <= 1029) id_service = 103;
    else if (id_apprenant >= 1030 && id_apprenant <= 1039) id_service = 104;
    else if (id_apprenant >=2000)  id_service=105;

    return inscription(id_service, id_apprenant);
}

//*************************************************//
QSqlQueryModel* service::planfication_service()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery(
        "SELECT a.id_apprenant, " " a.nom AS  apprenant, "
        "       s.id_service, "
        "       s.nom_service AS service, " "       s.capacite, "
        "       'surcharge' AS statut "
        "FROM ( " "    SELECT b.id_service, b.id_apprenant, "
        "           ROW_NUMBER() OVER (PARTITION BY b.id_service ORDER BY b.id_apprenant) AS rang "
        "    FROM beneficier b " ") num "
        "JOIN apprenant a ON num.id_apprenant = a.id_apprenant "
        "JOIN service s ON num.id_service = s.id_service "
        "WHERE num.rang > s.capacite"
        );

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id Apprenant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Apprenant"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Id Service"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Service"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Capacité"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Statut"));

    return model;
}







