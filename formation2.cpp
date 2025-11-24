#include "formation2.h"
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QObject>
#include <QTableView>
#include <QSqlError>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QSqlRecord>
#include <QDebug>






//constructeur par defaut
formation2::formation2() {}
//constructeur paramétré
formation2::formation2(int id,QString nom,QString type,QString horaire,QDate dateformation,int duree,QString lieu,int capacite,int tarif,int id_formateur)
{
    this->id=id;
    this->nom=nom;
    this->type=type;
    this->horaire=horaire;
    this->dateformation=dateformation;
    this->duree=duree;
    this->lieu=lieu;
    this->capacite=capacite;
    this->tarif=tarif;
    this->id_formateur=id_formateur;
}
bool formation2::ajouter()
{
    QSqlQuery query;
    m_lastError.clear();
    QString res = QString::number(id);
    //prepare() prend la requete en parametre pour la preparer à l'execution
    query.prepare("INSERT INTO FORMATION(ID_FORMATION,NOM,TYPE_FORMATION,HORAIRE,DATEFORMATION,DUREE,LIEU,CAPACITE,TARIF,IDFORMATEUR)"
                  "VALUES (:id,:nom,:type,:horaire,:dateformation,:duree,:lieu,:capacite,:tarif,:id_formateur)");

    //creation des variables liées
    query.bindValue(":id" ,res);
    query.bindValue(":nom" ,nom);
    query.bindValue(":type" ,type);
    query.bindValue(":horaire" ,horaire);
    query.bindValue(":dateformation" ,dateformation);
    query.bindValue(":duree" ,duree);
    query.bindValue(":lieu" ,lieu);
    query.bindValue(":capacite" ,capacite);
    query.bindValue(":tarif" ,tarif);
    query.bindValue(":id_formateur" ,id_formateur);

    if(!query.exec()){
        m_lastError = query.lastError().text();
        qWarning() << "Erreur ajout formation:" << m_lastError;
        return false;
    }

    return true; //exec() envoie la requete poue l'executer


}
QSqlQueryModel * formation2::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model ->setQuery("SELECT ID_FORMATION, NOM, TYPE_FORMATION, HORAIRE, DATEFORMATION, DUREE, LIEU, CAPACITE, TARIF, IDFORMATEUR FROM FORMATION");

    model -> setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model -> setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model -> setHeaderData(2,Qt::Horizontal,QObject::tr("TYPE"));
    model -> setHeaderData(3,Qt::Horizontal,QObject::tr("HORAIRE"));
    model -> setHeaderData(4,Qt::Horizontal,QObject::tr("DATE"));
    model -> setHeaderData(5,Qt::Horizontal,QObject::tr("DUREE"));
    model -> setHeaderData(6,Qt::Horizontal,QObject::tr("LIEU"));
    model -> setHeaderData(7,Qt::Horizontal,QObject::tr("CAPACITE"));
    model -> setHeaderData(8,Qt::Horizontal,QObject::tr("TARIF"));
    model -> setHeaderData(9,Qt::Horizontal,QObject::tr("ID_FORMATEUR"));


    return model;
}
bool formation2::supprimer(int id)
{
    QSqlQuery query;
    m_lastError.clear();
    query.prepare("DELETE FROM formation WHERE ID_FORMATION = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur SQL :" << query.lastError().text();
        m_lastError = query.lastError().text();
        return false;
    }

    return true;
}
bool formation2::modifier(int id,QString nom,QString type,QString horaire,QDate dateformation,int duree,QString lieu,int capacite,int tarif,int id_formateur)
{
    QSqlQuery query;
    m_lastError.clear();
    query.prepare("UPDATE FORMATION SET NOM = :nom,TYPE_FORMATION = :type,HORAIRE = :horaire,DATEFORMATION = :dateformation,"
                  "DUREE = :duree,LIEU = :lieu,CAPACITE = :capacite,TARIF = :tarif,IDFORMATEUR = :id_formateur WHERE ID_FORMATION = :id");
    query.bindValue(":id" ,id);
    query.bindValue(":nom" ,nom);
    query.bindValue(":type" ,type);
    query.bindValue(":horaire" ,horaire);
    query.bindValue(":dateformation" ,dateformation);
    query.bindValue(":duree" ,duree);
    query.bindValue(":lieu" ,lieu);
    query.bindValue(":capacite" ,capacite);
    query.bindValue(":tarif" ,tarif);
    query.bindValue(":id_formateur" ,id_formateur);


    if(!query.exec()){
        m_lastError = query.lastError().text();
        qWarning() << "Erreur modification formation:" << m_lastError;
        return false;
    }
    return true;
}
//fonction trier selon horaire
QSqlQueryModel* formation2::trier_par_horaire()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT ID_FORMATION, NOM, TYPE_FORMATION, HORAIRE, DATEFORMATION, DUREE, LIEU, CAPACITE, TARIF, IDFORMATEUR FROM formation ORDER BY horaire ASC"); // tri croissant
    return model;
}
//FONCTION RECHERCHER SELON LE NOM//
QSqlQueryModel* formation2::rechercherParNom(const QString &nom)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    if (nom.isEmpty()) {
        // si le champ est vide → afficher tout
        model->setQuery("SELECT ID_FORMATION, NOM, TYPE_FORMATION, HORAIRE, DATEFORMATION, DUREE, LIEU, CAPACITE, TARIF, IDFORMATEUR FROM FORMATION");
    } else {
        QSqlQuery query;
        query.prepare("SELECT ID_FORMATION, NOM, TYPE_FORMATION, HORAIRE, DATEFORMATION, DUREE, LIEU, CAPACITE, TARIF, IDFORMATEUR FROM FORMATION WHERE NOM LIKE :nom");
        query.bindValue(":nom", "%" + nom + "%"); // recherche partielle
        query.exec();
        model->setQuery(query);
    }

    model -> setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model -> setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model -> setHeaderData(2,Qt::Horizontal,QObject::tr("TYPE"));
    model -> setHeaderData(3,Qt::Horizontal,QObject::tr("HORAIRE"));
    model -> setHeaderData(4,Qt::Horizontal,QObject::tr("DATE"));
    model -> setHeaderData(5,Qt::Horizontal,QObject::tr("DUREE"));
    model -> setHeaderData(6,Qt::Horizontal,QObject::tr("LIEU"));
    model -> setHeaderData(7,Qt::Horizontal,QObject::tr("CAPACITE"));
    model -> setHeaderData(8,Qt::Horizontal,QObject::tr("TARIF"));
    model -> setHeaderData(9,Qt::Horizontal,QObject::tr("ID_FORMATEUR"));
    // adapte selon les colonnes de ta table

    return model;
}
//FONCTION EXPORTER EN PDF
bool formation2::exporterDoc(QSqlQueryModel *model, QString cheminFichier)
{
    QFile file(cheminFichier);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(nullptr, "Erreur", "Impossible d'ouvrir le fichier !");
        return false;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);

    out << "<html><head><meta charset='UTF-8'>";

    //  Style compact pour Word
    out << "<style>"
           "table {"
           "   width: 70%;"
           "   margin: auto;"
           "   font-size: 10pt;"
           "   border-collapse: collapse;"
           "   table-layout: fixed;"
           "}"
           "th, td {"
           "   word-wrap: break-word;"
           "   padding: 5px;"
           "   text-align: center;"
           "}"
           "th { background-color: #f0f0f0; }"
           "</style>";

    out << "</head><body>";

    out << "<h2 style='text-align:center;'>Liste des formations</h2>";
    out << "<table border='1'>";

    // En-têtes
    out << "<tr>";
    for(int col = 0; col < model->columnCount(); col++)
    {
        out << "<th>"
            << model->headerData(col, Qt::Horizontal).toString()
            << "</th>";
    }
    out << "</tr>";

    // Lignes
    for(int row = 0; row < model->rowCount(); row++)
    {
        out << "<tr>";
        for(int col = 0; col < model->columnCount(); col++)
        {
            out << "<td>"
                << model->data(model->index(row, col)).toString()
                << "</td>";
        }
        out << "</tr>";
    }

    out << "</table></body></html>";

    file.close();
    return true;
}




//fonction rechercher selon le nom
//bool formation2 :: recherche(QString nom){
    //QSqlQuery query;
    //QString IdF = QString :: number(id);
    //query.prepare("SELECT * FROM FORMATEURS WHERE IDFORMATEUR = :id");
    //query.bindValue(":id",IdF);
    //if (query.exec()) {
       // if (query.next()) { // formateur trouvé
            //return true;
        //}
    //}
    //return false;
//}//
