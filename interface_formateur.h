#ifndef INTERFACE_FORMATEUR_H
#define INTERFACE_FORMATEUR_H


#include <QMainWindow>

class MainWindow;  // déclaration avant

namespace Ui {
class interface_formateur;
}

class interface_formateur : public QMainWindow
{
    Q_OBJECT

public:
    explicit interface_formateur(MainWindow *menu, QWidget *parent = nullptr);
    ~interface_formateur();
    void setPage(int index);

private slots:
    void on_pushButton_clicked();// bouton formateur menu
    void on_pushButton_retour_menu_clicked(); // bouton retour vers menu
    void on_pushButton_employe_clicked();
    void on_pushButton_formateur_clicked();
    void on_pushButton_formation_clicked();

    void on_pushButton_stat_6_clicked();

    void on_pushButton_stat_4_clicked();

    void on_pushButton_stat_2_clicked();

    void on_pushButton_stat_3_clicked();

    void on_pushButton_service_clicked();

    void on_pushButton_apprenant_clicked();

    void on_pushButton_equipement_clicked();

private:
    Ui::interface_formateur *ui;
    MainWindow *menuPrincipal;     // pointeur vers le menu principal
};

#endif // INTERFACE_FORMATEUR_H
