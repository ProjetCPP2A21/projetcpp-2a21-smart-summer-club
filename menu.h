#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include "gestion_employe.h"

namespace Ui {
class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:

    void on_pushButton_11_clicked(); //bouton gestion_employé

private:
    Ui::Menu *ui;
    gestion_employe *fenetreGestion;

};

#endif // MENU_H
