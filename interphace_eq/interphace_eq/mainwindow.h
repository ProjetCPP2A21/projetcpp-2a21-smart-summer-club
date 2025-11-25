#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "equipementc.h"
#include <QMainWindow>
#include <QSqlQueryModel>
#include <QColor>
#include <QBrush>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextBrowser>
#include <QDialog>
#include <QPushButton>
#include <QPrinter>
#include <QPageSize>
#include <QScreen>
#include <QGuiApplication>
#include <QTextDocument>
#include <QPrinter>
#include <QPageSize>
#include <QPageLayout>
#include <QTextBrowser>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

// ===========================================================
//    CLASSE ColorSqlModel : Coloration intelligente du tableau
// ===========================================================

class ColorSqlModel : public QSqlQueryModel
{
public:
    ColorSqlModel(QObject *parent = nullptr) : QSqlQueryModel(parent) {}

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    {
        if (role == Qt::BackgroundRole)
        {
            QModelIndex etatIndex = this->index(index.row(), 4);
            QString etat = QSqlQueryModel::data(etatIndex, Qt::DisplayRole).toString();

            QString etatLower = etat.toLower().trimmed();

            // ===========================
            // 🚦 COLORATION AUTOMATIQUE
            // ===========================

            // Disponible → Vert
            if (etatLower.contains("dispon"))
                return QBrush(QColor(144, 238, 144));  // vert clair

            // En panne → Rouge (toutes variantes)
            if (
                etatLower.contains("panne") ||
                etatLower.contains("pan")   ||
                etatLower.contains("pann")  ||
                etatLower.contains("panee")
                )
            {
                return QBrush(QColor(255, 120, 120)); // rouge clair
            }

            // Réservé → Jaune
            if (etatLower.contains("reserv"))
                return QBrush(QColor(255, 255, 153));  // jaune clair
        }

        return QSqlQueryModel::data(index, role);
    }
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// ===========================================================
//                        MainWindow
// ===========================================================

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void clearFieldsEquipement();

private slots:
    void on_ajouterEquipement_clicked();
    void on_SupprimerEquipement_clicked();
    void on_ModifierEquipement_clicked();
    void on_EquipementTable_clicked(const QModelIndex &index);
    void on_pushButton_23_clicked();
    void on_pushButton_stat_8_clicked();
    void on_rechercherEquipement_clicked();
    void on_pushButton_stat_7_clicked();
    void on_ficheTechnique_clicked();

    // Nouveaux slots pour la recherche améliorée
    void on_RechercheEquipement_textChanged(const QString &text);
    void on_RechercheEquipement_focusIn();
    void on_RechercheEquipement_focusOut();

private:
    Ui::MainWindow *ui;
    equipementC e;
    ColorSqlModel *colorModel;
    bool recherchePlaceholderActive;
};

#endif // MAINWINDOW_H
