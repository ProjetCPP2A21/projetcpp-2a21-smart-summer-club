#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
    fenetreGestion = nullptr;
}


Menu::~Menu()
{
    delete ui;
}



void Menu::on_pushButton_11_clicked()
{
    if (!fenetreGestion)   // créer la fenêtre seulement si elle n’existe pas déjà
        fenetreGestion = new gestion_employe(this);

    fenetreGestion->show();   // afficher la fenêtre
    this->hide();
}



