#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "interface_formateur.h"
#include "service.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ✅ Implementation of setPosteEmploye
void MainWindow::setPosteEmploye(const QString &poste)
{
    posteEmploye = poste.toLower().trimmed();
    qDebug() << "Poste employé défini:" << posteEmploye;
}

// ✅ Implementation of hasAccess
bool MainWindow::hasAccess(const QString &requiredPoste)
{
    if (posteEmploye == requiredPoste.toLower()) {
        return true;
    }

    QMessageBox::warning(this, "Accès refusé",
                         "Vous n'avez pas l'autorisation d'accéder à cette section.\n"
                         "Votre poste : " + posteEmploye.toUpper() + "\n"
                                                        "Accès requis : " + requiredPoste.toUpper());
    return false;
}

void MainWindow::on_pushButton_clicked()
{
    if (!hasAccess("formateur")) {
        return;
    }

    interface_formateur *inter = new interface_formateur(this);
    inter->setPage(1);  // forcer l'affichage dans la page formateur
    inter->show();
    this->hide();
}

void MainWindow::on_pushButton_gestionemploye_clicked()
{
    if (!hasAccess("employe")) {
        return;
    }

    interface_formateur *inter = new interface_formateur(this);
    inter->setPage(0);  // forcer l'affichage dans la page employe
    inter->show();
    this->hide();
}

void MainWindow::on_pushButton_gestionformation_clicked()
{
    if (!hasAccess("formation")) {
        return;
    }

    interface_formateur *inter = new interface_formateur(this);
    inter->setPage(3);  // forcer l'affichage dans la page formation
    inter->show();
    this->hide();
}

void MainWindow::on_pushButton_gestionservice_clicked()
{
    if (!hasAccess("service")) {
        return;
    }

    interface_formateur *inter = new interface_formateur(this);
    inter->setPage(6);  // forcer l'affichage dans la page service
    service s;
    s.alert_capacite(101);
    s.alert_capacite(102);
    s.alert_capacite(103);
    s.alert_capacite(104);
    this->hide();
}

void MainWindow::on_pushButton_gestionapprenant_clicked()
{
    if (!hasAccess("apprenant")) {
        return;
    }

    interface_formateur *inter = new interface_formateur(this);
    inter->setPage(4);  // forcer l'affichage dans la page apprenant
    inter->show();
    this->hide();
}

void MainWindow::on_pushButton_gestionequipement_clicked()
{
    if (!hasAccess("equipement")) {
        return;
    }

    interface_formateur *inter = new interface_formateur(this);
    inter->setPage(5);  // forcer l'affichage dans la page equipement
    inter->show();
    this->hide();
}
