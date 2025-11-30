#include "statistic.h"
#include "ui_statistic.h"

Statistic::Statistic(QWidget *parent)
    : QDialog(parent), ui(new Ui::Statistic)
{
    ui->setupUi(this);
    loadData();
}

Statistic::~Statistic()
{
    delete ui;
}

void Statistic::loadData()
{
    stats.clear();

    QSqlQuery query("SELECT capacite FROM formation");

    while (query.next()) {
        int cap = query.value(0).toInt();
        stats[cap]++;
    }
}

void Statistic::paintEvent(QPaintEvent *)
{
    if (stats.isEmpty()) return;

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // -----------------------------------------------------
    //  CAMEMBERT
    // -----------------------------------------------------

    QRectF rect(40, 40, 350, 350);

    int total = 0;
    for (auto v : stats.values()) total += v;

    int start = 0;

    // Couleurs modernes type Google Charts
    QVector<QColor> colors = {
        QColor("#FF6384"),   // Rose
        QColor("#FFCD56"),   // Jaune
        QColor("#4BC0C0"),   // Turquoise
        QColor("#36A2EB"),   // Bleu clair
        QColor("#9966FF"),   // Violet
        QColor("#4CAF50"),   // Vert
        QColor("#F77825")    // Orange
    };

    int i = 0;

    // -----------------------------------------------------
    //  DESSIN DES TRANCHES
    // -----------------------------------------------------
    for (int cap : stats.keys())
    {
        int count = stats[cap];
        int angle = int((count / (double)total) * 360 * 16);

        p.setBrush(colors[i % colors.size()]);
        p.drawPie(rect, start, angle);

        start += angle;
        i++;
    }

    // -----------------------------------------------------
    //  LÉGENDE À DROITE
    // -----------------------------------------------------

    int xLegend = 430;
    int yLegend = 80;

    p.setPen(Qt::black);
    p.setFont(QFont("Segoe UI", 10));

    i = 0;
    for (int cap : stats.keys())
    {
        // Petit carré couleur
        p.setBrush(colors[i % colors.size()]);
        p.drawRect(xLegend, yLegend + i * 30, 20, 20);

        // Texte de la légende
        QString text = QString("Capacité %1 : %2 formations")
                           .arg(cap)
                           .arg(stats[cap]);

        p.drawText(xLegend + 30, yLegend + 15 + i * 30, text);

        i++;
    }
}
