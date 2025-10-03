#include "apprenant.h"
#include "ui_apprenant.h"

apprenant::apprenant(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::apprenant)
{
    ui->setupUi(this);
}

apprenant::~apprenant()
{
    delete ui;
}
