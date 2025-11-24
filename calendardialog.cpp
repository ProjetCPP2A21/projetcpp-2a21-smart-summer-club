#include "calendardialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QSqlQuery>
#include <QTextCharFormat>
#include <QSqlError>
#include <QDebug>
#include <QTableView>
#include <QToolTip>
#include <QCursor>
#include <QEvent>

CalendarDialog::CalendarDialog(QWidget *parent)
    : QDialog(parent),
      calendar(new QCalendarWidget(this)),
      listWidget(new QListWidget(this))
{
    setWindowTitle(tr("Calendrier des formations"));
    resize(500, 450);
    setStyleSheet("background-color: white;");

    calendar->setGridVisible(true);
    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    calendar->setStyleSheet("background-color: white;");

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(calendar);

    auto *label = new QLabel(tr("Formations prévues pour la date sélectionnée :"), this);
    label->setStyleSheet("background-color: white;");
    layout->addWidget(label);

    listWidget->setStyleSheet("background-color: white;");
    layout->addWidget(listWidget);

    loadData();
    setupCalendarHover();
    connect(calendar, &QCalendarWidget::selectionChanged,
            this, &CalendarDialog::refreshSelection);

    if (calendar->selectedDate().isValid())
        refreshSelection();
}

void CalendarDialog::loadData()
{
    formationsByDate.clear();
    QSqlQuery query("SELECT DATEFORMATION, NOM FROM FORMATION");

    while (query.next())
    {
        QDate date = query.value(0).toDate();
        QString nom = query.value(1).toString();

        if (!date.isValid())
            continue;

        formationsByDate[date].append(nom);
    }

    QTextCharFormat fmt;
    fmt.setBackground(QColor("#FFE082"));
    fmt.setFontWeight(QFont::Bold);

    for (auto it = formationsByDate.cbegin(); it != formationsByDate.cend(); ++it)
    {
        calendar->setDateTextFormat(it.key(), fmt);
    }
}

void CalendarDialog::refreshSelection()
{
    listWidget->clear();
    QDate date = calendar->selectedDate();
    const auto formations = formationsByDate.value(date);

    if (formations.isEmpty())
    {
        listWidget->addItem(tr("Aucune formation programmée."));
        return;
    }

    for (const QString &nom : formations)
    {
        listWidget->addItem(nom);
    }
}

void CalendarDialog::setupCalendarHover()
{
    calendarView = calendar->findChild<QTableView*>("qt_calendar_calendarview");
    if (!calendarView)
        return;

    calendarView->setMouseTracking(true);
    calendarView->viewport()->setMouseTracking(true);

    connect(calendarView, &QTableView::entered, this, [this](const QModelIndex &index){
        QDate date = index.data(Qt::UserRole).toDate();
        if (!date.isValid())
        {
            QToolTip::hideText();
            return;
        }

        const auto formations = formationsByDate.value(date);
        if (formations.isEmpty())
        {
            QToolTip::hideText();
            return;
        }

        QToolTip::showText(QCursor::pos(), formations.join("\n"), calendarView);
    });

    calendarView->viewport()->installEventFilter(this);
}

bool CalendarDialog::eventFilter(QObject *watched, QEvent *event)
{
    if (calendarView && watched == calendarView->viewport())
    {
        if (event->type() == QEvent::Leave)
        {
            QToolTip::hideText();
        }
    }
    return QDialog::eventFilter(watched, event);
}



