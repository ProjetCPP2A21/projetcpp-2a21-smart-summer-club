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
#include "employe.h"
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
#
#include <QMessageBox>
#include <QSqlError>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "statistic.h"
#include "calendardialog.h"
#include <QProcessEnvironment>
#include <QDate>
#include <QTime>
#include <QDebug>

#include <QDateTime>
#include <QDir>
#include <QSqlQuery>

#include "qrcodegen.hpp"
#include "sms.h"
#include "mainwindow.h"
#include "interface_formateur.h"
#include <QMessageBox>
#include <QTableView>
#include <QSqlError>
#include <QRegularExpression>
#include <QSqlRecord>
#include <QFileDialog>
#include <QDesktopServices>
#include <QStandardPaths>
#include <QFileInfo>
#include <QDir>
#include <QDate>
#include <QPrinter>
#include <QFocusEvent>
#include <QIntValidator>
#include <QRegularExpressionValidator>

interface_formateur::interface_formateur(MainWindow *menu, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::interface_formateur),
    menuPrincipal(menu), // on initialise avec le menu passé en paramètre
    colorModel(new ColorSqlModel(this)),
    recherchePlaceholderActive(false)
{
    ui->setupUi(this);
    //ARDUINO
    int ret = A.connect_arduino(); // Connexion à l'Arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
        break;
    case(-1):qDebug() << "arduino is not available";
    }
    QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(update_rfid()));
    connect(A.getserial(), &QSerialPort::readyRead,
            this, &interface_formateur::read_from_arduino);

    qDebug() << "=== DÉMARRAGE APPLICATION ===";
    qDebug() << "Couleurs activées: Vert(disponible), Rouge(en panne), Jaune(réservé)";

    // Afficher automatiquement les équipements au démarrage
    colorModel->setQuery("SELECT ID, NOM, PRIX, TYPE, ETAT, QUANTITE FROM EQUIPEMENT");
    ui->tableEquipement->setModel(colorModel);

    // Définir les en-têtes
    colorModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    colorModel->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    colorModel->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
    colorModel->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
    colorModel->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT"));
    colorModel->setHeaderData(5, Qt::Horizontal, QObject::tr("QUANTITE"));

    // Connecter les signaux pour la recherche améliorée
    connect(ui->RechercheEquipement, &QLineEdit::textChanged, this, &interface_formateur::on_RechercheEquipement_textChanged);
    connect(ui->RechercheEquipement, &QLineEdit::selectionChanged, this, [this]() {
        if (recherchePlaceholderActive) {
            ui->RechercheEquipement->clear();
            recherchePlaceholderActive = false;
            ui->RechercheEquipement->setStyleSheet("background-color: rgb(255, 255, 255); border-radius:10px; border: 3px solid #ffffff; color: rgb(0, 0, 0);");
        }
    });

    // Connecter les signaux de focus
    connect(ui->RechercheEquipement, &QLineEdit::cursorPositionChanged, this, [this](int oldPos, int newPos) {
        Q_UNUSED(oldPos)
        Q_UNUSED(newPos)
        if (recherchePlaceholderActive) {
            ui->RechercheEquipement->clear();
            recherchePlaceholderActive = false;
            ui->RechercheEquipement->setStyleSheet("background-color: rgb(255, 255, 255); border-radius:10px; border: 3px solid #ffffff; color: rgb(0, 0, 0);");
        }
    });
    ui->tableView_2->setModel(etmp.afficher());

    connect(ui->tableEquipement, &QTableView::clicked, this, &interface_formateur::on_EquipementTable_clicked);

    // 🆕 CREATE CHATBOT INTERFACE - PASS 'this' AS PARENT
    a.creerInterfaceChatbot(this);
    // 🆕 CREATE GROUPES INTERFACE
    a.creerInterfaceGroupes(this);
    // 🆕 CONNECT GROUP DISPLAY SIGNAL
    connect(&a, &apprenant::groupeAAfficher, this, &interface_formateur::onGroupeAAfficher);

    //--------------------DEBUT_FORMATEUR----------------------------------------------------------------------------------------------------------
    smsSender = new SmsSender(this);
    connect(smsSender, &SmsSender::smsSent, this, &interface_formateur::onSmsSent);
    connect(smsSender, &SmsSender::smsError, this, &interface_formateur::onSmsError);
    ui->lineEdit_IdFormateur->setValidator(new QIntValidator(1, 99999999, this));
    ui->lineEdit_contactFormateur->setValidator(new QIntValidator(1, 99999999, this));
    ui->lineEdit_salaireFormateur->setValidator(new QIntValidator(1, 99999999, this));
    QRegularExpression regex("^[A-Za-z]+$"); // uniquement lettres
    ui->lineEdit_NomFormateur->setValidator(new QRegularExpressionValidator(regex, this));
    ui->lineEdit_PrenomFormateur->setValidator(new QRegularExpressionValidator(regex, this));

    ui->lineEdit_IdFormateur->setValidator(new QIntValidator(1, 99999999, this));
    ui->lineEdit_nom_formateur_2->setValidator(new QRegularExpressionValidator(regex, this));
    ui->lineEdit_prenom_formateur_4->setValidator(new QRegularExpressionValidator(regex, this));
    ui->lineEdit_Specialite_formateur_4->setValidator(new QRegularExpressionValidator(regex, this));

    ui->Tab_Formateur->setModel(F.afficher());
    ui->Tab_Formateur->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->Tab_Formateur->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ui->pushButton_QRcode, &QPushButton::clicked,
            this, &interface_formateur::on_pushButton_QRcode_clicked);

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
    ui->lineEdit_ID_2->setValidator(intVal);
    ui->lineEdit_cin_2->setValidator(intVal);
    ui->lineEdit_num_2->setValidator(new QIntValidator(10000000, 99999999, this)); // 8 digits

    // letters + space + hyphen for name fields
    QRegularExpression nameRx("^[A-Za-zÀ-ÖØ-öø-ÿ\\-\\s]+$");
    QRegularExpressionValidator *nameVal = new QRegularExpressionValidator(nameRx, this);
    ui->lineEdit_nom_2->setValidator(nameVal);
    ui->lineEdit_prenom_2->setValidator(nameVal);

    // email validator
    QRegularExpression emailRx(R"(^[\w\.\-]+\@[\w\-]+\.[a-zA-Z]{2,}$)");
    ui->lineEdit_email_2->setValidator(new QRegularExpressionValidator(emailRx, this));

    // Display the list at startup
    ui->tableView_2->setModel(etmp.afficher());
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



    // Display the list at startup
    ui->tableView_2->setModel(etmp.afficher());

}

interface_formateur::~interface_formateur()
{
    delete ui;
}

void interface_formateur::setPage(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
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
    ui->stackedWidget->setCurrentIndex(3);
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
    ui->stackedWidget->setCurrentIndex(6);

    service s;
    for (int id_service = 1; id_service <= 105; ++id_service) {
        s.alert_capacite(id_service);
    }
}

void interface_formateur::on_pushButton_apprenant_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void interface_formateur::on_pushButton_equipement_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------DEBUT_FORMATEUR_CRUD-------------------------------------------------------------------------------------------------------------------------------------------------
//metier

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

        QString idd = QString::number(IDselection);
        QSqlQuery query;
        query.prepare("SELECT QRPATH FROM FORMATEUR WHERE IDFORMATEUR = :idd");
        query.bindValue(":idd", idd);
        if (query.exec()) {
            if (query.next()) { // formateur trouvé
                QString path = query.value("QRPATH").toString();

                if (!path.isEmpty() && QFile::exists(path)) {
                    QPixmap pixmap(path); // charger le QR depuis le fichier
                    ui->label_QRcode->setPixmap(
                        pixmap.scaled(
                            ui->label_QRcode->size(),
                            Qt::KeepAspectRatio,
                            Qt::SmoothTransformation
                            )
                        );
                } else {
                    qDebug() << "QR introuvable pour le formateur ID=" << idd;
                    ui->label_QRcode->clear();
                }
            } else {
                qDebug() << "Formateur non trouvé pour ID=" << idd;
                ui->label_QRcode->clear();
            }
        } else {
            qDebug() << "Erreur SQL :" << query.lastError().text();
        }
    }
}

void interface_formateur::on_pushButton_QRcode_clicked()
{
    QString idd = ui->lineEdit_IdFormateur->text();
    if (idd.isEmpty())  {
        qDebug() << "Selectionnez un formateur";
        return;
    }

    //QString dossier = "projetcpp-2a21-smart-summer-club-inet_CRUD_service/build/";
    QString dossier = QDir::currentPath() + "/QRcodes/";
    QString chemin = dossier + "formateur_" + idd + ".png";

    // Vérifier si le fichier existe déjà
    if (QFile::exists(chemin)) {
        qDebug() << "QR déjà existant, pas de regénération.";

        ui->label_QRcode->setPixmap(
            QPixmap(chemin).scaled(
                ui->label_QRcode->size(),
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation
                )
            );
        return;
    }

    // Génération normale si le QR n'existe pas
    F.setIdFormateur(idd.toInt());
    F.setNomFormateur(ui->lineEdit_NomFormateur->text());
    F.setPrenomFormateur(ui->lineEdit_PrenomFormateur->text());
    QImage qr = F.generateQrCode();
    if (qr.isNull()) {
        qDebug() << "Erreur génération QR";
        return;
    }

    // Création du dossier si besoin
    QDir dir;
    if (!dir.exists(dossier)) {
        if (!dir.mkpath(dossier)) {
            qDebug() << "Erreur création dossier :" << dossier;
            return;
        }
    }
    if (!qr.save(chemin)) {
        qDebug() << "Erreur sauvegarde QR";
        return;
    }

    ui->label_QRcode->setPixmap(
        QPixmap::fromImage(qr).scaled(
            ui->label_QRcode->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            )
        );

    // Mise à jour BD
    QSqlQuery query;
    query.prepare("UPDATE FORMATEUR SET QRPATH = :qr WHERE IDFORMATEUR = :id");
    query.bindValue(":qr", chemin);
    query.bindValue(":id", idd);
    if (!query.exec()) {
        qDebug() << "Erreur SQL :" << query.lastError().text();
    } else {
        qDebug() << "QR enregistré en BD pour formateur ID =" << idd;
    }
}

void interface_formateur::on_pushButton_SMS_clicked()
{
    int id = ui->lineEdit_IdFormateur->text().toInt();
    QString nom = ui->lineEdit_NomFormateur->text();
    QString prenom = ui->lineEdit_PrenomFormateur->text();
    QString contact = ui->lineEdit_contactFormateur->text();
    QString specialite = ui->comboBox_specialiteFormateur->currentText();
    double heuresPrevues = ui->doubleSpinBox_heureprevueFormateur->value();

    ui->stackedWidget->setCurrentIndex(2);
    if(id == 0){
        ui->lineEdit_IdFormateur_3->setText("");
        ui->lineEdit_heureprevueFormateur_2->setText("");
    }else{
        ui->lineEdit_IdFormateur_3->setText(QString::number(id));
        ui->lineEdit_nom_formateur_2->setText(nom);
        ui->lineEdit_prenom_formateur_4->setText(prenom);
        ui->lineEdit_phone_formateur->setText(contact);
        ui->lineEdit_heureprevueFormateur_2->setText(QString::number(heuresPrevues));
        ui->lineEdit_Specialite_formateur_4->setText(specialite);
    }
}

void interface_formateur::on_pushButton_retour_clicked()
{
    ui->label_QRcode->clear();
    ui->textEdit_message->clear();

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

    ui->stackedWidget->setCurrentIndex(1);
    ui->lineEdit_phone_formateur->clear();
    ui->lineEdit_IdFormateur->clear();
    ui->lineEdit_nom_formateur_2->clear();
    ui->lineEdit_prenom_formateur_4->clear();
    ui->lineEdit_Specialite_formateur_4->clear();
    ui->lineEdit_heureprevueFormateur_2->clear();
}

void interface_formateur::on_pushButton_Envoyer_message_clicked()
{
    QString num = ui->lineEdit_phone_formateur->text();
    QString number = "+216" + num;
    QString msg = ui->textEdit_message->toPlainText();
    QString text = "**********EDUCAMP***********\n" + msg;

    smsSender->sendSms(number, text);
}

void interface_formateur::onSmsSent()
{
    QMessageBox::information(this, "Succès", "SMS envoyé avec succès !");
}

void interface_formateur::onSmsError(QString err)
{
    QMessageBox::critical(this, "Erreur", "Échec de l'envoi : " + err);
}

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
            &interface_formateur::onTableSelectionChanged);
}

// INIT
void interface_formateur::on_pushButton_AjouterFormateur_clicked()
{
    ui->label_QRcode->clear();

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
    F.setSmsSender(smsSender);
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

        ui->label_QRcode->clear();

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

void interface_formateur::on_pushButton_listeformateur_2_clicked()
{
    ui->label_QRcode->clear();

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

        ui->label_QRcode->clear();

        ui->Tab_Formateur->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->Tab_Formateur->setSelectionMode(QAbstractItemView::SingleSelection);
        disconnect(ui->Tab_Formateur->selectionModel(), nullptr, this, nullptr);
        connect(ui->Tab_Formateur->selectionModel(),
                &QItemSelectionModel::selectionChanged,
                this,
                &interface_formateur::onTableSelectionChanged);
    }
}

void interface_formateur::on_pushButton_TRIER_FORMATEUR_2_clicked()
{
    Formateur F;

    ui->label_QRcode->clear();

    ui->Tab_Formateur->setModel(F.trierDateEmbauche());
    ui->Tab_Formateur->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->Tab_Formateur->setSelectionMode(QAbstractItemView::SingleSelection);
    disconnect(ui->Tab_Formateur->selectionModel(), nullptr, this, nullptr);
    connect(ui->Tab_Formateur->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &interface_formateur::onTableSelectionChanged);
}

void interface_formateur::on_pushButton_PDF_formateur_2_clicked()
{
    Formateur f;
    f.exporterPDF();

    ui->label_QRcode->clear();
}

void interface_formateur::on_pushButton_stat_formateur_clicked()
{
    ui->label_QRcode->clear();

    StatisticsDialog d(this);
    d.exec();
}
//-------------------------FIN_FORMATEUR_CRUD-------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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
    s.statistic_capacite();
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

    // Optionnel : message si rien n'est trouvé
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
    int id = ui->lineEdit_ID_2->text().toInt(&ok);
    if (!ok || id <= 0) {
        return tr("L'ID doit être un nombre positif.");
    }

    // ---- CIN -------------------------------------------------------
    if (ui->lineEdit_cin_2->text().isEmpty()) {
        return tr("Le CIN est obligatoire.");
    }

    // ---- NOM / PRENOM -----------------------------------------------
    if (ui->lineEdit_nom_2->text().trimmed().isEmpty()) {
        return tr("Le nom est obligatoire.");
    }
    if (ui->lineEdit_prenom_2->text().trimmed().isEmpty()) {
        return tr("Le prénom est obligatoire.");
    }

    // ---- POSTE ------------------------------------------------------
    if (ui->lineEdit_poste_2->text().trimmed().isEmpty()) {
        return tr("Le poste est obligatoire.");
    }

    // ---- NUM (8 digits) ---------------------------------------------
    QString numStr = ui->lineEdit_num_2->text();
    if (numStr.length() != 8 || !numStr[0].isDigit()) {
        return tr("Le numéro de téléphone doit contenir exactement 8 chiffres.");
    }

    // ---- EMAIL -------------------------------------------------------
    if (ui->lineEdit_email_2->text().trimmed().isEmpty()) {
        return tr("L'e-mail est obligatoire.");
    }
    QRegularExpression emailRx(R"(^[\w\.\-]+\@[\w\-]+\.[a-zA-Z]{2,}$)");
    if (!emailRx.match(ui->lineEdit_email_2->text()).hasMatch()) {
        return tr("Veuillez saisir une adresse e-mail valide.");
    }

    // ---- MDP ---------------------------------------------------------
    if (ui->lineEdit_mdp_2->text().isEmpty()) {
        return tr("Le mot de passe est obligatoire.");
    }

    return QString();   // no error
}

/* ------------------------------------------------------------------ */
/*                         CLEAR FIELDS                               */
/* ------------------------------------------------------------------ */
void interface_formateur::clearFields()
{
    ui->lineEdit_ID_2->clear();
    ui->lineEdit_nom_2->clear();
    ui->lineEdit_prenom_2->clear();
    ui->lineEdit_poste_2->clear();
    ui->lineEdit_cin_2->clear();
    ui->lineEdit_num_2->clear();
    ui->lineEdit_email_2->clear();
    ui->lineEdit_mdp_2->clear();
    ui->dateEdit_2->setDate(QDate::currentDate());
}

/* ==================== AJOUTER ==================== */
void interface_formateur::on_btajouter_2_clicked()
{
    QString err = validateFields(true, false, false);
    if (!err.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur de saisie"), err);
        return;
    }

    int     id          = ui->lineEdit_ID_2->text().toInt();
    QString nom         = ui->lineEdit_nom_2->text();
    QString prenom      = ui->lineEdit_prenom_2->text();
    QString poste       = ui->lineEdit_poste_2->text();
    int     cin         = ui->lineEdit_cin_2->text().toInt();
    int     num         = ui->lineEdit_num_2->text().toInt();
    QString email       = ui->lineEdit_email_2->text();
    QString mdp         = ui->lineEdit_mdp_2->text();
    QDate   dateembauche= ui->dateEdit_2->date();

    employe e(id, nom, prenom, poste, cin, num, dateembauche, email, mdp);
    if (e.ajouter()) {
        QMessageBox::information(this, tr("Succès"), tr("Ajout effectué !"));
        ui->tableView_3->setModel(e.afficher());
        clearFields();
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de l'ajout !"));
    }
}

/* ==================== SUPPRIMER ==================== */
void interface_formateur::on_btsupprimer_2_clicked()
{
    QString err = validateFields(false, false, true);
    if (!err.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur de saisie"), err);
        return;
    }

    int id = ui->lineEdit_ID_2->text().toInt();

    if (etmp.supprimer(id)) {
        QMessageBox::information(this, tr("Succès"), tr("Suppression effectuée !"));
        ui->tableView_3->setModel(etmp.afficher());
        clearFields();
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Suppression non effectuée !"));
    }
}

/* ==================== MODIFIER ==================== */
void interface_formateur::on_bmodifier_2_clicked()
{
    QString err = validateFields(false, true, false);
    if (!err.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur de saisie"), err);
        return;
    }

    int     id          = ui->lineEdit_ID_2->text().toInt();
    QString nom         = ui->lineEdit_nom_2->text();
    QString prenom      = ui->lineEdit_prenom_2->text();
    QString poste       = ui->lineEdit_poste_2->text();
    int     cin         = ui->lineEdit_cin_2->text().toInt();
    int     num         = ui->lineEdit_num_2->text().toInt();
    QString email       = ui->lineEdit_email_2->text();
    QString mdp         = ui->lineEdit_mdp_2->text();
    QDate   dateembauche= ui->dateEdit_2->date();

    etmp = employe(id, nom, prenom, poste, cin, num, dateembauche, email, mdp);
    if (etmp.modifier(id)) {
        QMessageBox::information(this, tr("Succès"), tr("Modification effectuée !"));
        ui->tableView_3->setModel(etmp.afficher());
        clearFields();
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de la modification !"));
    }
}

/* ==================== RECHERCHER (fill) ==================== */
void interface_formateur::on_pushButton_cin_4_clicked()
{
    bool ok;
    int id = ui->lineEdit_ID_2->text().toInt(&ok);
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
    ui->lineEdit_nom_2->setText   (r.value("NOMEMPLOYE").toString());
    ui->lineEdit_prenom_2->setText(r.value("PRENOMEMPLOYE").toString());
    ui->lineEdit_poste_2->setText (r.value("POSTEEMPLOYE").toString());
    ui->lineEdit_cin_2->setText   (r.value("CINEMPLOYE").toString());
    ui->lineEdit_num_2->setText   (r.value("TELEMPLOYER").toString());
    ui->lineEdit_email_2->setText (r.value("EMAILEMPLOYE").toString());
    ui->lineEdit_mdp_2->setText   (r.value("MDPEMPLOYE").toString());

    QDate d = r.value("DATEEMBAUCHE").toDate();
    if (d.isValid())
        ui->dateEdit_2->setDate(d);
    else
        ui->dateEdit_2->clear();

    QMessageBox::information(this, tr("Succès"), tr("Données chargées."));
    delete model;
}

/* ==================== RECHERCHER EMAIL ==================== */
void interface_formateur::on_btSearchEmail_2_clicked()
{
    QString email = ui->lineEdit_searchEmail_2->text().trimmed();

    if (email.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un email.");
        return;
    }

    QSqlQueryModel *model = etmp.rechercher_email(email);

    if (!model) {
        QMessageBox::critical(this, "Erreur SQL", "Recherche échouée.");
        return;
    }

    ui->tableView_3->setModel(model);
}

/* ==================== TRI CROISSANT ==================== */
void interface_formateur::on_btTriDate_2_clicked()
{
    ui->tableView_3->setModel(etmp.trier_date_croissant());
}

/* ==================== STATISTIQUES ==================== */
void interface_formateur::afficherStatistiques()
{
    QSqlQuery q;
    q.prepare("SELECT POSTEEMPLOYE, COUNT(*) FROM EMPLOYE GROUP BY POSTEEMPLOYE");
    if (!q.exec()) return;

    QPieSeries *series = new QPieSeries();

    while (q.next()) {
        series->append(q.value(0).toString(), q.value(1).toInt());
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des employés par poste");
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // vider ancien contenu
    if (ui->groupBox_stats_2->layout()) {
        QLayoutItem *item;
        QLayout *old = ui->groupBox_stats_2->layout();
        while ((item = old->takeAt(0))) {
            delete item->widget();
            delete item;
        }
        delete old;
    }

    // ajouter le chart
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    ui->groupBox_stats_2->setLayout(layout);
}

void interface_formateur::on_btnStats_2_clicked()
{
    afficherStatistiques();
}

/* ==================== EXPORT WORD ==================== */
void interface_formateur::exportWord()
{
    QString fileName = QFileDialog::getSaveFileName(this, "تصدير إلى Word", "", "ملف RTF (*.rtf)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "خطأ", "تعذر إنشاء الملف!");
        return;
    }

    QTextStream out(&file);
    out << "{\\rtf1\\ansi\\deff0\n";
    out << "\\b قائمة الموظفين \\b0\\par\n";

    QAbstractItemModel *model = ui->tableView_3->model();

    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            out << model->index(row, col).data().toString() << "\t";
        }
        out << "\\par\n";
    }

    out << "}";
    file.close();

    QMessageBox::information(this, "Word", "تم التصدير إلى RTF بنجاح!");
}

/* ==================== EXPORT PDF ==================== */
void interface_formateur::exportPDF()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "*.pdf");
    if (fileName.isEmpty())
        return;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));

    QPainter painter(&printer);
    painter.setFont(QFont("Arial", 16));
    painter.drawText(200, 50, "Liste des employés");

    int y = 100;
    painter.setFont(QFont("Arial", 12));

    QAbstractItemModel* model = ui->tableView_3->model();
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col)
            painter.drawText(50 + col * 100, y, model->index(row, col).data().toString());
        y += 30;

        if (y > printer.pageRect(QPrinter::Point).height() - 50) {
            printer.newPage();
            y = 100;
        }
    }

    painter.end();
    QMessageBox::information(this, "PDF", "Export PDF terminé !");
}

void interface_formateur::on_btnExportPDF_2_clicked()
{
    exportPDF();
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

//   EQUIPEMENT *********************************

// Fonction de recherche améliorée
void interface_formateur::on_RechercheEquipement_textChanged(const QString &text)
{
    if (text.isEmpty() && !recherchePlaceholderActive) {
        // Si le champ est vide et que ce n'est pas le placeholder, afficher tous les équipements
        colorModel->setQuery("SELECT ID, NOM, PRIX, TYPE, ETAT, QUANTITE FROM EQUIPEMENT");
    } else if (!text.isEmpty() && !recherchePlaceholderActive) {
        // Rechercher l'équipement par ID seulement si ce n'est pas le placeholder
        QString recherche = text.trimmed();

        // Vérifier si c'est un nombre (recherche par ID)
        bool ok;
        recherche.toInt(&ok);

        if (ok) {
            // Recherche par ID
            QString queryStr = "SELECT ID, NOM, PRIX, TYPE, ETAT, QUANTITE FROM EQUIPEMENT WHERE ID = '" + recherche + "'";
            colorModel->setQuery(queryStr);

            if (colorModel->lastError().isValid()) {
                qDebug() << "Erreur de recherche:" << colorModel->lastError().text();
            }
        } else {
            // Recherche par nom (si vous voulez aussi rechercher par nom)
            QString queryStr = "SELECT ID, NOM, PRIX, TYPE, ETAT, QUANTITE FROM EQUIPEMENT WHERE NOM LIKE '%" + recherche + "%'";
            colorModel->setQuery(queryStr);
        }
    }
}

void interface_formateur::on_ajouterEquipement_clicked()
{
    QString ID = ui->idEquipement->text().trimmed();
    QString NOM = ui->nomEquipement->text().trimmed();
    QString PRIX = ui->prixEquipement->text().trimmed();
    QString TYPE = ui->typeEquipemrnt->text().trimmed();
    QString ETAT = ui->etatEquipement->currentText().trimmed();
    QString QUANTITE = ui->quantiteEquipement->text().trimmed();
    QDate DATE_ACHAT = ui->datEquipement->date(); // Récupérer la date du DateEdit

    // Contrôle de saisie - Champs vides
    if (ID.isEmpty() || NOM.isEmpty() || PRIX.isEmpty() ||
        TYPE.isEmpty() || ETAT.isEmpty() || QUANTITE.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants",
                             "Veuillez remplir tous les champs avant d'ajouter un équipement.");
        return;
    }

    // Vérifier que l'ID contient seulement des chiffres
    bool idOk;
    ID.toInt(&idOk);
    if (!idOk) {
        QMessageBox::warning(this, "Erreur de saisie",
                             "L'ID doit contenir uniquement des chiffres.");
        ui->idEquipement->setFocus();
        return;
    }

    // Vérifier si le prix et la quantité sont des nombres valides
    bool prixOk, quantiteOk;
    double prix = PRIX.toDouble(&prixOk);
    int quantite = QUANTITE.toInt(&quantiteOk);

    if (!prixOk || prix <= 0) {
        QMessageBox::warning(this, "Erreur de saisie",
                             "Veuillez entrer un prix valide (> 0).");
        ui->prixEquipement->setFocus();
        return;
    }

    if (!quantiteOk || quantite < 0) {
        QMessageBox::warning(this, "Erreur de saisie",
                             "Veuillez entrer une quantité valide (nombre entier ≥ 0).");
        ui->quantiteEquipement->setFocus();
        return;
    }

    // Vérifier que la date d'achat n'est pas dans le futur
    if (DATE_ACHAT > QDate::currentDate()) {
        QMessageBox::warning(this, "Erreur de date",
                             "La date d'achat ne peut pas être dans le futur.");
        ui->datEquipement->setFocus();
        return;
    }

    // Utiliser le constructeur avec date d'achat
    equipementC e(ID, NOM, PRIX, TYPE, ETAT, QUANTITE, DATE_ACHAT);
    bool test = e.ajouter_EQUIPEMENT();

    if (test) {
        QMessageBox::information(this, "Succès", "Ajout effectué avec succès");
        clearFieldsEquipement();
        // Actualiser le modèle coloré
        colorModel->setQuery("SELECT ID, NOM, PRIX, TYPE, ETAT, QUANTITE FROM EQUIPEMENT");
        // NE PAS réinitialiser le placeholder de recherche ici
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
    ui->datEquipement->setDate(QDate::currentDate()); // Réinitialiser à la date actuelle
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

    equipementC e;
    bool test = e.supprimer_EQUIPEMENT(ID);

    if (test) {
        QMessageBox::information(nullptr, QObject::tr("Succès"),
                                 QObject::tr("L'équipement a été supprimé avec succès."));
        // Actualiser le modèle coloré
        colorModel->setQuery("SELECT ID, NOM, PRIX, TYPE, ETAT, QUANTITE FROM EQUIPEMENT");
        // NE PAS réinitialiser le placeholder de recherche ici
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Échec de la suppression de l'équipement."));
    }
}

void interface_formateur::on_ModifierEquipement_clicked()
{
    QString ID = ui->RechercheEquipement->text().trimmed();

    // Vérifier si c'est le placeholder ou vide
    if (ID.isEmpty() || recherchePlaceholderActive) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner ou entrer un ID valide.");
        return;
    }

    // Vérifier que l'ID de recherche contient seulement des chiffres
    bool idOk;
    ID.toInt(&idOk);
    if (!idOk) {
        QMessageBox::warning(this, "Erreur de saisie",
                             "L'ID doit contenir uniquement des chiffres.");
        ui->RechercheEquipement->setFocus();
        return;
    }

    QString NOM = ui->nomEquipement->text().trimmed();
    QString PRIX = ui->prixEquipement->text().trimmed();
    QString TYPE = ui->typeEquipemrnt->text().trimmed();
    QString ETAT = ui->etatEquipement->currentText().trimmed();
    QString QUANTITE = ui->quantiteEquipement->text().trimmed();
    QDate DATE_ACHAT = ui->datEquipement->date();

    // Vérifier les champs
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
        ui->prixEquipement->setFocus();
        return;
    }

    if (!quantiteOk || quantite < 0) {
        QMessageBox::warning(this, "Erreur de saisie",
                             "Veuillez entrer une quantité valide (nombre entier ≥ 0).");
        ui->quantiteEquipement->setFocus();
        return;
    }

    // Vérifier que la date d'achat n'est pas dans le futur
    if (DATE_ACHAT > QDate::currentDate()) {
        QMessageBox::warning(this, "Erreur de date",
                             "La date d'achat ne peut pas être dans le futur.");
        ui->datEquipement->setFocus();
        return;
    }

    equipementC e;
    e.setID(ID);
    e.setNom(NOM);
    e.setPrix(PRIX);
    e.setType(TYPE);
    e.setEtat(ETAT);
    e.setQuantite(QUANTITE);
    e.setDateAchat(DATE_ACHAT);
    e.setDureeVie(5); // Valeur par défaut

    if (e.modifier_EQUIPEMENT()) {
        QMessageBox::information(this, "Succès", "L'équipement a été modifié avec succès.");
        // Actualiser le modèle coloré
        colorModel->setQuery("SELECT ID, NOM, PRIX, TYPE, ETAT, QUANTITE FROM EQUIPEMENT");
        clearFieldsEquipement();
        // NE PAS réinitialiser le placeholder de recherche ici
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification (ID inexistant ?)");
    }
}

void interface_formateur::on_EquipementTable_clicked(const QModelIndex &index)
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

    // Charger les données complètes depuis la base de données pour avoir la date d'achat
    equipementC e_temp;
    QSqlQueryModel *fullModel = e_temp.fillEquipement(ID);

    QDate DATE_ACHAT = QDate::currentDate(); // Valeur par défaut
    if (fullModel && fullModel->rowCount() > 0) {
        QSqlRecord record = fullModel->record(0);
        DATE_ACHAT = record.value("DATE_ACHAT").toDate();
        delete fullModel;
    }

    ui->idEquipement->setText(ID);
    ui->nomEquipement->setText(NOM);
    ui->prixEquipement->setText(PRIX);
    ui->typeEquipemrnt->setText(TYPE);
    ui->etatEquipement->setCurrentText(ETAT);
    ui->quantiteEquipement->setText(QUANTITE);
    ui->datEquipement->setDate(DATE_ACHAT);

    // Pour identifier rapidement l'équipement sélectionné
    ui->RechercheEquipement->setText(ID);
    recherchePlaceholderActive = false;
    ui->RechercheEquipement->setStyleSheet("background-color: rgb(255, 255, 255); border-radius:10px; border: 3px solid #ffffff; color: rgb(0, 0, 0);");
}

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

// TRI avec modèle coloré
void interface_formateur::on_pushButton_23_clicked()
{
    colorModel->setQuery("SELECT ID, NOM, PRIX, TYPE, ETAT, QUANTITE FROM EQUIPEMENT ORDER BY TYPE");
    // NE PAS réinitialiser le placeholder de recherche ici
}

void interface_formateur::on_pushButton_stat_8_clicked()
{
    equipementC e;
    e.statistic_taux_utilisation(ui->tableEquipement);
}

// Ancienne fonction de recherche (maintenant remplacée par la recherche en temps réel)
void interface_formateur::on_rechercherEquipement_clicked()
{
    QString id = ui->RechercheEquipement->text().trimmed();

    // Si c'est le placeholder, on ne fait rien
    if (id.isEmpty() || recherchePlaceholderActive) {
        return;
    }

    // La recherche se fait maintenant automatiquement via on_RechercheEquipement_textChanged
    // Cette fonction peut être utilisée pour forcer une recherche si nécessaire
    on_RechercheEquipement_textChanged(id);
}

void interface_formateur::on_pushButton_stat_7_clicked()
{
    try {
        // Récupérer le nom du fichier
        QString filename = QFileDialog::getSaveFileName(this,
                                                        "Exporter en PDF",
                                                        QDir::homePath() + "/export_equipements_" + QDate::currentDate().toString("yyyyMMdd") + ".pdf",
                                                        "Fichiers PDF (*.pdf)");

        if (filename.isEmpty()) {
            return; // Annulation
        }

        // Vérifier l'extension .pdf
        if (!filename.endsWith(".pdf", Qt::CaseInsensitive)) {
            filename += ".pdf";
        }

        // Vérifier que le tableView existe et a des données
        if (!ui->tableEquipement || !ui->tableEquipement->model()) {
            QMessageBox::warning(this, "Erreur", "Aucune donnée à exporter !");
            return;
        }

        // Appeler la fonction d'export
        equipementC e;
        e.export_pdf(ui->tableEquipement, filename);

        QMessageBox::information(this, "Succès", "Export PDF réussi !\nFichier: " + filename);

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'export PDF: " + QString(e.what()));
    }
}

void interface_formateur::on_ficheTechnique_clicked()
{
    // Vérifier qu'un équipement est sélectionné
    QModelIndex currentIndex = ui->tableEquipement->currentIndex();

    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Sélection requise",
                             "Veuillez sélectionner un équipement dans le tableau pour générer sa fiche technique.");
        return;
    }

    // Récupérer l'ID de l'équipement sélectionné
    QString ID = ui->tableEquipement->model()->data(
                                                      ui->tableEquipement->model()->index(currentIndex.row(), 0)).toString();

    // Charger les données de l'équipement
    equipementC e_temp;
    QSqlQueryModel *model = e_temp.fillEquipement(ID);

    if (!model || model->rowCount() == 0) {
        QMessageBox::critical(this, "Erreur", "Impossible de charger les données de l'équipement.");
        return;
    }

    // Créer l'objet equipementC avec toutes les données
    QSqlRecord record = model->record(0);
    equipementC e(
        record.value("ID").toString(),
        record.value("NOM").toString(),
        record.value("PRIX").toString(),
        record.value("TYPE").toString(),
        record.value("ETAT").toString(),
        record.value("QUANTITE").toString(),
        record.value("DATE_ACHAT").toDate(),
        record.value("DUREE_VIE").toInt()
        );

    // Générer la fiche technique
    QString fiche = e.genererFicheTechnique();

    // Créer une boîte de dialogue simple et efficace
    QDialog *ficheDialog = new QDialog(this);
    ficheDialog->setWindowTitle("📋 Fiche Technique - " + e.getNom());
    ficheDialog->resize(1000, 800);

    QVBoxLayout *mainLayout = new QVBoxLayout(ficheDialog);

    // Créer un QTextBrowser pour afficher le HTML
    QTextBrowser *textBrowser = new QTextBrowser();
    textBrowser->setHtml(fiche);
    textBrowser->setOpenExternalLinks(false);

    // Boutons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *btnSave = new QPushButton("💾 Sauvegarder PDF");
    QPushButton *btnClose = new QPushButton("✕ Fermer");

    buttonLayout->addWidget(btnSave);
    buttonLayout->addStretch(); // Espace flexible
    buttonLayout->addWidget(btnClose);

    mainLayout->addWidget(textBrowser);
    mainLayout->addLayout(buttonLayout);

    // Connexions des boutons - Version ultra-simplifiée
    connect(btnSave, &QPushButton::clicked, [this, &e, fiche]() {
        QString fileName = QFileDialog::getSaveFileName(
            this,
            "Sauvegarder la fiche technique",
            QDir::homePath() + "/Fiche_Technique_" + e.getNom() + "_" + QDate::currentDate().toString("yyyyMMdd") + ".pdf",
            "Fichiers PDF (*.pdf)"
            );

        if (!fileName.isEmpty()) {
            // Méthode simple et fiable pour PDF
            QPrinter printer;
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName(fileName);
            printer.setPageSize(QPageSize(QPageSize::A4));

            QTextDocument doc;
            doc.setHtml(fiche);
            doc.print(&printer);

            QMessageBox::information(this, "Succès",
                                     QString("Fiche technique sauvegardée !\n\n"
                                             "📍 Fichier: %1\n"
                                             "📄 Format: PDF\n"
                                             "💾 Taille: %2 Ko")
                                         .arg(fileName)
                                         .arg(QFileInfo(fileName).size() / 1024));
        }
    });

    connect(btnClose, &QPushButton::clicked, ficheDialog, &QDialog::accept);

    ficheDialog->exec();
    delete model;
}

// Gestion du focus pour le placeholder
void interface_formateur::on_RechercheEquipement_focusIn()
{
    if (recherchePlaceholderActive) {
        ui->RechercheEquipement->clear();
        recherchePlaceholderActive = false;
        ui->RechercheEquipement->setStyleSheet("background-color: rgb(255, 255, 255); border-radius:10px; border: 3px solid #ffffff; color: rgb(0, 0, 0);");
    }
}

void interface_formateur::on_RechercheEquipement_focusOut()
{
    if (ui->RechercheEquipement->text().isEmpty() && !recherchePlaceholderActive) {
        ui->RechercheEquipement->setText("    Rechercher un equipement");
        recherchePlaceholderActive = true;
        ui->RechercheEquipement->setStyleSheet("background-color: rgb(255, 255, 255); border-radius:10px; border: 3px solid #ffffff; color: rgb(162, 162, 162);");
    }
}
//ARDUINO ISLEM
void interface_formateur::update_rfid()
{
    QSerialPort *serial = A.getserial();

    // Lire seulement si une ligne complète est arrivée
    while (serial->canReadLine()) {

        QByteArray data = serial->readLine();

        // Nettoyer l'UID reçu
        QString uid = QString::fromUtf8(data).trimmed(); // enlève \n et espaces
        uid = uid.replace(" ", "");                      // supprime les espaces internes

        // Si trop court → bruit → ignorer
        if (uid.length() < 4)
            continue;

        qDebug() << "📌 UID reçu :" << uid;

        // Vérification dans la table FORMATION
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM FORMATION WHERE NUM_RFID = :uid");
        query.bindValue(":uid", uid);

        if (!query.exec()) {
            qDebug() << "SQL ERROR :" << query.lastError().text();
            return;
        }

        query.next();

        int count = query.value(0).toInt();

        if (count > 0) {
            // --- CAS : RFID existe ---
            QMessageBox::information(this,
                                     "RFID",
                                     "✔ Ce numéro de carte existe dans une formation !");

            // Tu peux envoyer commande Arduino si besoin :
            // A.write_to_arduino("O");  // ouvrir servo
        }
        else {
            // --- CAS : RFID n'existe pas ---
            QMessageBox::warning(this,
                                 "RFID",
                                 "❌ Ce numéro de carte n'existe PAS : " + uid);

            // A.write_to_arduino("F");  // fermer servo
        }
    }
}

void interface_formateur::read_from_arduino()

{
    QByteArray data = A.read_from_arduino();
    QString msg = QString::fromUtf8(data).trimmed();

    qDebug() << "Reçu de l'Arduino :" << msg;

    if (msg.startsWith("ID:"))
    {
        int idA = msg.mid(3).toInt();

        // ✅ Recherche SQL
        QString service = a.rechercher_beneficier(idA).trimmed();

        // ✅ Si service trouvé → accès valide
        if (service != "") {
            QString msg = "ACCES:" + service;
            A.write_to_arduino(msg.toUtf8());

            QString response = "ACCES:" + service + "\n";
            A.write_to_arduino(response.toUtf8());

            qDebug() << "Accès valide, service =" << service;
        }
        else
        {
            // ❌ Aucun service → accès invalide
            A.write_to_arduino("REFUS\n");

            qDebug() << "Accès invalide";
        }
    }}








