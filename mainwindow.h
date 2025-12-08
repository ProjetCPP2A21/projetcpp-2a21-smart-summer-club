#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "interface_formateur.h"

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

    void setPosteEmploye(const QString &poste);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_gestionemploye_clicked();
    void on_pushButton_gestionformation_clicked();
    void on_pushButton_gestionapprenant_clicked();
    void on_pushButton_gestionservice_clicked();
    void on_pushButton_gestionequipement_clicked();

private:
    Ui::MainWindow *ui;
    interface_formateur *inter_forma;
    QString posteEmploye;

    bool hasAccess(const QString &requiredPoste);
};

#endif // MAINWINDOW_H
