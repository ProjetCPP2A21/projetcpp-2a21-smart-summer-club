#ifndef STATISTIC_H
#define STATISTIC_H
#include <QDialog>
#include <QPainter>
#include <QSqlQuery>
#include <QMap>

namespace Ui {
class Statistic;
}

class Statistic : public QDialog
{
    Q_OBJECT

public:
    explicit Statistic(QWidget *parent = nullptr);
    ~Statistic();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::Statistic *ui;

    QMap<int,int> stats;     // capacité → nombre de formations
    void loadData();         // charge depuis BD
};

#endif // STATISTIC_H
