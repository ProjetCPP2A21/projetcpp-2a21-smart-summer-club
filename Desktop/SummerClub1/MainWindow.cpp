#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "formation.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initTable();

    // Optionnel : remplir le combo type si tu ne l'as pas fait dans Designer
    if (ui->lineEdit_type->count() == 0) {
        ui->lineEdit_type->addItems({"Français", "Anglais", "Math", "Science","Physique"});
    }
    // s'assurer que la table sélectionne des lignes entières
    ui->tableFormations->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableFormations->setSelectionMode(QAbstractItemView::SingleSelection);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::initTable()
{
    ui->tableFormations->setColumnCount(8);
    QStringList headers = {"Id","Nom","Type","Horaire","Duree","Lieu","Capacite","Tarif"};
    ui->tableFormations->setHorizontalHeaderLabels(headers);
    ui->tableFormations->horizontalHeader()->setStretchLastSection(true);
}
void MainWindow::clearInputs()
{
    ui->lineEditId->clear();
    ui->lineEdit_Nom->clear();
    ui->lineEdit_type->setCurrentIndex(0);
    ui->lineEdit_h->setTime(QTime::fromString("00:00","hh:mm"));
    ui->lineEdit_D->clear();
    ui->lineEdit_lieu->clear();
    ui->lineEdit_Ca->clear();
    ui->lineEdit_Ta->clear();
}
// Vérifie les champs et retourne false si erreur (et remplit errMsg)
bool MainWindow::validateInputs(QString &errMsg)
{
    if (ui->lineEditId->text().trimmed().isEmpty()) { errMsg = "Id obligatoire"; return false; }
    if (ui->lineEdit_Nom->text().trimmed().isEmpty()) { errMsg = "Nom obligatoire"; return false; }
    // tu peux ajouter d'autres validations (nombres pour capacité/tarif, etc.)
    return true;
}



void MainWindow::on_pushButtonAjouter_clicked()
    {
        QString err;
        if (!validateInputs(err)) {
            QMessageBox::warning(this, "Erreur", err);
            return;
        }

        int row = ui->tableFormations->rowCount();
        ui->tableFormations->insertRow(row);

        ui->tableFormations->setItem(row, 0, new QTableWidgetItem(ui->lineEditId->text().trimmed()));
        ui->tableFormations->setItem(row, 1, new QTableWidgetItem(ui->lineEdit_Nom->text().trimmed()));
        ui->tableFormations->setItem(row, 2, new QTableWidgetItem(ui->lineEdit_type->currentText()));
        QTime t = ui->lineEdit_h->time();
        QTableWidgetItem *horaireItem = new QTableWidgetItem(t.toString("HH:mm"));
        horaireItem->setData(Qt::UserRole, t); // on garde le QTime pour trier
        ui->tableFormations->setItem(row, 3, horaireItem);
        ui->tableFormations->setItem(row, 4, new QTableWidgetItem(ui->lineEdit_D->text().trimmed()));
        ui->tableFormations->setItem(row, 5, new QTableWidgetItem(ui->lineEdit_lieu->text().trimmed()));
        ui->tableFormations->setItem(row, 6, new QTableWidgetItem(ui->lineEdit_Ca->text().trimmed()));
        ui->tableFormations->setItem(row, 7, new QTableWidgetItem(ui->lineEdit_Ta->text().trimmed()));

        clearInputs();
    }




// Supprimer la ligne sélectionnée
void MainWindow::on_pushButtonsupprimer_clicked()
{
    auto sel = ui->tableFormations->selectionModel();
    if (!sel->hasSelection()) {
        QMessageBox::information(this, "Info", "Veuillez sélectionner une ligne à supprimer.");
        return;
    }
    int row = ui->tableFormations->currentRow();
    if (row >= 0) {
        ui->tableFormations->removeRow(row);
    }

}

// Sauvegarder le tableau dans un fichier CSV (ex: formations.csv)
void MainWindow::on_pushButtonSauvegarder_clicked()
{
    QString path = "formations.csv";
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier pour sauvegarder.");
        return;
    }
    QTextStream out(&file);

    // en-tête
    QStringList headers;
    for (int c = 0; c < ui->tableFormations->columnCount(); ++c)
        headers << ui->tableFormations->horizontalHeaderItem(c)->text();
    out << headers.join(",") << "\n";

    // lignes
    for (int r = 0; r < ui->tableFormations->rowCount(); ++r) {
        QStringList row;
        for (int c = 0; c < ui->tableFormations->columnCount(); ++c) {
            QTableWidgetItem *it = ui->tableFormations->item(r, c);
            row << (it ? it->text() : "");
        }
        out << row.join(",") << "\n";
    }
    file.close();
    QMessageBox::information(this, "Sauvegarde", "Formations sauvegardées dans " + path);
}






// Modifier la ligne sélectionnée avec les valeurs des champs
void MainWindow::on_pushButtonModifier_clicked()
{
    auto sel = ui->tableFormations->selectionModel();
    if (!sel->hasSelection()) {
        QMessageBox::information(this, "Info", "Veuillez sélectionner une ligne à modifier.");
        return;
    }
    QString err;
    if (!validateInputs(err)) {
        QMessageBox::warning(this, "Erreur", err);
        return;
    }

    int row = ui->tableFormations->currentRow();
    if (row >= 0) {
        ui->tableFormations->setItem(row, 0, new QTableWidgetItem(ui->lineEditId->text().trimmed()));
        ui->tableFormations->setItem(row, 1, new QTableWidgetItem(ui->lineEdit_Nom->text().trimmed()));
        ui->tableFormations->setItem(row, 2, new QTableWidgetItem(ui->lineEdit_type->currentText()));
        ui->tableFormations->setItem(row, 3, new QTableWidgetItem(ui->lineEdit_h->time().toString("hh:mm")));
        ui->tableFormations->setItem(row, 4, new QTableWidgetItem(ui->lineEdit_D->text().trimmed()));
        ui->tableFormations->setItem(row, 5, new QTableWidgetItem(ui->lineEdit_lieu->text().trimmed()));
        ui->tableFormations->setItem(row, 6, new QTableWidgetItem(ui->lineEdit_Ca->text().trimmed()));
        ui->tableFormations->setItem(row, 7, new QTableWidgetItem(ui->lineEdit_Ta->text().trimmed()));
        clearInputs();
    }

}
void MainWindow::on_pushButtonTrier_clicked()
{
    int colHoraire = 3; // colonne Horaire (0 = première colonne, 3 = 4ème)

    struct RowData {
        QTime t;
        QStringList cells;
    };

    QVector<RowData> rows;

    // Récupérer toutes les lignes actuelles
    for (int r = 0; r < ui->tableFormations->rowCount(); ++r) {
        QTableWidgetItem *it = ui->tableFormations->item(r, colHoraire);
        QTime tt;
        if (it) tt = it->data(Qt::UserRole).toTime();
        if (!tt.isValid() && it) tt = QTime::fromString(it->text(), "HH:mm");

        RowData rd;
        rd.t = tt;
        for (int c = 0; c < ui->tableFormations->columnCount(); ++c) {
            QTableWidgetItem *ci = ui->tableFormations->item(r, c);
            rd.cells << (ci ? ci->text() : QString());
        }
        rows.append(rd);
    }

    // Trier le vecteur par horaire
    std::sort(rows.begin(), rows.end(), [](const RowData &a, const RowData &b){
        if (!a.t.isValid() && !b.t.isValid()) return false;
        if (!a.t.isValid()) return false;
        if (!b.t.isValid()) return true;
        return a.t < b.t;
    });

    // Réécrire le tableau trié
    ui->tableFormations->setRowCount(0);
    for (const RowData &rd : rows) {
        int newRow = ui->tableFormations->rowCount();
        ui->tableFormations->insertRow(newRow);
        for (int c = 0; c < rd.cells.size(); ++c) {
            QTableWidgetItem *newIt = new QTableWidgetItem(rd.cells[c]);
            if (c == colHoraire && rd.t.isValid()) {
                newIt->setData(Qt::UserRole, rd.t);
            }
            ui->tableFormations->setItem(newRow, c, newIt);
        }
    }
}

