#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "service.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //ajouter//
    void on_button_ajouter_clicked();
    //recherche//
    void on_pushButton_89_clicked();
    //supprimer//
    void on_pushButton_91_clicked();
    //modifier//
    void on_pushButton_88_clicked();
    //save modification
    void on_pushButton_ANNULER_4_clicked();



private:
    Ui::MainWindow *ui;
    service s;
    bool verife();
};

#endif // MAINWINDOW_H
