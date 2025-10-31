#ifndef INTERFACE_FORMATEUR_H
#define INTERFACE_FORMATEUR_H
#include <QMainWindow>
#include "formateurs.h"



class MainWindow;  // déclaration avant

namespace Ui {
class interface_formateur;
}

class interface_formateur : public QMainWindow //interface PRINCIPALE
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

    void on_pushButton_AJOUTER_5_clicked(); // Bouton ajout FORMATEUR

 //   void on_pushButton_SupprimerFormateur(); // Bouton supprimer FORMATEUR

  //  void on_pushButton_AFFICHER_FORMATEUR_clicked(); // Bouton afficher FORMATEUR


private:
    Ui::interface_formateur *ui;
    MainWindow *menuPrincipal;     // pointeur vers le menu principal
   //30.10
    Formateur F; // POINTEUR ???

};

#endif // INTERFACE_FORMATEUR_H
