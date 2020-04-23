#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <math.h>
#include <thread>


using namespace std;

void calc_2(Calculator *calc, double delta, vector<QLineSeries *> &result)
{
    vector<vector<double>> res = calc->calculate(delta, 1);
    for (size_t i = 0; i <res[0].size(); i++)
    {
        result[0]->append(res[TIME][i], res[CURRENT][i]);
        result[1]->append(res[TIME][i], res[VOLTAGE][i]);
        result[2]->append(res[TIME][i], res[RESISTANCE][i]);
        result[3]->append(res[TIME][i], res[CURRES][i]);
    }
}

void calc_4(Calculator *calc, double delta, vector<QLineSeries *> &result)
{
    vector<vector<double>> res = calc->calculate(delta, 0);
    for (size_t i = 0; i <res[0].size(); i++)
    {
        result[4]->append(res[TIME][i], res[CURRENT][i]);
        result[5]->append(res[TIME][i], res[VOLTAGE][i]);
        result[6]->append(res[TIME][i], res[RESISTANCE][i]);
        result[7]->append(res[TIME][i], res[CURRES][i]);
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), d_validator(this)
{
    ui->setupUi(this);

    ui->Ck_edit->setValidator(&d_validator);
    ui->Rk_edit->setValidator(&d_validator);
    ui->Lk_edit->setValidator(&d_validator);
    ui->I0_edit->setValidator(&d_validator);
    ui->Uc0_edit->setValidator(&d_validator);
    ui->dt_edit->setValidator(&d_validator);


    delta = 1e-6;

    create_charts();
    run_calculations();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::run_calculations()
{
    std::thread runge2(calc_2, &calc, delta, std::ref(plots));
    std::thread runge4(calc_4, &calc, delta, std::ref(plots));

    runge2.join();
    runge4.join();

    for (size_t i = 0; i < charts.size(); i++)
    {
        plots[i]->setName("2 порядок");
        plots[i + 4]->setName("4 порядок");
        charts[i]->addSeries(plots[i]);
        charts[i]->addSeries(plots[i + 4]);
        charts[i]->createDefaultAxes();
    }

    ui->chart_tI->setChart(charts[0]);
    ui->chart_tU->setChart(charts[1]);
    ui->chart_tR->setChart(charts[2]);
    ui->chart_tIR->setChart(charts[3]);
}

void MainWindow::clear_charts()
{
    plots.clear();
    charts.clear();
}

void MainWindow::create_charts()
{
    for (auto i = 0; i < 4; i++)
    {
        QChart *chart = new QChart();
        charts.push_back(chart);
    }

    charts[0]->setTitle("I(t)");
    charts[1]->setTitle("Uc(t)");
    charts[2]->setTitle("Rp(t)");
    charts[3]->setTitle("I*Rp(t)");

    for (auto i = 0; i < 8; i++)
    {
        QLineSeries *series = new QLineSeries();
        plots.push_back(series);
    }
}


void MainWindow::on_calculate_button_clicked()
{

    QString _Ck = ui->Ck_edit->text();
    if (!_Ck.isEmpty())
        calc.set_Ck((_Ck.replace(",", ".")).toDouble());
    QString _Lk = ui->Lk_edit->text();
    if (!_Lk.isEmpty())
        calc.set_Lk((_Lk.replace(",", ".")).toDouble());
    QString _Rk = ui->Rk_edit->text();
    if (!_Rk.isEmpty())
        calc.set_Rk((_Rk.replace(",", ".")).toDouble());
    QString _I0 = ui->I0_edit->text();
    if (!_I0.isEmpty())
        calc.set_I0((_I0.replace(",", ".")).toDouble());
    QString _Uc0 = ui->Uc0_edit->text();
    if (!_Uc0.isEmpty())
        calc.set_Uc0((_Uc0.replace(",", ".")).toDouble());
    QString _dt= ui->dt_edit->text();
    if (!_dt.isEmpty())
        delta = (_dt.replace(",", ".")).toDouble();

    clear_charts();
    create_charts();
    run_calculations();
}
