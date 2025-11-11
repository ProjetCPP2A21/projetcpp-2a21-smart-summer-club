#ifndef INTERFACE_FORMATEUR_H
#define INTERFACE_FORMATEUR_H
#include <QMainWindow>
#include "formateurs.h"
#include "service.h"
#include "formation2.h"


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

    //void on_pushButton_AFFICHER_FORMATEUR_clicked(); // Bouton Afficher FOORMATEUR

    //SELECTION DU TABLEAU FORMATEUR
    void onTableSelectionChanged();//const QItemSelection &selected,const QItemSelection &deselected);

    void on_pushButton_SupprimerFormateur_clicked(); // Bouton supprimer FORMATEUR

    void on_pushButton_RechercheFormateur_clicked();

    void on_pushButton_AjouterFormateur_clicked();

    void on_pushButton_ANNULER_5_clicked();

    void on_pushButton_modifierFormateur_clicked();

    //selection tableau service//
    //ajouteet afficher//
    void on_pushButton_AJOUTER_3_clicked();
    //supprimer  service //
    void on_pushButton_92_clicked();
    //recherche//
    void on_pushButton_89_clicked();
    //charger donner //
    void on_pushButton_90_clicked();
    //modification//
    void on_pushButton_ANNULER_7_clicked();
    //statistique//
    void on_pushButton_stat_13_clicked();
    void on_pushButton_ANNULER_3_clicked();
    //GESTION DES FORMATIONS//

    void on_pushButtonAjouter_clicked();



    void on_pushButtonModifier_clicked();

    void on_pushButtonsupprimer_clicked();
    void on_lineEditId_editingFinished();


    void on_pushButtonTrier_clicked();

private:
    Ui::interface_formateur *ui;
    MainWindow *menuPrincipal;     // pointeur vers le menu principal
    Formateur F; // POINTEUR ???
    int IDselection= -2;
    /****service***/
    service s;
    bool verife();
    bool cleardonner();
    //formation//
    formation2 F2;
    formation2 ftmp;
};

#endif // INTERFACE_FORMATEUR_H
