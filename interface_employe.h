#ifndef INTERFACE_EMPLOYE_H
#define INTERFACE_EMPLOYE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Interface_employe;
}
QT_END_NAMESPACE

class Interface_employe : public QMainWindow
{
    Q_OBJECT

public:
    Interface_employe(QWidget *parent = nullptr);
    ~Interface_employe();

private:
    Ui::Interface_employe *ui;
};
#endif // INTERFACE_EMPLOYE_H
