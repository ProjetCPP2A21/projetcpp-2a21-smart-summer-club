#include "service.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    service w;
    w.show();
    return a.exec();
}
