#ifndef FORMATION_H
#define FORMATION_H

#include <QMainWindow>
#include <formation2.h>

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





private:
    Ui::formation *ui;
    formation2 F;
    formation2 ftmp;
    bool afficherclique = false;

};
#endif // FORMATION_H
