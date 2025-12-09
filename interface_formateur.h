#ifndef INTERFACE_FORMATEUR_H
#define INTERFACE_FORMATEUR_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QBrush>
#include <QColor>
#include <QModelIndex>
#include <QTextBrowser>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextBrowser>
#include <QPushButton>
#include <QPrinter>
#include <QTextDocument>
#include <QFileDialog>
#include <QStandardPaths>
#include <QFileInfo>
#include <QPageSize>

#include "arduino.h"
#include "formateurs.h"
#include "service.h"
#include "formation2.h"
#include "employe.h"
#include "equipement.h"
#include "apprenant.h"
#include "sendgridclient.h"
#include "sms.h"

class MainWindow;

/* ============================
        ColorSqlModel
   ============================ */

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
            QString e = etat.toLower().trimmed();

            if (e.contains("dispon"))
                return QBrush(QColor(144, 238, 144)); // vert

            if (e.contains("panne") || e.contains("pan") || e.contains("pann"))
                return QBrush(QColor(255, 120, 120)); // rouge

            if (e.contains("reserv"))
                return QBrush(QColor(255, 255, 153)); // jaune
        }

        return QSqlQueryModel::data(index, role);
    }
};

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

    // === BOUTONS MENU PRINCIPAL ===
    void on_pushButton_clicked();
    void on_pushButton_retour_menu_clicked();
    void on_pushButton_employe_clicked();
    void on_pushButton_formateur_clicked();
    void on_pushButton_formation_clicked();
    void on_pushButton_stat_6_clicked();
    void on_pushButton_stat_4_clicked();
    void on_pushButton_stat_2_clicked();
    void on_pushButton_service_clicked();
    void on_pushButton_apprenant_clicked();
    void on_pushButton_equipement_clicked();

    // === FORMATEUR ===
    void on_pushButton_AJOUTER_5_clicked();
    void on_pushButton_AjouterFormateur_clicked();
    void on_pushButton_ANNULER_5_clicked();
    void on_pushButton_modifierFormateur_clicked();
    void on_pushButton_SupprimerFormateur_clicked();
    void onTableSelectionChanged();
    void on_pushButton_listeformateur_2_clicked();
    void on_pushButton_TRIER_FORMATEUR_2_clicked();
    void on_pushButton_RechercheFormateur_clicked();
    void on_pushButton_stat_formateur_clicked();
    void on_pushButton_PDF_formateur_2_clicked();
    void on_pushButton_retour_clicked();
    void on_pushButton_Envoyer_message_clicked();
    void onSmsSent();
    void onSmsError(QString err);
    void on_pushButton_SMS_clicked();
    void on_pushButton_QRcode_clicked();
    void lireBufferArduino();       // Slot pour lire le code envoyé par Arduino
    void verifierIdTFT(const QString &code); // Vérifie ID dans Oracle

    // === SERVICE ===
    void on_pushButton_AJOUTER_3_clicked();
    void on_pushButton_92_clicked();
    void on_pushButton_89_clicked();
    void on_pushButton_90_clicked();
    void on_pushButton_ANNULER_7_clicked();
    void on_pushButton_stat_13_clicked();
    void on_pushButton_ANNULER_3_clicked();

    // === FORMATION ===
    void on_pushButtonAjouter_clicked();
    void on_pushButtonModifier_clicked();
    void on_pushButtonsupprimer_clicked();
    void on_pushButtonTrier_clicked();
    void on_lineEditId_editingFinished();
    void on_pushButton_rechercher_clicked();
    void on_lineEdit_rechercher_textChanged(const QString &text);
    void on_pushButton_stat_clicked();

    // === EMPLOYE ===
    void on_btajouter_clicked();
    void on_btsupprimer_clicked();
    void on_bmodifier_clicked();
    void on_pushButton_cin_3_clicked();
    void clearFields();
    QString validateFields(bool forAdd, bool forModify, bool forDelete) const;

    // === EQUIPEMENT ===
    void on_SupprimerEquipement_clicked();
    void on_ModifierEquipement_clicked();
    void clearFieldsEquipement();
    void on_EquipementTable_clicked(const QModelIndex &index);
    void on_ajouterEquipement_clicked();
    void on_rechercherEquipement_clicked();
    void on_pushButton_86_clicked();
    void on_pushButton_87_clicked();
    void on_pushButton_91_clicked();

    // Équipement - méthodes supplémentaires de MainWindow
    void on_RechercheEquipement_textChanged(const QString &text);
    void on_RechercheEquipement_focusIn();
    void on_RechercheEquipement_focusOut();
    void on_pushButton_23_clicked();
    void on_pushButton_stat_8_clicked();
    void on_pushButton_stat_7_clicked();
    void on_ficheTechnique_clicked();

    // === APPRENANT ===
    void on_pushButton_AJOUTER_6_clicked();
    void on_pushButton_ANNULER_6_clicked();
    void on_pushButton_19_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_20_clicked();
    void on_lineEdit_RECHERCHE_2_returnPressed();
    void on_lineEdit_RECHERCHE_2_textChanged(const QString &text);
    void onApprenantTableSelectionChanged();

    // === GROUPE ===
    void onGroupeAAfficher(QSqlQueryModel *model);

    void on_pushButton_47_clicked();
    void on_pushButton_42_clicked();
    //Arduino
    void update_rfid();
    //arduino apprenant
    void readArduinoData();


private:
    Ui::interface_formateur *ui;
    MainWindow *menuPrincipal;

    // --- formateur
    Formateur F, F1;
    int IDselection = -2;
    SmsSender *smsSender;
    //Connexion------------
    QByteArray data;
    Arduino B;
    QSerialPort *arduinoSerial;
    Arduino arduino;

    service s;

    formation2 F2, ftmp;
    Arduino A;
    bool afficherclique = false;
    void clearInputs();
    SendGridClient sendgridClient;

    employe etmp;
    apprenant a;

    // === EQUIPEMENT ===
    equipementC e;
    ColorSqlModel *colorModel;
    bool recherchePlaceholderActive;

    // Service validation method
    bool verife();
};

#endif // INTERFACE_FORMATEUR_H
