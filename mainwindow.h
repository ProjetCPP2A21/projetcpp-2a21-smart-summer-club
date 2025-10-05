#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
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


private slots:
    void on_pushButton_clicked();  // bouton qui ouvre interface formateur
    void on_pushButton_gestionemploye_clicked(); // bouton qui ouvre interface employe

    void on_pushButton_gestionformation_clicked();

    void on_pushButton_gestionapprenant_clicked();

    void on_pushButton_gestionservice_clicked();

private:
    Ui::MainWindow *ui;
    interface_formateur *inter_form;  // pointeur vers la 2e fenêtre
};
#endif // MAINWINDOW_H
