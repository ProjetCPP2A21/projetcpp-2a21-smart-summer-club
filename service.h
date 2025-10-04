#ifndef SERVICE_H
#define SERVICE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class service;
}
QT_END_NAMESPACE

class service : public QMainWindow
{
    Q_OBJECT

public:
    service(QWidget *parent = nullptr);
    ~service();

private slots:
    void on_pushButton_stat_13_clicked();

private:
    Ui::service *ui;
};
#endif // SERVICE_H
