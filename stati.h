#ifndef STATI_H
#define STATI_H

#include <QMainWindow>

namespace Ui {
class stati;
}

class stati : public QMainWindow
{
    Q_OBJECT

public:
    explicit stati(QWidget *parent = nullptr);
    ~stati();

private:
    Ui::stati *ui;
};

#endif // STATI_H
