#include "formation.h"
#include "ui_formation.h"


#include <QMessageBox>

formation::formation(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::formation)
{
    ui->setupUi(this);


}

formation::~formation()
{
    delete ui;
}

void formation::on_pushButtonAjouter_clicked()
{
    //Récuperation des formations saisies dans les 8 champs
    int id=ui->lineEditId->text() .toInt();
    QString nom=ui->lineEdit_Nom->text();
    QString type=ui->lineEdit_type->currentText();
    int horaire=ui->lineEdit_h->text() .toInt();
    int duree=ui->lineEdit_D->text() .toInt();
    QString lieu=ui->lineEdit_lieu->text();
    int capacite=ui->lineEdit_Ca->text() .toInt();
    int tarif=ui->lineEdit_Ta->text() .toInt();
    //instancier un objet de la classe formation2 en utilisant les informations dans l'interface
    formation2 F(id, nom, type, horaire, duree, lieu, capacite, tarif);
    //inserer l'objet fprmation instancié dans la table formation et recuperer la valeur de reour de query.exec()
    bool test=F.ajouter();

    if(test) //si requete executé==> QmessageBox::information
    {
        //Refresh (Actualiser)

        QMessageBox::information(nullptr, QMessageBox::tr("ok"),QObject::tr("Ajout effecutué\n""Click Cancel to exist."),QMessageBox::Cancel);
    }
    else //si requete non executé ==>QMessagebox::critical
        QMessageBox::critical(nullptr, QObject::tr(" not ok"),QObject::tr("Ajout non effecutué\n""Click Cancel to exist."),QMessageBox::Cancel);





}


