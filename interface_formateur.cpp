#include "interface_formateur.h"
#include "ui_interface_formateur.h"
#include "statisticsdialog.h"
#include "mainwindow.h"
#include "formateurs.h"
#include <QMessageBox>
#include <QTableView>


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
    QDate date =ui->dateEdit_embaucheFormateur->date();
    QString dateEmbauche =date.toString();
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

   /* if(afficherclique){
        ui->Tab_Formateur->setModel(F.afficher());
    }*/

    if(test){
      //  if(afficherclique){
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

