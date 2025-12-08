#include "gestion_employe.h"
#include "ui_gestion_employe.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlRecord>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QPieSlice>

#include <QVBoxLayout>
#include <QLayout>
#include <QLayoutItem>

//j'ajoute
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QPageSize>
#include <QMarginsF>

using namespace QtCharts;



gestion_employe::gestion_employe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gestion_employe)
{
    ui->setupUi(this);

    // ---- INPUT VALIDATORS (set once at start) ----
    QIntValidator *intVal = new QIntValidator(this);
    ui->lineEdit_ID_2->setValidator(intVal);
    ui->lineEdit_cin_2->setValidator(intVal);
    ui->lineEdit_num_2->setValidator(new QIntValidator(10000000, 99999999, this)); // 8 digits

    // letters + space + hyphen for name fields
    QRegularExpression nameRx("^[A-Za-zÀ-ÖØ-öø-ÿ\\-\\s]+$");
    QRegularExpressionValidator *nameVal = new QRegularExpressionValidator(nameRx, this);
    ui->lineEdit_nom_2->setValidator(nameVal);
    ui->lineEdit_prenom_2->setValidator(nameVal);

    // email validator
    QRegularExpression emailRx(R"(^[\w\.\-]+\@[\w\-]+\.[a-zA-Z]{2,}$)");
    ui->lineEdit_email_2->setValidator(new QRegularExpressionValidator(emailRx, this));

    // Display the list at startup
    ui->tableView_2->setModel(etmp.afficher());

    // Connect pushButton_23 to navigate to page_employe
    connect(ui->pushButton_23, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget_principale->setCurrentWidget(ui->page_employe);
    });


}

gestion_employe::~gestion_employe()
{
    delete ui;
}

/* ------------------------------------------------------------------ */
/*                         INPUT VALIDATION                           */
/* ------------------------------------------------------------------ */
QString gestion_employe::validateFields(bool forAdd, bool forModify, bool forDelete) const
{
    //zedtou
    Q_UNUSED(forAdd);
    Q_UNUSED(forModify);
    Q_UNUSED(forDelete);
    // ---- ID -------------------------------------------------------
    bool ok;
    int id = ui->lineEdit_ID_2->text().toInt(&ok);
    if (!ok || id <= 0) {
        return tr("L'ID doit être un nombre positif.");
    }

    // ---- CIN -------------------------------------------------------
    if (ui->lineEdit_cin_2->text().isEmpty()) {
        return tr("Le CIN est obligatoire.");
    }
    // (already forced to digits by validator)

    // ---- NOM / PRENOM -----------------------------------------------
    if (ui->lineEdit_nom_2->text().trimmed().isEmpty()) {
        return tr("Le nom est obligatoire.");
    }
    if (ui->lineEdit_prenom_2->text().trimmed().isEmpty()) {
        return tr("Le prénom est obligatoire.");
    }

    // ---- POSTE ------------------------------------------------------
    if (ui->lineEdit_poste_2->text().trimmed().isEmpty()) {
        return tr("Le poste est obligatoire.");
    }

    // ---- NUM (8 digits) ---------------------------------------------
    QString numStr = ui->lineEdit_num_2->text();
    if (numStr.length() != 8 || !numStr[0].isDigit()) {
        return tr("Le numéro de téléphone doit contenir exactement 8 chiffres.");
    }

    // ---- EMAIL -------------------------------------------------------
    if (ui->lineEdit_email_2->text().trimmed().isEmpty()) {
        return tr("L'e-mail est obligatoire.");
    }
    // (validator already checks format, but we double-check)
    QRegularExpression emailRx(R"(^[\w\.\-]+\@[\w\-]+\.[a-zA-Z]{2,}$)");
    if (!emailRx.match(ui->lineEdit_email_2->text()).hasMatch()) {
        return tr("Veuillez saisir une adresse e-mail valide.");
    }

    // ---- MDP ---------------------------------------------------------
    if (ui->lineEdit_mdp_2->text().isEmpty()) {
        return tr("Le mot de passe est obligatoire.");
    }

    // ---- DATE (QDateEdit already guarantees a valid date) -----------

    return QString();   // no error
}



/* ------------------------------------------------------------------ */
/*                         CLEAR FIELDS                               */
/* ------------------------------------------------------------------ */
void gestion_employe::clearFields()
{
    ui->lineEdit_ID_2->clear();
    ui->lineEdit_nom_2->clear();
    ui->lineEdit_prenom_2->clear();
    ui->lineEdit_poste_2->clear();
    ui->lineEdit_cin_2->clear();
    ui->lineEdit_num_2->clear();
    ui->lineEdit_email_2->clear();
    ui->lineEdit_mdp_2->clear();
    ui->dateEdit_2->setDate(QDate::currentDate());
}

/* ==================== AJOUTER ==================== */
void gestion_employe::on_btajouter_2_clicked()
{
    QString err = validateFields(true, false, false);
    if (!err.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur de saisie"), err);
        return;
    }

    int     id          = ui->lineEdit_ID_2->text().toInt();
    QString nom         = ui->lineEdit_nom_2->text();
    QString prenom      = ui->lineEdit_prenom_2->text();
    QString poste       = ui->lineEdit_poste_2->text();
    int     cin         = ui->lineEdit_cin_2->text().toInt();
    int     num         = ui->lineEdit_num_2->text().toInt();
    QString email       = ui->lineEdit_email_2->text();
    QString mdp         = ui->lineEdit_mdp_2->text();
    QDate   dateembauche= ui->dateEdit_2->date();

    employe e(id, nom, prenom, poste, cin, num, dateembauche, email, mdp);
    if (e.ajouter()) {
        QMessageBox::information(this, tr("Succès"), tr("Ajout effectué !"));
        ui->tableView_2->setModel(e.afficher());
        clearFields();
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de l'ajout !"));
    }
}

/* ==================== SUPPRIMER ==================== */
void gestion_employe::on_btsupprimer_2_clicked()
{
    QString err = validateFields(false, false, true);
    if (!err.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur de saisie"), err);
        return;
    }

    int id = ui->lineEdit_ID_2->text().toInt();

    if (etmp.supprimer(id)) {
        QMessageBox::information(this, tr("Succès"), tr("Suppression effectuée !"));
        ui->tableView_2->setModel(etmp.afficher());
        clearFields();
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Suppression non effectuée !"));
    }
}

/* ==================== MODIFIER ==================== */
void gestion_employe::on_bmodifier_2_clicked()
{
    QString err = validateFields(false, true, false);
    if (!err.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur de saisie"), err);
        return;
    }

    int     id          = ui->lineEdit_ID_2->text().toInt();
    QString nom         = ui->lineEdit_nom_2->text();
    QString prenom      = ui->lineEdit_prenom_2->text();
    QString poste       = ui->lineEdit_poste_2->text();
    int     cin         = ui->lineEdit_cin_2->text().toInt();
    int     num         = ui->lineEdit_num_2->text().toInt();
    QString email       = ui->lineEdit_email_2->text();
    QString mdp         = ui->lineEdit_mdp_2->text();
    QDate   dateembauche= ui->dateEdit_2->date();

    etmp = employe(id, nom, prenom, poste, cin, num, dateembauche, email, mdp);
    if (etmp.modifier(id)) {
        QMessageBox::information(this, tr("Succès"), tr("Modification effectuée !"));
        ui->tableView_2->setModel(etmp.afficher());
        clearFields();
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de la modification !"));
    }
}

/* ==================== RECHERCHER (fill) ==================== */
void gestion_employe::on_pushButton_cin_4_clicked()
{
    bool ok;
    int id = ui->lineEdit_ID_2->text().toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this, tr("Input error"),
                             tr("Veuillez entrer un ID numérique valide."));
        return;
    }

    QSqlQueryModel *model = etmp.fill(id);
    if (!model) {
        QMessageBox::critical(this, tr("Database error"),
                              tr("Échec de l'exécution de la requête."));
        return;
    }

    if (model->rowCount() == 0) {
        QMessageBox::warning(this, tr("Introuvable"),
                             tr("Aucun employé avec l'ID %1").arg(id));
        clearFields();
        delete model;
        return;
    }

    QSqlRecord r = model->record(0);
    ui->lineEdit_nom_2->setText   (r.value("NOMEMPLOYE").toString());
    ui->lineEdit_prenom_2->setText(r.value("PRENOMEMPLOYE").toString());
    ui->lineEdit_poste_2->setText (r.value("POSTEEMPLOYE").toString());
    ui->lineEdit_cin_2->setText   (r.value("CINEMPLOYE").toString());
    ui->lineEdit_num_2->setText   (r.value("TELEMPLOYER").toString());
    ui->lineEdit_email_2->setText (r.value("EMAILEMPLOYE").toString());
    ui->lineEdit_mdp_2->setText   (r.value("MDPEMPLOYE").toString());

    QDate d = r.value("DATEEMBAUCHE").toDate();
    if (d.isValid())
        ui->dateEdit_2->setDate(d);
    else
        ui->dateEdit_2->clear();

    QMessageBox::information(this, tr("Succès"), tr("Données chargées."));
    delete model;
}
//rechercher
void gestion_employe::on_btSearchEmail_2_clicked()
{
    QString email = ui->lineEdit_searchEmail_2->text().trimmed();

    if (email.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un email.");
        return;
    }

    QSqlQueryModel *model = etmp.rechercher_email(email);

    if (!model) {
        QMessageBox::critical(this, "Erreur SQL", "Recherche échouée.");
        return;
    }

    ui->tableView_2->setModel(model);
}
//tri croissant
void gestion_employe::on_btTriDate_2_clicked()
{
    ui->tableView_2->setModel(etmp.trier_date_croissant());
}


//stat

void gestion_employe::afficherStatistiques()
{
    QSqlQuery q;
    q.prepare("SELECT POSTEEMPLOYE, COUNT(*) FROM EMPLOYER GROUP BY POSTEEMPLOYE");
    if (!q.exec()) return;

    QPieSeries *series = new QPieSeries();

    while (q.next()) {
        series->append(q.value(0).toString(), q.value(1).toInt());
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des employés par poste");
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // vider ancien contenu
    if (ui->groupBox_stats_2->layout()) {
        QLayoutItem *item;
        QLayout *old = ui->groupBox_stats_2->layout();
        while ((item = old->takeAt(0))) {
            delete item->widget();
            delete item;
        }
        delete old;
    }

    // ajouter le chart
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    ui->groupBox_stats_2->setLayout(layout);
}
void gestion_employe::on_btnStats_2_clicked()
{
    afficherStatistiques(); // إذا تحب تربطها بالإحصائيات
}
//pdf

void gestion_employe::exportWord()
{
    // فتح نافذة لاختيار اسم الملف
    QString fileName = QFileDialog::getSaveFileName(this, "تصدير إلى Word", "", "ملف RTF (*.rtf)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "خطأ", "تعذر إنشاء الملف!");
        return;
    }

    QTextStream out(&file);
    out << "{\\rtf1\\ansi\\deff0\n";
    out << "\\b قائمة الموظفين \\b0\\par\n";

    QAbstractItemModel *model = ui->tableView_2->model();

    // إضافة البيانات
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            out << model->index(row, col).data().toString() << "\t";
        }
        out << "\\par\n";
    }

    out << "}";
    file.close();

    QMessageBox::information(this, "Word", "تم التصدير إلى RTF بنجاح!");
}

void gestion_employe::exportPDF()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "*.pdf");
    if (fileName.isEmpty())
        return;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));

    QPainter painter(&printer);
    painter.setFont(QFont("Arial", 16));
    painter.drawText(200, 50, "Liste des employés");

    int y = 100;
    painter.setFont(QFont("Arial", 12));

    QAbstractItemModel* model = ui->tableView_2->model();
    for (int row = 0; row < model->rowCount(); ++row) {
        QString line;
        for (int col = 0; col < model->columnCount(); ++col)
            painter.drawText(50 + col * 100, y, model->index(row, col).data().toString());
        y += 30;

        if (y > printer.pageRect(QPrinter::Point).height() - 50) {
            printer.newPage();
            y = 100;
        }
    }

    painter.end();
    QMessageBox::information(this, "PDF", "Export PDF terminé !");
}

void gestion_employe::on_btnExportPDF_2_clicked()
{
    exportPDF();
}

void gestion_employe::on_pushButton_clicked()
{
    ui->stackedWidget_login->setCurrentIndex(1);
}

void gestion_employe::on_pushButton_valider_mdp_clicked()
{
    int cin = ui->lineEdit_cin2->text().toInt();
    int id = ui->lineEdit_ID2->text().toInt();
    QDate dateembauche = ui->dateEdit2->date();

    QString mdp = etmp.recuperer_mdp(id, cin, dateembauche);

    if (!mdp.isEmpty()) {
        ui->lineEdit_mdp2->setText(mdp);
        QMessageBox::information(this, "Succès", "Mot de passe récupéré avec succès !");
        
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Connexion", "Voulez-vous vous connecter maintenant ?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
             ui->stackedWidget_login->setCurrentIndex(0);
             ui->lineEdit_2->setText(mdp); 
             ui->lineEdit->setText(QString::number(id)); 
        }
    } else {
        QMessageBox::warning(this, "Erreur", 
            QString("Informations incorrectes.\nID: %1\nCIN: %2\nDate: %3")
            .arg(id).arg(cin).arg(dateembauche.toString("dd/MM/yyyy")));
    }
}

void gestion_employe::on_pushButton_se_connecter_clicked()
{
    int id = ui->lineEdit->text().toInt();
    QString mdp = ui->lineEdit_2->text();

    if (etmp.seConnecter(id, mdp)) {
        QMessageBox::information(this, "Succès", "Connexion réussie !");
        ui->stackedWidget_principale->setCurrentWidget(ui->page_menu);
    } else {
        QMessageBox::warning(this, "Erreur", "Identifiant ou mot de passe incorrect.");
    }
}
