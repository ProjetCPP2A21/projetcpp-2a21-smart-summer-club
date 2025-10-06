#include "interface_employe.h"
#include "ui_interface_employe.h"

Interface_employe::Interface_employe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Interface_employe)
{
    ui->setupUi(this);
}

Interface_employe::~Interface_employe()
{
    delete ui;
}
