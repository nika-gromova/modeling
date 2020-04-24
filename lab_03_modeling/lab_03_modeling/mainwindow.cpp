#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

const double step = 0.1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->edit_k0->setValidator(&d_validator);
    ui->edit_kn->setValidator(&d_validator);
    ui->edit_a0->setValidator(&d_validator);
    ui->edit_an->setValidator(&d_validator);
    ui->edit_len->setValidator(&d_validator);
    ui->edit_R->setValidator(&d_validator);
    ui->edit_T0->setValidator(&d_validator);
    ui->edit_F0->setValidator(&d_validator);

    ui->edit_k0->setText("0,4");
    ui->edit_kn->setText("0,1");
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
    //series->clear();
    chart->removeAllSeries();

    QString _k0 = ui->edit_k0->text();
    QString _kN = ui->edit_kn->text();
    if (!_k0.isEmpty())
        _math.set_k0((_k0.replace(",", ".")).toDouble());
    if (!_kN.isEmpty())
        _math.set_kn((_kN.replace(",", ".")).toDouble());

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
    vector<double> res = _math.calculate_T();

    chart = new QChart();
    chart->setTitle("T(x)");
    chart->legend()->setVisible(false);

    series = new QLineSeries();

    double x = 0;
    for (auto i = 0; i < res.size(); i ++)
    {
        series->append(x, res[i]);
        x += step;
        cout << i << ". " << x << " " << res[i] << endl;
    }
    chart->addSeries(series);

    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, _math.get_len() + 1);
    axisX->setTitleText("x");

    // double tmp = *max_element(res.begin(), res.end());
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 500);
    axisY->setTitleText("T(x)");


    chart->setAxisX(axisX, series);
    chart->setAxisY(axisY, series);
    ui->plot_widget->setChart(chart);
}
