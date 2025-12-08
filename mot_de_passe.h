#ifndef MOT_DE_PASSE_H
#define MOT_DE_PASSE_H

#include <QMainWindow>

namespace Ui {
class mot_de_passe;
}

class mot_de_passe : public QMainWindow
{
    Q_OBJECT

public:
    explicit mot_de_passe(QWidget *parent = nullptr);
    ~mot_de_passe();

private:
    Ui::mot_de_passe *ui;
};

#endif // MOT_DE_PASSE_H
