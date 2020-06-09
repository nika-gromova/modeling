#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

const double step = 0.1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->edit_a0->setValidator(&d_validator);
    ui->edit_an->setValidator(&d_validator);
    ui->edit_len->setValidator(&d_validator);
    ui->edit_R->setValidator(&d_validator);
    ui->edit_T0->setValidator(&d_validator);
    ui->edit_F0->setValidator(&d_validator);

    ui->edit_a0->setText("0,05");
    ui->edit_an->setText("0,01");
    ui->edit_len->setText("10");
    ui->edit_T0->setText("300");
    ui->edit_R->setText("0,5");
    ui->edit_F0->setText("50");

    calculate();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calculate_button_clicked()
{
    chart->removeAllSeries();
    series.clear();

    QString _a0 = ui->edit_a0->text();
    QString _aN = ui->edit_an->text();
    if (!_a0.isEmpty())
        _math.set_alpha0((_a0.replace(",", ".")).toDouble());
    if (!_aN.isEmpty())
        _math.set_alphan((_aN.replace(",", ".")).toDouble());

    QString _len = ui->edit_len->text(), _F0 = ui->edit_F0->text();
    QString _T0 = ui->edit_T0->text(), _R = ui->edit_R->text();
    double len = (_len.replace(",", ".")).toDouble();
    double F0 = (_F0.replace(",", ".")).toDouble();
    double T0 = (_T0.replace(",", ".")).toDouble();
    double R = (_R.replace(",", ".")).toDouble();
    _math.set_other(len, T0, R, F0);
    _math.set_h(step);

    calculate();
}

void MainWindow::calculate()
{
    ui->plot_widget->setRenderHint(QPainter::Antialiasing);
    vector<vector<double>> res = _math.calc_all_T();
    cout << res.size() << endl;
    cout << res[0].size() << endl;

    chart = new QChart();
    chart->setTitle("График температурного поля");
    chart->legend()->setVisible(false);
    double tau = 1e-1;

    for (auto i = 0; i < res[0].size(); i++)
    {
        if (i % 50 == 0)
        {
            QLineSeries *plot = new QLineSeries();

            for (auto j = 0; j < res.size(); j++)
            {
                plot->append(j * tau, res[j][i]);
            }
            series.push_back(plot);
        }
    }

    /*
    for (auto i = 0; i < res.size(); i++)
    {
        double x = 0;
        QLineSeries *plot = new QLineSeries();

        for (auto j = 0; j < res[i].size(); j++)
        {
            plot->append(x, res[i][j]);
            x += step;
        }
        series.push_back(plot);
    }
    */

    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("t, c");
    axisX->setRange(0, 30);


    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("T, K");
    axisY->setRange(300, 1100);


    for (auto i = 0; i < series.size(); i++)
    {
        chart->addSeries(series[i]);
        chart->setAxisX(axisX, series[i]);
        chart->setAxisY(axisY, series[i]);
    }
    ///chart->createDefaultAxes();
    ui->plot_widget->setChart(chart);
}
