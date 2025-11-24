#ifndef FORMATION_H
#define FORMATION_H

#include <QMainWindow>
#include <formation2.h>
#include "sendgridclient.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "arduino.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class formation;
}
QT_END_NAMESPACE

class formation : public QMainWindow
{
    Q_OBJECT

public:
    formation(QWidget *parent = nullptr);
    ~formation();

private slots:
    void on_pushButtonAjouter_clicked();

    void on_pushButtonsupprimer_clicked();
    //void onTableSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);


    void on_pushButtonModifier_clicked();

    void on_pushButtonTrier_clicked();
    void on_lineEditId_editingFinished();  // quand on finit d'écrire l'ID


    void on_pushButton_rechercher_clicked();
    void on_lineEdit_rechercher_textChanged(const QString &text);  // Quand on efface

    void on_pushButton_exporter_clicked();

    void on_pushButton_stat_clicked();



    void on_pushButton_47_clicked();
    void on_arduino_data();   // Quand Arduino envoie RFID
    void verifierCarte(QString);

private:
    Ui::formation *ui;
    formation2 F;
    formation2 ftmp;
    bool afficherclique = false;
    void clearInputs();
    SendGridClient sendgridClient;
    Arduino A;

};
#endif // FORMATION_H
