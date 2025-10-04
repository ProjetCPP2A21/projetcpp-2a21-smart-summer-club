#include "service.h"
#include "ui_service.h"
#include "stati.h"

service::service(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::service)
{
    ui->setupUi(this);
}

service::~service()
{
    delete ui;
}

void service::on_pushButton_stat_13_clicked()
{
    stati *s=new stati();
    s->show();
}

