#ifndef INTERFACE_FORMATEUR_H
#define INTERFACE_FORMATEUR_H
#include "statistique.h"
//#include "rapport.h"
#include <QObject>
#include <QMainWindow>

namespace Ui {
class interface_formateur;
}

class interface_formateur : public QMainWindow
{
    Q_OBJECT

public:
    explicit interface_formateur(QWidget *parent = nullptr);
    ~interface_formateur();

private slots:
  //  void on_pushButton_stat_clicked(); //bouton statistique

    void on_pushButton_clicked();// bouton formateur dans menu_princ
    void on_pushButton_stat_2_clicked();

private:
    Ui::interface_formateur *ui;
    statistique *stat; // pointeur vers interface statistique
};

#endif // INTERFACE_FORMATEUR_H
