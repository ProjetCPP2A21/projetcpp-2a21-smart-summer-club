#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "interface_formateur.h"

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

void MainWindow::on_pushButton_clicked()
{
    interface_formateur *inter = new interface_formateur(this);
    inter->setPage(1); //forcer l'affichage dans la page formateur
    inter->show();
    this->hide();
}

void MainWindow::on_pushButton_gestionemploye_clicked()
{
    interface_formateur *inter = new interface_formateur(this);
    inter->setPage(0); //forcer l'affichage dans la page employe
    inter->show();
    this->hide();
}


void MainWindow::on_pushButton_gestionformation_clicked()
{
    interface_formateur *inter = new interface_formateur(this);
    inter->setPage(2); //forcer l'affichage dans la page employe
    inter->show();
    this->hide();
}





void MainWindow::on_pushButton_gestionservice_clicked()
{
    interface_formateur *inter = new interface_formateur(this);
    inter->setPage(5); //forcer l'affichage dans la page employe
    inter->show();
    this->hide();
}

