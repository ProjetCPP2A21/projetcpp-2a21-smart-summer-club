#ifndef GESTION_EMPLOYE_H
#define GESTION_EMPLOYE_H

#include <QMainWindow>
#include <QMessageBox>
#include "employe.h"

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>

//j'ajoute
//#include <QtPdf/QPdfWriter>
//#include <QPainter>




QT_BEGIN_NAMESPACE
namespace Ui {
class gestion_employe;
}
QT_END_NAMESPACE

class gestion_employe : public QMainWindow
{
    Q_OBJECT

public:
    explicit gestion_employe(QWidget *parent = nullptr);
    ~gestion_employe();

private slots:
    void on_btajouter_2_clicked();
    void on_btsupprimer_2_clicked();
    void on_bmodifier_2_clicked();

    void on_pushButton_cin_4_clicked();

    void clearFields();

    void on_btSearchEmail_2_clicked();
    void on_btTriDate_2_clicked();


    void afficherStatistiques();
    void on_btnStats_2_clicked();
//j'ajoute
    void exportWord();
    void exportPDF();



    void on_btnExportPDF_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_valider_mdp_clicked();
    void on_pushButton_se_connecter_clicked();











    QString validateFields(bool forAdd, bool forModify, bool forDelete) const ;





private:
    Ui::gestion_employe *ui;
    employe etmp; // ✅ plus d’erreur ici
};

#endif // GESTION_EMPLOYE_H
