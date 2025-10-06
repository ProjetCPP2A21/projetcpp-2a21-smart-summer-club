#include "interface_employe.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Interface_employe w;
    w.show();
    return a.exec();
}
