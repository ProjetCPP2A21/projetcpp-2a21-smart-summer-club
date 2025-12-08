#include "mot_de_passe.h"
#include "ui_mot_de_passe.h"

mot_de_passe::mot_de_passe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mot_de_passe)
{
    ui->setupUi(this);
}

mot_de_passe::~mot_de_passe()
{
    delete ui;
}
