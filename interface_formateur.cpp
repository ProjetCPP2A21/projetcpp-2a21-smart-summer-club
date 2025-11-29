#include "ui_interface_formateur.h"
#include "statisticsdialog.h"
#include "mainwindow.h"
#include "formateurs.h"
#include "service.h"
#include <QMessageBox>
#include <QTableView>
#include "service.h"
#include "formation2.h"
#include <QSqlError>
#include "employe.h"  // assure-toi que le chemin est correct
#include <QSortFilterProxyModel>
#include "equipement.h"
#include "interface_formateur.h"
#include <QRegularExpression>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollBar>

#include <QTableView>
#include <formation2.h>
#include <QMessageBox>
#include <QSqlError>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <statistic.h>
#include "calendardialog.h"
#include <QProcessEnvironment>
#include <QDate>
#include <QTime>
#include <QDebug>



interface_formateur::interface_formateur(MainWindow *menu, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::interface_formateur),
    menuPrincipal(menu)// on initialise avec le menu passé en paramètre
{
    ui->setupUi(this);
    // 🆕 CREATE CHATBOT INTERFACE - PASS 'this' AS PARENT
    a.creerInterfaceChatbot(this);
    // 🆕 CREATE GROUPES INTERFACE
    a.creerInterfaceGroupes(this);
    // 🆕 CONNECT GROUP DISPLAY SIGNAL
    connect(&a, &apprenant::groupeAAfficher, this, &interface_formateur::onGroupeAAfficher);



//--------------------DEBUT_FORMATEUR----------------------------------------------------------------------------------------------------------
    ui->lineEdit_IdFormateur->setValidator(new QIntValidator(1, 99999999, this));
    ui->lineEdit_contactFormateur->setValidator(new QIntValidator(1, 99999999, this));
    ui->lineEdit_salaireFormateur->setValidator(new QIntValidator(1, 99999999, this));
    QRegularExpression regex("^[A-Za-z]+$"); // uniquement lettres
    ui->lineEdit_NomFormateur->setValidator(new QRegularExpressionValidator(regex, this));
    ui->lineEdit_PrenomFormateur->setValidator(new QRegularExpressionValidator(regex, this));

    ui->Tab_Formateur->setModel(F.afficher());
    ui->Tab_Formateur->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->Tab_Formateur->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ui->checkBox_hommeFormateur, &QCheckBox::toggled, [=](bool checked) {
        if (checked) ui->checkBox_femmeFormateur->setChecked(false);
    });
    connect(ui->checkBox_femmeFormateur, &QCheckBox::toggled, [=](bool checked) {
        if (checked) ui->checkBox_hommeFormateur->setChecked(false);
    });

    disconnect(ui->Tab_Formateur->selectionModel(), nullptr, this, nullptr);
    connect(ui->Tab_Formateur->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &interface_formateur::onTableSelectionChanged);
    ui->table->setModel(s.affiche());

    ui->doubleSpinBox_heureprevueFormateur->setMinimum(0.0);  // modif
    ui->doubleSpinBox_heureprevueFormateur->setMaximum(50.0); // modif
    ui->doubleSpinBox_heureprevueFormateur->setSingleStep(0.25); // modif
//--------------------FIN_FORMATEUR----------------------------------------------------------------------------------------------------------

    //FORMATION//

    // Connecte le signal quand l'utilisateur finit de saisir l'ID
    connect(ui->lineEditId, &QLineEdit::editingFinished,
            this, &interface_formateur::on_lineEditId_editingFinished);
    formation2 F;
    ui->tableFormation->setModel(ftmp.afficher());
    QIntValidator *validator = new QIntValidator(0, 999999, this);
    ui->lineEditId->setValidator(validator);
    ui->lineEdit_D->setValidator(validator);
    ui->lineEdit_Ta->setValidator(validator);
    ui->lineEdit_id2->setValidator(validator);
    ui->comboBox_Ca->setCurrentIndex(0);

    QString sgApiKey = qEnvironmentVariable("SENDGRID_API_KEY");
    QString sgFromEmail = qEnvironmentVariable("SENDGRID_FROM_EMAIL");
    QString sgFromName = qEnvironmentVariable("SENDGRID_FROM_NAME");
    QString recipientsEnv = qEnvironmentVariable("SENDGRID_TO_EMAILS");
    QStringList recipients;
    for (const QString &email : recipientsEnv.split(';', Qt::SkipEmptyParts))
        recipients << email.trimmed();
    qDebug() << "[SendGrid] API key set:" << !sgApiKey.isEmpty();
    qDebug() << "[SendGrid] From email:" << sgFromEmail;
    qDebug() << "[SendGrid] From name:" << sgFromName;
    qDebug() << "[SendGrid] Recipients:" << recipients;

    sendgridClient.configure(sgApiKey, sgFromEmail, sgFromName, recipients);
    if (!sendgridClient.isConfigured())
    {
        qWarning() << "[SendGrid] Client is not fully configured. Emails will not be sent.";
    }
    ui->dateEdit_date->setCalendarPopup(true);
    ui->dateEdit_date->setDate(QDate::currentDate());



    // ---- INPUT VALIDATORS (set once at start) ----
    QIntValidator *intVal = new QIntValidator(this);
    ui->lineEdit_ID->setValidator(intVal);
    ui->lineEdit_cin->setValidator(intVal);
    ui->lineEdit_num->setValidator(new QIntValidator(10000000, 99999999, this)); // 8 digits

    // letters + space + hyphen for name fields
    QRegularExpression nameRx("^[A-Za-zÀ-ÖØ-öø-ÿ\\-\\s]+$");
    QRegularExpressionValidator *nameVal = new QRegularExpressionValidator(nameRx, this);
    ui->lineEdit_nom->setValidator(nameVal);
    ui->lineEdit_prenom->setValidator(nameVal);

    // email validator
    QRegularExpression emailRx(R"(^[\w\.\-]+\@[\w\-]+\.[a-zA-Z]{2,}$)");
    ui->lineEdit_email->setValidator(new QRegularExpressionValidator(emailRx, this));

    // Display the list at startup
    ui->tableView->setModel(etmp.afficher());
    // ========== APPRENANT VALIDATION ==========
    // Contrôle de saisie pour l'ID (chiffres seulement)
    ui->lineEdit_cin_6->setValidator(new QIntValidator(0, 99999999, this));

    // Contrôle de saisie Nom et Prénom (lettres et espaces)
    QRegularExpression regexLettres("^[A-Za-z ÀÂÄÉÈÊËÎÏÔÖÙÛÜÇàâäéèêëîïôöùûüç]+$");
    ui->lineEdit_nom_3->setValidator(new QRegularExpressionValidator(regexLettres, this));
    ui->lineEdit_prenom_3->setValidator(new QRegularExpressionValidator(regexLettres, this));

    // Contrôle de saisie pour la date de naissance (max 17 ans)
    QDate aujourdhui = QDate::currentDate();
    QDate dateMin = QDate(1900, 1, 1);        // Date minimum
    QDate dateMax = aujourdhui.addYears(0);   // Au moins 17 ans (max 17 ans)
    ui->dateEdit_embauche_3->setDateRange(dateMin, dateMax);
    ui->dateEdit_embauche_3->setDate(aujourdhui.addYears(-17)); // Valeur par défaut: 17 ans

    // Contrôle de saisie pour Email
    QRegularExpressionValidator *emailValidator = new QRegularExpressionValidator(emailRx, this);
    ui->lineEdit_contact_3->setValidator(emailValidator);

    // Set the apprenant table model
    ui->tableView_2->setModel(a.afficher());

    // Apprenant button connections
    connect(ui->pushButton_AJOUTER_6, &QPushButton::clicked, this, &interface_formateur::on_pushButton_AJOUTER_6_clicked);
    connect(ui->pushButton_ANNULER_6, &QPushButton::clicked, this, &interface_formateur::on_pushButton_ANNULER_6_clicked);
    connect(ui->pushButton_19, &QPushButton::clicked, this, &interface_formateur::on_pushButton_19_clicked);
    connect(ui->pushButton_17, &QPushButton::clicked, this, &interface_formateur::on_pushButton_17_clicked);
    connect(ui->pushButton_18, &QPushButton::clicked, this, &interface_formateur::on_pushButton_18_clicked);
    connect(ui->pushButton_20, &QPushButton::clicked, this, &interface_formateur::on_pushButton_20_clicked);
    connect(ui->pushButton_stat_6, &QPushButton::clicked, this, &interface_formateur::on_pushButton_stat_6_clicked);
    connect(ui->lineEdit_RECHERCHE_2, &QLineEdit::textChanged, this, &interface_formateur::on_lineEdit_RECHERCHE_2_textChanged);
    // Recherche quand on appuie sur Entrée (au cas où)
    connect(ui->lineEdit_RECHERCHE_2, &QLineEdit::returnPressed, this, &interface_formateur::on_lineEdit_RECHERCHE_2_returnPressed);
    connect(ui->tableView_2->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &interface_formateur::onApprenantTableSelectionChanged);

}


interface_formateur::~interface_formateur()
{
    delete ui;
}

void interface_formateur::setPage(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}


void interface_formateur::on_pushButton_clicked()
{
    QMessageBox::information(this, "Formateur", "Bouton Formateur cliqué !");
}

void interface_formateur::on_pushButton_retour_menu_clicked()
{
    this->hide();                // cacher la fenêtre
    menuPrincipal->show();       // réafficher le menu principal
}

void interface_formateur::on_pushButton_employe_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void interface_formateur::on_pushButton_formateur_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void interface_formateur::on_pushButton_formation_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}



void interface_formateur::on_pushButton_stat_4_clicked()
{
    Statistic d(this); // création de la dialog
    d.exec();
}


void interface_formateur::on_pushButton_stat_2_clicked()
{
    StatisticsDialog d(this); // création de la dialog
    d.exec();
}

void interface_formateur::on_pushButton_stat_6_clicked()
{
    a.statistiques_ages(this);
}

/*service*/
void interface_formateur::on_pushButton_service_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);

     service s;
    for (int id_service = 1; id_service <= 105; ++id_service) {
        s.alert_capacite(id_service);
    }


}


void interface_formateur::on_pushButton_apprenant_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void interface_formateur::on_pushButton_equipement_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------DEBUT_FORMATEUR_CRUD-------------------------------------------------------------------------------------------------------------------------------------------------

// AJOUT
void interface_formateur::on_pushButton_AJOUTER_5_clicked()
{
    // Récupertaion des informations
    QString idText = ui->lineEdit_IdFormateur->text().trimmed();
    if (idText.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur", "L'ID du formateur ne peut pas être vide !");
        return;
    }
    int id = idText.toInt();

    QString contact = ui->lineEdit_contactFormateur->text().trimmed();
    QRegularExpression regex("^\\d{8}$");
    if (!regex.match(contact).hasMatch()) {
        QMessageBox::warning(nullptr, "Erreur", "Le contact doit contenir exactement 8 chiffres !");
        return;
    }
    QString nom =ui->lineEdit_NomFormateur->text();
    QString prenom =ui->lineEdit_PrenomFormateur->text();
    //QString contact =ui->lineEdit_contactFormateur->text();
    float salaire= ui->lineEdit_salaireFormateur->text().toFloat();
    QString specialite =ui->comboBox_specialiteFormateur->currentText();
    float heuresPrevues= ui->doubleSpinBox_heureprevueFormateur->value();
    QDate dateEmbauche = ui->dateEdit_embaucheFormateur->date();//modif
    //QString dateStr = dateEmbauche.toString("yyyy-MM-dd");//modif
    QString sexe;

    if(ui->checkBox_hommeFormateur->isChecked()){
        sexe = "Homme";
    }else if(ui->checkBox_femmeFormateur->isChecked()){
        sexe ="Femme";
    }else{
        sexe ="";
    }


    Formateur F(id,nom,prenom,contact,sexe,dateEmbauche,specialite,heuresPrevues,salaire);
    bool test= F.ajouter();

    if(test){
        ui->Tab_Formateur->setModel(F.afficher());
        QMessageBox :: information(nullptr,QObject :: tr("OK"),
                                  QObject::tr("Ajout effectué\n"
                                              "Click cancel to exit"), QMessageBox :: Cancel);
    }else{
        QMessageBox :: critical(nullptr,QObject :: tr("not OK"),
                               QObject::tr("Ajout non effectué\n"
                                           "Click cancel to exit"), QMessageBox :: Cancel);
    }

    ui->lineEdit_IdFormateur->clear();
    ui->lineEdit_NomFormateur->clear();
    ui->lineEdit_PrenomFormateur->clear();
    ui->lineEdit_contactFormateur->clear();
    ui->lineEdit_salaireFormateur->clear();
    ui->comboBox_specialiteFormateur->setCurrentIndex(0);
    ui->doubleSpinBox_heureprevueFormateur->setValue(0);
    ui->dateEdit_embaucheFormateur->setDate(QDate::currentDate());
    ui->checkBox_hommeFormateur->setChecked(false);
    ui->checkBox_femmeFormateur->setChecked(false);

    ui->Tab_Formateur->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->Tab_Formateur->setSelectionMode(QAbstractItemView::SingleSelection);
    disconnect(ui->Tab_Formateur->selectionModel(), nullptr, this, nullptr);
    connect(ui->Tab_Formateur->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &interface_formateur::onTableSelectionChanged);}


// INIT
void interface_formateur::on_pushButton_AjouterFormateur_clicked()
{
    ui->lineEdit_IdFormateur->clear();
    ui->lineEdit_NomFormateur->clear();
    ui->lineEdit_PrenomFormateur->clear();
    ui->lineEdit_contactFormateur->clear();
    ui->lineEdit_salaireFormateur->clear();
    ui->comboBox_specialiteFormateur->setCurrentIndex(0);
    ui->doubleSpinBox_heureprevueFormateur->setValue(0);
    ui->dateEdit_embaucheFormateur->setDate(QDate::currentDate());
    ui->checkBox_hommeFormateur->setChecked(false);
    ui->checkBox_femmeFormateur->setChecked(false);

    ui->Tab_Formateur->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->Tab_Formateur->setSelectionMode(QAbstractItemView::SingleSelection);
    disconnect(ui->Tab_Formateur->selectionModel(), nullptr, this, nullptr);
    connect(ui->Tab_Formateur->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &interface_formateur::onTableSelectionChanged);
}


void interface_formateur::on_pushButton_ANNULER_5_clicked()
{
    ui->lineEdit_IdFormateur->clear();
    ui->lineEdit_NomFormateur->clear();
    ui->lineEdit_PrenomFormateur->clear();
    ui->lineEdit_contactFormateur->clear();
    ui->lineEdit_salaireFormateur->clear();
    ui->comboBox_specialiteFormateur->setCurrentIndex(0);
    ui->doubleSpinBox_heureprevueFormateur->setValue(0);
    ui->dateEdit_embaucheFormateur->setDate(QDate::currentDate());
    ui->checkBox_hommeFormateur->setChecked(false);
    ui->checkBox_femmeFormateur->setChecked(false);

    ui->Tab_Formateur->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->Tab_Formateur->setSelectionMode(QAbstractItemView::SingleSelection);
    disconnect(ui->Tab_Formateur->selectionModel(), nullptr, this, nullptr);
    connect(ui->Tab_Formateur->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &interface_formateur::onTableSelectionChanged);
}


void interface_formateur::on_pushButton_modifierFormateur_clicked()
{
    QString idText = ui->lineEdit_IdFormateur->text().trimmed();
    if (idText.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur", "L'ID du formateur ne peut pas être vide !");
        return;
    }
    int id = idText.toInt();

    QString contact = ui->lineEdit_contactFormateur->text().trimmed();
    QRegularExpression regex("^\\d{8}$");
    if (!regex.match(contact).hasMatch()) {
        QMessageBox::warning(nullptr, "Erreur", "Le contact doit contenir exactement 8 chiffres !");
        return;
    }

    //int id= ui->lineEdit_IdFormateur->text().toInt();
    QString nom =ui->lineEdit_NomFormateur->text();
    QString prenom =ui->lineEdit_PrenomFormateur->text();
    //QString contact =ui->lineEdit_contactFormateur->text();
    float salaire= ui->lineEdit_salaireFormateur->text().toFloat();
    QString specialite =ui->comboBox_specialiteFormateur->currentText();
    float heuresPrevues= ui->doubleSpinBox_heureprevueFormateur->value();
    QDate dateEmbauche =ui->dateEdit_embaucheFormateur->date();//modif
    QString sexe;

    if(ui->checkBox_hommeFormateur->isChecked()){
        sexe = "Homme";
    }else if(ui->checkBox_femmeFormateur->isChecked()){
        sexe ="Femme";
    }else{
        sexe ="";
    }

    Formateur F(id,nom,prenom,contact,sexe,dateEmbauche,specialite,heuresPrevues,salaire);
    bool test= F.modifier();
    if(test){
        ui->Tab_Formateur->setModel(F.afficher());
        QMessageBox :: information(nullptr,QObject :: tr("OK"),
                                  QObject::tr("Modification effectuée\n"
                                              "Click cancel to exit"), QMessageBox :: Cancel);
    }else{
        QMessageBox :: critical(nullptr,QObject :: tr("not OK"),
                               QObject::tr("Modification non effectuée\n"
                                           "Click cancel to exit"), QMessageBox :: Cancel);
    }

    ui->Tab_Formateur->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->Tab_Formateur->setSelectionMode(QAbstractItemView::SingleSelection);
    disconnect(ui->Tab_Formateur->selectionModel(), nullptr, this, nullptr);
    connect(ui->Tab_Formateur->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &interface_formateur::onTableSelectionChanged);
}


void interface_formateur::on_pushButton_SupprimerFormateur_clicked()
{
    //int id=ui->lineEdit_IdFormateur->text().toInt();
    if(IDselection == -1){
        QMessageBox::information(this, tr("Aucune selection"),tr("Veuillez selectionner un formateur à supprimer."));
        return;
    }

    int reply = QMessageBox::question(this, tr("Confirmation"),
                                      tr("Voulez-vous supprimer ce formateur ?"),
                                      QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No)
        return;

    bool test= F.supprimer(IDselection);
    if(test){
        QMessageBox::information(this, tr("Succès"),
                                 tr("Le formateur a été supprimé avec succès."));

        ui->Tab_Formateur->setModel(F.afficher());
        IDselection = -2;
        ui->lineEdit_IdFormateur->clear();
        ui->lineEdit_NomFormateur->clear();
        ui->lineEdit_PrenomFormateur->clear();
        ui->lineEdit_contactFormateur->clear();
        ui->lineEdit_salaireFormateur->clear();
        ui->comboBox_specialiteFormateur->setCurrentIndex(0);
        ui->doubleSpinBox_heureprevueFormateur->setValue(0);
        ui->dateEdit_embaucheFormateur->setDate(QDate::currentDate());
        ui->checkBox_hommeFormateur->setChecked(false);
        ui->checkBox_femmeFormateur->setChecked(false);

        ui->Tab_Formateur->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->Tab_Formateur->setSelectionMode(QAbstractItemView::SingleSelection);
        disconnect(ui->Tab_Formateur->selectionModel(), nullptr, this, nullptr);
        connect(ui->Tab_Formateur->selectionModel(),
                &QItemSelectionModel::selectionChanged,
                this,
                &interface_formateur::onTableSelectionChanged);

    }else
        QMessageBox :: critical(nullptr,QObject :: tr("not OK"),
                               QObject::tr("Suppression non effectuée\n"
                                           "Click cancel to exit"), QMessageBox :: Cancel);
}


void interface_formateur::on_pushButton_listeformateur_clicked()
{
    ui->lineEdit_IdFormateur->clear();
    ui->lineEdit_NomFormateur->clear();
    ui->lineEdit_PrenomFormateur->clear();
    ui->lineEdit_contactFormateur->clear();
    ui->lineEdit_salaireFormateur->clear();
    ui->comboBox_specialiteFormateur->setCurrentIndex(0);
    ui->doubleSpinBox_heureprevueFormateur->setValue(0);
    ui->dateEdit_embaucheFormateur->setDate(QDate::currentDate());
    ui->checkBox_hommeFormateur->setChecked(false);
    ui->checkBox_femmeFormateur->setChecked(false);


    ui->Tab_Formateur->setModel(F.afficher());
    ui->Tab_Formateur->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->Tab_Formateur->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ui->checkBox_hommeFormateur, &QCheckBox::toggled, [=](bool checked) {
        if (checked) ui->checkBox_femmeFormateur->setChecked(false);
    });
    connect(ui->checkBox_femmeFormateur, &QCheckBox::toggled, [=](bool checked) {
        if (checked) ui->checkBox_hommeFormateur->setChecked(false);
    });

    disconnect(ui->Tab_Formateur->selectionModel(), nullptr, this, nullptr);
    connect(ui->Tab_Formateur->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &interface_formateur::onTableSelectionChanged);
    ui->table->setModel(s.affiche());

    ui->doubleSpinBox_heureprevueFormateur->setMinimum(0.0);  // modif
    ui->doubleSpinBox_heureprevueFormateur->setMaximum(50.0); // modif
    ui->doubleSpinBox_heureprevueFormateur->setSingleStep(0.25); // modif
}


void interface_formateur::onTableSelectionChanged()
{

    QModelIndexList indexes = ui->Tab_Formateur->selectionModel()->selectedRows();
    if (!indexes.isEmpty()) {
        int row = indexes.first().row();

        IDselection = ui->Tab_Formateur->model()->index(row, 0).data().toInt();
        QString nom = ui->Tab_Formateur->model()->index(row, 1).data().toString();
        QString prenom = ui->Tab_Formateur->model()->index(row, 2).data().toString();
        QString contact = ui->Tab_Formateur->model()->index(row, 3).data().toString();
        QString sexe = ui->Tab_Formateur->model()->index(row, 4).data().toString();//MODIF
        QString specialite = ui->Tab_Formateur->model()->index(row, 6).data().toString();//modif
        float heuresPrevues = ui->Tab_Formateur->model()->index(row, 7).data().toFloat();//modif
        float salaire= ui->Tab_Formateur->model()->index(row, 8).data().toFloat();


        ui->lineEdit_IdFormateur->setText(QString::number(IDselection));
        ui->lineEdit_NomFormateur->setText(nom);
        ui->lineEdit_PrenomFormateur->setText(prenom);
        ui->lineEdit_contactFormateur->setText(contact);
        if(sexe =="Femme"){
            ui->checkBox_hommeFormateur->setChecked(false);
            ui->checkBox_femmeFormateur->setChecked(true);
        }else{
            ui->checkBox_hommeFormateur->setChecked(true);
            ui->checkBox_femmeFormateur->setChecked(false);
        }
        ui->lineEdit_salaireFormateur->setText(QString::number(salaire));

        QModelIndex index = ui->Tab_Formateur->model()->index(row, 5);
        QDate date = index.data().toDate(); // récupère la date directement

        if (date.isValid()) {
            ui->dateEdit_embaucheFormateur->setDate(date);
        }
        ui->doubleSpinBox_heureprevueFormateur->setValue(heuresPrevues);
        if(specialite =="Français"){
            ui->comboBox_specialiteFormateur->setCurrentIndex(0);
        }else if(specialite =="Anglais"){
            ui->comboBox_specialiteFormateur->setCurrentIndex(1);
        }else if(specialite =="Science"){
            ui->comboBox_specialiteFormateur->setCurrentIndex(2);
        }else if(specialite =="Physique"){
            ui->comboBox_specialiteFormateur->setCurrentIndex(3);
        }else if(specialite =="Arabe"){
            ui->comboBox_specialiteFormateur->setCurrentIndex(4);
        }
    }
}


void interface_formateur::on_pushButton_RechercheFormateur_clicked()
{
    QString id_formateurchercher = ui->lineEdit_RechercheFormateur->text();

    if (id_formateurchercher.isEmpty()) {
        QMessageBox::warning(this, "Champ vide", "Veuillez saisir un ID");
        return;
    }

    int id = id_formateurchercher.toInt();
    Formateur F1;
    bool test=F1.recherche(id);
    if (test) {
        ui->lineEdit_IdFormateur->setText(QString::number(id));
        ui->lineEdit_NomFormateur->setText(F1.getNomFormateur());
        ui->lineEdit_PrenomFormateur->setText(F1.getPrenomFormateur());
        if (F.getSexeFormateur() == "Homme") {
            ui->checkBox_hommeFormateur->setChecked(true);
        } else {
            ui->checkBox_hommeFormateur->setChecked(false);
        }
        ui->lineEdit_contactFormateur->setText(F1.getContactFormateur());
        ui->comboBox_specialiteFormateur->setCurrentText(F1.getSpecialiteFormateur());
        ui->lineEdit_salaireFormateur->setText(QString::number(F1.getSalaireFormateur(), 'f', 2));
        ui->dateEdit_embaucheFormateur->setDate(F1.getDateEmbauche());
        ui->doubleSpinBox_heureprevueFormateur->setValue(F1.getHeuresPrevuesFormateur());
        ui->lineEdit_RechercheFormateur->clear();

        ui->Tab_Formateur->setModel(F1.Afficher_recherche(id));
    } else {
        QMessageBox::critical(this, "Erreur", "Aucun formateur trouvé avec cet ID.");
        ui->Tab_Formateur->setModel(nullptr);
        ui->lineEdit_IdFormateur->clear();
        ui->lineEdit_NomFormateur->clear();
        ui->lineEdit_PrenomFormateur->clear();
        ui->lineEdit_contactFormateur->clear();
        ui->lineEdit_salaireFormateur->clear();
        ui->comboBox_specialiteFormateur->setCurrentIndex(0);
        ui->doubleSpinBox_heureprevueFormateur->setValue(0);
        ui->dateEdit_embaucheFormateur->setDate(QDate::currentDate());
        ui->checkBox_hommeFormateur->setChecked(false);
        ui->checkBox_femmeFormateur->setChecked(false);
        ui->lineEdit_RechercheFormateur->clear();

        ui->Tab_Formateur->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->Tab_Formateur->setSelectionMode(QAbstractItemView::SingleSelection);
        disconnect(ui->Tab_Formateur->selectionModel(), nullptr, this, nullptr);
        connect(ui->Tab_Formateur->selectionModel(),
                &QItemSelectionModel::selectionChanged,
                this,
                &interface_formateur::onTableSelectionChanged);
    }
}


void interface_formateur::on_pushButton_TRIER_FORMATEUR_clicked()
{
    Formateur F;
    ui->Tab_Formateur->setModel(F.trierDateEmbauche());
    ui->Tab_Formateur->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->Tab_Formateur->setSelectionMode(QAbstractItemView::SingleSelection);
    disconnect(ui->Tab_Formateur->selectionModel(), nullptr, this, nullptr);
    connect(ui->Tab_Formateur->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &interface_formateur::onTableSelectionChanged);
}


void interface_formateur::on_pushButton_PDF_formateur_clicked()
{
    Formateur f;
    f.exporterPDF();
}


void interface_formateur::on_on_pushButton_stat_formateur_clicked()
{
    StatisticsDialog d(this);
    d.exec();
}
//-------------------------FIN_FORMATEUR_CRUD-------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



//------------------------GESTION_SERVICE_CRUD----------------------------------
bool interface_formateur::verife()
{
    QString id_text = ui->id_line->text();
    QString nom = ui->nom_line->text();
    QString montant_text = ui->montant_line->text();
    QString horaire = ui->horaire_line->text();
    QString capacite_text = ui->capacite_line->text();
    QString status = ui->status_line->text();
    QString type = ui->type_combo->currentText();
    int id = id_text.toInt();
    double montant = montant_text.toDouble();
    int capacite = capacite_text.toInt();

    if(id_text.isEmpty() || id<=0)
    {
        QMessageBox::critical(this, "erreur", "verfier voter id stp!!");
        return false;
    }
    if(nom.isEmpty())
    {
        QMessageBox::critical(this, "erreur", "verifier  voter nom de service stp!!");
        return false;
    }
    if(montant_text.isEmpty() || montant<=0)
    {
        QMessageBox::critical(this, "erreur", "verifier  voter monatnt  de service stp!!");
        return false;
    }
    if(horaire.isEmpty())
    {
        QMessageBox::critical(this, "erreur", "verifier  voter horaire de service stp!!");
        return false;
    }
    if(capacite_text.isEmpty() || capacite<=0)
    {
        QMessageBox::critical(this, "erreur", "verifier  voter capacite de service stp!!");
        return false;
    }
    if(status.isEmpty() )
    {
        QMessageBox::critical(this, "erreur", "verifier  voter status service stp!!");
        return false;
    }
    if(type.isEmpty() ||  ui->type_combo->currentIndex() == 0)
    {
        QMessageBox::critical(this, "erreur", "verifier  voter type  de service stp!!");
        return false;
    }

    return true;
}



void interface_formateur::on_pushButton_AJOUTER_3_clicked()
{
    if(verife()){
        int id_service = ui->id_line->text().toInt();
        QString nom_service = ui->nom_line->text();
        double montant = ui->montant_line->text().toDouble();
        QString horaire = ui->horaire_line->text();
        int capacite = ui->capacite_line->text().toInt();
        QString status_service = ui->status_line->text();
        QString type_service = ui->type_combo->currentText();


        service s(id_service, nom_service, montant, horaire,capacite, status_service,type_service);
        bool test=s.ajoute_service();

        if (test) {
            ui->table->setModel(s.affiche());
            QMessageBox::information(this, "Succès", "Service ajouté avec succès !");
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de l'ajout du service.");
        }
        if (test)
        {
            ui->id_line->clear();
            ui->nom_line->clear();
            ui->montant_line->clear();
            ui->horaire_line->clear();
            ui->capacite_line->clear();
            ui->status_line->clear();
            ui->type_combo->setCurrentIndex(0);

        }

    }
}



void interface_formateur::on_pushButton_92_clicked()
{
    QString id_supprimer = ui->id2->text();

    if (id_supprimer.isEmpty()) {
        QMessageBox::warning(this, "Champ vide", "Veuillez saisir un ID service tu va supprimer  !");
        return;
    }

    int id = id_supprimer.toInt();
    service s;
    bool  test=s.recherch_id(id);
    if(test)
    {
        s.supprime_service(id);
        QMessageBox::information(this, "Champ vide", "supprision avec succe  !");
        ui->table->setModel(s.affiche());
    }
    else
    {
        QMessageBox::warning(this, "Champ vide", "supprision avec echoue  !");
    }

}


void interface_formateur::on_pushButton_89_clicked()
{
    QString id_chercher = ui->id2->text();

    if (id_chercher.isEmpty()) {
        QMessageBox::warning(this, "Champ vide", "Veuillez saisir un ID !");
        return;
    }

    int id = id_chercher.toInt();
    service s;
    bool test=s.recherch_id(id);
    if (test) {
        QMessageBox::information(this, "valide", "service trouve.");
        ui->table->setModel(s.affiche_id(id));
    } else {
        QMessageBox::critical(this, "Erreur", "Aucun service trouvé avec cet ID.");
        ui->table->setModel(nullptr);

    }
}


void interface_formateur::on_pushButton_90_clicked()
{
    service s;
    QString idText = ui->id2->text();
    if (idText.isEmpty()) {
        QMessageBox::warning(this, "Champ vide", "Veuillez saisir un ID service tu va supprimer  !");
        return;
    }
    int id = idText.toInt();

    if (s.charge_donner(id)) {
        ui->id_line->setText(QString::number(s.getid()));
        ui->id_line->setDisabled(true);
        ui->nom_line->setText(s.getnom_service());
        ui->montant_line->setText(QString::number(s.getmontant()));
        ui->horaire_line->setText(s.gethoraire());
        ui->capacite_line->setText(QString::number(s.getcapacite()));
        ui->status_line->setText(s.getstatus());
        ui->type_combo->setCurrentText(s.gettype_service());

    } else {
        QMessageBox::critical(this, "Erreur", "Service introuvable.");

    }
}


void interface_formateur::on_pushButton_ANNULER_7_clicked()
{
    service s;
    QString id_modi = ui->id2->text();
    if (id_modi.isEmpty()) {
        QMessageBox::warning(this, "Champ vide", "Veuillez saisir un ID service tu va modifier  !");
        return;
    }
    int id = id_modi.toInt();
    s.setid(ui->id_line->text().toInt());
    s.setnom(ui->nom_line->text());
    s.setmontant(ui->montant_line->text().toDouble());
    s.sethoraire(ui->horaire_line->text());
    s.setcapacite(ui->capacite_line->text().toInt());
    s.setstatus(ui->status_line->text());
    s.settype(ui->type_combo->currentText());
    bool rechercher_id=s.recherch_id(id);
    if (rechercher_id) {
        s.update_service(id);
        QMessageBox::information(this, "Succès", "Service modifié avec succès.");
        ui->table->setModel(s.affiche());
    }
    if(s.update_service(id))
    {
        ui->id_line->setDisabled(false);
        ui->id_line->clear();
        ui->nom_line->clear();
        ui->montant_line->clear();
        ui->horaire_line->clear();
        ui->capacite_line->clear();
        ui->status_line->clear();
        ui->type_combo->setCurrentIndex(0);
        ui->id2->clear();

    }
    s.alert_capacite(id);
}



//stat gestion service//

void interface_formateur::on_pushButton_stat_13_clicked()
{
    service s;
    s.statistic_capacite(ui->table);
}


void interface_formateur::on_pushButton_ANNULER_3_clicked()
{

    ui->id_line->clear();
    ui->nom_line->clear();
    ui->montant_line->clear();
    ui->horaire_line->clear();
    ui->capacite_line->clear();
    ui->status_line->clear();
    ui->type_combo->setCurrentIndex(0);

}
//GSETION DES FORMATIONs//
void interface_formateur::on_pushButtonAjouter_clicked()
{
    // Validation des champs requis
    QString idText = ui->lineEditId->text().trimmed();
    QString nom=ui->lineEdit_Nom->text().trimmed();
    QString lieu=ui->lineEdit_lieu->text().trimmed();
    QString idFormateurText = ui->lineEdit_id2->text().trimmed();

    if (idText.isEmpty() || nom.isEmpty() || lieu.isEmpty() || idFormateurText.isEmpty())
    {
        QMessageBox::warning(this, tr("Champs manquants"),
                             tr("Merci de remplir les champs Id, Nom, Lieu et Id formateur."));
        return;
    }
    if (ui->comboBox_Ca->currentIndex() == -1)
    {
        QMessageBox::warning(this, tr("Capacité manquante"),
                             tr("Merci de sélectionner une capacité."));
        return;
    }

    int id=idText.toInt();
    QString type=ui->lineEdit_type->currentText();
    QString horaire = ui->lineEdit_h->time().toString("HH:mm");
    int duree=ui->lineEdit_D->text().toInt();
    int capacite=ui->comboBox_Ca->currentText().toInt();
    int tarif=ui->lineEdit_Ta->text().toInt();
    int id_formateur=idFormateurText.toInt();
    QDate dateformation = ui->dateEdit_date->date();

    //instancier un objet de la classe formation2 en utilisant les informations dans l'interface
    formation2 F (id, nom, type, horaire, dateformation, duree, lieu, capacite, tarif ,id_formateur);
    //inserer l'objet fprmation instancié dans la table formation et recuperer la valeur de reour de query.exec()
    bool test=F.ajouter();

    if(test) //si requete executé==> QmessageBox::information
    {
        //Refresh (Actualiser)
        ui->tableFormation->setModel(ftmp.afficher());

        QMessageBox::information(this, tr("Ajout"),
                                 tr("Ajout effectué avec succès."));
        if (sendgridClient.isConfigured())
        {
            qDebug() << "[SendGrid] Attempting to send email...";
            if (!sendgridClient.sendFormationCreatedEmail(nom, type, horaire, lieu, dateformation,
                                                          capacite, tarif, id_formateur, id))
            {
                QString err = sendgridClient.lastError();
                qWarning() << "Erreur envoi email SendGrid:" << err;
                QMessageBox::warning(this, tr("SendGrid"), err.isEmpty() ? tr("Échec d'envoi via SendGrid.") : err);
            }
            else
            {
                qDebug() << "[SendGrid] Email sent successfully.";
            }
        }
        else
        {
            qWarning() << "[SendGrid] Client not configured. Email skipped.";
        }
    }
    else //si requete non executé ==>QMessagebox::critical
    {
        QString err = F.lastError();
        QMessageBox::critical(this, tr("Ajout échoué"),
                              err.isEmpty() ? tr("Ajout non effectué.") : err);
        return;
    }
    clearInputs();
    ui->dateEdit_date->setDate(QDate::currentDate());



}



void interface_formateur::on_pushButtonsupprimer_clicked()
{
    QString idText = ui->lineEditId->text().trimmed();
    if (idText.isEmpty())
    {
        QMessageBox::warning(this, tr("Id manquant"), tr("Merci de saisir l'identifiant à supprimer."));
        return;
    }
    int id = idText.toInt();
    qDebug() << "ID à supprimer =" << id;

    bool test = ftmp.supprimer(id);

    if (test)
    {
        ui->tableFormation->setModel(ftmp.afficher());
        QMessageBox::information(nullptr, "OK", "Suppression effectuée ");
        ui->tableFormation->setModel(ftmp.afficher()); // Actualiser la table
    } else {
        QString err = ftmp.lastError();
        QMessageBox::critical(this, "Erreur", err.isEmpty() ? "Suppression non effectuée." : err);
    }
    clearInputs();
    ui->dateEdit_date->setDate(QDate::currentDate());
}
/*
void formation::onTableSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    if (!selected.indexes().isEmpty())
    {
        QModelIndex index = selected.indexes().first();
        int row = index.row();

        QAbstractItemModel *model = ui->tableFormation->model();

        int id = model->index(row, 0).data().toInt();
        QString nom = model->index(row, 1).data().toString();
        QString type = model->index(row, 2).data().toString();
        int horaire = model->index(row, 3).data().toInt();
        int duree = model->index(row, 4).data().toInt();
        QString lieu = model->index(row, 5).data().toString();
        int capacite = model->index(row, 6).data().toInt();
        int tarif  = model->index(row, 7).data().toInt();
        //int id_formateur  = model->index(row, 8).data().toInt();



        QTime h(horaire, 0);

        ui->lineEditId->setText(QString::number(id));
        ui->lineEdit_Nom->setText(nom);
        ui->lineEdit_type->setCurrentText(type);
        ui->lineEdit_h->setTime(h);
        ui->lineEdit_D->setText(QString::number(duree));
        ui->lineEdit_lieu->setText(lieu);
        ui->lineEdit_Ca->setText(QString::number(capacite));
        ui->lineEdit_Ta->setText(QString::number(tarif));
        //ui->lineEdit_id2->setText(QString::number(id_formateur));


    }
}
*/



void interface_formateur::on_pushButtonModifier_clicked()
{

    QString idText = ui->lineEditId->text().trimmed();
    QString nom=ui->lineEdit_Nom->text().trimmed();
    QString lieu=ui->lineEdit_lieu->text().trimmed();
    QString idFormateurText = ui->lineEdit_id2->text().trimmed();

    if (idText.isEmpty())
    {
        QMessageBox::warning(this, tr("Id manquant"),
                             tr("Merci de saisir l'identifiant de la formation à modifier."));
        return;
    }
    if (nom.isEmpty() || lieu.isEmpty() || idFormateurText.isEmpty())
    {
        QMessageBox::warning(this, tr("Champs manquants"),
                             tr("Merci de remplir les champs Nom, Lieu et Id formateur."));
        return;
    }
    if (ui->comboBox_Ca->currentIndex() == -1)
    {
        QMessageBox::warning(this, tr("Capacité manquante"),
                             tr("Merci de sélectionner une capacité."));
        return;
    }

    int id=idText.toInt();
    QString type=ui->lineEdit_type->currentText();
    QString horaire = ui->lineEdit_h->time().toString("HH:mm");
    int duree=ui->lineEdit_D->text() .toInt();
    int capacite=ui->comboBox_Ca->currentText().toInt();
    int tarif=ui->lineEdit_Ta->text() .toInt();
    int id_formateur=idFormateurText.toInt();
    QDate dateformation = ui->dateEdit_date->date();


    bool test = ftmp.modifier(id,nom,type,horaire,dateformation,duree,lieu,capacite,tarif,id_formateur);

    if (test)
    {
        ui->tableFormation->setModel(ftmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("Modification réussie"),
                                 QObject::tr("Les informations ont été modifiées avec succès.\n"), QMessageBox::Ok);
        ui->tableFormation->setModel(ftmp.afficher()); // 🔄 Actualiser le tableau
    }
    else
    {
        QString err = ftmp.lastError();
         QMessageBox::critical(this, QObject::tr("Erreur"),
                              err.isEmpty() ? QObject::tr("La modification a échoué.\n")
                                            : err);
    }
    clearInputs();
    ui->dateEdit_date->setDate(QDate::currentDate());


}
void interface_formateur::on_lineEditId_editingFinished()
{
    QString id = ui->lineEditId->text().trimmed();

    if (id.isEmpty()) return;

    QSqlQuery query;
    query.prepare("SELECT NOM, TYPE_FORMATION,HORAIRE,DATEFORMATION,DUREE,LIEU,CAPACITE,TARIF,IDFORMATEUR  FROM FORMATION WHERE ID_FORMATION = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur SQL", query.lastError().text());
        return;
    }
    if (query.next()) {

        // Remplir les autres champs
        ui->lineEdit_Nom->setText(query.value(0).toString());
        ui->lineEdit_type->setCurrentText(query.value(1).toString());
        ui->lineEdit_h->setTime(QTime::fromString(query.value(2).toString(), "hh:mm"));
        ui->dateEdit_date->setDate(query.value(3).toDate());
        ui->lineEdit_D->setText(query.value(4).toString());
        ui->lineEdit_lieu->setText(query.value(5).toString());;
        ui->comboBox_Ca->setCurrentText(query.value(6).toString());
        ui->lineEdit_Ta->setText(query.value(7).toString());
        ui->lineEdit_id2->setText(query.value(8).toString());

    } else {

    }

}

void interface_formateur::clearInputs()
{
    ui->lineEditId->clear();
    ui->lineEdit_Nom->clear();
    ui->lineEdit_type->setCurrentIndex(0);
    ui->lineEdit_h->setTime(QTime(0,0));
    ui->lineEdit_D->clear();
    ui->lineEdit_lieu->clear();
    ui->comboBox_Ca->setCurrentIndex(0);
    ui->lineEdit_Ta->clear();
    ui->lineEdit_id2->clear();
    ui->dateEdit_date->setDate(QDate::currentDate());
}


//fontion trier
void interface_formateur::on_pushButtonTrier_clicked()
{
    ui->tableFormation->setModel(ftmp.trier_par_horaire());
}







//fonction rechercher
void interface_formateur::on_pushButton_rechercher_clicked()
{
    QString nom = ui->lineEdit_rechercher->text().trimmed(); // récupère le texte

    formation2 f;
    QSqlQueryModel *model = f.rechercherParNom(nom);
    ui->tableFormation->setModel(model);

    // Optionnel : message si rien n’est trouvé
    if (model->rowCount() == 0 && !nom.isEmpty()) {
        QMessageBox::information(this, "Résultat", "Aucune formation trouvée avec ce nom.");
    }

}
void interface_formateur::on_lineEdit_rechercher_textChanged(const QString &text)
{
    // Si on efface le texte → afficher tout
    if (text.isEmpty()) {
        formation2 f;
        QSqlQueryModel *model = f.afficher();
        ui->tableFormation->setModel(model);
    }
}
//fonction exporter
void interface_formateur::on_pushButton_42_clicked()
{
    QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->tableFormation->model());

    QString fichier = QFileDialog::getSaveFileName(
        this,
        "Exporter en Word",
        "Liste_Formations.doc",
        "Document Word (*.doc)");

    if(fichier.isEmpty()) return;

    formation2 f;
    if(f.exporterDoc(model, fichier))
        QMessageBox::information(this, "Succès", "Exportation réussie !");

}






void interface_formateur::on_pushButton_stat_clicked()
{
    Statistic S(this); // création de la dialog
    S.exec();
}

void interface_formateur::on_pushButton_47_clicked()
{
    CalendarDialog dialog(this);
    dialog.exec();
}





//gestion employeeee


/* ------------------------------------------------------------------ */
/*                         INPUT VALIDATION                           */
/* ------------------------------------------------------------------ */
QString interface_formateur::validateFields(bool forAdd, bool forModify, bool forDelete) const
{
    Q_UNUSED(forAdd);
    Q_UNUSED(forModify);
    Q_UNUSED(forDelete);
    // ---- ID -------------------------------------------------------
    bool ok;
    int id = ui->lineEdit_ID->text().toInt(&ok);
    if (!ok || id <= 0) {
        return tr("L'ID doit être un nombre positif.");
    }

    // ---- CIN -------------------------------------------------------
    if (ui->lineEdit_cin->text().isEmpty()) {
        return tr("Le CIN est obligatoire.");
    }
    // (already forced to digits by validator)

    // ---- NOM / PRENOM -----------------------------------------------
    if (ui->lineEdit_nom->text().trimmed().isEmpty()) {
        return tr("Le nom est obligatoire.");
    }
    if (ui->lineEdit_prenom->text().trimmed().isEmpty()) {
        return tr("Le prénom est obligatoire.");
    }

    // ---- POSTE ------------------------------------------------------
    if (ui->lineEdit_poste->text().trimmed().isEmpty()) {
        return tr("Le poste est obligatoire.");
    }

    // ---- NUM (8 digits) ---------------------------------------------
    QString numStr = ui->lineEdit_num->text();
    if (numStr.length() != 8 || !numStr[0].isDigit()) {
        return tr("Le numéro de téléphone doit contenir exactement 8 chiffres.");
    }

    // ---- EMAIL -------------------------------------------------------
    if (ui->lineEdit_email->text().trimmed().isEmpty()) {
        return tr("L'e-mail est obligatoire.");
    }
    // (validator already checks format, but we double-check)
    QRegularExpression emailRx(R"(^[\w\.\-]+\@[\w\-]+\.[a-zA-Z]{2,}$)");
    if (!emailRx.match(ui->lineEdit_email->text()).hasMatch()) {
        return tr("Veuillez saisir une adresse e-mail valide.");
    }

    // ---- MDP ---------------------------------------------------------
    if (ui->lineEdit_mdp->text().isEmpty()) {
        return tr("Le mot de passe est obligatoire.");
    }

    // ---- DATE (QDateEdit already guarantees a valid date) -----------

    return QString();   // no error
}

/* ------------------------------------------------------------------ */
/*                         CLEAR FIELDS                               */
/* ------------------------------------------------------------------ */
void interface_formateur::clearFields()
{
    ui->lineEdit_ID->clear();
    ui->lineEdit_nom->clear();
    ui->lineEdit_prenom->clear();
    ui->lineEdit_poste->clear();
    ui->lineEdit_cin->clear();
    ui->lineEdit_num->clear();
    ui->lineEdit_email->clear();
    ui->lineEdit_mdp->clear();
    ui->dateEdit->setDate(QDate::currentDate());
}

/* ==================== AJOUTER ==================== */
void interface_formateur::on_btajouter_clicked()
{
    QString err = validateFields(true, false, false);
    if (!err.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur de saisie"), err);
        return;
    }

    int     id          = ui->lineEdit_ID->text().toInt();
    QString nom         = ui->lineEdit_nom->text();
    QString prenom      = ui->lineEdit_prenom->text();
    QString poste       = ui->lineEdit_poste->text();
    int     cin         = ui->lineEdit_cin->text().toInt();
    int     num         = ui->lineEdit_num->text().toInt();
    QString email       = ui->lineEdit_email->text();
    QString mdp         = ui->lineEdit_mdp->text();
    QDate   dateembauche= ui->dateEdit->date();

    employe e(id, nom, prenom, poste, cin, num, dateembauche, email, mdp);
    if (e.ajouter()) {
        QMessageBox::information(this, tr("Succès"), tr("Ajout effectué !"));
        ui->tableView->setModel(e.afficher());
        clearFields();
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de l'ajout !"));
    }
}

/* ==================== SUPPRIMER ==================== */
void interface_formateur::on_btsupprimer_clicked()
{
    QString err = validateFields(false, false, true);
    if (!err.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur de saisie"), err);
        return;
    }

    int id = ui->lineEdit_ID->text().toInt();

    if (etmp.supprimer(id)) {
        QMessageBox::information(this, tr("Succès"), tr("Suppression effectuée !"));
        ui->tableView->setModel(etmp.afficher());
        clearFields();
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Suppression non effectuée !"));
    }
}

/* ==================== MODIFIER ==================== */
void interface_formateur::on_bmodifier_clicked()
{
    QString err = validateFields(false, true, false);
    if (!err.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur de saisie"), err);
        return;
    }

    int     id          = ui->lineEdit_ID->text().toInt();
    QString nom         = ui->lineEdit_nom->text();
    QString prenom      = ui->lineEdit_prenom->text();
    QString poste       = ui->lineEdit_poste->text();
    int     cin         = ui->lineEdit_cin->text().toInt();
    int     num         = ui->lineEdit_num->text().toInt();
    QString email       = ui->lineEdit_email->text();
    QString mdp         = ui->lineEdit_mdp->text();
    QDate   dateembauche= ui->dateEdit->date();

    etmp = employe(id, nom, prenom, poste, cin, num, dateembauche, email, mdp);
    if (etmp.modifier(id)) {
        QMessageBox::information(this, tr("Succès"), tr("Modification effectuée !"));
        ui->tableView->setModel(etmp.afficher());
        clearFields();
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de la modification !"));
    }
}

#include <QSqlRecord>
/* ==================== RECHERCHER (fill) ==================== */
void interface_formateur::on_pushButton_cin_3_clicked()
{
    bool ok;
    int id = ui->lineEdit_ID->text().toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this, tr("Input error"),
                             tr("Veuillez entrer un ID numérique valide."));
        return;
    }

    QSqlQueryModel *model = etmp.fill(id);
    if (!model) {
        QMessageBox::critical(this, tr("Database error"),
                              tr("Échec de l'exécution de la requête."));
        return;
    }

    if (model->rowCount() == 0) {
        QMessageBox::warning(this, tr("Introuvable"),
                             tr("Aucun employé avec l'ID %1").arg(id));
        clearFields();
        delete model;
        return;
    }

    QSqlRecord r = model->record(0);
    ui->lineEdit_nom->setText   (r.value("NOM").toString());
    ui->lineEdit_prenom->setText(r.value("PRENOM").toString());
    ui->lineEdit_poste->setText (r.value("POSTE").toString());
    ui->lineEdit_cin->setText   (r.value("CIN").toString());
    ui->lineEdit_num->setText   (r.value("NUM").toString());
    ui->lineEdit_email->setText (r.value("EMAIL").toString());
    ui->lineEdit_mdp->setText   (r.value("MDP").toString());

    QDate d = r.value("DATEEMBAUCHE").toDate();
    if (d.isValid())
        ui->dateEdit->setDate(d);
    else
        ui->dateEdit->clear();

    QMessageBox::information(this, tr("Succès"), tr("Données chargées."));
    delete model;
}



// ========== APPRENANT SLOT IMPLEMENTATIONS ==========

void interface_formateur::on_pushButton_AJOUTER_6_clicked()
{
    // Récupération des données
    int id_apprenant = ui->lineEdit_cin_6->text().toInt();
    QString nom = ui->lineEdit_nom_3->text();
    QString prenom = ui->lineEdit_prenom_3->text();
    QDate date_naiss = ui->dateEdit_embauche_3->date();
    QString email = ui->lineEdit_contact_3->text();

    // Validation
    if (nom.isEmpty() || prenom.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants", "Le nom et le prénom sont obligatoires !");
        return;
    }

    if (email.isEmpty()) {
        QMessageBox::warning(this, "Email manquant", "L'email est obligatoire !");
        return;
    }

    // Ajouter l'apprenant
    bool test = a.ajouter_apprenant(id_apprenant, nom, prenom, date_naiss, email);
    int id_service = 0;
    if (id_apprenant >= 1001 && id_apprenant <= 1009) id_service = 101;
    else if (id_apprenant >= 1010 && id_apprenant <= 1019) id_service = 102;
    else if (id_apprenant >= 1020 && id_apprenant <= 1029) id_service = 103;
    else if (id_apprenant >= 1030 && id_apprenant <= 1039) id_service = 104;
    else if(id_apprenant>=2000) id_service=105;
    service s;

    if (test ) {
        QMessageBox::information(this, "Succès", "Apprenant ajouté avec succès !");
        on_pushButton_ANNULER_6_clicked(); // Réinitialiser les champs
        ui->tableView_2->setModel(a.afficher()); // Actualiser le tableau

        s.inscription(id_service, id_apprenant);
        s.alert_capacite(id_service);



    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de l'apprenant !");
    }


}

void interface_formateur::on_pushButton_ANNULER_6_clicked()
{
    // Réinitialiser tous les champs apprenant
    ui->lineEdit_cin_6->clear();
    ui->lineEdit_nom_3->clear();
    ui->lineEdit_prenom_3->clear();
    ui->lineEdit_contact_3->clear();

    QDate aujourdhui = QDate::currentDate();
    ui->dateEdit_embauche_3->setDate(aujourdhui.addYears(-17)); // Réinitialiser à 17 ans
}

void interface_formateur::on_pushButton_19_clicked()
{
    QSqlQueryModel *model = a.trier_par_date();
    if (model) {
        ui->tableView_2->setModel(model);
        QMessageBox::information(this, "Tri Réussi", "Apprenants triés par date de naissance (du plus âgé au plus jeune)");
    } else {
        QMessageBox::warning(this, "Erreur", "Échec du tri des apprenants");
    }
}

void interface_formateur::on_pushButton_18_clicked()
{
    // Supprimer l'apprenant
    int id_apprenant = ui->lineEdit_RECHERCHE_2->text().toInt();

    if (id_apprenant <= 0) {
        QMessageBox::warning(this, "ID manquant", "Veuillez sélectionner ou saisir un apprenant à supprimer !");
        return;
    }

    int reply = QMessageBox::question(this, "Confirmation",
                                      "Voulez-vous vraiment supprimer cet apprenant ?",
                                      QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        bool test = a.supprimer(id_apprenant);
        if (test) {
            QMessageBox::information(this, "Succès", "Apprenant supprimé !");
            ui->tableView_2->setModel(a.afficher());
            on_pushButton_ANNULER_6_clicked();

        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression !");
        }
    }
}

void interface_formateur::on_pushButton_17_clicked()  // MODIFIER
{
    int id_apprenant = ui->lineEdit_cin_6->text().toInt();

    if (id_apprenant <= 0) {
        QMessageBox::warning(this, "ID manquant", "Veuillez sélectionner ou saisir un apprenant à modifier !");
        return;
    }

    QString nom = ui->lineEdit_nom_3->text();
    QString prenom = ui->lineEdit_prenom_3->text();
    QDate date_naiss = ui->dateEdit_embauche_3->date();
    QString email = ui->lineEdit_contact_3->text();

    bool test = a.modifier(id_apprenant, nom, prenom, date_naiss, email);

    if (test) {
        QMessageBox::information(this, "Modification", "Modification de l'apprenant réussie !");
        ui->tableView_2->setModel(a.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification !");
    }
}

void interface_formateur::on_pushButton_20_clicked()
{
    a.exporter_vers_word();

}

void interface_formateur::on_lineEdit_RECHERCHE_2_returnPressed()
{
    // Appelle la même fonction que textChanged
    on_lineEdit_RECHERCHE_2_textChanged(ui->lineEdit_RECHERCHE_2->text());
}

void interface_formateur::on_lineEdit_RECHERCHE_2_textChanged(const QString &text)
{
    QString recherche = text.trimmed();

    if (recherche.isEmpty()) {
        ui->tableView_2->setModel(a.afficher()); // Afficher tous si recherche vide
        return;
    }

    // Solution temporaire - filtre le modèle existant
    QSqlQueryModel *model = a.afficher();
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setFilterKeyColumn(0); // Colonne ID
    proxyModel->setFilterFixedString(recherche);
    ui->tableView_2->setModel(proxyModel);
}
void interface_formateur::onApprenantTableSelectionChanged()
{
    QModelIndexList indexes = ui->tableView_2->selectionModel()->selectedRows();
    if (!indexes.isEmpty()) {
        int row = indexes.first().row();
        QAbstractItemModel *model = ui->tableView_2->model();

        int id = model->index(row, 0).data().toInt();
        QString nom = model->index(row, 1).data().toString();
        QString prenom = model->index(row, 2).data().toString();
        QDate date_naiss = model->index(row, 3).data().toDate();
        QString email = model->index(row, 4).data().toString();

        // Remplir les champs
        ui->lineEdit_cin_6->setText(QString::number(id));
        ui->lineEdit_nom_3->setText(nom);
        ui->lineEdit_prenom_3->setText(prenom);
        ui->dateEdit_embauche_3->setDate(date_naiss);
        ui->lineEdit_contact_3->setText(email);
    }
}

// 🆕 IMPLEMENT THE SLOT TO DISPLAY IN tableView_2
void interface_formateur::onGroupeAAfficher(QSqlQueryModel *model)
{
    if (model) {
        ui->tableView_2->setModel(model);  // ✅ Uses tableView_2 (integration table)
        QMessageBox::information(this, "Succès", "Groupe affiché dans le tableau !");
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible d'afficher le groupe");
    }
}



//      CRUDDDDDD   EQUIPEMENT *********************************



void interface_formateur::on_ajouterEquipement_clicked()
{
    QString ID = ui->idEquipement->text().trimmed();
    QString NOM = ui->nomEquipement->text().trimmed();
    QString PRIX = ui->prixEquipement->text().trimmed();
    QString TYPE = ui->typeEquipemrnt->text().trimmed();
    QString ETAT = ui->etatEquipement->currentText().trimmed();
    QString QUANTITE = ui->quantiteEquipement->text().trimmed();

    // 🔹 Vérifier que les champs ne sont pas vides
    if (ID.isEmpty() || NOM.isEmpty() || PRIX.isEmpty() ||
        TYPE.isEmpty() || ETAT.isEmpty() || QUANTITE.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants",
                             "Veuillez remplir tous les champs avant d'ajouter un équipement.");
        return;
    }

    // 🔹 Vérifier que l'ID contient uniquement des chiffres
    QRegularExpression regexID("^[0-9]+$");
    if (!regexID.match(ID).hasMatch()) {
        QMessageBox::warning(this, "ID invalide",
                             "L'ID doit contenir uniquement des chiffres (0-9).");
        return;
    }

    // 🔹 Vérifier que le prix et la quantité sont valides
    bool prixOk, quantiteOk;
    double prix = PRIX.toDouble(&prixOk);
    int quantite = QUANTITE.toInt(&quantiteOk);

    if (!prixOk || prix <= 0) {
        QMessageBox::warning(this, "Erreur de saisie",
                             "Veuillez entrer un prix valide (> 0).");
        return;
    }

    if (!quantiteOk || quantite < 0) {
        QMessageBox::warning(this, "Erreur de saisie",
                             "Veuillez entrer une quantité valide (nombre entier ≥ 0).");
        return;
    }

    // 🔹 Création de l’objet équipement + insertion DB
    equipement e(ID, NOM, PRIX, TYPE, ETAT, QUANTITE);
    bool test = e.ajouter_EQUIPEMENT();

    if (test) {
        QMessageBox::information(this, "Succès", "Ajout effectué avec succès");
        clearFieldsEquipement();
        ui->tableEquipement->setModel(e.afficher());
    } else {
        QMessageBox::critical(this, "Échec", "Ajout non effectué (ID déjà existant ?)");
    }
}
void interface_formateur::clearFieldsEquipement()
{
    ui->idEquipement->clear();
    ui->nomEquipement->clear();
    ui->prixEquipement->clear();
    ui->typeEquipemrnt->clear();
    ui->etatEquipement->setCurrentIndex(0);
    ui->quantiteEquipement->clear();
}

void interface_formateur::on_SupprimerEquipement_clicked()
{
    QModelIndex currentIndex = ui->tableEquipement->currentIndex();

    if (!currentIndex.isValid()) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"),
                             QObject::tr("Veuillez sélectionner une ligne à supprimer."), QMessageBox::Ok);
        return;
    }

    QString ID = ui->tableEquipement->model()->data(
                                                      ui->tableEquipement->model()->index(currentIndex.row(), 0)
                                                      ).toString();

    equipement e;
    bool test = e.supprimer_EQUIPEMENT(ID);

    if (test) {
        QMessageBox::information(nullptr, QObject::tr("Succès"),
                                 QObject::tr("L'équipement a été supprimé avec succès."));
        // ✅ Actualiser l'affichage après suppression
        ui->tableEquipement->setModel(e.afficher());
        clearFieldsEquipement();
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Échec de la suppression de l'équipement."));
    }
}




void interface_formateur::on_ModifierEquipement_clicked()
{
    QString ID = ui->RechercheEquipement->text().trimmed();

    if (ID.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner ou entrer un ID valide.");
        return;
    }

    QString NOM = ui->nomEquipement->text().trimmed();
    QString PRIX = ui->prixEquipement->text().trimmed();
    QString TYPE = ui->typeEquipemrnt->text().trimmed();
    QString ETAT = ui->etatEquipement->currentText().trimmed();
    QString QUANTITE = ui->quantiteEquipement->text().trimmed();

    // ✅ Vérifier les champs
    if (NOM.isEmpty() || PRIX.isEmpty() || TYPE.isEmpty() ||
        ETAT.isEmpty() || QUANTITE.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants",
                             "Veuillez remplir tous les champs avant de modifier un équipement.");
        return;
    }

    bool prixOk, quantiteOk;
    double prix = PRIX.toDouble(&prixOk);
    int quantite = QUANTITE.toInt(&quantiteOk);

    if (!prixOk || prix <= 0) {
        QMessageBox::warning(this, "Erreur de saisie",
                             "Veuillez entrer un prix valide (> 0).");
        return;
    }

    if (!quantiteOk || quantite < 0) {
        QMessageBox::warning(this, "Erreur de saisie",
                             "Veuillez entrer une quantité valide (nombre entier ≥ 0).");
        return;
    }

    equipement e(ID, NOM, PRIX, TYPE, ETAT, QUANTITE);

    if (e.modifier_EQUIPEMENT()) {
        QMessageBox::information(this, "Succès", "L'équipement a été modifié avec succès.");
        ui->tableEquipement->setModel(e.afficher());
        clearFieldsEquipement();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification (ID inexistant ?)");
    }
}


void interface_formateur::on_tableEquipement_activated(const QModelIndex &index)
{
    int row = index.row();

    QAbstractItemModel *model = ui->tableEquipement->model();
    if (!model)
        return;

    QString ID = model->index(row, 0).data().toString();
    QString NOM = model->index(row, 1).data().toString();
    QString PRIX = model->index(row, 2).data().toString();
    QString TYPE = model->index(row, 3).data().toString();
    QString ETAT = model->index(row, 4).data().toString();
    QString QUANTITE = model->index(row, 5).data().toString();

    ui->idEquipement->setText(ID);
    ui->nomEquipement->setText(NOM);
    ui->prixEquipement->setText(PRIX);
    ui->typeEquipemrnt->setText(TYPE);
    ui->etatEquipement->setCurrentText(ETAT);
    ui->quantiteEquipement->setText(QUANTITE);

    // Pour identifier rapidement l'équipement sélectionné
    ui->RechercheEquipement->setText(ID);
}


void interface_formateur::on_rechercherEquipement_clicked()
{
        QString id = ui->RechercheEquipement->text().trimmed();

        if (id.isEmpty()) {
            QMessageBox::warning(this, "Erreur",
                                 "Veuillez entrer un ID d'équipement.");
            return;
        }

        // Appel fonction fillEquipement dans la classe equipement
        QSqlQueryModel *model = e.fillEquipement(id);

        if (!model) {
            QMessageBox::critical(this, "Erreur BD",
                                  "Échec d'exécution de la requête.");
            return;
        }

        if (model->rowCount() == 0) {
            QMessageBox::warning(this, "Introuvable",
                                 "Aucun équipement trouvé avec l'ID : " + id);
            clearFieldsEquipement();
            delete model;
            return;
        }

        // -------------------- Remplissage des champs --------------------
        QSqlRecord r = model->record(0);

        ui->nomEquipement->setText(r.value("NOM").toString());
        ui->prixEquipement->setText(r.value("PRIX").toString());
        ui->typeEquipemrnt->setText(r.value("TYPE").toString());
        ui->etatEquipement->setCurrentText(r.value("ETAT").toString());
        ui->quantiteEquipement->setText(r.value("QUANTITE").toString());

        QMessageBox::information(this, "Succès",
                                 "Équipement chargé avec succès.");

        delete model;
}

/****************service************************/
void interface_formateur::on_pushButton_86_clicked()
{
    service s;
    QSqlQueryModel* model = s.tri_capacite();
    if(model) {
        ui->table->setModel(model);
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de trier par capacité.");
    }
}
#include <QStandardPaths>
#include<QDirIterator>

void interface_formateur::on_pushButton_87_clicked()
{
    service s;
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
    + QDir::separator()
        + "service.pdf";

        s.export_pdf(ui->table,filePath);
        QMessageBox::information(this, "Export", "PDF généré  service.pdf");


}


void interface_formateur::on_pushButton_91_clicked()
{
    service s;

    ui->table->setModel(s.planfication_service());
}

// Add these implementations at the end of interface_formateur.cpp

void interface_formateur::on_pushButton_AjouterEquipement_clicked()
{
    // This function is declared but not implemented
    // You can either implement it or remove the declaration from the header
    on_ajouterEquipement_clicked(); // Call the existing function if they do the same thing
}

void interface_formateur::on_EquipementTable_clicked(const QModelIndex &index)
{
    // This function is declared but not implemented
    // You can either implement it or remove the declaration from the header
    on_tableEquipement_activated(index); // Call the existing function if they do the same thing
}


