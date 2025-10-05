#include "interface_formateur.h"
#include "ui_interface_formateur.h"
#include "statisticsdialog.h"
#include "mainwindow.h"
#include <QMessageBox>

interface_formateur::interface_formateur(MainWindow *menu, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::interface_formateur),
    menuPrincipal(menu)   // on initialise avec le menu passé en paramètre
{
    ui->setupUi(this);
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

