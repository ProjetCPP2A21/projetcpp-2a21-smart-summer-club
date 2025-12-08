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
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , colorModel(new ColorSqlModel(this))
    , recherchePlaceholderActive(true)
    , arduino(new Arduino(this))
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

    // Connecter le signal textChanged pour verifmoteur
    connect(ui->verifmoteur, &QLineEdit::textChanged, this, &MainWindow::on_verifmoteur_textChanged);

    // Connecter le signal returnPressed pour verifmoteur (optionnel)
    connect(ui->verifmoteur, &QLineEdit::returnPressed, this, [this]() {
        QString id = ui->verifmoteur->text().trimmed();
        if (!id.isEmpty()) {
            // Envoyer la commande à Arduino
            arduino->verifierID(id);

            // Afficher un message de confirmation
            QMessageBox::information(this, "Commande envoyée",
                                     QString("Commande envoyée à Arduino:\nSTART %1").arg(id));
        }
    });

    // Connecter les signaux d'Arduino
    connect(arduino, &Arduino::etatChanged, this, &MainWindow::onArduinoEtatChanged);
    connect(arduino, &Arduino::messageInfo, this, &MainWindow::onArduinoMessageInfo);

    // Définir un placeholder pour verifmoteur
    ui->verifmoteur->setPlaceholderText("Entrez un ID et appuyez sur Entrée...");

    // Initialiser le label d'état Arduino
    ui->labelEtatArduino->setText("🔄 Recherche Arduino...");
    ui->labelEtatArduino->setStyleSheet("QLabel { "
                                        "color: #0c5460; "
                                        "font-weight: bold; "
                                        "padding: 10px; "
                                        "background-color: #d1ecf1; "
                                        "border: 2px solid #bee5eb; "
                                        "border-radius: 8px; "
                                        "}");

    // Style initial pour verifmoteur
    ui->verifmoteur->setStyleSheet("QLineEdit { "
                                   "background-color: white; "
                                   "border: 2px solid #cccccc; "
                                   "border-radius: 5px; "
                                   "padding: 8px; "
                                   "font-size: 14px; "
                                   "}");

    // Essayer de connecter Arduino après un délai
    QTimer::singleShot(1500, this, [this]() {
        qDebug() << "Tentative de connexion Arduino...";
        if (arduino->connecterArduino()) {
            ui->labelEtatArduino->setText("✅ Arduino connecté et prêt");
            ui->labelEtatArduino->setStyleSheet("QLabel { "
                                                "color: #155724; "
                                                "font-weight: bold; "
                                                "padding: 10px; "
                                                "background-color: #d4edda; "
                                                "border: 2px solid #c3e6cb; "
                                                "border-radius: 8px; "
                                                "}");

            // Tester la communication
            QTimer::singleShot(500, [this]() {
                // Simplement afficher un message de debug
                qDebug() << "Arduino connecté avec succès";
                qDebug() << "Prêt à recevoir des commandes START [ID]";
            });
        } else {
            ui->labelEtatArduino->setText("⚠️ Mode simulation - Arduino non détecté");
            ui->labelEtatArduino->setStyleSheet("QLabel { "
                                                "color: #856404; "
                                                "font-weight: bold; "
                                                "padding: 10px; "
                                                "background-color: #fff3cd; "
                                                "border: 2px solid #ffeaa7; "
                                                "border-radius: 8px; "
                                                "}");
        }
    });
}

MainWindow::~MainWindow()
{
    // Arrêter le moteur Arduino avant de quitter
    arduino->arreterMoteur();
    delete ui;
}

void MainWindow::on_verifmoteur_textChanged(const QString &text)
{
    // Si le champ est vide, réinitialiser l'état
    if (text.trimmed().isEmpty()) {
        ui->labelEtatArduino->setText("🔄 Entrez un ID pour vérifier...");
        ui->labelEtatArduino->setStyleSheet("QLabel { "
                                            "color: #0c5460; "
                                            "font-weight: bold; "
                                            "padding: 10px; "
                                            "background-color: #d1ecf1; "
                                            "border: 2px solid #bee5eb; "
                                            "border-radius: 8px; "
                                            "}");

        ui->verifmoteur->setStyleSheet("QLineEdit { "
                                       "background-color: white; "
                                       "border: 2px solid #cccccc; "
                                       "border-radius: 5px; "
                                       "padding: 8px; "
                                       "font-size: 14px; "
                                       "}");
        return;
    }

    // Si l'utilisateur tape, on peut afficher un message
    ui->labelEtatArduino->setText("🔍 Vérification en cours...");
    ui->labelEtatArduino->setStyleSheet("QLabel { "
                                        "color: #856404; "
                                        "font-weight: bold; "
                                        "padding: 10px; "
                                        "background-color: #fff3cd; "
                                        "border: 2px solid #ffeaa7; "
                                        "border-radius: 8px; "
                                        "}");

    // La vérification réelle se fait quand on appuie sur Entrée
    // ou via un timer pour vérification automatique
}

void MainWindow::onArduinoEtatChanged(bool moteurActif, const QString &message)
{
    // Mettre à jour l'interface avec l'état d'Arduino
    updateArduinoUI(moteurActif, message);
}

void MainWindow::onArduinoMessageInfo(const QString &message)
{
    qDebug() << "[ARDUINO MSG]" << message;

    // Vous pouvez ajouter un log des messages Arduino si vous voulez
    // Par exemple dans un QTextEdit dédié
}

void MainWindow::updateArduinoUI(bool moteurActif, const QString &message)
{
    // Mettre à jour le label avec le message
    ui->labelEtatArduino->setText(message);

    // Appliquer le style en fonction de l'état
    if (moteurActif) {
        // ID valide - Moteur tourne
        ui->labelEtatArduino->setStyleSheet("QLabel { "
                                            "color: #155724; "
                                            "font-weight: bold; "
                                            "padding: 10px; "
                                            "background-color: #d4edda; "
                                            "border: 2px solid #c3e6cb; "
                                            "border-radius: 8px; "
                                            "}");

        // Style pour le champ de texte
        ui->verifmoteur->setStyleSheet("QLineEdit { "
                                       "background-color: #d4edda; "
                                       "border: 2px solid #28a745; "
                                       "border-radius: 5px; "
                                       "padding: 8px; "
                                       "font-size: 14px; "
                                       "font-weight: bold; "
                                       "color: #155724; "
                                       "}");

        // Animation ou effet visuel (optionnel)
        QTimer::singleShot(3000, this, [this]() {
            if (arduino->moteurEnMarche()) {
                QMessageBox::information(this, "Rotation terminée",
                                         "✅ La rotation du moteur est terminée!\n"
                                         "Le moteur a effectué un tour complet de 360°.");
            }
        });

    } else if (message.contains("❌") || message.contains("ERREUR") || message.contains("invalide")) {
        // Erreur détectée
        ui->labelEtatArduino->setStyleSheet("QLabel { "
                                            "color: #721c24; "
                                            "font-weight: bold; "
                                            "padding: 10px; "
                                            "background-color: #f8d7da; "
                                            "border: 2px solid #f5c6cb; "
                                            "border-radius: 8px; "
                                            "}");

        ui->verifmoteur->setStyleSheet("QLineEdit { "
                                       "background-color: #f8d7da; "
                                       "border: 2px solid #dc3545; "
                                       "border-radius: 5px; "
                                       "padding: 8px; "
                                       "font-size: 14px; "
                                       "font-weight: bold; "
                                       "color: #721c24; "
                                       "}");

        // Bip sonore ou notification (simulé)
        QApplication::beep();

    } else if (message.contains("✅") || message.contains("SUCCES")) {
        // Succès (mais moteur pas nécessairement actif)
        ui->labelEtatArduino->setStyleSheet("QLabel { "
                                            "color: #155724; "
                                            "font-weight: bold; "
                                            "padding: 10px; "
                                            "background-color: #d4edda; "
                                            "border: 2px solid #c3e6cb; "
                                            "border-radius: 8px; "
                                            "}");

        ui->verifmoteur->setStyleSheet("QLineEdit { "
                                       "background-color: #d4edda; "
                                       "border: 2px solid #28a745; "
                                       "border-radius: 5px; "
                                       "padding: 8px; "
                                       "font-size: 14px; "
                                       "}");

    } else {
        // État neutre / informatif
        ui->labelEtatArduino->setStyleSheet("QLabel { "
                                            "color: #0c5460; "
                                            "font-weight: bold; "
                                            "padding: 10px; "
                                            "background-color: #d1ecf1; "
                                            "border: 2px solid #bee5eb; "
                                            "border-radius: 8px; "
                                            "}");

        ui->verifmoteur->setStyleSheet("QLineEdit { "
                                       "background-color: white; "
                                       "border: 2px solid #cccccc; "
                                       "border-radius: 5px; "
                                       "padding: 8px; "
                                       "font-size: 14px; "
                                       "}");
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
    QDate DATE_ACHAT = ui->datEquipement->date();

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
    ui->datEquipement->setDate(QDate::currentDate());
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
    e.setDureeVie(5);

    if (e.modifier_EQUIPEMENT()) {
        QMessageBox::information(this, "Succès", "L'équipement a été modifié avec succès.");
        // Actualiser le modèle coloré
        colorModel->setQuery("SELECT ID, NOM, PRIX, TYPE, ETAT, QUANTITE FROM EQUIPEMENT");
        clearFieldsEquipement();
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

    QDate DATE_ACHAT = QDate::currentDate();
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

    // SUPPRIMÉ: Ne pas copier automatiquement dans verifmoteur
    // ui->verifmoteur->setText(ID);  // Cette ligne a été supprimée

    // Option: Vérification automatique de l'ID sélectionné (désactivée)
    // QTimer::singleShot(500, [this, ID]() {
    //     if (!ID.isEmpty()) {
    //         arduino->verifierID(ID);
    //     }
    // });
}

void MainWindow::on_pushButton_23_clicked()
{
    // TRI avec modèle coloré
    colorModel->setQuery("SELECT ID, NOM, PRIX, TYPE, ETAT, QUANTITE FROM EQUIPEMENT ORDER BY TYPE");
}

void MainWindow::on_pushButton_stat_8_clicked()
{
    equipementC e;
    e.statistic_taux_utilisation(ui->tableView_Equipement);
}

void MainWindow::on_rechercherEquipement_clicked()
{
    QString id = ui->RechercheEquipement->text().trimmed();

    if (id.isEmpty() || recherchePlaceholderActive) {
        return;
    }

    on_RechercheEquipement_textChanged(id);
}

void MainWindow::on_pushButton_stat_7_clicked()
{
    try {
        QString filename = QFileDialog::getSaveFileName(this,
                                                        "Exporter en PDF",
                                                        QDir::homePath() + "/export_equipements_" + QDate::currentDate().toString("yyyyMMdd") + ".pdf",
                                                        "Fichiers PDF (*.pdf)");

        if (filename.isEmpty()) {
            return;
        }

        if (!filename.endsWith(".pdf", Qt::CaseInsensitive)) {
            filename += ".pdf";
        }

        if (!ui->tableView_Equipement || !ui->tableView_Equipement->model()) {
            QMessageBox::warning(this, "Erreur", "Aucune donnée à exporter !");
            return;
        }

        equipementC e;
        e.export_pdf(ui->tableView_Equipement, filename);

        QMessageBox::information(this, "Succès", "Export PDF réussi !\nFichier: " + filename);

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'export PDF: " + QString(e.what()));
    }
}

void MainWindow::on_ficheTechnique_clicked()
{
    QModelIndex currentIndex = ui->tableView_Equipement->currentIndex();

    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Sélection requise",
                             "Veuillez sélectionner un équipement dans le tableau pour générer sa fiche technique.");
        return;
    }

    QString ID = ui->tableView_Equipement->model()->data(
                                                      ui->tableView_Equipement->model()->index(currentIndex.row(), 0)).toString();

    equipementC e_temp;
    QSqlQueryModel *model = e_temp.fillEquipement(ID);

    if (!model || model->rowCount() == 0) {
        QMessageBox::critical(this, "Erreur", "Impossible de charger les données de l'équipement.");
        return;
    }

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

    QString fiche = e.genererFicheTechnique();

    QDialog *ficheDialog = new QDialog(this);
    ficheDialog->setWindowTitle("📋 Fiche Technique - " + e.getNom());
    ficheDialog->resize(1000, 800);

    QVBoxLayout *mainLayout = new QVBoxLayout(ficheDialog);

    QTextBrowser *textBrowser = new QTextBrowser();
    textBrowser->setHtml(fiche);
    textBrowser->setOpenExternalLinks(false);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *btnSave = new QPushButton("💾 Sauvegarder PDF");
    QPushButton *btnClose = new QPushButton("✕ Fermer");

    buttonLayout->addWidget(btnSave);
    buttonLayout->addStretch();
    buttonLayout->addWidget(btnClose);

    mainLayout->addWidget(textBrowser);
    mainLayout->addLayout(buttonLayout);

    connect(btnSave, &QPushButton::clicked, [this, &e, fiche]() {
        QString fileName = QFileDialog::getSaveFileName(
            this,
            "Sauvegarder la fiche technique",
            QDir::homePath() + "/Fiche_Technique_" + e.getNom() + "_" + QDate::currentDate().toString("yyyyMMdd") + ".pdf",
            "Fichiers PDF (*.pdf)"
            );

        if (!fileName.isEmpty()) {
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

void MainWindow::on_RechercheEquipement_textChanged(const QString &text)
{
    if (text.isEmpty() && !recherchePlaceholderActive) {
        colorModel->setQuery("SELECT ID, NOM, PRIX, TYPE, ETAT, QUANTITE FROM EQUIPEMENT");
    } else if (!text.isEmpty() && !recherchePlaceholderActive) {
        QString recherche = text.trimmed();

        bool ok;
        recherche.toInt(&ok);

        if (ok) {
            QString queryStr = "SELECT ID, NOM, PRIX, TYPE, ETAT, QUANTITE FROM EQUIPEMENT WHERE ID = '" + recherche + "'";
            colorModel->setQuery(queryStr);

            if (colorModel->lastError().isValid()) {
                qDebug() << "Erreur de recherche:" << colorModel->lastError().text();
            }
        } else {
            QString queryStr = "SELECT ID, NOM, PRIX, TYPE, ETAT, QUANTITE FROM EQUIPEMENT WHERE NOM LIKE '%" + recherche + "%'";
            colorModel->setQuery(queryStr);
        }
    }
}

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
