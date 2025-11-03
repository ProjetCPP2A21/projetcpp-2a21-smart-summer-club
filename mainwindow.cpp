#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "service.h"
#include <QMessageBox>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->table->setModel(s.affiche());
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::verife()
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
        QMessageBox::critical(nullptr, "erreur", "verifier  voter nom de service stp!!");
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



void MainWindow::on_button_ajouter_clicked()
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
        // Appeler la fonction d'ajout
        if (test) {
            ui->table->setModel(s.affiche());
            QMessageBox::information(this, "Succès", "Service ajouté avec succès !");
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de l'ajout du service.");
        }
    }
}


/*void MainWindow::on_pushButton_85_clicked()
{
    service s;
    QSqlQueryModel* model = s.affiche();
    if (model) {
        ui->table->setModel(model); // ui->table doit être un QTableView
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible d'afficher les services.");
    }

}
*/


void MainWindow::on_pushButton_89_clicked()
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


void MainWindow::on_pushButton_91_clicked()
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




void MainWindow::on_pushButton_88_clicked()
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





void MainWindow::on_pushButton_ANNULER_4_clicked()
{

    service s;
    QString id_modi = ui->id2->text();
    if (id_modi.isEmpty()) {
        QMessageBox::warning(this, "Champ vide", "Veuillez saisir un ID service tu va supprimer  !");
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

}




