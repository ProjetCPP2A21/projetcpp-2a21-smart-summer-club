#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTableView>
#include <QSqlError>
#include <QRegularExpression>
#include <QSqlRecord>
#include <QFileDialog>
#include <QDesktopServices>
#include <QStandardPaths>
#include <QFileInfo>
#include <QDir>
#include <QDate>
#include <QPrinter>
#include <QFocusEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , colorModel(new ColorSqlModel(this))
    , recherchePlaceholderActive(true)
{
    ui->setupUi(this);

    qDebug() << "=== DÉMARRAGE APPLICATION ===";
    qDebug() << "Couleurs activées: Vert(disponible), Rouge(en panne), Jaune(réservé)";

    // Afficher automatiquement les équipements au démarrage
    colorModel->setQuery("SELECT ID, NOM, PRIX, TYPE, ETAT, QUANTITE FROM EQUIPEMENT");
    ui->tableView_Equipement->setModel(colorModel);

    // Définir les en-têtes
    colorModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    colorModel->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    colorModel->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
    colorModel->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
    colorModel->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT"));
    colorModel->setHeaderData(5, Qt::Horizontal, QObject::tr("QUANTITE"));

    // Connecter les signaux pour la recherche améliorée
    connect(ui->RechercheEquipement, &QLineEdit::textChanged, this, &MainWindow::on_RechercheEquipement_textChanged);
    connect(ui->RechercheEquipement, &QLineEdit::selectionChanged, this, [this]() {
        if (recherchePlaceholderActive) {
            ui->RechercheEquipement->clear();
            recherchePlaceholderActive = false;
            ui->RechercheEquipement->setStyleSheet("background-color: rgb(255, 255, 255); border-radius:10px; border: 3px solid #ffffff; color: rgb(0, 0, 0);");
        }
    });

    // Connecter les signaux de focus
    connect(ui->RechercheEquipement, &QLineEdit::cursorPositionChanged, this, [this](int oldPos, int newPos) {
        Q_UNUSED(oldPos)
        Q_UNUSED(newPos)
        if (recherchePlaceholderActive) {
            ui->RechercheEquipement->clear();
            recherchePlaceholderActive = false;
            ui->RechercheEquipement->setStyleSheet("background-color: rgb(255, 255, 255); border-radius:10px; border: 3px solid #ffffff; color: rgb(0, 0, 0);");
        }
    });

    connect(ui->tableView_Equipement, &QTableView::clicked, this, &MainWindow::on_EquipementTable_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Fonction de recherche améliorée
void MainWindow::on_RechercheEquipement_textChanged(const QString &text)
{
    if (text.isEmpty() && !recherchePlaceholderActive) {
        // Si le champ est vide et que ce n'est pas le placeholder, afficher tous les équipements
        colorModel->setQuery("SELECT ID, NOM, PRIX, TYPE, ETAT, QUANTITE FROM EQUIPEMENT");
    } else if (!text.isEmpty() && !recherchePlaceholderActive) {
        // Rechercher l'équipement par ID seulement si ce n'est pas le placeholder
        QString recherche = text.trimmed();

        // Vérifier si c'est un nombre (recherche par ID)
        bool ok;
        recherche.toInt(&ok);

        if (ok) {
            // Recherche par ID
            QString queryStr = "SELECT ID, NOM, PRIX, TYPE, ETAT, QUANTITE FROM EQUIPEMENT WHERE ID = '" + recherche + "'";
            colorModel->setQuery(queryStr);

            if (colorModel->lastError().isValid()) {
                qDebug() << "Erreur de recherche:" << colorModel->lastError().text();
            }
        } else {
            // Recherche par nom (si vous voulez aussi rechercher par nom)
            QString queryStr = "SELECT ID, NOM, PRIX, TYPE, ETAT, QUANTITE FROM EQUIPEMENT WHERE NOM LIKE '%" + recherche + "%'";
            colorModel->setQuery(queryStr);
        }
    }
}

void MainWindow::on_ajouterEquipement_clicked()
{
    QString ID = ui->idEquipement->text().trimmed();
    QString NOM = ui->nomEquipement->text().trimmed();
    QString PRIX = ui->prixEquipement->text().trimmed();
    QString TYPE = ui->typeEquipement->text().trimmed();
    QString ETAT = ui->etatEquipement->currentText().trimmed();
    QString QUANTITE = ui->quantiteEquipement->text().trimmed();
    QDate DATE_ACHAT = ui->datEquipement->date(); // Récupérer la date du DateEdit

    // Contrôle de saisie - Champs vides
    if (ID.isEmpty() || NOM.isEmpty() || PRIX.isEmpty() ||
        TYPE.isEmpty() || ETAT.isEmpty() || QUANTITE.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants",
                             "Veuillez remplir tous les champs avant d'ajouter un équipement.");
        return;
    }

    // Vérifier que l'ID contient seulement des chiffres
    bool idOk;
    ID.toInt(&idOk);
    if (!idOk) {
        QMessageBox::warning(this, "Erreur de saisie",
                             "L'ID doit contenir uniquement des chiffres.");
        ui->idEquipement->setFocus();
        return;
    }

    // Vérifier si le prix et la quantité sont des nombres valides
    bool prixOk, quantiteOk;
    double prix = PRIX.toDouble(&prixOk);
    int quantite = QUANTITE.toInt(&quantiteOk);

    if (!prixOk || prix <= 0) {
        QMessageBox::warning(this, "Erreur de saisie",
                             "Veuillez entrer un prix valide (> 0).");
        ui->prixEquipement->setFocus();
        return;
    }

    if (!quantiteOk || quantite < 0) {
        QMessageBox::warning(this, "Erreur de saisie",
                             "Veuillez entrer une quantité valide (nombre entier ≥ 0).");
        ui->quantiteEquipement->setFocus();
        return;
    }

    // Vérifier que la date d'achat n'est pas dans le futur
    if (DATE_ACHAT > QDate::currentDate()) {
        QMessageBox::warning(this, "Erreur de date",
                             "La date d'achat ne peut pas être dans le futur.");
        ui->datEquipement->setFocus();
        return;
    }

    // Utiliser le constructeur avec date d'achat
    equipementC e(ID, NOM, PRIX, TYPE, ETAT, QUANTITE, DATE_ACHAT);
    bool test = e.ajouter_EQUIPEMENT();

    if (test) {
        QMessageBox::information(this, "Succès", "Ajout effectué avec succès");
        clearFieldsEquipement();
        // Actualiser le modèle coloré
        colorModel->setQuery("SELECT ID, NOM, PRIX, TYPE, ETAT, QUANTITE FROM EQUIPEMENT");
        // NE PAS réinitialiser le placeholder de recherche ici
    } else {
        QMessageBox::critical(this, "Échec", "Ajout non effectué (ID déjà existant ?)");
    }
}

void MainWindow::clearFieldsEquipement()
{
    ui->idEquipement->clear();
    ui->nomEquipement->clear();
    ui->prixEquipement->clear();
    ui->typeEquipement->clear();
    ui->etatEquipement->setCurrentIndex(0);
    ui->quantiteEquipement->clear();
    ui->datEquipement->setDate(QDate::currentDate()); // Réinitialiser à la date actuelle
}

void MainWindow::on_SupprimerEquipement_clicked()
{
    QModelIndex currentIndex = ui->tableView_Equipement->currentIndex();

    if (!currentIndex.isValid()) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"),
                             QObject::tr("Veuillez sélectionner une ligne à supprimer."), QMessageBox::Ok);
        return;
    }

    QString ID = ui->tableView_Equipement->model()->data(
                                                      ui->tableView_Equipement->model()->index(currentIndex.row(), 0)
                                                      ).toString();

    equipementC e;
    bool test = e.supprimer_EQUIPEMENT(ID);

    if (test) {
        QMessageBox::information(nullptr, QObject::tr("Succès"),
                                 QObject::tr("L'équipement a été supprimé avec succès."));
        // Actualiser le modèle coloré
        colorModel->setQuery("SELECT ID, NOM, PRIX, TYPE, ETAT, QUANTITE FROM EQUIPEMENT");
        // NE PAS réinitialiser le placeholder de recherche ici
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Échec de la suppression de l'équipement."));
    }
}

void MainWindow::on_ModifierEquipement_clicked()
{
    QString ID = ui->RechercheEquipement->text().trimmed();

    // Vérifier si c'est le placeholder ou vide
    if (ID.isEmpty() || recherchePlaceholderActive) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner ou entrer un ID valide.");
        return;
    }

    // Vérifier que l'ID de recherche contient seulement des chiffres
    bool idOk;
    ID.toInt(&idOk);
    if (!idOk) {
        QMessageBox::warning(this, "Erreur de saisie",
                             "L'ID doit contenir uniquement des chiffres.");
        ui->RechercheEquipement->setFocus();
        return;
    }

    QString NOM = ui->nomEquipement->text().trimmed();
    QString PRIX = ui->prixEquipement->text().trimmed();
    QString TYPE = ui->typeEquipement->text().trimmed();
    QString ETAT = ui->etatEquipement->currentText().trimmed();
    QString QUANTITE = ui->quantiteEquipement->text().trimmed();
    QDate DATE_ACHAT = ui->datEquipement->date();

    // Vérifier les champs
    if (NOM.isEmpty() || PRIX.isEmpty() || TYPE.isEmpty() ||
        ETAT.isEmpty() || QUANTITE.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants",
                             "Veuillez remplir tous les champs avant de modifier un équipement.");
        return;
    }

    bool prixOk, quantiteOk;
    double prix = PRIX.toDouble(&prixOk);
    int quantite = QUANTITE.toInt(&quantiteOk);

    if (!prixOk || prix <= 0) {
        QMessageBox::warning(this, "Erreur de saisie",
                             "Veuillez entrer un prix valide (> 0).");
        ui->prixEquipement->setFocus();
        return;
    }

    if (!quantiteOk || quantite < 0) {
        QMessageBox::warning(this, "Erreur de saisie",
                             "Veuillez entrer une quantité valide (nombre entier ≥ 0).");
        ui->quantiteEquipement->setFocus();
        return;
    }

    // Vérifier que la date d'achat n'est pas dans le futur
    if (DATE_ACHAT > QDate::currentDate()) {
        QMessageBox::warning(this, "Erreur de date",
                             "La date d'achat ne peut pas être dans le futur.");
        ui->datEquipement->setFocus();
        return;
    }

    equipementC e;
    e.setID(ID);
    e.setNom(NOM);
    e.setPrix(PRIX);
    e.setType(TYPE);
    e.setEtat(ETAT);
    e.setQuantite(QUANTITE);
    e.setDateAchat(DATE_ACHAT);
    e.setDureeVie(5); // Valeur par défaut

    if (e.modifier_EQUIPEMENT()) {
        QMessageBox::information(this, "Succès", "L'équipement a été modifié avec succès.");
        // Actualiser le modèle coloré
        colorModel->setQuery("SELECT ID, NOM, PRIX, TYPE, ETAT, QUANTITE FROM EQUIPEMENT");
        clearFieldsEquipement();
        // NE PAS réinitialiser le placeholder de recherche ici
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification (ID inexistant ?)");
    }
}

void MainWindow::on_EquipementTable_clicked(const QModelIndex &index)
{
    int row = index.row();

    QAbstractItemModel *model = ui->tableView_Equipement->model();
    if (!model)
        return;

    QString ID = model->index(row, 0).data().toString();
    QString NOM = model->index(row, 1).data().toString();
    QString PRIX = model->index(row, 2).data().toString();
    QString TYPE = model->index(row, 3).data().toString();
    QString ETAT = model->index(row, 4).data().toString();
    QString QUANTITE = model->index(row, 5).data().toString();

    // Charger les données complètes depuis la base de données pour avoir la date d'achat
    equipementC e_temp;
    QSqlQueryModel *fullModel = e_temp.fillEquipement(ID);

    QDate DATE_ACHAT = QDate::currentDate(); // Valeur par défaut
    if (fullModel && fullModel->rowCount() > 0) {
        QSqlRecord record = fullModel->record(0);
        DATE_ACHAT = record.value("DATE_ACHAT").toDate();
        delete fullModel;
    }

    ui->idEquipement->setText(ID);
    ui->nomEquipement->setText(NOM);
    ui->prixEquipement->setText(PRIX);
    ui->typeEquipement->setText(TYPE);
    ui->etatEquipement->setCurrentText(ETAT);
    ui->quantiteEquipement->setText(QUANTITE);
    ui->datEquipement->setDate(DATE_ACHAT);

    // Pour identifier rapidement l'équipement sélectionné
    ui->RechercheEquipement->setText(ID);
    recherchePlaceholderActive = false;
    ui->RechercheEquipement->setStyleSheet("background-color: rgb(255, 255, 255); border-radius:10px; border: 3px solid #ffffff; color: rgb(0, 0, 0);");
}

void MainWindow::on_pushButton_23_clicked()
{
    // TRI avec modèle coloré
    colorModel->setQuery("SELECT ID, NOM, PRIX, TYPE, ETAT, QUANTITE FROM EQUIPEMENT ORDER BY TYPE");
    // NE PAS réinitialiser le placeholder de recherche ici
}

void MainWindow::on_pushButton_stat_8_clicked()
{
    equipementC e;
    e.statistic_taux_utilisation(ui->tableView_Equipement);
}

// Ancienne fonction de recherche (maintenant remplacée par la recherche en temps réel)
void MainWindow::on_rechercherEquipement_clicked()
{
    QString id = ui->RechercheEquipement->text().trimmed();

    // Si c'est le placeholder, on ne fait rien
    if (id.isEmpty() || recherchePlaceholderActive) {
        return;
    }

    // La recherche se fait maintenant automatiquement via on_RechercheEquipement_textChanged
    // Cette fonction peut être utilisée pour forcer une recherche si nécessaire
    on_RechercheEquipement_textChanged(id);
}

void MainWindow::on_pushButton_stat_7_clicked()
{
    try {
        // Récupérer le nom du fichier
        QString filename = QFileDialog::getSaveFileName(this,
                                                        "Exporter en PDF",
                                                        QDir::homePath() + "/export_equipements_" + QDate::currentDate().toString("yyyyMMdd") + ".pdf",
                                                        "Fichiers PDF (*.pdf)");

        if (filename.isEmpty()) {
            return; // Annulation
        }

        // Vérifier l'extension .pdf
        if (!filename.endsWith(".pdf", Qt::CaseInsensitive)) {
            filename += ".pdf";
        }

        // Vérifier que le tableView existe et a des données
        if (!ui->tableView_Equipement || !ui->tableView_Equipement->model()) {
            QMessageBox::warning(this, "Erreur", "Aucune donnée à exporter !");
            return;
        }

        // Appeler la fonction d'export
        equipementC e;
        e.export_pdf(ui->tableView_Equipement, filename);

        QMessageBox::information(this, "Succès", "Export PDF réussi !\nFichier: " + filename);

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'export PDF: " + QString(e.what()));
    }
}

void MainWindow::on_ficheTechnique_clicked()
{
    // Vérifier qu'un équipement est sélectionné
    QModelIndex currentIndex = ui->tableView_Equipement->currentIndex();

    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Sélection requise",
                             "Veuillez sélectionner un équipement dans le tableau pour générer sa fiche technique.");
        return;
    }

    // Récupérer l'ID de l'équipement sélectionné
    QString ID = ui->tableView_Equipement->model()->data(
                                                      ui->tableView_Equipement->model()->index(currentIndex.row(), 0)).toString();

    // Charger les données de l'équipement
    equipementC e_temp;
    QSqlQueryModel *model = e_temp.fillEquipement(ID);

    if (!model || model->rowCount() == 0) {
        QMessageBox::critical(this, "Erreur", "Impossible de charger les données de l'équipement.");
        return;
    }

    // Créer l'objet equipementC avec toutes les données
    QSqlRecord record = model->record(0);
    equipementC e(
        record.value("ID").toString(),
        record.value("NOM").toString(),
        record.value("PRIX").toString(),
        record.value("TYPE").toString(),
        record.value("ETAT").toString(),
        record.value("QUANTITE").toString(),
        record.value("DATE_ACHAT").toDate(),
        record.value("DUREE_VIE").toInt()
        );

    // Générer la fiche technique
    QString fiche = e.genererFicheTechnique();

    // Créer une boîte de dialogue simple et efficace
    QDialog *ficheDialog = new QDialog(this);
    ficheDialog->setWindowTitle("📋 Fiche Technique - " + e.getNom());
    ficheDialog->resize(1000, 800);

    QVBoxLayout *mainLayout = new QVBoxLayout(ficheDialog);

    // Créer un QTextBrowser pour afficher le HTML
    QTextBrowser *textBrowser = new QTextBrowser();
    textBrowser->setHtml(fiche);
    textBrowser->setOpenExternalLinks(false);

    // Boutons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *btnSave = new QPushButton("💾 Sauvegarder PDF");
    QPushButton *btnClose = new QPushButton("✕ Fermer");

    buttonLayout->addWidget(btnSave);
    buttonLayout->addStretch(); // Espace flexible
    buttonLayout->addWidget(btnClose);

    mainLayout->addWidget(textBrowser);
    mainLayout->addLayout(buttonLayout);

    // Connexions des boutons - Version ultra-simplifiée
    connect(btnSave, &QPushButton::clicked, [this, &e, fiche]() {
        QString fileName = QFileDialog::getSaveFileName(
            this,
            "Sauvegarder la fiche technique",
            QDir::homePath() + "/Fiche_Technique_" + e.getNom() + "_" + QDate::currentDate().toString("yyyyMMdd") + ".pdf",
            "Fichiers PDF (*.pdf)"
            );

        if (!fileName.isEmpty()) {
            // Méthode simple et fiable pour PDF
            QPrinter printer;
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName(fileName);
            printer.setPageSize(QPageSize(QPageSize::A4));

            QTextDocument doc;
            doc.setHtml(fiche);
            doc.print(&printer);

            QMessageBox::information(this, "Succès",
                                     QString("Fiche technique sauvegardée !\n\n"
                                             "📍 Fichier: %1\n"
                                             "📄 Format: PDF\n"
                                             "💾 Taille: %2 Ko")
                                         .arg(fileName)
                                         .arg(QFileInfo(fileName).size() / 1024));
        }
    });

    connect(btnClose, &QPushButton::clicked, ficheDialog, &QDialog::accept);

    ficheDialog->exec();
    delete model;
}

// Gestion du focus pour le placeholder
void MainWindow::on_RechercheEquipement_focusIn()
{
    if (recherchePlaceholderActive) {
        ui->RechercheEquipement->clear();
        recherchePlaceholderActive = false;
        ui->RechercheEquipement->setStyleSheet("background-color: rgb(255, 255, 255); border-radius:10px; border: 3px solid #ffffff; color: rgb(0, 0, 0);");
    }
}

void MainWindow::on_RechercheEquipement_focusOut()
{
    if (ui->RechercheEquipement->text().isEmpty() && !recherchePlaceholderActive) {
        ui->RechercheEquipement->setText("    Rechercher un equipement");
        recherchePlaceholderActive = true;
        ui->RechercheEquipement->setStyleSheet("background-color: rgb(255, 255, 255); border-radius:10px; border: 3px solid #ffffff; color: rgb(162, 162, 162);");
    }
}
