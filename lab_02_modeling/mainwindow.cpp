#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <QChart>
#include <QLineSeries>
#include <thread>

using namespace std;

void calc_2(Calculator *calc, double delta, vector<QLineSeries *> &result)
{
    vector<vector<double>> res = calc->calculate(delta, 1);
    for (size_t i = 0; i <res[0].size(); i++)
    {
        *(result[0]) << QPointF(res[TIME][i], res[CURRENT][i]);
        *(result[1]) << QPointF(res[TIME][i], res[VOLTAGE][i]);
        *(result[2]) << QPointF(res[TIME][i], res[RESISTANCE][i]);
        *(result[3]) << QPointF(res[TIME][i], res[CURRES][i]);
    }
}

void calc_4(Calculator *calc, double delta, vector<QLineSeries *> &result)
{
    vector<vector<double>> res = calc->calculate(delta, 0);
    for (size_t i = 0; i <res[0].size(); i++)
    {
        *(result[4]) << QPointF(res[TIME][i], res[CURRENT][i]);
        *(result[5]) << QPointF(res[TIME][i], res[VOLTAGE][i]);
        *(result[6]) << QPointF(res[TIME][i], res[RESISTANCE][i]);
        *(result[7]) << QPointF(res[TIME][i], res[CURRES][i]);
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QChart *chart = new QChart();

    vector<QLineSeries *> plots;
    for (auto i = 0; i < 8; i++)
    {
        QLineSeries *series = new QLineSeries();
        plots.push_back(series);
    }

    double delta = 1e-7;
    std::thread runge2(calc_2, &calc, delta, std::ref(plots));
    std::thread runge4(calc_4, &calc, delta, std::ref(plots));

    runge2.join();
    runge4.join();

    chart->addSeries(plots[0]);
    ui->chart_tI->setChart(chart);
}

MainWindow::~MainWindow()
{
    delete ui;
}

