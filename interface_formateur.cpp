#include "interface_formateur.h"
#include "ui_interface_formateur.h"
#include <QMessageBox>

interface_formateur::interface_formateur(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::interface_formateur)
{
    ui->setupUi(this);
}

interface_formateur::~interface_formateur()
{
    delete ui;
}

/*void interface_formateur::on_pushButton_stat_clicked()
{
    stat = new statistique(this);  // création de l'interface_formateur
    stat->show();
    // this->hide();
}*/

void interface_formateur::on_pushButton_clicked()
{
    QMessageBox::information(this, "Formateur", "Bouton Formateur cliqué !");
}



/*void interface_formateur::on_pushButton_rapport_clicked()
{
    rap = new rapport(this);  // création de dialog rapport
    rap->show();
    // this->hide();

    // QMessageBox::information(this, "rapport", "Bouton rapport cliqué !");
}*/





void interface_formateur::on_pushButton_stat_2_clicked()
{
    stat = new statistique(this);  // création de l'interface_formateur
    stat->show();
    // this->hide();
}

