#include "app.h"
#include "ui_app.h"
#include "apprenant.h"

app::app(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::app)
{
    ui->setupUi(this);
    apprenant = new class apprenant(); // création fenêtre apprenant
}

app::~app()
{
    delete ui;
}

void app::on_pushButton_7_clicked()
{
    apprenant->show();  // quand je clique, la 4e fenêtre s'affiche
    this->hide();  // cacher la fenêtre principale
}

