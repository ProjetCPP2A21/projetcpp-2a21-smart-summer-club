#include "apprenant.h"
#include "ui_apprenant.h"
#include <QSqlError>
#include <QMessageBox>
#include <QWidget>
#include <QObject>
#include <QMainWindow>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QRegularExpression>  // Ajoutez cette ligne en haut du fichier
#include <QRegularExpressionValidator>
#include <QIntValidator>
#include <QFile>
#include <QFileDialog>
#include <QChart>
#include <QChartView>
#include <QPieSeries>
#include <QBarSeries>
#include <QBarSet>
#include <QValueAxis>
#include <QVBoxLayout>


apprenant::apprenant(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::apprenant)
{
    ui->setupUi(this);

    // Contrôle de saisie pour l'ID (chiffres seulement)
    ui->lineEdit_cin_3->setValidator(new QIntValidator(0, 99999999, this));
    // Contrôle de saisie Nom et Prénom (lettres et espaces)
    QRegularExpression regexLettres("^[A-Za-z ÀÂÄÉÈÊËÎÏÔÖÙÛÜÇàâäéèêëîïôöùûüç]+$");
    ui->lineEdit_nom_3->setValidator(new QRegularExpressionValidator(regexLettres, this));
    ui->lineEdit_prenom_3->setValidator(new QRegularExpressionValidator(regexLettres, this));
    ui->tableView->setModel(Etmp->afficher());
    // Contrôle de saisie pour la date de naissance (max 17 ans)
    QDate aujourdhui = QDate::currentDate();
    QDate dateMin = QDate(1900, 1, 1);        // Date minimum
    QDate dateMax = aujourdhui.addYears(0); // Au moins 17 ans (max 17 ans)
    // Contrôle de saisie pour Email

    QRegularExpression regexEmail("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    ui->lineEdit_contact_3->setValidator(new QRegularExpressionValidator(regexEmail, this));

    ui->dateEdit_embauche_3->setDateRange(dateMin, dateMax);
    ui->dateEdit_embauche_3->setDate(aujourdhui.addYears(-17)); // Valeur par défaut: 17 ans
}
apprenant::~apprenant()
{
    delete ui;
}

apprenant::apprenant(int id_apprenant,QString nom,QString prenom,QDate date_naiss,QString email){
    this->id_apprenant=id_apprenant;
    this->nom=nom;
    this->prenom=prenom;
    this->date_naiss=date_naiss;
    this->email=email;
}

bool apprenant::ajouter(){
    //ToDo
    QSqlQuery query;
    QString res = QString::number(id_apprenant);
    query.prepare("INSERT INTO apprenant (id, nom, prenom , date_naiss, email) "
                  "VALUES (:id_apprenant, :nom, :prenom, :date_naiss, :email)");
    query.bindValue(":id_apprenant",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":date_naiss",date_naiss);
    query.bindValue(":email",email);
    if (!query.exec()) {
        qDebug() << "Add failed:" << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel * apprenant::afficher(){
    QSqlQueryModel *model = new QSqlQueryModel();
    // Change from "etudiant" to "apprenants"
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

bool apprenant::supprimer(int id_apprenant){
    QSqlQuery query;
    QString res=QString::number(id_apprenant);
    // Change from "apprenant" to "apprenants"
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

    // Try different date formats for Oracle
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

void apprenant::on_pushButton_AJOUTER_3_clicked()
{
    int id_apprenant = ui->lineEdit_cin_3->text().toInt();
    QString nom = ui->lineEdit_nom_3->text();
    QString prenom = ui->lineEdit_prenom_3->text();
    QDate date_naiss = ui->dateEdit_embauche_3->date();
    QString email = ui->lineEdit_contact_3->text();
    QDate aujourdhui = QDate::currentDate();
    int age = aujourdhui.year() - date_naiss.year();

    // Vérifier si l'anniversaire est déjà passé cette année
    if (aujourdhui < QDate(aujourdhui.year(), date_naiss.month(), date_naiss.day())) {
        age--;
    }

    // Validation de l'âge (max 17 ans)
    if (age > 17) {
        QMessageBox::warning(this, "Erreur", "L'apprenant doit avoir au maximum 17 ans");
        return;
    }

    if (age < 0) {
        QMessageBox::warning(this, "Erreur", "Date de naissance invalide");
        return;
    }

    // Validation de l'email - version statique
    static QRegularExpression regexEmail("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    QRegularExpressionMatch match = regexEmail.match(email);

    if (!match.hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une adresse email valide");
        return;
    }

    bool test=ajouter_apprenant(id_apprenant, nom, prenom, date_naiss,email);
    if(test)
    {
        //Refresh (Actualiser)
        ui->tableView->setModel(Etmp->afficher());
    // Exemple : juste afficher la date pour vérifier
        QMessageBox::information(this, "OK", "Ajout effectué!");
    }
    else
        QMessageBox::critical(this, "Error", "Ajout non effectué. Check console for details.");
}
void apprenant::on_pushButton_18_clicked()
{
    int id_apprenant =ui->lineEdit_RECHERCHE_2->text().toInt();
    bool test=Etmp->supprimer(id_apprenant);
    if(test)
    {
        //Refresh (Actualiser)
        ui->tableView->setModel(Etmp->afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Suppression effectuée\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                 QObject::tr("Suppression non effectuée\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
}

void apprenant::on_pushButton_ANNULER_3_clicked()
{
    // Vider tous les champs
    ui->lineEdit_cin_3->clear();
    ui->lineEdit_nom_3->clear();
    ui->lineEdit_prenom_3->clear();
    ui->lineEdit_contact_3->clear();
    ui->dateEdit_embauche_3->setDate(QDate::currentDate()); // Remettre la date actuelle

    // Optionnel: Décocher les checkboxes
    ui->checkBox_3->setChecked(false);
    ui->checkBox_4->setChecked(false);
}

void apprenant::on_pushButton_17_clicked()
{
    // Récupérer l'ID à modifier depuis le champ de recherche
    int id_apprenant = ui->lineEdit_RECHERCHE_2->text().toInt();

    if (id_apprenant == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide");
        return;
    }

    // Récupérer les nouvelles valeurs
    QString nouveau_nom = ui->lineEdit_nom_3->text();
    QString nouveau_prenom = ui->lineEdit_prenom_3->text();
    QDate nouvelle_date_naiss = ui->dateEdit_embauche_3->date();
    QString nouvel_email = ui->lineEdit_contact_3->text();

    // Validation de l'âge
    QDate aujourdhui = QDate::currentDate();
    int age = aujourdhui.year() - nouvelle_date_naiss.year();
    if (aujourdhui < QDate(aujourdhui.year(), nouvelle_date_naiss.month(), nouvelle_date_naiss.day())) {
        age--;
    }
    if (age > 17 || age < 0) {
        QMessageBox::warning(this, "Erreur", "L'âge doit être entre 0 et 17 ans");
        return;
    }

    // Validation de l'email
    static QRegularExpression regexEmail("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    if (!regexEmail.match(nouvel_email).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Email invalide");
        return;
    }

    // Préparer et exécuter la requête UPDATE avec TO_DATE
    QSqlQuery query;
    query.prepare("UPDATE apprenant SET NOM=:nom, PRENOM=:prenom, DATE_NAISS=TO_DATE(:date_naiss, 'YYYY-MM-DD'), EMAIL=:email WHERE ID_APPRENANT=:id");
    query.bindValue(":id", id_apprenant);
    query.bindValue(":nom", nouveau_nom);
    query.bindValue(":prenom", nouveau_prenom);
    query.bindValue(":date_naiss", nouvelle_date_naiss.toString("yyyy-MM-dd"));
    query.bindValue(":email", nouvel_email);

    if (query.exec()) {
        ui->tableView->setModel(Etmp->afficher());
        QMessageBox::information(this, "Succès", "Modification effectuée!");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification: " + query.lastError().text());
    }
}

void apprenant::on_pushButton_19_clicked()
{
    // Trier par date de naissance (croissant)
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT ID_APPRENANT, NOM, PRENOM, DATE_NAISS, EMAIL FROM apprenant ORDER BY DATE_NAISS ASC");

    // Set header names
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Naiss"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));

    ui->tableView->setModel(model);

    QMessageBox::information(this, "Tri", "Tri par date de naiss (du plus âgé au plus jeune)");
}

void apprenant::on_pushButton_20_clicked()
{
    // Choisir l'emplacement de sauvegarde
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter vers Word", "liste_apprenants.doc", "Documents Word (*.doc)");

    if (fileName.isEmpty()) return;

    // Récupérer les données
    QSqlQueryModel *model = afficher();

    // Créer le document HTML
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

    // Sauvegarder le fichier
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << html;
        file.close();
        QMessageBox::information(this, "Succès", "Liste exportée vers:\n" + fileName);
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible de sauvegarder le fichier");
    }

    delete model;
}

void apprenant::on_pushButton_stat_clicked()
{
    // Calculer les tranches d'âge (max 17 ans)
    QSqlQuery query;
    query.exec("SELECT DATE_NAISS FROM apprenant");

    int tranches[4] = {0}; // 0: <15, 1:15, 2:16, 3:17

    QDate aujourdhui = QDate::currentDate();

    while (query.next()) {
        QDate date_naiss = query.value(0).toDate();
        int age = aujourdhui.year() - date_naiss.year();

        // Ajuster si l'anniversaire n'est pas encore passé cette année
        if (aujourdhui < QDate(aujourdhui.year(), date_naiss.month(), date_naiss.day())) {
            age--;
        }

        if (age < 15) tranches[0]++;
        else if (age == 15) tranches[1]++;
        else if (age == 16) tranches[2]++;
        else if (age == 17) tranches[3]++;
    }

    // Créer le graphique camembert SANS QtCharts::
    QPieSeries *series = new QPieSeries();

    QStringList labels = {"Moins de 15 ans", "15 ans", "16 ans", "17 ans"};
    QList<QColor> colors = {
        QColor(255, 235, 235),  // #FFEBEB
        QColor(78, 205, 196),   // #4ECDC4
        QColor(69, 183, 209),   // #45B7D1
        QColor(150, 206, 180)   // #96CEB4
    };

    for (int i = 0; i < 4; i++) {
        if (tranches[i] > 0) {
            QPieSlice *slice = series->append(labels[i] + " (" + QString::number(tranches[i]) + ")", tranches[i]);
            slice->setColor(colors[i]);
            slice->setLabelVisible(true);
        }
    }

    // Créer et configurer le chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des apprenants par tranche d'âge");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Afficher dans une fenêtre
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Statistiques");
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(chartView);
    dialog->resize(800, 600);
    dialog->exec();
}

void apprenant::on_lineEdit_RECHERCHE_2_textChanged(const QString &arg1)
{
    QString recherche = arg1.trimmed();

    if (recherche.isEmpty()) {
        // Si le champ est vide, afficher tous les apprenants
        ui->tableView->setModel(afficher());
        return;
    }

    // Rechercher par ID
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT ID_APPRENANT, NOM, PRENOM, DATE_NAISS, EMAIL FROM apprenant WHERE ID_APPRENANT = " + recherche);

    // Set header names
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Naiss"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));

    ui->tableView->setModel(model);

    // Afficher un message si aucun résultat
    if (model->rowCount() == 0 && !recherche.isEmpty()) {
        // Optionnel: message temporaire
        qDebug() << "Aucun apprenant trouvé avec ID:" << recherche;
    }
}


