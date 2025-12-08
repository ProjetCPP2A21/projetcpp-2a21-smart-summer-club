#include "equipement.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QChart>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QTableView>
#include <QBrush>
#include <QColor>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextTable>
#include <QFileDialog>
#include <QPrinter>
#include <QPageSize>
#include <QDesktopServices>
#include <QDateTime>
#include <QDir>
#include <QPainter>
#include <QRegularExpression>

equipementC::equipementC()
{
    ID = "";
    NOM = "";
    PRIX = "";
    TYPE = "";
    ETAT = "";
    QUANTITE = "";
    DATE_ACHAT = QDate::currentDate();
    DUREE_VIE = 0;
}

equipementC::equipementC(QString ID, QString NOM, QString PRIX, QString TYPE, QString ETAT, QString QUANTITE)
{
    this->ID = ID;
    this->NOM = NOM;
    this->PRIX = PRIX;
    this->TYPE = TYPE;
    this->ETAT = ETAT;
    this->QUANTITE = QUANTITE;
    this->DATE_ACHAT = QDate::currentDate();
    this->DUREE_VIE = 5; // Valeur par défaut
}

equipementC::equipementC(QString ID, QString NOM, QString PRIX, QString TYPE, QString ETAT, QString QUANTITE, QDate DATE_ACHAT)
{
    this->ID = ID;
    this->NOM = NOM;
    this->PRIX = PRIX;
    this->TYPE = TYPE;
    this->ETAT = ETAT;
    this->QUANTITE = QUANTITE;
    this->DATE_ACHAT = DATE_ACHAT;
    this->DUREE_VIE = 5; // Valeur par défaut
}

equipementC::equipementC(QString ID, QString NOM, QString PRIX, QString TYPE, QString ETAT, QString QUANTITE, QDate DATE_ACHAT, int DUREE_VIE)
{
    this->ID = ID;
    this->NOM = NOM;
    this->PRIX = PRIX;
    this->TYPE = TYPE;
    this->ETAT = ETAT;
    this->QUANTITE = QUANTITE;
    this->DATE_ACHAT = DATE_ACHAT;
    this->DUREE_VIE = DUREE_VIE;
}

bool equipementC::ajouter_EQUIPEMENT()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EQUIPEMENT (ID, NOM, PRIX, TYPE, ETAT, QUANTITE, DATE_ACHAT, DUREE_VIE) "
                  "VALUES (:ID, :NOM, :PRIX, :TYPE, :ETAT, :QUANTITE, :DATE_ACHAT, :DUREE_VIE)");

    query.bindValue(":ID", ID);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRIX", PRIX);
    query.bindValue(":TYPE", TYPE);
    query.bindValue(":ETAT", ETAT);
    query.bindValue(":QUANTITE", QUANTITE);
    query.bindValue(":DATE_ACHAT", DATE_ACHAT);
    query.bindValue(":DUREE_VIE", DUREE_VIE);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Erreur d'ajout:" << query.lastError().text();
        return false;
    }
}

QSqlQueryModel* equipementC::afficher()
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

bool equipementC::modifier_EQUIPEMENT()
{
    QSqlQuery query;
    query.prepare("UPDATE EQUIPEMENT SET NOM = :NOM, PRIX = :PRIX, TYPE = :TYPE, "
                  "ETAT = :ETAT, QUANTITE = :QUANTITE, DATE_ACHAT = :DATE_ACHAT, DUREE_VIE = :DUREE_VIE WHERE ID = :ID");

    query.bindValue(":ID", ID);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRIX", PRIX);
    query.bindValue(":TYPE", TYPE);
    query.bindValue(":ETAT", ETAT);
    query.bindValue(":QUANTITE", QUANTITE);
    query.bindValue(":DATE_ACHAT", DATE_ACHAT);
    query.bindValue(":DUREE_VIE", DUREE_VIE);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Erreur de modification:" << query.lastError().text();
        return false;
    }
}

bool equipementC::supprimer_EQUIPEMENT(const QString &id)
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

QSqlQueryModel* equipementC::fillEquipement(QString id)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM EQUIPEMENT WHERE ID = '" + id + "'");

    if (model->lastError().isValid()) {
        delete model;
        return nullptr;
    }

    return model;
}

QSqlQueryModel* equipementC::trierParType()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT ID, NOM, PRIX, TYPE, ETAT, QUANTITE FROM EQUIPEMENT ORDER BY TYPE");

    // Définir les en-têtes de colonnes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("QUANTITE"));

    return model;
}

void equipementC::statistic_taux_utilisation(QTableView *view)
{
    // Récupérer le modèle de la table
    QAbstractItemModel *model = view->model();

    // Créer la série et le set
    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Nombre d'équipements");

    QStringList categories;

    // Compter les équipements par état (taux d'utilisation)
    QMap<QString, int> countByEtat;

    for (int row = 0; row < model->rowCount(); ++row) {
        QString etat = model->data(model->index(row, 4)).toString(); // colonne ETAT
        countByEtat[etat]++;
    }

    // Remplir les données du graphique
    for (auto it = countByEtat.begin(); it != countByEtat.end(); ++it) {
        *set << it.value();
        categories << it.key();
        qDebug() << "État:" << it.key() << "Nombre:" << it.value();
    }

    // Vérifier s'il y a des données
    if (set->count() == 0) {
        qDebug() << "Aucune donnée valide pour le graphique.";
        delete set;
        delete series;
        return;
    }

    // Ajouter le set à la série
    series->append(set);

    // Créer le graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Nombre d'équipements par taux d'utilisation");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Axe X : catégories (états)
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("État d'utilisation");
    chart->setAxisX(axisX, series);

    // Axe Y : valeurs (nombre d'équipements)
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Nombre d'équipements");
    axisY->setLabelFormat("%d");
    chart->setAxisY(axisY, series);

    // Personnaliser les couleurs
    set->setColor(QColor(70, 130, 180)); // Bleu acier
    set->setLabelColor(Qt::black);

    // Afficher le graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setWindowTitle("Statistique - Équipements par taux d'utilisation");
    chartView->resize(600, 400);
    chartView->show();
}

void equipementC::export_pdf(QTableView *view, const QString &filename)
{
    QAbstractItemModel *model = view->model();
    QString html;
    html += "<h2 style='color:blue;'>Liste des equipements</h2>";
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

int equipementC::calculerAge()
{
    QDate currentDate = QDate::currentDate();
    return DATE_ACHAT.daysTo(currentDate) / 365;
}

int equipementC::calculerDureeVieRestante()
{
    int age = calculerAge();
    return qMax(0, DUREE_VIE - age);
}

double equipementC::calculerPourcentageUsure()
{
    if (DUREE_VIE <= 0) return 0;
    int age = calculerAge();
    return qMin(100.0, (age * 100.0) / DUREE_VIE);
}

QString equipementC::obtenirStatutVie()
{
    double usure = calculerPourcentageUsure();

    if (usure >= 80) return "🔴 FIN DE VIE (À REMPLACER)";
    else if (usure >= 60) return "🟠 USURE AVANCÉE";
    else if (usure >= 40) return "🟡 USURE MODÉRÉE";
    else if (usure >= 20) return "🔵 BON ÉTAT";
    else return "🟢 TRÈS BON ÉTAT";
}

QString equipementC::genererFicheTechnique()
{
    // Calculs préliminaires
    int age = calculerAge();
    int vieRestante = calculerDureeVieRestante();
    double valeurResiduelle = getPrix().toDouble() * (1 - (age * 1.0) / getDureeVie());
    double coutJournalier = getPrix().toDouble() / (getDureeVie() * 365);
    QString statutUrgence = obtenirStatutVie();
    double pourcentageUsure = calculerPourcentageUsure();

    // Déterminer la classe CSS pour la barre de progression et le badge
    QString progressClass, badgeClass, badgeText;
    if (pourcentageUsure < 40) {
        progressClass = "progress-bon";
        badgeClass = "statut-bon";
        badgeText = "🟢 EXCELLENT";
    } else if (pourcentageUsure < 70) {
        progressClass = "progress-moyen";
        badgeClass = "statut-moyen";
        badgeText = "🟡 BON";
    } else {
        progressClass = "progress-critique";
        badgeClass = "statut-critique";
        badgeText = "🔴 ATTENTION";
    }

    // Génération de la fiche technique avec design moderne
    QString fiche = QString(
                        "<!DOCTYPE html>"
                        "<html>"
                        "<head>"
                        "<meta charset='UTF-8'>"
                        "<style>"
                        "* { margin: 0; padding: 0; box-sizing: border-box; }"
                        "body { "
                        "   font-family: 'Segoe UI', system-ui, -apple-system, sans-serif; "
                        "   background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); "
                        "   min-height: 100vh; padding: 20px; "
                        "   display: flex; justify-content: center; align-items: flex-start;"
                        "}"
                        ".fiche-container { "
                        "   background: white; "
                        "   border-radius: 20px; "
                        "   box-shadow: 0 20px 40px rgba(0,0,0,0.1); "
                        "   padding: 30px; "
                        "   max-width: 95%; "
                        "   width: 100%; "
                        "   margin: 0 auto; "
                        "}"
                        ".header { "
                        "   text-align: center; "
                        "   background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); "
                        "   color: white; "
                        "   padding: 25px; "
                        "   border-radius: 15px; "
                        "   margin-bottom: 30px; "
                        "   position: relative; "
                        "   overflow: hidden; "
                        "}"
                        ".header::before { "
                        "   content: ''; "
                        "   position: absolute; "
                        "   top: -50%; "
                        "   left: -50%; "
                        "   width: 200%; "
                        "   height: 200%; "
                        "   background: radial-gradient(circle, rgba(255,255,255,0.1) 1%, transparent 1%); "
                        "   background-size: 20px 20px; "
                        "   animation: float 20s linear infinite; "
                        "}"
                        "@keyframes float { "
                        "   0% { transform: translate(0, 0) rotate(0deg); }"
                        "   100% { transform: translate(-20px, -20px) rotate(360deg); }"
                        "}"
                        ".header h1 { "
                        "   margin: 0; "
                        "   font-size: 28px; "
                        "   font-weight: 700; "
                        "   letter-spacing: 1px; "
                        "   position: relative; "
                        "   z-index: 2; "
                        "}"
                        ".header h2 { "
                        "   margin: 8px 0 0 0; "
                        "   font-size: 16px; "
                        "   opacity: 0.9; "
                        "   font-weight: 400; "
                        "   position: relative; "
                        "   z-index: 2; "
                        "}"
                        ".grid-container { "
                        "   display: grid; "
                        "   grid-template-columns: repeat(auto-fit, minmax(350px, 1fr)); "
                        "   gap: 25px; "
                        "   margin-bottom: 25px; "
                        "}"
                        ".card { "
                        "   background: #f8f9fa; "
                        "   border-radius: 15px; "
                        "   padding: 25px; "
                        "   border-left: 5px solid #667eea; "
                        "   transition: transform 0.3s ease, box-shadow 0.3s ease; "
                        "   height: fit-content; "
                        "}"
                        ".card:hover { "
                        "   transform: translateY(-5px); "
                        "   box-shadow: 0 10px 25px rgba(0,0,0,0.1); "
                        "}"
                        ".card-title { "
                        "   color: #2c3e50; "
                        "   font-size: 18px; "
                        "   font-weight: 700; "
                        "   margin-bottom: 20px; "
                        "   display: flex; "
                        "   align-items: center; "
                        "   gap: 10px; "
                        "}"
                        ".info-item { "
                        "   display: flex; "
                        "   justify-content: space-between; "
                        "   align-items: center; "
                        "   padding: 12px 0; "
                        "   border-bottom: 1px solid rgba(0,0,0,0.05); "
                        "}"
                        ".info-item:last-child { border-bottom: none; }"
                        ".info-label { "
                        "   font-weight: 600; "
                        "   color: #555; "
                        "   font-size: 14px; "
                        "   flex: 1; "
                        "}"
                        ".info-value { "
                        "   color: #2c3e50; "
                        "   font-size: 15px; "
                        "   font-weight: 600; "
                        "   text-align: right; "
                        "   flex: 1; "
                        "}"
                        ".progress-container { "
                        "   background: #e9ecef; "
                        "   border-radius: 10px; "
                        "   height: 12px; "
                        "   margin: 8px 0; "
                        "   overflow: hidden; "
                        "   position: relative; "
                        "}"
                        ".progress-fill { "
                        "   height: 100%; "
                        "   border-radius: 10px; "
                        "   transition: width 0.5s ease; "
                        "   position: relative; "
                        "}"
                        ".progress-fill::after { "
                        "   content: ''; "
                        "   position: absolute; "
                        "   top: 0; "
                        "   left: 0; "
                        "   right: 0; "
                        "   bottom: 0; "
                        "   background: linear-gradient(90deg, transparent, rgba(255,255,255,0.3), transparent); "
                        "   animation: shimmer 2s infinite; "
                        "}"
                        "@keyframes shimmer { "
                        "   0% { transform: translateX(-100%); }"
                        "   100% { transform: translateX(100%); }"
                        "}"
                        ".progress-bon { background: linear-gradient(90deg, #28a745, #20c997); }"
                        ".progress-moyen { background: linear-gradient(90deg, #ffc107, #fd7e14); }"
                        ".progress-critique { background: linear-gradient(90deg, #dc3545, #e83e8c); }"
                        ".statut-badge { "
                        "   display: inline-flex; "
                        "   align-items: center; "
                        "   gap: 6px; "
                        "   padding: 8px 16px; "
                        "   border-radius: 25px; "
                        "   font-size: 12px; "
                        "   font-weight: 700; "
                        "   margin-top: 5px; "
                        "}"
                        ".statut-bon { background: #d4edda; color: #155724; border: 2px solid #c3e6cb; }"
                        ".statut-moyen { background: #fff3cd; color: #856404; border: 2px solid #ffeaa7; }"
                        ".statut-critique { background: #f8d7da; color: #721c24; border: 2px solid #f5c6cb; }"
                        ".highlight-box { "
                        "   background: linear-gradient(135deg, #fff3cd, #ffeaa7); "
                        "   padding: 20px; "
                        "   border-radius: 12px; "
                        "   border-left: 4px solid #ffc107; "
                        "   margin-top: 20px; "
                        "}"
                        ".footer { "
                        "   text-align: center; "
                        "   margin-top: 30px; "
                        "   padding-top: 20px; "
                        "   border-top: 1px solid #dee2e6; "
                        "   color: #6c757d; "
                        "   font-size: 12px; "
                        "}"
                        ".valeur-importante { "
                        "   font-size: 18px; "
                        "   font-weight: 700; "
                        "   color: #2c3e50; "
                        "}"
                        ".unite { "
                        "   font-size: 12px; "
                        "   color: #6c757d; "
                        "   margin-left: 2px; "
                        "}"
                        "@media (max-width: 768px) { "
                        "   .grid-container { grid-template-columns: 1fr; }"
                        "   .fiche-container { padding: 20px; margin: 10px; }"
                        "   .header h1 { font-size: 24px; }"
                        "   .info-item { flex-direction: column; align-items: flex-start; gap: 5px; }"
                        "   .info-value { text-align: left; }"
                        "}"
                        "</style>"
                        "</head>"
                        "<body>"
                        "<div class='fiche-container'>"

                        // En-tête
                        "<div class='header'>"
                        "<h1>📋 FICHE TECHNIQUE</h1>"
                        "<h2>Équipement N°%1 - %2</h2>"
                        "</div>"

                        "<div class='grid-container'>"

                        // Informations générales
                        "<div class='card'>"
                        "<div class='card-title'>🔷 INFORMATIONS GÉNÉRALES</div>"
                        "<div class='info-item'><span class='info-label'>Identifiant</span><span class='info-value'>%1</span></div>"
                        "<div class='info-item'><span class='info-label'>Nom</span><span class='info-value'>%2</span></div>"
                        "<div class='info-item'><span class='info-label'>Type</span><span class='info-value'>%3</span></div>"
                        "<div class='info-item'><span class='info-label'>État actuel</span><span class='info-value'>%4</span></div>"
                        "<div class='info-item'><span class='info-label'>Quantité disponible</span><span class='info-value'><span class='valeur-importante'>%5</span><span class='unite'>unité(s)</span></span></div>"
                        "</div>"

                        // Informations financières
                        "<div class='card'>"
                        "<div class='card-title'>💰 INFORMATIONS FINANCIÈRES</div>"
                        "<div class='info-item'><span class='info-label'>Prix d'achat</span><span class='info-value'><span class='valeur-importante'>%6</span><span class='unite'>€</span></span></div>"
                        "<div class='info-item'><span class='info-label'>Valeur résiduelle</span><span class='info-value'><span class='valeur-importante'>%7</span><span class='unite'>€</span></span></div>"
                        "<div class='info-item'><span class='info-label'>Coût journalier</span><span class='info-value'><span class='valeur-importante'>%8</span><span class='unite'>€/jour</span></span></div>"
                        "</div>"

                        // Cycle de vie
                        "<div class='card'>"
                        "<div class='card-title'>⏳ CYCLE DE VIE</div>"
                        "<div class='info-item'><span class='info-label'>Date d'achat</span><span class='info-value'>%9</span></div>"
                        "<div class='info-item'><span class='info-label'>Âge</span><span class='info-value'><span class='valeur-importante'>%10</span><span class='unite'>ans</span></span></div>"
                        "<div class='info-item'><span class='info-label'>Durée de vie totale</span><span class='info-value'><span class='valeur-importante'>%11</span><span class='unite'>ans</span></span></div>"
                        "<div class='info-item'><span class='info-label'>Vie restante</span><span class='info-value'><span class='valeur-importante'>%12</span><span class='unite'>ans</span></span></div>"
                        "<div class='info-item'>"
                        "<span class='info-label'>Taux d'usure</span>"
                        "<span class='info-value'>"
                        "<span class='valeur-importante'>%13%</span>"
                        "<div class='progress-container'><div class='progress-fill %14' style='width: %13%;'></div></div>"
                        "<div class='statut-badge %15'>%16</div>"
                        "</span>"
                        "</div>"
                        "</div>"

                        // Analyse
                        "<div class='card'>"
                        "<div class='card-title'>📊 ANALYSE & RECOMMANDATIONS</div>"
                        "<div class='info-item'><span class='info-label'>Prochaine maintenance</span><span class='info-value'>%17</span></div>"
                        "<div class='info-item'><span class='info-label'>Fin de vie estimée</span><span class='info-value'>%18</span></div>"
                        "<div class='info-item'><span class='info-label'>Priorité remplacement</span><span class='info-value'>%19</span></div>"
                        "<div class='highlight-box'>"
                        "<strong>💡 Recommandation :</strong><br>%20"
                        "</div>"
                        "</div>"

                        "</div>" // Fin grid-container

                        // Pied de page
                        "<div class='footer'>"
                        "📄 Document généré le %21 | Système de Gestion d'Équipements"
                        "</div>"

                        "</div>"
                        "</body>"
                        "</html>"
                        )
                        .arg(getID())
                        .arg(getNom())
                        .arg(getType())
                        .arg(getEtat())
                        .arg(getQuantite())
                        .arg(getPrix())
                        .arg(QString::number(valeurResiduelle, 'f', 2))
                        .arg(QString::number(coutJournalier, 'f', 3))
                        .arg(getDateAchat().toString("dd/MM/yyyy"))
                        .arg(age)
                        .arg(getDureeVie())
                        .arg(vieRestante)
                        .arg(QString::number(pourcentageUsure, 'f', 1))
                        .arg(progressClass)
                        .arg(badgeClass)
                        .arg(badgeText)
                        .arg(getDateAchat().addYears(getDureeVie() / 2).toString("dd/MM/yyyy"))
                        .arg(getDateAchat().addYears(getDureeVie()).toString("dd/MM/yyyy"))
                        .arg(statutUrgence.contains("🔴") ? "🔴 HAUTE" : statutUrgence.contains("🟠") ? "🟠 MOYENNE" : "🟢 FAIBLE")
                        .arg(obtenirRecommandation())
                        .arg(QDate::currentDate().toString("dd/MM/yyyy à HH:mm"));

    return fiche;
}

QString equipementC::obtenirRecommandation()
{
    double usure = calculerPourcentageUsure();

    if (usure >= 80)
        return "Équipement en fin de vie. Planifier son remplacement rapidement.";
    else if (usure >= 60)
        return "Surveiller attentivement l'état et prévoir une maintenance corrective.";
    else if (usure >= 40)
        return "Maintenance préventive recommandée lors de la prochaine intervention.";
    else if (usure >= 20)
        return "État satisfaisant. Poursuivre l'utilisation normale.";
    else
        return "État excellent. Aucune action requise pour le moment.";
}

