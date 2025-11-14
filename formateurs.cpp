#include "formateurs.h"
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QFileDialog>
#include <QPdfWriter>
#include <QTableView>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QPainter>
#include <QString>
#include <QObject>
#include <QDate>
#include <QMap>



// Constructeur par défaut
Formateur :: Formateur(){

};

// Constructeur paramétré
Formateur :: Formateur(int id, const QString &nom, const QString &prenom,const QString &contact,const QString &sexe,
                      const QDate &date, const QString &specialite,float h, float s)
{
    IdFormateur = id;
    NomFormateur = nom;
    PrenomFormateur = prenom;
    SexeFormateur= sexe;
    ContactFormateur= contact;
    DateEmbauche= date;
    SpecialiteFormateur=specialite;
    HeuresPrevuesFormateur= h;
    SalaireFormateur=s;
};

// --- Getters ---
int Formateur :: getIdFormateur() const {return IdFormateur;}
QString Formateur :: getNomFormateur() const {return NomFormateur;}
QString Formateur :: getPrenomFormateur() const {return PrenomFormateur;}
QString Formateur :: getContactFormateur() const {return ContactFormateur;}
QString Formateur :: getSexeFormateur() const {return SexeFormateur;}
QDate Formateur :: getDateEmbauche() const {return DateEmbauche;}
QString Formateur :: getSpecialiteFormateur() const {return SpecialiteFormateur;}
float Formateur :: getHeuresPrevuesFormateur() const {return HeuresPrevuesFormateur;}
float Formateur :: getSalaireFormateur() const{return SalaireFormateur;}

// --- Setters ---
void Formateur :: setIdFormateur(int id){IdFormateur = id;}
void Formateur :: setNomFormateur(const QString &nom){NomFormateur=nom;}
void Formateur :: setPrenomFormateur(const QString &prenom){PrenomFormateur = prenom;}
void Formateur :: setContactFormateur(const QString &contact){ContactFormateur=contact;}
void Formateur :: setSexeFormateur(const QString &sexe){SexeFormateur= sexe;}
void Formateur :: setDateEmbauche(const QDate &date){DateEmbauche = date;}
void Formateur :: setSpecialiteFormateur(const QString &spec){SpecialiteFormateur = spec;}
void Formateur :: setHeuresPrevuesFormateur(float heures){HeuresPrevuesFormateur= heures;}
void Formateur :: setSalaireFormateur(float salaire){SalaireFormateur=salaire;}




bool Formateur :: ajouter()
{
    QSqlQuery query;
    QString IdF = QString ::number(IdFormateur);
    query.prepare("INSERT INTO FORMATEUR(IDFORMATEUR,NOM,PRENOM,CONTACT,SEXE,DATE_EMBAUCHE,SPECIALITE,NB_HEURES_PREVUES,SALAIRE)" "VALUES(:Id,:Nom,:Prenom,:Contact,:Sexe,TO_DATE(:Date, 'YYYY-MM-DD'),:Specialite,:h,:s)");
    query.bindValue(":Id",IdF);
    query.bindValue(":Nom",NomFormateur);
    query.bindValue(":Prenom",PrenomFormateur);
    query.bindValue(":Sexe",SexeFormateur);
    query.bindValue(":Contact",ContactFormateur);
    query.bindValue(":Date",DateEmbauche);
    query.bindValue(":Specialite",SpecialiteFormateur);
    query.bindValue(":h",HeuresPrevuesFormateur);
    query.bindValue(":s",SalaireFormateur);
    //return query.exec();
    if (!query.exec()) {
        qDebug() << "Erreur SQL:" << query.lastError().text();
        return false;
    }
    return true;
}


bool Formateur::modifier()
{
    QSqlQuery query;
    QString IdF = QString ::number(IdFormateur);
    query.prepare("UPDATE FORMATEUR SET "
                  "NOM= :Nom, "
                  "PRENOM= :Prenom, "
                  "CONTACT= :Contact, "
                  "SEXE= :Sexe, "
                  "DATE_EMBAUCHE= :Date, "
                  "SPECIALITE= :Specialite, "
                  "NB_HEURES_PREVUES= :HeuresPrevues, "
                  "SALAIRE= :Salaire "
                  "WHERE IDFORMATEUR = :Id");
    query.bindValue(":Id",IdF);
    query.bindValue(":Nom",NomFormateur);
    query.bindValue(":Prenom",PrenomFormateur);
    query.bindValue(":Contact",ContactFormateur);
    query.bindValue(":Sexe",SexeFormateur);
    query.bindValue(":Date",DateEmbauche);
    query.bindValue(":Specialite",SpecialiteFormateur);
    query.bindValue(":HeuresPrevues",HeuresPrevuesFormateur);
    query.bindValue(":Salaire",SalaireFormateur);

    return query.exec();
}


bool Formateur :: supprimer(int id)
{
    QSqlQuery query;
    QString IdF = QString :: number(id);
    query.prepare("DELETE FROM FORMATEUR WHERE IDFORMATEUR = :id;");
    query.bindValue(":id",IdF);
    return query.exec();
}


QSqlQueryModel * Formateur :: afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model ->setQuery("SELECT * FROM FORMATEUR");
    model -> setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model -> setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model -> setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
    model -> setHeaderData(4,Qt::Horizontal,QObject::tr("SEXE"));
    model -> setHeaderData(3,Qt::Horizontal,QObject::tr("CONTACT"));
    model -> setHeaderData(5,Qt::Horizontal,QObject::tr("DATE"));
    model -> setHeaderData(6,Qt::Horizontal,QObject::tr("SPECIALITE"));
    model -> setHeaderData(7,Qt::Horizontal,QObject::tr("HEURES_PREVUES"));
    model -> setHeaderData(8,Qt::Horizontal,QObject::tr("SALAIRE"));
    return model;
}


QSqlQueryModel* Formateur::Afficher_recherche(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM FORMATEUR WHERE IDFORMATEUR = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
        return nullptr;
    }
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(query);
    model -> setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model -> setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model -> setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
    model -> setHeaderData(4,Qt::Horizontal,QObject::tr("SEXE"));
    model -> setHeaderData(3,Qt::Horizontal,QObject::tr("CONTACT"));
    model -> setHeaderData(5,Qt::Horizontal,QObject::tr("DATE"));
    model -> setHeaderData(6,Qt::Horizontal,QObject::tr("SPECIALITE"));
    model -> setHeaderData(7,Qt::Horizontal,QObject::tr("HEURES_PREVUES"));
    model -> setHeaderData(8,Qt::Horizontal,QObject::tr("SALAIRE"));
    return model;
}


QMap<QString, int> Formateur::statistiquesSexe()
{
    QMap<QString, int> stats;
    stats["Homme"] = 0;
    stats["Femme"] = 0;

    QSqlQuery query("SELECT SEXE, COUNT(*) FROM FORMATEUR GROUP BY SEXE");
    while (query.next()) {
        QString sexe = query.value(0).toString().toLower();
        int count = query.value(1).toInt();
        if (sexe.contains("h"))  // correspond à homme, H, homme
            stats["Homme"] = count;
        else if (sexe.contains("f"))
            stats["Femme"] = count;

        qDebug() << "Résultat final:" << stats;
    }

    return stats;
}


QSqlQueryModel * Formateur::trierDateEmbauche()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM FORMATEUR ORDER BY DATE_EMBAUCHE ASC");

    // Optionnel : personnaliser les en-têtes de colonnes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Sexe"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Contact"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date d'embauche"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Spécialité"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Heures prévues"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Salaire"));
    return model;
}


bool Formateur :: recherche(int id)
{
    if (id<= 0) {
        QMessageBox::critical(nullptr, "Erreur", "Ajouter ID formateur rechercher !");
        return false;
    }
    QSqlQuery query;
    QString IdF = QString :: number(id);
    query.prepare("SELECT * FROM FORMATEUR WHERE IDFORMATEUR = :id");
    query.bindValue(":id",IdF);
    if (query.exec()) {
        if (query.next()) { // formateur trouvé
            this->NomFormateur = query.value("NOM").toString();
            this->PrenomFormateur = query.value("PRENOM").toString();
            this->SexeFormateur = query.value("SEXE").toString();
            this->ContactFormateur = query.value("CONTACT").toString();
            this->SpecialiteFormateur = query.value("SPECIALITE").toString();
            this->SalaireFormateur = query.value("SALAIRE").toFloat();
            this->DateEmbauche = query.value("DATE_EMBAUCHE").toDate(); //modif
            this->HeuresPrevuesFormateur = query.value("NB_HEURES_PREVUES").toFloat();
            return true;
        }
    }
    return false;
}


void Formateur::exporterPDF()
{
    // Choisir l’emplacement du fichier
    QString filePath = QFileDialog::getSaveFileName(
        nullptr,
        "Enregistrer le fichier PDF",
        "Liste_Formateurs.pdf",
        "Fichiers PDF (*.pdf)"
        );

    if (filePath.isEmpty()) {
        QMessageBox::information(nullptr, "Annulé", "Exportation annulée.");
        return;
    }
    QPdfWriter pdf("Liste_Formateurs.pdf");
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setPageMargins(QMarginsF(5, 20, 20, 20));

    QPainter painter(&pdf);
    int y = 100;

    painter.setFont(QFont("Times", 16));
    painter.drawText(200, y, "Liste des Formateurs");
    y += 200;

    painter.setFont(QFont("Times", 10));
    painter.drawLine(100, y,9200, y);
    y += 280;

    // En-têtes du tableau
    painter.drawText(10, y, "ID");
    painter.drawText(1000, y, "Nom");
    painter.drawText(2000, y, "Prénom");
    painter.drawText(3000, y, "Contact");
    painter.drawText(4000, y, "Sexe");
    painter.drawText(5000, y, "Spécialité");
    painter.drawText(6000, y, "Heures prévues");
    painter.drawText(7500, y, "Salaire");
    painter.drawText(8400, y, "Date Embauche");
    y += 80;
    painter.drawLine(100, y, 9200, y);
    y += 400;

    // Données
    QSqlQuery query;
    query.prepare("SELECT * FROM FORMATEUR");
    if (query.exec()) {
        while (query.next()) {
            painter.drawText(10, y, query.value("IDFORMATEUR").toString());
            painter.drawText(1000, y, query.value("NOM").toString());
            painter.drawText(2000, y, query.value("PRENOM").toString());
            painter.drawText(3000, y, query.value("CONTACT").toString());
            painter.drawText(4000, y, query.value("SEXE").toString());
            painter.drawText(5000, y, query.value("SPECIALITE").toString());
            painter.drawText(6000, y, query.value("NB_HEURES_PREVUES").toString());
            painter.drawText(7500, y, query.value("SALAIRE").toString());
            painter.drawText(8500, y, query.value("DATE_EMBAUCHE").toDate().toString("dd/MM/yyyy"));
            y += 500;
        }

        QMessageBox::information(nullptr, "PDF Exporté", "Le fichier PDF a été généré avec succès !");
    } else {
        QMessageBox::warning(nullptr, "Erreur", "Impossible de récupérer les données de la base !");
    }

    painter.end();
}
