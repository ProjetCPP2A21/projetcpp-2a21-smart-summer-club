#include "formation.h"
#include "ui_formation.h"
#include <QTableView>
#include <formation2.h>
#include <QMessageBox>
#include <QSqlError>







formation::formation(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::formation)
{
    ui->setupUi(this);
    // Connecte le signal quand l'utilisateur finit de saisir l'ID
    connect(ui->lineEditId, &QLineEdit::editingFinished,
            this, &formation::on_lineEditId_editingFinished);
    formation2 F;
    ui->tableFormation->setModel(ftmp.afficher());
    QIntValidator *validator = new QIntValidator(0, 999999, this);
    ui->lineEditId->setValidator(validator);
    ui->lineEdit_D->setValidator(validator);
    ui->lineEdit_Ca->setValidator(validator);
    ui->lineEdit_Ta->setValidator(validator);
    //ui->lineEdit_id2->setValidator(validator);


}

formation::~formation()
{
    delete ui;
}

void formation::on_pushButtonAjouter_clicked()
{
    //Récuperation des formations saisies dans les 8 champs
    int id=ui->lineEditId->text().toInt();
    QString nom=ui->lineEdit_Nom->text();
    QString type=ui->lineEdit_type->currentText();
    int horaire=ui->lineEdit_h->text() .toInt();
    int duree=ui->lineEdit_D->text() .toInt();
    QString lieu=ui->lineEdit_lieu->text();
    int capacite=ui->lineEdit_Ca->text() .toInt();
    int tarif=ui->lineEdit_Ta->text() .toInt();
    //int id_formateur=ui->lineEdit_id2->text() .toInt();

    //instancier un objet de la classe formation2 en utilisant les informations dans l'interface
    formation2 F (id, nom, type, horaire, duree, lieu, capacite, tarif );
    //inserer l'objet fprmation instancié dans la table formation et recuperer la valeur de reour de query.exec()
    bool test=F.ajouter();

    if(test) //si requete executé==> QmessageBox::information
    {
        //Refresh (Actualiser)
        ui->tableFormation->setModel(ftmp.afficher());

        QMessageBox::information(nullptr, QMessageBox::tr("ok"),QObject::tr("Ajout effecutué\n""Click Cancel to exist."),QMessageBox::Cancel);
    }
    else //si requete non executé ==>QMessagebox::critical
        QMessageBox::critical(nullptr, QObject::tr(" not ok"),QObject::tr("Ajout non effecutué\n""Click Cancel to exist."),QMessageBox::Cancel);
    ui->lineEditId->clear();
    ui->lineEdit_Nom->clear();
    ui->lineEdit_type->setCurrentIndex(0);
    ui->lineEdit_h->clear();
    ui->lineEdit_D->clear();
    ui->lineEdit_lieu->clear();
    ui->lineEdit_Ca->clear();
    ui->lineEdit_Ta->clear();
    //ui->lineEdit_id2->clear();



}



void formation::on_pushButtonsupprimer_clicked()
{
    int id = ui->lineEditId->text().toInt();
    qDebug() << "ID à supprimer =" << id;

    bool test = ftmp.supprimer(id);

    if (test)
    {
        ui->tableFormation->setModel(ftmp.afficher());
        QMessageBox::information(nullptr, "OK", "Suppression effectuée ");
        ui->tableFormation->setModel(ftmp.afficher()); // Actualiser la table
    } else {
        QMessageBox::critical(nullptr, "Erreur", "Suppression non effectuée ");
    }
    ui->lineEditId->clear();
    ui->lineEdit_Nom->clear();
    ui->lineEdit_type->setCurrentIndex(0);
    ui->lineEdit_h->clear();
    ui->lineEdit_D->clear();
    ui->lineEdit_lieu->clear();
    ui->lineEdit_Ca->clear();
    ui->lineEdit_Ta->clear();
    //ui->lineEdit_id2->clear();
}
/*
void formation::onTableSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    if (!selected.indexes().isEmpty())
    {
        QModelIndex index = selected.indexes().first();
        int row = index.row();

        QAbstractItemModel *model = ui->tableFormation->model();

        int id = model->index(row, 0).data().toInt();
        QString nom = model->index(row, 1).data().toString();
        QString type = model->index(row, 2).data().toString();
        int horaire = model->index(row, 3).data().toInt();
        int duree = model->index(row, 4).data().toInt();
        QString lieu = model->index(row, 5).data().toString();
        int capacite = model->index(row, 6).data().toInt();
        int tarif  = model->index(row, 7).data().toInt();
        //int id_formateur  = model->index(row, 8).data().toInt();



        QTime h(horaire, 0);

        ui->lineEditId->setText(QString::number(id));
        ui->lineEdit_Nom->setText(nom);
        ui->lineEdit_type->setCurrentText(type);
        ui->lineEdit_h->setTime(h);
        ui->lineEdit_D->setText(QString::number(duree));
        ui->lineEdit_lieu->setText(lieu);
        ui->lineEdit_Ca->setText(QString::number(capacite));
        ui->lineEdit_Ta->setText(QString::number(tarif));
        //ui->lineEdit_id2->setText(QString::number(id_formateur));


    }
}
*/



void formation::on_pushButtonModifier_clicked()
{

    int id=ui->lineEditId->text().toInt();
    QString nom=ui->lineEdit_Nom->text();
    QString type=ui->lineEdit_type->currentText();
    int horaire=ui->lineEdit_h->text() .toInt();
    int duree=ui->lineEdit_D->text() .toInt();
    QString lieu=ui->lineEdit_lieu->text();
    int capacite=ui->lineEdit_Ca->text() .toInt();
    int tarif=ui->lineEdit_Ta->text() .toInt();
    //int id_formateur=ui->lineEdit_id2->text() .toInt();


        bool test = ftmp.modifier(id,nom,type,horaire,duree,lieu,capacite,tarif);

        if (test)
        {
            ui->tableFormation->setModel(ftmp.afficher());
            QMessageBox::information(nullptr, QObject::tr("Modification réussie"),
                                     QObject::tr("Les informations ont été modifiées avec succès.\n"), QMessageBox::Ok);
            ui->tableFormation->setModel(ftmp.afficher()); // 🔄 Actualiser le tableau
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                  QObject::tr("La modification a échoué.\n"), QMessageBox::Cancel);
        }
        ui->lineEditId->clear();
        ui->lineEdit_Nom->clear();
        ui->lineEdit_type->setCurrentIndex(0);
        ui->lineEdit_h->clear();
        ui->lineEdit_D->clear();
        ui->lineEdit_lieu->clear();
        ui->lineEdit_Ca->clear();
        ui->lineEdit_Ta->clear();
        //ui->lineEdit_id2->clear();


}
void formation::on_lineEditId_editingFinished()
{
    QString id = ui->lineEditId->text().trimmed();

    if (id.isEmpty()) return;

    QSqlQuery query;
    query.prepare("SELECT NOM, TYPE_FORMATION,HORAIRE,DUREE,LIEU,CAPACITE,TARIF  FROM FORMATION WHERE ID_FORMATION = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.next()) {
            // Remplir les autres champs
            ui->lineEdit_Nom->setText(query.value(0).toString());
            ui->lineEdit_type->setCurrentText(query.value(1).toString());
            ui->lineEdit_h->setTime(QTime::fromString(query.value(2).toString(), "hh:mm"));
            ui->lineEdit_D->setText(query.value(3).toString());
            ui->lineEdit_lieu->setText(query.value(4).toString());;
            ui->lineEdit_Ca->setText(query.value(5).toString());
            ui->lineEdit_Ta->setText(query.value(6).toString());

        } else {
            QMessageBox::warning(this, "Avertissement", "Aucune formation trouvée avec cet ID !");
            ui->lineEditId->clear();
            ui->lineEdit_Nom->clear();
            ui->lineEdit_type->setCurrentIndex(0);
            ui->lineEdit_h->clear();
            ui->lineEdit_D->clear();
            ui->lineEdit_lieu->clear();
            ui->lineEdit_Ca->clear();
            ui->lineEdit_Ta->clear();
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la recherche : " + query.lastError().text());
    }
}



void formation::on_pushButtonTrier_clicked()
{
    ui->tableFormation->setModel(ftmp.trier_par_horaire());
}

