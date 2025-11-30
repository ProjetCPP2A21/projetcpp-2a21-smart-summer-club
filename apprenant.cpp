#include "apprenant.h"
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QRegularExpression>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QtCharts>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QDialog>
#include <QVBoxLayout>
#include <QSqlRecord>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollBar>

// Constructeur modifié
apprenant::apprenant(QObject *parent) : QObject(parent)
{
    // Plus d'initialisation UI ici
}

apprenant::apprenant(int id_apprenant, QString nom, QString prenom, QDate date_naiss, QString email)
{
    this->id_apprenant = id_apprenant;
    this->nom = nom;
    this->prenom = prenom;
    this->date_naiss = date_naiss;
    this->email = email;
}

apprenant::~apprenant()
{
    // Plus de delete ui
}

bool apprenant::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(id_apprenant);
    query.prepare("INSERT INTO apprenant (id, nom, prenom, date_naiss, email) "
                  "VALUES (:id_apprenant, :nom, :prenom, :date_naiss, :email)");
    query.bindValue(":id_apprenant", res);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":date_naiss", date_naiss);
    query.bindValue(":email", email);

    if (!query.exec()) {
        qDebug() << "Add failed:" << query.lastError().text();
        return false;
    }
    return true;

}

QSqlQueryModel *apprenant::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT id_apprenant, nom, prenom, date_naiss, email FROM apprenant");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date_naiss"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));

    if (model->lastError().isValid()) {
        qDebug() << "Select failed:" << model->lastError().text();
    }
    return model;
}

bool apprenant::supprimer(int id_apprenant)
{
    QSqlQuery query;
    QString res = QString::number(id_apprenant);
    query.prepare("DELETE FROM apprenant WHERE id_apprenant = ?");
    query.addBindValue(res);

    if (!query.exec()) {
        qDebug() << "Delete failed:" << query.lastError().text();
        return false;
    }
    QSqlQuery req2;
    req2.prepare("DELETE FROM beneficier WHERE id_apprenant = ?");
    req2.addBindValue(id_apprenant);

    if (!req2.exec()) {
        qDebug() << "Delete failed (beneficier):" << req2.lastError().text();
        return false;
    }

    return true;
}

bool apprenant::ajouter_apprenant(int id_apprenant, const QString &nom, const QString &prenom, const QDate &date_naiss, const QString &email)
{
    QSqlQuery query;

    qDebug() << "=== DEBUG AJOUT ORACLE DATE ===";
    QString dateStr = date_naiss.toString("dd/MM/yyyy");
    qDebug() << "Using date format:" << dateStr;

    query.prepare("INSERT INTO apprenant (ID_APPRENANT, NOM, PRENOM, DATE_NAISS, EMAIL) "
                  "VALUES (:id, :nom, :prenom, TO_DATE(:date_naiss, 'DD/MM/YYYY'), :email)");

    query.bindValue(":id", id_apprenant);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":date_naiss", dateStr);
    query.bindValue(":email", email);

    if (query.exec()) {
        qDebug() << "SUCCESS: Added apprenant to apprenant table";
        return true;
    } else {
        qDebug() << "SQL ERROR:" << query.lastError().text();
        return false;
    }
}

bool apprenant::modifier(int id_apprenant, const QString &nom, const QString &prenom, const QDate &date_naiss, const QString &email)
{
    QSqlQuery query;
    QString dateStr = date_naiss.toString("dd/MM/yyyy");

    query.prepare("UPDATE apprenant SET NOM=:nom, PRENOM=:prenom, DATE_NAISS=TO_DATE(:date_naiss, 'DD/MM/YYYY'), EMAIL=:email WHERE ID_APPRENANT=:id");
    query.bindValue(":id", id_apprenant);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":date_naiss", dateStr);
    query.bindValue(":email", email);

    if (query.exec()) {
        qDebug() << "SUCCESS: Modified apprenant";
        return true;
    } else {
        qDebug() << "SQL ERROR:" << query.lastError().text();
        return false;
    }
}

QSqlQueryModel *apprenant::trier_par_date()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT ID_APPRENANT, NOM, PRENOM, DATE_NAISS, EMAIL FROM apprenant ORDER BY DATE_NAISS ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Naiss"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));

    return model;
}

void apprenant::exporter_vers_word()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Exporter vers Word", "liste_apprenants.doc", "Documents Word (*.doc)");

    if (fileName.isEmpty()) return;

    QSqlQueryModel *model = afficher();

    QString html;
    html += "<html><head><meta charset=\"UTF-8\"><title>Liste des Apprenants</title></head><body>";
    html += "<h1>Liste des Apprenants</h1>";
    html += "<table border='1' cellpadding='5' cellspacing='0' width='100%'>";

    // En-têtes du tableau
    html += "<tr style='background-color: #f0f0f0;'>";
    for (int col = 0; col < model->columnCount(); ++col) {
        html += "<th>" + model->headerData(col, Qt::Horizontal).toString() + "</th>";
    }
    html += "</tr>";

    // Données
    for (int row = 0; row < model->rowCount(); ++row) {
        html += "<tr>";
        for (int col = 0; col < model->columnCount(); ++col) {
            html += "<td>" + model->data(model->index(row, col)).toString() + "</td>";
        }
        html += "</tr>";
    }

    html += "</table>";
    html += "<p>Total: " + QString::number(model->rowCount()) + " apprenant</p>";
    html += "</body></html>";

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << html;
        file.close();
        QMessageBox::information(nullptr, "Succès", "Liste exportée vers:\n" + fileName);
    } else {
        QMessageBox::critical(nullptr, "Erreur", "Impossible de sauvegarder le fichier");
    }

    delete model;
}

void apprenant::statistiques_ages(QWidget *parent)
{
    // Calculer les tranches d'âge (max 17 ans)
    QSqlQuery query;
    query.exec("SELECT DATE_NAISS FROM apprenant");

    int tranches[4] = {0}; // 0: <15, 1:15, 2:16, 3:17

    QDate aujourdhui = QDate::currentDate();

    while (query.next()) {
        QDate date_naiss = query.value(0).toDate();
        int age = aujourdhui.year() - date_naiss.year();

        // Ajuster si l'anniversaire n'est pas encore passé cette année
        if (aujourdhui < QDate(aujourdhui.year(), date_naiss.month(), date_naiss.day())) {
            age--;
        }

        if (age < 15) tranches[0]++;
        else if (age == 15) tranches[1]++;
        else if (age == 16) tranches[2]++;
        else if (age == 17) tranches[3]++;
    }

    // Créer le graphique camembert
    QPieSeries *series = new QPieSeries();

    QStringList labels = {"Moins de 15 ans", "15 ans", "16 ans", "17 ans"};
    QList<QColor> colors = {
        QColor(255, 235, 235),  // #FFEBEB
        QColor(78, 205, 196),   // #4ECDC4
        QColor(69, 183, 209),   // #45B7D1
        QColor(150, 206, 180)   // #96CEB4
    };

    for (int i = 0; i < 4; i++) {
        if (tranches[i] > 0) {
            QPieSlice *slice = series->append(labels[i] + " (" + QString::number(tranches[i]) + ")", tranches[i]);
            slice->setColor(colors[i]);
            slice->setLabelVisible(true);
        }
    }

    // Créer et configurer le chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des apprenants par tranche d'âge");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Afficher dans une fenêtre - USE THE PARENT PARAMETER
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QDialog *dialog = new QDialog(parent);  // ✅ Use the parent parameter
    dialog->setWindowTitle("Statistiques des Âges");
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(chartView);
    dialog->resize(800, 600);
    dialog->exec();
}
// 🆕 IMPLÉMENTATION CHATBOT
void apprenant::creerInterfaceChatbot(QWidget *parent)
{
    // === BOUTON AFFICHER/MASQUER ===
    pushButton_TOGGLE_CHATBOT = new QPushButton("🤖 Ouvrir l'Assistant", parent);
    pushButton_TOGGLE_CHATBOT->setObjectName("pushButton_TOGGLE_CHATBOT");
    pushButton_TOGGLE_CHATBOT->setStyleSheet(
        "QPushButton { "
        "background-color: #9b59b6; "
        "color: white; "
        "padding: 8px 15px; "
        "border: none; "
        "border-radius: 5px; "
        "font-size: 10pt; "
        "margin: 5px; "
        "}"
        "QPushButton:hover { "
        "background-color: #8e44ad; "
        "}"
        );

    // 🆕 POSITION EN HAUT À GAUCHE
    pushButton_TOGGLE_CHATBOT->setGeometry(20, 20, 150, 35);

    // === FRAME CHATBOT (CACHÉ AU DÉBUT) ===
    frameChatbot = new QFrame(parent);
    frameChatbot->setObjectName("frameChatbot");
    frameChatbot->setStyleSheet(
        "QFrame { "
        "background-color: #f8f9fa; "
        "border: 2px solid #dee2e6; "
        "border-radius: 15px; "
        "padding: 15px; "
        "}"
        );
    // 🆕 POSITION SOUS LE BOUTON
    frameChatbot->setGeometry(20, 60, 380, 400);
    frameChatbot->hide();  // 🆕 CACHÉ AU DÉBUT

    // === LAYOUT VERTICAL ===
    QVBoxLayout *layoutChatbot = new QVBoxLayout(frameChatbot);
    layoutChatbot->setSpacing(10);

    // === TITRE ===
    QLabel *labelTitre = new QLabel("🤖 Assistant Apprenants", frameChatbot);
    labelTitre->setStyleSheet(
        "QLabel { "
        "font-size: 16pt; "
        "font-weight: bold; "
        "color: #2c3e50; "
        "margin-bottom: 5px; "
        "padding: 5px; "
        "}"
        );
    labelTitre->setAlignment(Qt::AlignCenter);
    layoutChatbot->addWidget(labelTitre);

    // === SÉPARATEUR ===
    QFrame *separateur = new QFrame(frameChatbot);
    separateur->setFrameShape(QFrame::HLine);
    separateur->setFrameShadow(QFrame::Sunken);
    separateur->setStyleSheet("background-color: #bdc3c7; margin: 5px 0px;");
    layoutChatbot->addWidget(separateur);

    // === ZONE DE CHAT (TEXTE EN NOIR) ===
    textEdit_chat = new QTextEdit(frameChatbot);
    textEdit_chat->setObjectName("textEdit_chat");
    textEdit_chat->setReadOnly(true);
    textEdit_chat->setStyleSheet(
        "QTextEdit { "
        "background-color: white; "
        "color: black; "  // 🎯 TEXTE EN NOIR GARANTI
        "border: 1px solid #ced4da; "
        "border-radius: 10px; "
        "padding: 10px; "
        "min-height: 200px; "
        "max-height: 250px; "
        "font-size: 10pt; "
        "}"
        );
    layoutChatbot->addWidget(textEdit_chat);

    // === ZONE DE SAISIE ===
    QHBoxLayout *layoutSaisie = new QHBoxLayout();

    lineEdit_question = new QLineEdit(frameChatbot);
    lineEdit_question->setObjectName("lineEdit_question");
    lineEdit_question->setPlaceholderText("Posez votre question...");
    lineEdit_question->setStyleSheet(
        "QLineEdit { "
        "padding: 10px; "
        "border: 2px solid #3498db; "
        "border-radius: 8px; "
        "font-size: 10pt; "
        "background-color: white; "
        "color: black; "  // 🎯 TEXTE EN NOIR
        "}"
        );
    layoutSaisie->addWidget(lineEdit_question);

    // === BOUTON ENVOYER ===
    pushButton_CHATBOT = new QPushButton("💬", frameChatbot);
    pushButton_CHATBOT->setObjectName("pushButton_CHATBOT");
    pushButton_CHATBOT->setStyleSheet(
        "QPushButton { "
        "background-color: #3498db; "
        "color: white; "
        "padding: 10px 15px; "
        "border: none; "
        "border-radius: 8px; "
        "font-size: 12pt; "
        "min-width: 50px; "
        "}"
        "QPushButton:hover { "
        "background-color: #2980b9; "
        "}"
        );
    layoutSaisie->addWidget(pushButton_CHATBOT);

    layoutChatbot->addLayout(layoutSaisie);

    // === CONNECTIONS ===
    connect(pushButton_CHATBOT, &QPushButton::clicked, this, &apprenant::on_pushButton_CHATBOT_clicked);
    connect(lineEdit_question, &QLineEdit::returnPressed, this, &apprenant::on_pushButton_CHATBOT_clicked);
    connect(pushButton_TOGGLE_CHATBOT, &QPushButton::clicked, this, &apprenant::on_pushButton_TOGGLE_CHATBOT_clicked);  // 🆕 CONNECTION

    // === MESSAGE DE BIENVENUE ===
    textEdit_chat->setTextColor(Qt::black);  // 🎯 FORCER LA COULEUR NOIRE
    textEdit_chat->append("🤖 Assistant: Bonjour ! Je suis votre assistant.");
    textEdit_chat->append("Je peux vous aider avec:");
    textEdit_chat->append("• Le nombre d'apprenants");
    textEdit_chat->append("• Les services disponibles");
    textEdit_chat->append("• Les apprenants récents");
    textEdit_chat->append("");
}

// 🆕 NOUVELLE FONCTION POUR AFFICHER/MASQUER
void apprenant::on_pushButton_TOGGLE_CHATBOT_clicked()
{
    if(frameChatbot->isVisible()) {
        frameChatbot->hide();
        pushButton_TOGGLE_CHATBOT->setText("🤖 Ouvrir l'Assistant");
    } else {
        frameChatbot->show();
        pushButton_TOGGLE_CHATBOT->setText("❌ Fermer l'Assistant");
        lineEdit_question->setFocus(); // Focus sur le champ de saisie
    }
}

// MODIFIE AUSSI on_pushButton_CHATBOT_clicked() POUR LA COULEUR:
void apprenant::on_pushButton_CHATBOT_clicked()
{
    QString question = lineEdit_question->text().trimmed();

    if(question.isEmpty()) {
        return;
    }

    // 🎯 FORCER LES COULEURS
    textEdit_chat->setTextColor(QColor(44, 62, 80)); // Bleu foncé pour l'utilisateur
    textEdit_chat->append("👤 Vous: " + question);

    QString reponse = traiterQuestionChatbot(question);

    textEdit_chat->setTextColor(QColor(231, 76, 60)); // Rouge pour l'assistant
    textEdit_chat->append("🤖 Assistant: " + reponse);

    textEdit_chat->setTextColor(Qt::black); // Retour au noir
    textEdit_chat->append("");

    // Scroll vers le bas
    QScrollBar *scrollbar = textEdit_chat->verticalScrollBar();
    scrollbar->setValue(scrollbar->maximum());

    lineEdit_question->clear();
}

QString apprenant::traiterQuestionChatbot(const QString &question)
{
    QString questionLower = question.toLower();

    // === DESCRIPTION COMPLÈTE DE L'INTERFACE ===
    if(questionLower.contains("interface") || questionLower.contains("écran") ||
        questionLower.contains("fenêtre") || questionLower.contains("description") ||
        questionLower.contains("décrire") || questionLower.contains("expliquer") ||
        questionLower.contains("quoi faire") || questionLower.contains("comment utiliser")) {
        return "🎯 **DESCRIPTION COMPLÈTE DE L'INTERFACE GESTION DES APPRENANTS**\n\n"
               "**📋 PANEL GAUCHE - Ajout d'apprenants :**\n"
               "• 🆔 **ID** : Numéro unique (chiffres seulement)\n"
               "• 👤 **Nom & Prénom** : Lettres et espaces seulement\n"
               "• 🎂 **Date de naissance** : Maximum 17 ans\n"
               "• 📧 **Email** : Format valide requis\n"
               "• ➕ **Ajouter** : Enregistre le nouvel apprenant\n"
               "• 🗑️ **Annuler** : Vide tous les champs\n\n"

               "**🔧 PANEL DROITE - Gestion avancée :**\n"
               "• 🔍 **Recherche** : Trouve un apprenant par ID\n"
               "• ✏️ **Modifier** : Met à jour les infos\n"
               "• 🗑️ **Supprimer** : Supprime avec l'icône poubelle\n"
               "• 📊 **Statistiques** : Graphique par tranche d'âge\n"
               "• 📥 **Télécharger** : Export Word de la liste\n"
               "• 🔄 **Trier** : Par date de naissance\n\n"

               "**📊 TABLEAU PRINCIPAL :**\n"
               "Affiche tous les apprenants avec : ID, Nom, Prénom, Date de naissance, Email\n\n"
               "**💡 ASTUCES :**\n"
               "- La recherche se fait automatiquement quand vous tapez un ID\n"
               "- L'âge est limité à 17 ans maximum\n"
               "- Les emails doivent être valides\n"
               "- Utilisez 'Annuler' pour recommencer";
    }

    // === FONCTIONNALITÉS SPÉCIFIQUES ===
    if(questionLower.contains("ajouter") || questionLower.contains("nouvel apprenant")) {
        return "**📝 POUR AJOUTER UN APPRENANT :**\n\n"
               "1. **Remplir le formulaire gauche**\n"
               "2. **ID** : 8 chiffres maximum\n"
               "3. **Nom/Prénom** : Lettres seulement\n"
               "4. **Date naissance** : Maximum 17 ans\n"
               "5. **Email** : Format valide requis\n"
               "✅ **Validation automatique** sur tous les champs !";
    }

    if(questionLower.contains("modifier") || questionLower.contains("changer")) {
        return "**✏️ POUR MODIFIER UN APPRENANT :**\n\n"
               "1. **Rechercher** l'apprenant par ID\n"
               "2. **Modifier** les champs dans le formulaire\n"
               "3. **Cliquer sur 'Modifier'**\n\n"
               "💡 Les mêmes validations s'appliquent !";
    }

    if(questionLower.contains("supprimer") || questionLower.contains("effacer")) {
        return "**🗑️ POUR SUPPRIMER UN APPRENANT :**\n\n"
               "1. **Entrer l'ID** dans la recherche\n"
               "2. **Cliquer sur l'icône poubelle** 🗑️\n\n"
               "⚠️ **Attention :** Action irréversible !";
    }

    if(questionLower.contains("rechercher") || questionLower.contains("trouver")) {
        return "**🔍 POUR RECHERCHER UN APPRENANT :**\n\n"
               "• **Taper l'ID** dans le champ recherche\n"
               "• **Recherche automatique** immédiate\n"
               "• **Résultat** dans le tableau\n\n"
               "💡 La recherche se vide pour tout réafficher";
    }

    if(questionLower.contains("statistique") || questionLower.contains("graphique")) {
        return "**📊 STATISTIQUES DISPONIBLES :**\n\n"
               "• **Répartition par âge** : Camembert interactif\n"
               "• **Tranches** : <15 ans, 15 ans, 16 ans, 17 ans\n"
               "• **Couleurs** différenciées pour chaque tranche\n\n"
               "📈 **Cliquez sur 'Statistiques'** pour visualiser !";
    }

    if(questionLower.contains("exporter") || questionLower.contains("word") || questionLower.contains("télécharger")) {
        return "**📥 EXPORTER EN WORD :**\n\n"
               "1. **Cliquer sur l'icône télécharger** 📥\n"
               "2. **Choisir l'emplacement** du fichier\n"
               "3. **Nommer** le fichier .doc\n"
               "4. **Sauvegarder** avec mise en forme automatique\n\n"
               "📋 **Contient** : En-têtes, tableau complet, totaux";
    }

    if(questionLower.contains("trier") || questionLower.contains("ordre")) {
        return "**🔄 TRI DISPONIBLE :**\n\n"
               "• **Par date de naissance** : Du plus âgé au plus jeune\n"
               "• **Cliquez sur 'Trier'** avec l'icône 📊\n\n"
               "👴→👶 Affichage par ordre d'âge croissant";
    }

    if(questionLower.contains("validation") || questionLower.contains("règle")) {
        return "**✅ RÈGLES DE VALIDATION :**\n\n"
               "• **ID** : Chiffres seulement (0-99999999)\n"
               "• **Nom/Prénom** : Lettres et espaces seulement\n"
               "• **Âge** : Maximum 17 ans\n"
               "• **Email** : Format valide requis\n"
               "🚫 **Messages d'erreur** guides en cas de problème";
    }

    // === SALUTATIONS AVEC CONTEXTE ===
    if(questionLower.contains("bonjour") || questionLower.contains("salut") ||
        questionLower.contains("coucou") || questionLower.contains("hello")) {
        return "👋 **Bonjour ! Je suis votre assistant SmartSummer Club !**\n\n"
               "Je peux vous aider avec :\n"
               "• 📝 **Ajouter/modifier/supprimer** des apprenants\n"
               "• 🔍 **Rechercher** et **trier** les données\n"
               "• 📊 **Statistiques** et **rapports**\n"
               "• 📥 **Exporter** les listes\n"
               "• 🎯 **Expliquer** toutes les fonctionnalités\n\n"
               "Dites-moi ce que vous voulez faire ! 😊";
    }

    // === RESTE DU CODE EXISTANT ===
    if(questionLower.contains("combien") && questionLower.contains("apprenant")) {
        return getNombreApprenants() + "\n\n💡 **Astuce** : Utilisez 'Statistiques' pour voir la répartition par âge !";
    }

    if(questionLower.contains("service") && questionLower.contains("disponible")) {
        return getServicesDisponibles();
    }

    if(questionLower.contains("réserver") || questionLower.contains("reserver") ||
        questionLower.contains("réservation") || questionLower.contains("reservation")) {
        return "Pour réserver un service :\n"
               "1. Allez dans l'onglet 'Services'\n"
               "2. Choisissez le service souhaité\n"
               "3. Cliquez sur 'Réserver'\n"
               "4. Sélectionnez la date et l'horaire";
    }

    if(questionLower.contains("récent") || questionLower.contains("recent") ||
        questionLower.contains("dernier") || questionLower.contains("nouveau")) {
        return getApprenantsRecents();
    }

    if(questionLower.contains("aide") || questionLower.contains("help") ||
        questionLower.contains("que peux-tu") || questionLower.contains("tu fais quoi")) {
        return "Je peux vous aider avec :\n"
               "• Le nombre total d'apprenants\n"
               "• Les services disponibles\n"
               "• Les apprenants récents\n"
               "• Comment réserver un service\n"
               "• Les procédures générales";
    }

    if(questionLower.contains("merci") || questionLower.contains("thanks")) {
        return "De rien ! N'hésitez pas si vous avez d'autres questions 😊";
    }

    // === QUESTION INCONNUE AMÉLIORÉE ===
    return "🤔 Je n'ai pas compris votre question sur la gestion des apprenants.\n\n"
           "**Voici ce que je peux expliquer :**\n"
           "• \"Description interface\" → Vue complète\n"
           "• \"Comment ajouter\" → Procédure détaillée\n"
           "• \"Comment modifier/supprimer\" → Guides pas-à-pas\n"
           "• \"Statistiques\" → Graphiques disponibles\n"
           "• \"Exporter\" → Export Word\n"
           "• \"Règles validation\" → Critères de saisie\n\n"
           "📞 **Je suis là pour vous guider dans toute l'interface !**";
}

QString apprenant::getNombreApprenants()
{
    QSqlQuery query;

    // 🆕 ESSAIE DIFFÉRENTS NOMS DE TABLE
    QStringList tables = {"apprenants", "APPRENANTS", "apprenant", "APPRENANT", "etudiants", "ETUDIANTS"};

    for(const QString &table : tables) {
        if(query.exec("SELECT COUNT(*) FROM " + table)) {
            if(query.next()) {
                int count = query.value(0).toInt();
                return "Il y a actuellement **" + QString::number(count) + "** apprenants dans la base de données.";
            }
        }
    }

    return "❌ Je n'ai pas pu trouver la table des apprenants.";
}

QString apprenant::getServicesDisponibles()
{
    QSqlQuery query;

    // 🆕 ESSAIE DIFFÉRENTS NOMS DE TABLE SERVICE
    QStringList tables = {"services", "SERVICES", "service", "SERVICE", "formations", "FORMATIONS"};

    for(const QString &table : tables) {
        QString requete = "SELECT ";

        // 🆕 ESSAIE DIFFÉRENTS NOMS DE COLONNES
        if(query.exec("SELECT NOM, TYPE, DESCRIPTION FROM " + table + " LIMIT 1")) {
            // Table trouvée avec ces colonnes
            if(query.exec("SELECT NOM, TYPE FROM " + table + " WHERE STATUT='Disponible' OR DISPONIBLE=1")) {
                return construireReponseServices(query);
            }
        }

        // 🆕 ESSAIE AUTRE COMBINAISON DE COLONNES
        if(query.exec("SELECT NOM_SERVICE, TYPE_SERVICE FROM " + table + " LIMIT 1")) {
            if(query.exec("SELECT NOM_SERVICE, TYPE_SERVICE FROM " + table + " WHERE STATUT='Disponible'")) {
                return construireReponseServices(query);
            }
        }
    }

    return "ℹ️ La gestion des services n'est pas encore disponible dans cette version.";
}

QString apprenant::construireReponseServices(QSqlQuery &query)
{
    QString reponse = "📋 **Services disponibles :**\n\n";
    int count = 0;

    while(query.next()) {
        count++;
        QString nom = query.value(0).toString();
        QString type = query.value(1).toString();

        reponse += "• **" + nom + "** - " + type + "\n";
    }

    if(count == 0) {
        return "Aucun service disponible pour le moment.";
    }

    reponse += "\n*Total : " + QString::number(count) + " services*";
    return reponse;
}

QString apprenant::getApprenantsRecents()
{
    // 🆕 VERSION ULTRA SIMPLE
    int total = 0;
    QSqlQuery countQuery;
    if(countQuery.exec("SELECT COUNT(*) FROM apprenant")) {
        if(countQuery.next()) {
            total = countQuery.value(0).toInt();
        }
    }

    return "👥 **Derniers apprenants :**\n\n"
           "• Voir la liste complète avec 'Afficher'\n"
           "• **Total : " + QString::number(total) + " apprenants**\n"
                                      "• Utilisez la recherche par ID pour trouver un apprenant spécifique";
}

QString apprenant::construireReponseApprenants(QSqlQuery &query, const QString &format)
{
    QString reponse = "👥 **Derniers apprenants inscrits :**\n\n";
    int count = 0;

    while(query.next()) {
        count++;
        QString affichage;

        if(format == "PRENOM, NOM") {
            affichage = query.value(0).toString() + " " + query.value(1).toString();
        }
        else if(format == "NOM, PRENOM") {
            affichage = query.value(1).toString() + " " + query.value(0).toString();
        }
        else {
            affichage = query.value(0).toString();
        }

        reponse += "• **" + affichage + "**\n";
    }

    if(count == 0) {
        return "Aucun apprenant trouvé dans la base de données.";
    }

    return reponse;
}

// 🆕 FONCTION DE DEBUG
void apprenant::debugTables()
{
    qDebug() << "=== DEBUG TABLES DISPONIBLES ===";
    QStringList tables = QSqlDatabase::database().tables();
    for(const QString &table : tables) {
        qDebug() << "Table:" << table;

        QSqlQuery query;
        if(query.exec("SELECT * FROM " + table + " LIMIT 1")) {
            QSqlRecord record = query.record();
            for(int i = 0; i < record.count(); i++) {
                qDebug() << "  - Colonne:" << record.fieldName(i);
            }
        }
    }
}

// ==============================================
// 🆕 FONCTIONS GROUPES
// ==============================================

void apprenant::creerInterfaceGroupes(QWidget *parent)
{
    // === BOUTON POUR AFFICHER/MASQUER LES GROUPES ===
    pushButton_TOGGLE_GROUPES = new QPushButton("🎯 Groupes", parent);
    pushButton_TOGGLE_GROUPES->setObjectName("pushButton_TOGGLE_GROUPES");
    pushButton_TOGGLE_GROUPES->setStyleSheet(
        "QPushButton { "
        "background-color: #9b59b6; "
        "color: white; "
        "padding: 8px 15px; "
        "border: none; "
        "border-radius: 5px; "
        "font-size: 10pt; "
        "font-weight: bold; "
        "}"
        "QPushButton:hover { "
        "background-color: #8e44ad; "
        "}"
        );
    // 🆕 POSITION EN HAUT À DROITE (à côté du chatbot)
    pushButton_TOGGLE_GROUPES->setGeometry(180, 20, 120, 35);

    // === FRAME GROUPES (CACHÉ AU DÉBUT) ===
    frameGroupes = new QFrame(parent);
    frameGroupes->setObjectName("frameGroupes");
    frameGroupes->setStyleSheet(
        "QFrame { "
        "background-color: #2c3e50; "
        "border: 2px solid #34495e; "
        "border-radius: 15px; "
        "padding: 15px; "
        "}"
        "QLabel { "
        "color: white; "
        "font-size: 10pt; "
        "}"
        "QSpinBox, QComboBox, QPushButton { "
        "padding: 8px; "
        "border-radius: 5px; "
        "font-size: 9pt; "
        "}"
        );
    // 🆕 POSITION SOUS LE BOUTON GROUPES
    frameGroupes->setGeometry(180, 60, 300, 500);
    frameGroupes->hide();  // CACHÉ AU DÉBUT !

    QVBoxLayout *layoutGroupes = new QVBoxLayout(frameGroupes);
    layoutGroupes->setSpacing(10);  // 🆕 ESPACEMENT

    // === TITRE ===
    QLabel *labelTitre = new QLabel("🎯 GROUPES ÉQUILIBRÉS", frameGroupes);
    labelTitre->setStyleSheet("font-size: 12pt; font-weight: bold; color: #3498db; margin-bottom: 5px;");
    labelTitre->setAlignment(Qt::AlignCenter);
    layoutGroupes->addWidget(labelTitre);

    // === SÉPARATEUR ===
    QFrame *separateur = new QFrame(frameGroupes);
    separateur->setFrameShape(QFrame::HLine);
    separateur->setFrameShadow(QFrame::Sunken);
    separateur->setStyleSheet("background-color: #3498db; margin: 5px 0px;");
    layoutGroupes->addWidget(separateur);

    // === NOMBRE DE GROUPES ===
    QHBoxLayout *layoutNbGroupes = new QHBoxLayout();
    QLabel *labelNbGroupes = new QLabel("Nb groupes:", frameGroupes);
    labelNbGroupes->setStyleSheet("color: white;");
    spinBox_NB_GROUPES = new QSpinBox(frameGroupes);
    spinBox_NB_GROUPES->setRange(2, 10);
    spinBox_NB_GROUPES->setValue(4);
    spinBox_NB_GROUPES->setStyleSheet("background-color: white; color: black;");
    spinBox_NB_GROUPES->setFixedWidth(60);

    layoutNbGroupes->addWidget(labelNbGroupes);
    layoutNbGroupes->addWidget(spinBox_NB_GROUPES);
    layoutNbGroupes->addStretch();
    layoutGroupes->addLayout(layoutNbGroupes);

    // === BOUTON CRÉER GROUPES ===
    pushButton_CREER_GROUPES = new QPushButton("🔄 Créer les Groupes", frameGroupes);
    pushButton_CREER_GROUPES->setStyleSheet(
        "QPushButton { "
        "background-color: #27ae60; "
        "color: white; "
        "padding: 10px 5px; "
        "border: none; "
        "border-radius: 5px; "
        "font-size: 10pt; "
        "}"
        "QPushButton:hover { "
        "background-color: #219653; "
        "}"
        );
    pushButton_CREER_GROUPES->setFixedHeight(35);
    layoutGroupes->addWidget(pushButton_CREER_GROUPES);

    // === COMBO BOX GROUPES ===
    QLabel *labelSelectGroupe = new QLabel("Sélectionner un groupe:", frameGroupes);
    labelSelectGroupe->setStyleSheet("color: white; margin-top: 10px;");
    layoutGroupes->addWidget(labelSelectGroupe);

    comboBox_GROUPES = new QComboBox(frameGroupes);
    comboBox_GROUPES->setStyleSheet("background-color: white; color: black;");
    comboBox_GROUPES->setPlaceholderText("Choisir un groupe...");
    comboBox_GROUPES->setFixedHeight(30);
    layoutGroupes->addWidget(comboBox_GROUPES);

    // === BOUTON AFFICHER GROUPE ===
    pushButton_AFFICHER_GROUPE = new QPushButton("👥 Afficher ce Groupe", frameGroupes);
    pushButton_AFFICHER_GROUPE->setStyleSheet(
        "QPushButton { "
        "background-color: #3498db; "
        "color: white; "
        "padding: 10px 5px; "
        "border: none; "
        "border-radius: 5px; "
        "font-size: 10pt; "
        "}"
        "QPushButton:hover { "
        "background-color: #2980b9; "
        "}"
        );
    pushButton_AFFICHER_GROUPE->setFixedHeight(35);
    layoutGroupes->addWidget(pushButton_AFFICHER_GROUPE);

    // === BOUTON EXPORTER GROUPES ===
    pushButton_EXPORTER_GROUPES = new QPushButton("📥 Exporter Tous les Groupes", frameGroupes);
    pushButton_EXPORTER_GROUPES->setStyleSheet(
        "QPushButton { "
        "background-color: #e74c3c; "
        "color: white; "
        "padding: 10px 5px; "
        "border: none; "
        "border-radius: 5px; "
        "font-size: 10pt; "
        "}"
        "QPushButton:hover { "
        "background-color: #c0392b; "
        "}"
        );
    pushButton_EXPORTER_GROUPES->setFixedHeight(35);
    layoutGroupes->addWidget(pushButton_EXPORTER_GROUPES);

    // === LABEL STATUT ===
    labelStatutGroupe = new QLabel("Créez des groupes avec des âges moyens similaires", frameGroupes);
    labelStatutGroupe->setStyleSheet("color: #bdc3c7; font-style: italic; margin-top: 10px; font-size: 9pt;");
    labelStatutGroupe->setWordWrap(true);  // 🆕 TEXTE QUI REVIENT À LA LIGNE
    labelStatutGroupe->setFixedHeight(40);
    layoutGroupes->addWidget(labelStatutGroupe);

    // === ESPACE FLEXIBLE POUR PUSHER TOUT VERS LE HAUT ===
    layoutGroupes->addStretch();

    // === CONNECTIONS ===
    connect(pushButton_CREER_GROUPES, &QPushButton::clicked, this, &apprenant::on_pushButton_CREER_GROUPES_clicked);
    connect(pushButton_AFFICHER_GROUPE, &QPushButton::clicked, this, &apprenant::on_pushButton_AFFICHER_GROUPE_clicked);
    connect(pushButton_EXPORTER_GROUPES, &QPushButton::clicked, this, &apprenant::on_pushButton_EXPORTER_GROUPES_clicked);
    connect(pushButton_TOGGLE_GROUPES, &QPushButton::clicked, this, &apprenant::on_pushButton_TOGGLE_GROUPES_clicked);
}

QMap<QString, QList<int>> apprenant::creerGroupesEquilibres(int nombreGroupes)
{
    QMap<QString, QList<int>> groupes;

    // Récupérer tous les apprenants
    QSqlQuery query;
    query.exec("SELECT ID_APPRENANT, DATE_NAISS FROM apprenant ORDER BY DATE_NAISS");

    QList<QPair<int, double>> apprenantsAges;
    QDate aujourdhui = QDate::currentDate();

    while (query.next()) {
        int id = query.value(0).toInt();
        QDate dateNaiss = query.value(1).toDate();
        int age = aujourdhui.year() - dateNaiss.year();
        if (aujourdhui < QDate(aujourdhui.year(), dateNaiss.month(), dateNaiss.day())) {
            age--;
        }
        apprenantsAges.append(qMakePair(id, (double)age));
    }

    if (apprenantsAges.isEmpty()) {
        QMessageBox::warning(nullptr, "Aucun apprenant", "Aucun apprenant trouvé dans la base.");
        return groupes;
    }

    // Initialiser les groupes
    for (int i = 0; i < nombreGroupes; i++) {
        groupes[QString("Groupe %1").arg(i + 1)] = QList<int>();
    }

    // Algorithme de répartition équilibrée
    for (int i = 0; i < apprenantsAges.size(); i++) {
        int groupeIndex;
        if ((i / nombreGroupes) % 2 == 0) {
            groupeIndex = i % nombreGroupes;
        } else {
            groupeIndex = nombreGroupes - 1 - (i % nombreGroupes);
        }
        QString nomGroupe = QString("Groupe %1").arg(groupeIndex + 1);
        groupes[nomGroupe].append(apprenantsAges[i].first);
    }

    return groupes;
}

double apprenant::calculerAgeMoyenGroupe(const QList<int>& idsApprenants)
{
    if (idsApprenants.isEmpty()) return 0.0;

    QSqlQuery query;
    QDate aujourdhui = QDate::currentDate();
    double totalAge = 0.0;

    for (int id : idsApprenants) {
        query.prepare("SELECT DATE_NAISS FROM apprenant WHERE ID_APPRENANT = ?");
        query.addBindValue(id);
        if (query.exec() && query.next()) {
            QDate dateNaiss = query.value(0).toDate();
            int age = aujourdhui.year() - dateNaiss.year();
            if (aujourdhui < QDate(aujourdhui.year(), dateNaiss.month(), dateNaiss.day())) {
                age--;
            }
            totalAge += age;
        }
    }
    return totalAge / idsApprenants.size();
}

QSqlQueryModel* apprenant::afficherGroupe(const QList<int>& idsApprenants)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    if (idsApprenants.isEmpty()) {
        model->setQuery("SELECT '' as ID, '' as Nom, '' as Prénom, '' as 'Date naissance', '' as Email WHERE 1=0");
        return model;
    }

    QStringList idsStr;
    for (int id : idsApprenants) {
        idsStr.append(QString::number(id));
    }

    QString queryStr = QString("SELECT ID_APPRENANT as ID, NOM, PRENOM, DATE_NAISS, EMAIL FROM apprenant WHERE ID_APPRENANT IN (%1) ORDER BY NOM, PRENOM")
                           .arg(idsStr.join(","));

    model->setQuery(queryStr);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));

    return model;
}

void apprenant::exporterGroupesWord(const QMap<QString, QList<int>>& groupes)
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Exporter les groupes", "groupes_apprenants.doc", "Documents Word (*.doc)");
    if (fileName.isEmpty()) return;

    QString html;
    html += "<html><head><meta charset=\"UTF-8\"><title>Groupes d'Apprenants</title></head><body>";
    html += "<h1>📊 Groupes d'Apprenants - SmartSummer Club</h1>";

    QDate aujourdhui = QDate::currentDate();
    int totalApprenants = 0;

    for (auto it = groupes.begin(); it != groupes.end(); ++it) {
        QString nomGroupe = it.key();
        QList<int> ids = it.value();
        double ageMoyen = calculerAgeMoyenGroupe(ids);
        totalApprenants += ids.size();

        html += QString("<h2>%1 (%2 apprenants - Âge moyen: %3 ans)</h2>").arg(nomGroupe).arg(ids.size()).arg(ageMoyen, 0, 'f', 1);
        html += "<table border='1' cellpadding='5' cellspacing='0' width='100%'>";
        html += "<tr style='background-color: #f0f0f0;'><th>ID</th><th>Nom</th><th>Prénom</th><th>Date Naissance</th><th>Âge</th><th>Email</th></tr>";

        for (int id : ids) {
            QSqlQuery query;
            query.prepare("SELECT NOM, PRENOM, DATE_NAISS, EMAIL FROM apprenant WHERE ID_APPRENANT = ?");
            query.addBindValue(id);
            if (query.exec() && query.next()) {
                QString nom = query.value(0).toString();
                QString prenom = query.value(1).toString();
                QDate dateNaiss = query.value(2).toDate();
                QString email = query.value(3).toString();
                int age = aujourdhui.year() - dateNaiss.year();
                if (aujourdhui < QDate(aujourdhui.year(), dateNaiss.month(), dateNaiss.day())) age--;

                html += QString("<tr><td>%1</td><td>%2</td><td>%3</td><td>%4</td><td>%5 ans</td><td>%6</td></tr>")
                            .arg(id).arg(nom).arg(prenom).arg(dateNaiss.toString("dd/MM/yyyy")).arg(age).arg(email);
            }
        }
        html += "</table><br>";
    }

    html += QString("<p><strong>Total général:</strong> %1 apprenants</p>").arg(totalApprenants);
    html += "<p><em>Généré le " + QDate::currentDate().toString("dd/MM/yyyy") + "</em></p>";
    html += "</body></html>";

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << html;
        file.close();
        QMessageBox::information(nullptr, "Succès", "Groupes exportés vers:\n" + fileName);
    } else {
        QMessageBox::critical(nullptr, "Erreur", "Impossible de sauvegarder le fichier");
    }
}

void apprenant::on_pushButton_CREER_GROUPES_clicked()
{
    if (!spinBox_NB_GROUPES) return;

    int nbGroupes = spinBox_NB_GROUPES->value();
    groupesActuels = creerGroupesEquilibres(nbGroupes);

    comboBox_GROUPES->clear();
    QString message = "📊 **GROUPES CRÉÉS AVEC SUCCÈS**\n\n";

    if (labelStatutGroupe) {
        labelStatutGroupe->setStyleSheet("color: #f39c12; font-weight: bold; margin-top: 10px;");
        labelStatutGroupe->setText(QString("✅ %1 groupes créés - Sélectionnez un groupe à afficher").arg(nbGroupes));
    }

    for (auto it = groupesActuels.begin(); it != groupesActuels.end(); ++it) {
        QString nomGroupe = it.key();
        comboBox_GROUPES->addItem(nomGroupe);
        double ageMoyen = calculerAgeMoyenGroupe(it.value());
        message += QString("• %1 : %2 apprenants (Âge moyen: %3 ans)\n").arg(nomGroupe).arg(it.value().size()).arg(ageMoyen, 0, 'f', 1);
    }

    QMessageBox::information(nullptr, "Groupes Créés", message);
}

void apprenant::on_pushButton_AFFICHER_GROUPE_clicked()
{
    QString groupeSelectionne = comboBox_GROUPES->currentText();
    if (groupeSelectionne.isEmpty() || !groupesActuels.contains(groupeSelectionne)) {
        QMessageBox::warning(nullptr, "Erreur", "Veuillez sélectionner un groupe valide.");
        return;
    }

    QList<int> ids = groupesActuels[groupeSelectionne];
    QSqlQueryModel *model = afficherGroupe(ids);

    double ageMoyen = calculerAgeMoyenGroupe(ids);
    if (labelStatutGroupe) {
        labelStatutGroupe->setText(QString("🔍 %1\n%2 apprenants\nÂge moyen: %3 ans")
                                       .arg(groupeSelectionne)
                                       .arg(ids.size())
                                       .arg(ageMoyen, 0, 'f', 1));
        labelStatutGroupe->setStyleSheet("color: #2ecc71; font-weight: bold; margin-top: 10px; font-size: 9pt;");
    }

    // Note: The model will be used by interface_formateur to display in table
    // 🆕 EMIT SIGNAL WITH THE MODEL
    emit groupeAAfficher(model);
}

void apprenant::on_pushButton_EXPORTER_GROUPES_clicked()
{
    if (groupesActuels.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur", "Aucun groupe à exporter. Créez d'abord des groupes.");
        return;
    }
    exporterGroupesWord(groupesActuels);
}

// 🆕 FONCTION POUR AFFICHER/MASQUER LES GROUPES
void apprenant::on_pushButton_TOGGLE_GROUPES_clicked()
{
    if (frameGroupes->isVisible()) {
        // Masquer l'interface groupes
        frameGroupes->hide();
        pushButton_TOGGLE_GROUPES->setText("🎯 Groupes");
        pushButton_TOGGLE_GROUPES->setStyleSheet(
            "QPushButton { "
            "background-color: #9b59b6; "
            "color: white; "
            "padding: 8px 15px; "
            "border: none; "
            "border-radius: 5px; "
            "font-size: 10pt; "
            "font-weight: bold; "
            "}"
            "QPushButton:hover { "
            "background-color: #8e44ad; "
            "}"
            );
        // 🆕 REPOSITIONNE LE BOUTON
        pushButton_TOGGLE_GROUPES->setGeometry(180, 20, 120, 35);
    } else {
        // Afficher l'interface groupes
        frameGroupes->show();
        pushButton_TOGGLE_GROUPES->setText("❌ Groupes");
        pushButton_TOGGLE_GROUPES->setStyleSheet(
            "QPushButton { "
            "background-color: #e74c3c; "
            "color: white; "
            "padding: 8px 15px; "
            "border: none; "
            "border-radius: 5px; "
            "font-size: 10pt; "
            "font-weight: bold; "
            "}"
            "QPushButton:hover { "
            "background-color: #c0392b; "
            "}"
            );

        // Focus sur le spinbox pour faciliter l'utilisation
        if (spinBox_NB_GROUPES) {
            spinBox_NB_GROUPES->setFocus();
        }
    }
}

QSqlQueryModel* apprenant::getGroupeModel(const QString& groupeName)
{
    if (groupesActuels.contains(groupeName)) {
        return afficherGroupe(groupesActuels[groupeName]);
    }
    return nullptr;
}
