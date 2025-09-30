#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void on_pushButtonAjouter_clicked();
    void on_pushButtonsupprimer_clicked();
    void on_pushButtonSauvegarder_clicked();
    void on_pushButtonModifier_clicked();
    void on_pushButtonTrier_clicked();



private:
    Ui::MainWindow *ui;
    void initTable();
    void clearInputs();
    bool validateInputs(QString &errMsg);
};
#endif // MAINWINDOW_H
