#ifndef APPRENANT_H
#define APPRENANT_H

#include <QWidget>
#include <QObject>
#include <QMainWindow>

#include <QDialog>

namespace Ui {
class apprenant;
}

class apprenant : public QWidget
{
    Q_OBJECT

public:
    explicit apprenant(QWidget *parent = nullptr);
    ~apprenant();

private:
    Ui::apprenant *ui;
};

#endif // APP_H
