#ifndef FORMATION_H
#define FORMATION_H

#include <QMainWindow>
#include <formation2.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class formation;
}
QT_END_NAMESPACE

class formation : public QMainWindow
{
    Q_OBJECT

public:
    formation(QWidget *parent = nullptr);
    ~formation();

private slots:
    void on_pushButtonAjouter_clicked();

private:
    Ui::formation *ui;
    formation2 ftmp;
};
#endif // FORMATION_H
