#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "interface_formateur.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    inter_form = new interface_formateur(); // création fenêtre formateur
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    inter_form->show();  // quand je clique, la 2e fenêtre s'affiche
    this->hide();  // cacher la fenêtre principale
}




