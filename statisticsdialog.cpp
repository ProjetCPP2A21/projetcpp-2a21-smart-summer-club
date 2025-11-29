#include "statisticsdialog.h"
#include "ui_statisticsdialog.h"
#include "formateurs.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QLegend>
//using namespace QtCharts;

StatisticsDialog::StatisticsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StatisticsDialog)
{
    ui->setupUi(this);


    Formateur f;
    QMap<QString, int> stats = f.statistiquesSexe();

    // Création du graphique
    QPieSeries *series = new QPieSeries();
    series->append("Hommes", stats["Homme"]);
    series->append("Femmes", stats["Femme"]);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des formateurs selon le sexe");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->verticalLayout_2->addWidget(chartView);
}

StatisticsDialog::~StatisticsDialog()
{
    delete ui;
}
