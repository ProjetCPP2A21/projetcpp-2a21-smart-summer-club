#include "formation.h"
#include "ui_formation.h"
#include <QTableView>
#include <formation2.h>
#include <QMessageBox>
#include <QSqlError>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <statistic.h>
#include "calendardialog.h"
#include <QProcessEnvironment>
#include <QDate>
#include <QTime>
#include <QDebug>






formation::formation(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::formation)
{
    ui->setupUi(this);

    // Connecte le signal quand l'utilisateur finit de saisir l'ID
    connect(ui->lineEditId, &QLineEdit::editingFinished,
            this, &formation::on_lineEditId_editingFinished);
    ui->tableFormation->setModel(ftmp.afficher());
    QIntValidator *validator = new QIntValidator(0, 999999, this);
    ui->lineEditId->setValidator(validator);
    ui->lineEdit_D->setValidator(validator);
    ui->lineEdit_Ta->setValidator(validator);
    ui->lineEdit_id2->setValidator(validator);
    ui->comboBox_Ca->setCurrentIndex(0);

    QString sgApiKey = qEnvironmentVariable("SENDGRID_API_KEY");
    QString sgFromEmail = qEnvironmentVariable("SENDGRID_FROM_EMAIL");
    QString sgFromName = qEnvironmentVariable("SENDGRID_FROM_NAME");
    QString recipientsEnv = qEnvironmentVariable("SENDGRID_TO_EMAILS");
    QStringList recipients;
    for (const QString &email : recipientsEnv.split(';', Qt::SkipEmptyParts))
        recipients << email.trimmed();
    qDebug() << "[SendGrid] API key set:" << !sgApiKey.isEmpty();
    qDebug() << "[SendGrid] From email:" << sgFromEmail;
    qDebug() << "[SendGrid] From name:" << sgFromName;
    qDebug() << "[SendGrid] Recipients:" << recipients;

    sendgridClient.configure(sgApiKey, sgFromEmail, sgFromName, recipients);
    if (!sendgridClient.isConfigured())
    {
        qWarning() << "[SendGrid] Client is not fully configured. Emails will not be sent.";
    }
    ui->dateEdit_date->setCalendarPopup(true);
    ui->dateEdit_date->setDate(QDate::currentDate());
    // Connexion Arduino
    int ret = A.connect_arduino();
    if(ret == 1)
        qDebug() << "Arduino connecté.";
    else
        qDebug() << "Erreur connexion Arduino.";

    // Dès que Arduino envoie un RFID → on_arduino_data()
    connect(A.getserial(), &QSerialPort::readyRead,
            this, &formation::on_arduino_data);
}

formation::~formation()
{
    delete ui;
    A.close_arduino();
}

void formation::on_pushButtonAjouter_clicked()
{
    // Validation des champs requis
    QString idText = ui->lineEditId->text().trimmed();
    QString nom=ui->lineEdit_Nom->text().trimmed();
    QString lieu=ui->lineEdit_lieu->text().trimmed();
    QString idFormateurText = ui->lineEdit_id2->text().trimmed();

    if (idText.isEmpty() || nom.isEmpty() || lieu.isEmpty() || idFormateurText.isEmpty())
    {
        QMessageBox::warning(this, tr("Champs manquants"),
                             tr("Merci de remplir les champs Id, Nom, Lieu et Id formateur."));
        return;
    }
    if (ui->comboBox_Ca->currentIndex() == -1)
    {
        QMessageBox::warning(this, tr("Capacité manquante"),
                             tr("Merci de sélectionner une capacité."));
        return;
    }

    int id=idText.toInt();
    QString type=ui->lineEdit_type->currentText();
    QString horaire = ui->lineEdit_h->time().toString("HH:mm");
    int duree=ui->lineEdit_D->text().toInt();
    int capacite=ui->comboBox_Ca->currentText().toInt();
    int tarif=ui->lineEdit_Ta->text().toInt();
    int id_formateur=idFormateurText.toInt();
    QDate dateformation = ui->dateEdit_date->date();

    //instancier un objet de la classe formation2 en utilisant les informations dans l'interface
    formation2 F (id, nom, type, horaire, dateformation, duree, lieu, capacite, tarif ,id_formateur);
    //inserer l'objet fprmation instancié dans la table formation et recuperer la valeur de reour de query.exec()
    bool test=F.ajouter();

    if(test) //si requete executé==> QmessageBox::information
    {
        //Refresh (Actualiser)
        ui->tableFormation->setModel(ftmp.afficher());

        QMessageBox::information(this, tr("Ajout"),
                                 tr("Ajout effectué avec succès."));
        if (sendgridClient.isConfigured())
        {
            qDebug() << "[SendGrid] Attempting to send email...";
            if (!sendgridClient.sendFormationCreatedEmail(nom, type, horaire, lieu, dateformation,
                                                          capacite, tarif, id_formateur, id))
            {
                QString err = sendgridClient.lastError();
                qWarning() << "Erreur envoi email SendGrid:" << err;
                QMessageBox::warning(this, tr("SendGrid"), err.isEmpty() ? tr("Échec d'envoi via SendGrid.") : err);
            }
            else
            {
                qDebug() << "[SendGrid] Email sent successfully.";
            }
        }
        else
        {
            qWarning() << "[SendGrid] Client not configured. Email skipped.";
        }
    }
    else //si requete non executé ==>QMessagebox::critical
    {
        QString err = F.lastError();
        QMessageBox::critical(this, tr("Ajout échoué"),
                              err.isEmpty() ? tr("Ajout non effectué.") : err);
        return;
    }
    clearInputs();
    ui->dateEdit_date->setDate(QDate::currentDate());



}



void formation::on_pushButtonsupprimer_clicked()
{
    QString idText = ui->lineEditId->text().trimmed();
    if (idText.isEmpty())
    {
        QMessageBox::warning(this, tr("Id manquant"), tr("Merci de saisir l'identifiant à supprimer."));
        return;
    }
    int id = idText.toInt();
    qDebug() << "ID à supprimer =" << id;

    bool test = ftmp.supprimer(id);

    if (test)
    {
        ui->tableFormation->setModel(ftmp.afficher());
        QMessageBox::information(nullptr, "OK", "Suppression effectuée ");
        ui->tableFormation->setModel(ftmp.afficher()); // Actualiser la table
    } else {
        QString err = ftmp.lastError();
        QMessageBox::critical(this, "Erreur", err.isEmpty() ? "Suppression non effectuée." : err);
    }
    clearInputs();
    ui->dateEdit_date->setDate(QDate::currentDate());
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

    QString idText = ui->lineEditId->text().trimmed();
    QString nom=ui->lineEdit_Nom->text().trimmed();
    QString lieu=ui->lineEdit_lieu->text().trimmed();
    QString idFormateurText = ui->lineEdit_id2->text().trimmed();

    if (idText.isEmpty())
    {
        QMessageBox::warning(this, tr("Id manquant"),
                             tr("Merci de saisir l'identifiant de la formation à modifier."));
        return;
    }
    if (nom.isEmpty() || lieu.isEmpty() || idFormateurText.isEmpty())
    {
        QMessageBox::warning(this, tr("Champs manquants"),
                             tr("Merci de remplir les champs Nom, Lieu et Id formateur."));
        return;
    }
    if (ui->comboBox_Ca->currentIndex() == -1)
    {
        QMessageBox::warning(this, tr("Capacité manquante"),
                             tr("Merci de sélectionner une capacité."));
        return;
    }

    int id=idText.toInt();
    QString type=ui->lineEdit_type->currentText();
    QString horaire = ui->lineEdit_h->time().toString("HH:mm");
    int duree=ui->lineEdit_D->text() .toInt();
    int capacite=ui->comboBox_Ca->currentText().toInt();
    int tarif=ui->lineEdit_Ta->text() .toInt();
    int id_formateur=idFormateurText.toInt();
    QDate dateformation = ui->dateEdit_date->date();


        bool test = ftmp.modifier(id,nom,type,horaire,dateformation,duree,lieu,capacite,tarif,id_formateur);

        if (test)
        {
            ui->tableFormation->setModel(ftmp.afficher());
            QMessageBox::information(nullptr, QObject::tr("Modification réussie"),
                                     QObject::tr("Les informations ont été modifiées avec succès.\n"), QMessageBox::Ok);
            ui->tableFormation->setModel(ftmp.afficher()); // 🔄 Actualiser le tableau
        }
        else
        {
            QString err = ftmp.lastError();
            QMessageBox::critical(this, QObject::tr("Erreur"),
                                  err.isEmpty() ? QObject::tr("La modification a échoué.\n")
                                                : err);
        }
        clearInputs();
        ui->dateEdit_date->setDate(QDate::currentDate());


}
void formation::on_lineEditId_editingFinished()
{
    QString id = ui->lineEditId->text().trimmed();

    if (id.isEmpty()) return;

    QSqlQuery query;
    query.prepare("SELECT NOM, TYPE_FORMATION,HORAIRE,DATEFORMATION,DUREE,LIEU,CAPACITE,TARIF,IDFORMATEUR  FROM FORMATION WHERE ID_FORMATION = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur SQL", query.lastError().text());
        return;
    }
    if (query.next()) {

            // Remplir les autres champs
        ui->lineEdit_Nom->setText(query.value(0).toString());
        ui->lineEdit_type->setCurrentText(query.value(1).toString());
        ui->lineEdit_h->setTime(QTime::fromString(query.value(2).toString(), "hh:mm"));
        ui->dateEdit_date->setDate(query.value(3).toDate());
        ui->lineEdit_D->setText(query.value(4).toString());
        ui->lineEdit_lieu->setText(query.value(5).toString());;
        ui->comboBox_Ca->setCurrentText(query.value(6).toString());
        ui->lineEdit_Ta->setText(query.value(7).toString());
        ui->lineEdit_id2->setText(query.value(8).toString());

    } else {

        }

}

void formation::clearInputs()
{
    ui->lineEditId->clear();
    ui->lineEdit_Nom->clear();
    ui->lineEdit_type->setCurrentIndex(0);
    ui->lineEdit_h->setTime(QTime(0,0));
    ui->lineEdit_D->clear();
    ui->lineEdit_lieu->clear();
    ui->comboBox_Ca->setCurrentIndex(0);
    ui->lineEdit_Ta->clear();
    ui->lineEdit_id2->clear();
    ui->dateEdit_date->setDate(QDate::currentDate());
}


//fontion trier
void formation::on_pushButtonTrier_clicked()
{
    ui->tableFormation->setModel(ftmp.trier_par_horaire());
}







//fonction rechercher
void formation::on_pushButton_rechercher_clicked()
{
    QString nom = ui->lineEdit_rechercher->text().trimmed(); // récupère le texte

    formation2 f;
    QSqlQueryModel *model = f.rechercherParNom(nom);
    ui->tableFormation->setModel(model);

    // Optionnel : message si rien n’est trouvé
    if (model->rowCount() == 0 && !nom.isEmpty()) {
        QMessageBox::information(this, "Résultat", "Aucune formation trouvée avec ce nom.");
    }

}
void formation::on_lineEdit_rechercher_textChanged(const QString &text)
{
    // Si on efface le texte → afficher tout
    if (text.isEmpty()) {
        formation2 f;
        QSqlQueryModel *model = f.afficher();
        ui->tableFormation->setModel(model);
    }
}
//fonction exporter

void formation::on_pushButton_exporter_clicked()
{
    QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->tableFormation->model());

    QString fichier = QFileDialog::getSaveFileName(
        this,
        "Exporter en Word",
        "Liste_Formations.doc",
        "Document Word (*.doc)");

    if(fichier.isEmpty()) return;

    formation2 f;
    if(f.exporterDoc(model, fichier))
        QMessageBox::information(this, "Succès", "Exportation réussie !");
}



void formation::on_pushButton_stat_clicked()
{
    Statistic S(this); // création de la dialog
    S.exec();
}

void formation::on_pushButton_47_clicked()
{
    CalendarDialog dialog(this);
    dialog.exec();
}
//ARDUINO
// Lecture des données série
void formation::on_arduino_data()
{
    QByteArray data = A.read_from_arduino();
    QString rfid = QString::fromUtf8(data).trimmed();

    if(rfid.length() > 0)
    {
        verifierCarte(rfid);
    }
}

// Vérification dans la base SQL
void formation::verifierCarte(QString rfid)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM formation WHERE num_rfid = :n");
    query.bindValue(":n", rfid);
    query.exec();
    query.next();

    if(query.value(0).toInt() > 0)
    {
        QMessageBox::information(this, "RFID", " Carte reconnue");
        A.write_to_arduino("O");  // ouvrir servo
    }
    else
    {
        QMessageBox::warning(this, "RFID", " Carte inconnue");
        A.write_to_arduino("F");  // fermer servo
    }
}
