#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "equipementc.h"
#include "arduino.h"
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

            if (etatLower.contains("dispon"))
                return QBrush(QColor(144, 238, 144));

            if (etatLower.contains("panne") || etatLower.contains("pan") ||
                etatLower.contains("pann") || etatLower.contains("panee"))
            {
                return QBrush(QColor(255, 120, 120));
            }

            if (etatLower.contains("reserv"))
                return QBrush(QColor(255, 255, 153));
        }

        return QSqlQueryModel::data(index, role);
    }
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

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

    void on_RechercheEquipement_textChanged(const QString &text);
    void on_RechercheEquipement_focusIn();
    void on_RechercheEquipement_focusOut();

    void on_verifmoteur_textChanged(const QString &text);
    void onArduinoEtatChanged(bool moteurActif, const QString &message);
    void onArduinoMessageInfo(const QString &message);

private:
    Ui::MainWindow *ui;
    equipementC e;
    ColorSqlModel *colorModel;
    bool recherchePlaceholderActive;
    Arduino *arduino;

    void updateArduinoUI(bool moteurActif, const QString &message);
};

#endif // MAINWINDOW_H
