#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleValidator>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>

#include "math_functions.h"
using namespace QtCharts;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_calculate_button_clicked();

private:
    void calculate(void);

private:
    Ui::MainWindow *ui;
    QDoubleValidator d_validator;
    QChart *chart;
    vector<QLineSeries *> series;

    MathFunctions _math;
};

#endif // MAINWINDOW_H
