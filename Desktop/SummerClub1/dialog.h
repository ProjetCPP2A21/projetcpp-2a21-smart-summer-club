#ifndef DIALOG_H
#define DIALOG_H
#include "formation.h"
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    void setFormation(Formation f);
    ~Dialog();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
