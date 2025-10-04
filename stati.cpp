#include "stati.h"
#include "ui_stati.h"

stati::stati(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::stati)
{
    ui->setupUi(this);
}

stati::~stati()
{
    delete ui;
}
