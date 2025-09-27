#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "formation.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
Formation f;
f.setId(ui->lineEdit_id->text());
f.setNom(ui->lineEdit_nom->text());
f.setType(ui->lineEdit_type->currentText());
f.setHoraire(ui->lineEdit_h->text());
f.setDuree(ui->lineEdit_D->text());
f.setLieu(ui->lineEdit_lieu->text());
f.setCapacite(ui->lineEdit_Ca->text());
f.setTarif(ui->lineEdit_Ta->text());


}

