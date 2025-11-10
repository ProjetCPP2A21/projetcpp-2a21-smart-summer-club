#ifndef APP_H
#define APP_H

#include <apprenant.h>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class app;
}
QT_END_NAMESPACE

class app : public QMainWindow
{
    Q_OBJECT

public:
    app(QWidget *parent = nullptr);
    ~app();


private slots:
    void on_pushButton_7_clicked();  // bouton qui ouvre interface apprenants

private:
    Ui::app *ui;
    apprenant *apprenant;  // pointeur vers la 4e fenêtre




};
#endif // MAINWINDOW_H
