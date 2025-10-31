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
    //ui->tableView->setModel(F.afficher());
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
    bool test=F.ajouter();
    if(test){
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
}



//30.10
/*BOUTON AFFICHER FORMATEUR
void interface_formateur::on_pushButton_AFFICHER_FORMATEUR_clicked()
{

    Formateur F;
    QSqlQueryModel *model = F.afficher();
    ui->tableView_Formateurs->setModel(model);
    ui->tableView_Formateurs->resizeColumnsToContents();

    /*bool test=F.ajouter();
    if(test){
        QMessageBox :: information(nullptr,QObject :: tr("OK"),
                                  QObject::tr("Affichage effectué\n"
                                              "Click cancel to exit"), QMessageBox :: Cancel);
    }else{
        QMessageBox :: critical(nullptr,QObject :: tr("not OK"),
                               QObject::tr("Affichage non effectué\n"
                                           "Click cancel to exit"), QMessageBox :: Cancel);
    }
}




 BOUTON SUPPRIMER FORMATEUR
void interface_formateur::on_pushButton_SupprimerFormateur()
{
    int id=ui->lineEdit_IdFormateur->text().toInt();
    bool test= F.supprimer(id);
    if(test){
        QMessageBox :: information(nullptr,QObject :: tr("OK"),
            QObject::tr("Suppression effectuée\n"
                        "Click cancel to exit"), QMessageBox :: Cancel);
    }else
        QMessageBox :: critical(nullptr,QObject :: tr("not OK"),
                                  QObject::tr("Suppression non effectuée\n"
                                              "Click cancel to exit"), QMessageBox :: Cancel);

}
*/
















