#include "interface_formateur.h"
#include "ui_interface_formateur.h"
#include "statisticsdialog.h"
#include "mainwindow.h"
#include "formateurs.h"
#include <QMessageBox>
#include <QTableView>
#include "service.h"
#include "formation2.h"
#include <QSqlError>


interface_formateur::interface_formateur(MainWindow *menu, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::interface_formateur),
    menuPrincipal(menu)   // on initialise avec le menu passé en paramètre
{
    ui->setupUi(this);

    ui->Tab_Formateur->setModel(F.afficher());
    //afficherclique= true;
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


    //FORMATION//

    // Connecte le signal quand l'utilisateur finit de saisir l'ID
    connect(ui->lineEditId, &QLineEdit::editingFinished,
            this, &interface_formateur::on_lineEditId_editingFinished);
    formation2 F;
    ui->tableFormation->setModel(ftmp.afficher());
    QIntValidator *validator = new QIntValidator(0, 999999, this);
    ui->lineEditId->setValidator(validator);
    ui->lineEdit_D->setValidator(validator);
    ui->lineEdit_Ca->setValidator(validator);
    ui->lineEdit_Ta->setValidator(validator);
    //ui->lineEdit_id2->setValidator(validator);

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
    StatisticsDialog d(this); // création de la dialog
    d.exec();
}


void interface_formateur::on_pushButton_stat_2_clicked()
{
    StatisticsDialog d(this); // création de la dialog
    d.exec();
}


void interface_formateur::on_pushButton_stat_3_clicked()
{
    StatisticsDialog d(this); // création de la dialog
    d.exec();
}

void interface_formateur::on_pushButton_stat_6_clicked()
{
    StatisticsDialog d(this); // création de la dialog
    d.exec();
}

/*service*/
void interface_formateur::on_pushButton_service_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void interface_formateur::on_pushButton_apprenant_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void interface_formateur::on_pushButton_equipement_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


// BOUTON AJOUETR FORMATEUR
void interface_formateur::on_pushButton_AJOUTER_5_clicked()
{
    // Récupertaion des informations
    int id= ui->lineEdit_IdFormateur->text().toInt();
    QString nom =ui->lineEdit_NomFormateur->text();
    QString prenom =ui->lineEdit_PrenomFormateur->text();
    QString contact =ui->lineEdit_contactFormateur->text();
    float salaire= ui->lineEdit_salaireFormateur->text().toFloat();
    QString specialite =ui->comboBox_specialiteFormateur->currentText();
    float heuresPrevues= ui->doubleSpinBox_heureprevueFormateur->value();
    // QDate date =ui->dateEdit_embaucheFormateur->date().toString("yyyy-MM-dd");
    QString dateEmbauche = ui->dateEdit_embaucheFormateur->date().toString("yyyy-MM-dd");
    //QString dateEmbauche =date;
    QString sexe;

    if(ui->checkBox_hommeFormateur->isChecked()){
        sexe = "Homme";
    }else if(ui->checkBox_femmeFormateur->isChecked()){
        sexe ="Femme";
    }else{
        sexe ="";
    }


    Formateur F(id,nom,prenom,sexe,contact,dateEmbauche,specialite,heuresPrevues,salaire);
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

    // Réinitialisation des champs
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



// Bouton de réinitialisation des champs
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


//BOUTON SUPPRIMER FORMATEUR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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



// Methode : selectionner un formateur du tableau
void interface_formateur::onTableSelectionChanged()
{
    // Vérifier s’il y a une ligne sélectionnée
    QModelIndexList indexes = ui->Tab_Formateur->selectionModel()->selectedRows();
    if (!indexes.isEmpty()) {
        int row = indexes.first().row(); // la première ligne sélectionnée

        // Récupérer les valeurs de la ligne
        IDselection = ui->Tab_Formateur->model()->index(row, 0).data().toInt();
        QString nom = ui->Tab_Formateur->model()->index(row, 1).data().toString();
        QString prenom = ui->Tab_Formateur->model()->index(row, 2).data().toString();
        QString contact = ui->Tab_Formateur->model()->index(row, 3).data().toString();
        QString sexe = ui->Tab_Formateur->model()->index(row, 4).data().toString();
        //QString date = ui->Tab_Formateur->model()->index(row, 5).data().toString();
        //QString specialite = ui->Tab_Formateur->model()->index(row, 6).data().toString();
        //float heuresPrevues = ui->Tab_Formateur->model()->index(row, 7).data().toFloat();
        float salaire= ui->Tab_Formateur->model()->index(row, 8).data().toFloat();

        // remplir les champs du formulaire automatiquement
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
        /*     //ui->doubleSpinBox_heureprevueFormateur->setValue(heuresPrevues);
        //ui->dateEdit_embaucheFormateur->setDate(QDate::fromString(date, Qt::TextDate));

        if(spc ==""){
            ui->comboBox_specialiteFormateur->setCurrentIndex(0);
        }else if(spc ==""){
            ui->comboBox_specialiteFormateur->setCurrentIndex(1);
        }else if(spc ==""){
            ui->comboBox_specialiteFormateur->setCurrentIndex(2);
        }else if(spc ==""){
            ui->comboBox_specialiteFormateur->setCurrentIndex(3);
        }else if(spc ==""){
            ui->comboBox_specialiteFormateur->setCurrentIndex(4);
        }else if(spc ==""){
            ui->comboBox_specialiteFormateur->setCurrentIndex(5);
        }else if(spc ==""){
            ui->comboBox_specialiteFormateur->setCurrentIndex(6);
        }
*/
    }
}


// Metier : Recherche d'un formateur selon don ID
void interface_formateur::on_pushButton_RechercheFormateur_clicked()
{
    int id= ui->lineEdit_RechercheFormateur->text().toInt();

    bool test= F.recherche(id);
    if(test == true){
        QMessageBox::information(this, tr("Succès"),
                                 tr("Formateur trouvé !"));

        // remplir les champs du formulaire automatiquement
        ui->lineEdit_IdFormateur->setText(QString::number(id));
        ui->lineEdit_NomFormateur->setText(F.getNomFormateur());
        ui->lineEdit_PrenomFormateur->setText(F.getPrenomFormateur());
        ui->lineEdit_contactFormateur->setText(F.getContactFormateur());
        QString seexe = F.getPrenomFormateur();
        if(seexe =="Femme"){
            ui->checkBox_hommeFormateur->setChecked(false);
            ui->checkBox_femmeFormateur->setChecked(true);
        }else{
            ui->checkBox_hommeFormateur->setChecked(true);
            ui->checkBox_femmeFormateur->setChecked(false);
        }
        //ui->lineEdit_salaireFormateur->setText(QString::number(salaire));
        /*     //ui->doubleSpinBox_heureprevueFormateur->setValue(heuresPrevues);
        //ui->dateEdit_embaucheFormateur->setDate(QDate::fromString(date, Qt::TextDate));

        if(spc ==""){
            ui->comboBox_specialiteFormateur->setCurrentIndex(0);
        }else if(spc ==""){
            ui->comboBox_specialiteFormateur->setCurrentIndex(1);
        }else if(spc ==""){
            ui->comboBox_specialiteFormateur->setCurrentIndex(2);
        }else if(spc ==""){
            ui->comboBox_specialiteFormateur->setCurrentIndex(3);
        }else if(spc ==""){
            ui->comboBox_specialiteFormateur->setCurrentIndex(4);
        }else if(spc ==""){
            ui->comboBox_specialiteFormateur->setCurrentIndex(5);
        }else if(spc ==""){
            ui->comboBox_specialiteFormateur->setCurrentIndex(6);
        }
*/
    }else{
        QMessageBox::information(this, tr("Echec"),
                                 tr("Formateur non trouvé."));
    }
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

    // Récupertaion des informations
    int id= ui->lineEdit_IdFormateur->text().toInt();
    QString nom =ui->lineEdit_NomFormateur->text();
    QString prenom =ui->lineEdit_PrenomFormateur->text();
    QString contact =ui->lineEdit_contactFormateur->text();
    float salaire= ui->lineEdit_salaireFormateur->text().toFloat();
    QString specialite =ui->comboBox_specialiteFormateur->currentText();
    float heuresPrevues= ui->doubleSpinBox_heureprevueFormateur->value();
    QDate date =ui->dateEdit_embaucheFormateur->date();
    QString dateEmbauche =date.toString("yyyy-MM-dd");
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
                               QObject::tr("modification non effectuée\n"
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

//gestion service CRUD//
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
}





void interface_formateur::on_pushButton_stat_13_clicked()
{
    StatisticsDialog d(this); // création de la dialog
    d.exec();
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
    //Récuperation des formations saisies dans les 8 champs
    int id=ui->lineEditId->text().toInt();
    QString nom=ui->lineEdit_Nom->text();
    QString type=ui->lineEdit_type->currentText();
    QString horaire = ui->lineEdit_h->time().toString("HH:mm");
    int duree=ui->lineEdit_D->text() .toInt();
    QString lieu=ui->lineEdit_lieu->text();
    int capacite=ui->lineEdit_Ca->text() .toInt();
    int tarif=ui->lineEdit_Ta->text() .toInt();
    int id_formateur=ui->lineEdit_id2->text() .toInt();

    //instancier un objet de la classe formation2 en utilisant les informations dans l'interface
    formation2 F (id, nom, type, horaire, duree, lieu, capacite, tarif , id_formateur );
    //inserer l'objet fprmation instancié dans la table formation et recuperer la valeur de reour de query.exec()
    bool test=F.ajouter();

    if(test) //si requete executé==> QmessageBox::information
    {
        //Refresh (Actualiser)
        ui->tableFormation->setModel(ftmp.afficher());

        QMessageBox::information(nullptr, QMessageBox::tr("ok"),QObject::tr("Ajout effecutué\n""Click Cancel to exist."),QMessageBox::Cancel);
    }
    else //si requete non executé ==>QMessagebox::critical
        QMessageBox::critical(nullptr, QObject::tr(" not ok"),QObject::tr("Ajout non effecutué\n""Click Cancel to exist."),QMessageBox::Cancel);
    ui->lineEditId->clear();
    ui->lineEdit_Nom->clear();
    ui->lineEdit_type->setCurrentIndex(0);
    ui->lineEdit_h->clear();
    ui->lineEdit_D->clear();
    ui->lineEdit_lieu->clear();
    ui->lineEdit_Ca->clear();
    ui->lineEdit_Ta->clear();
    ui->lineEdit_id2->clear();



}



void interface_formateur::on_pushButtonsupprimer_clicked()
{
    int id = ui->lineEditId->text().toInt();
    qDebug() << "ID à supprimer =" << id;

    bool test = ftmp.supprimer(id);

    if (test)
    {
        ui->tableFormation->setModel(ftmp.afficher());
        QMessageBox::information(nullptr, "OK", "Suppression effectuée ");
        ui->tableFormation->setModel(ftmp.afficher()); // Actualiser la table
    } else {
        QMessageBox::critical(nullptr, "Erreur", "Suppression non effectuée ");
    }
    ui->lineEditId->clear();
    ui->lineEdit_Nom->clear();
    ui->lineEdit_type->setCurrentIndex(0);
    ui->lineEdit_h->clear();
    ui->lineEdit_D->clear();
    ui->lineEdit_lieu->clear();
    ui->lineEdit_Ca->clear();
    ui->lineEdit_Ta->clear();
    ui->lineEdit_id2->clear();
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

    int id=ui->lineEditId->text().toInt();
    QString nom=ui->lineEdit_Nom->text();
    QString type=ui->lineEdit_type->currentText();
    QString horaire = ui->lineEdit_h->time().toString("HH:mm");
    int duree=ui->lineEdit_D->text() .toInt();
    QString lieu=ui->lineEdit_lieu->text();
    int capacite=ui->lineEdit_Ca->text() .toInt();
    int tarif=ui->lineEdit_Ta->text() .toInt();
    int id_formateur=ui->lineEdit_id2->text() .toInt();


    bool test = ftmp.modifier(id,nom,type,horaire,duree,lieu,capacite,tarif,id_formateur);

    if (test)
    {
        ui->tableFormation->setModel(ftmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("Modification réussie"),
                                 QObject::tr("Les informations ont été modifiées avec succès.\n"), QMessageBox::Ok);
        ui->tableFormation->setModel(ftmp.afficher()); // 🔄 Actualiser le tableau
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("La modification a échoué.\n"), QMessageBox::Cancel);
    }
    ui->lineEditId->clear();
    ui->lineEdit_Nom->clear();
    ui->lineEdit_type->setCurrentIndex(0);
    ui->lineEdit_h->clear();
    ui->lineEdit_D->clear();
    ui->lineEdit_lieu->clear();
    ui->lineEdit_Ca->clear();
    ui->lineEdit_Ta->clear();
    ui->lineEdit_id2->clear();


}
void interface_formateur::on_lineEditId_editingFinished()
{
    QString id = ui->lineEditId->text().trimmed();

    if (id.isEmpty()) return;

    QSqlQuery query;
    query.prepare("SELECT NOM, TYPE_FORMATION,HORAIRE,DUREE,LIEU,CAPACITE,TARIF,IDFORMATEUR  FROM FORMATION WHERE ID_FORMATION = :id");
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
        ui->lineEdit_D->setText(query.value(3).toString());
        ui->lineEdit_lieu->setText(query.value(4).toString());;
        ui->lineEdit_Ca->setText(query.value(5).toString());
        ui->lineEdit_Ta->setText(query.value(6).toString());
        ui->lineEdit_id2->setText(query.value(7).toString());

    } else {

    }

}



void interface_formateur::on_pushButtonTrier_clicked()
{
    ui->tableFormation->setModel(ftmp.trier_par_horaire());
}
