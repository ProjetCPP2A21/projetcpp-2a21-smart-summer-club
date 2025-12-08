#ifndef CALENDARDIALOG_H
#define CALENDARDIALOG_H

#include <QDialog>
#include <QCalendarWidget>
#include <QListWidget>
#include <QMap>
#include <QDate>
#include <QTableView>

class CalendarDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CalendarDialog(QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    QCalendarWidget *calendar;
    QListWidget *listWidget;
    QTableView *calendarView = nullptr;
    QMap<QDate, QStringList> formationsByDate;

    void loadData();//charge les données
    void refreshSelection();//met à jour l’affichage quand l’utilisateur sélectionne une date
    void setupCalendarHover();//configure le comportement lors du survol du calendrier
};

#endif // CALENDARDIALOG_H


