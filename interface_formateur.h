#ifndef INTERFACE_FORMATEUR_H
#define INTERFACE_FORMATEUR_H
#include <QMainWindow>
#include "formateurs.h"
#include "service.h"
#include "formation2.h"
#include "employe.h"
#include "equipement.h"
#include "apprenant.h"

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



    void on_pushButton_service_clicked();

    void on_pushButton_apprenant_clicked();

    void on_pushButton_equipement_clicked();


//-----------------DEBUT_BOUTONS_FORMATEUR------------------------------
    void on_pushButton_AJOUTER_5_clicked(); // Ajout
    void on_pushButton_AjouterFormateur_clicked(); //INIT
    void on_pushButton_ANNULER_5_clicked();

    void on_pushButton_modifierFormateur_clicked();
    void on_pushButton_SupprimerFormateur_clicked();

    void onTableSelectionChanged();
    void on_pushButton_listeformateur_clicked();

    void on_pushButton_RechercheFormateur_clicked();
    void on_pushButton_TRIER_FORMATEUR_clicked();
    void on_on_pushButton_stat_formateur_clicked();
    void on_pushButton_PDF_formateur_clicked();
//-----------------FIN_BOUTONS_FORMATEUR------------------------------


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



    //employe
    void on_btajouter_clicked();
    void on_btsupprimer_clicked();
    void on_bmodifier_clicked();

    void on_pushButton_cin_3_clicked();

    void clearFields();

    QString validateFields(bool forAdd, bool forModify, bool forDelete) const;
    //crud equipement
    void on_pushButton_AjouterEquipement_clicked();
    void on_pushButton_SupprimerEquipement_clicked();
    void on_pushButton_modifierEquipement_clicked();
    void on_pushButton_rechercherEquipement();
    // Apprenant buttons
    void on_pushButton_AJOUTER_6_clicked();
    void on_pushButton_ANNULER_6_clicked();
    void on_pushButton_19_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_20_clicked();
    void on_lineEdit_RECHERCHE_2_returnPressed();
    void onApprenantTableSelectionChanged();
    void on_lineEdit_RECHERCHE_2_textChanged(const QString &text);

    void on_ajouterEquipement_clicked();



private:
    Ui::interface_formateur *ui;
    // pointeur vers menu principal
    MainWindow *menuPrincipal;


//--------FORMATEUR-----------------
    Formateur F;
    Formateur F1;
    int IDselection= -2;
//--------FORMATEUR-----------------


    /****service***/
    service s;
    bool verife();
    bool cleardonner();

    //formation//
    formation2 F2;
    formation2 ftmp;
    employe etmp; // pointeur ok avec forward declaration
    Equipement E;
    apprenant a;
};

#endif // INTERFACE_FORMATEUR_H
