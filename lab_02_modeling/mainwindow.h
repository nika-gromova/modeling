#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleValidator>
#include <QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
using namespace QtCharts;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


#include "mathfunctions.h"
#include "data.h"
#include "calculator.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_calculate_button_clicked();

private:
    void run_calculations(void);
    void clear_charts(void);
    void create_charts(void);

private:
    Ui::MainWindow *ui;
    QDoubleValidator d_validator;

    Calculator calc;
    double delta;

    vector<QChart *> charts;
    vector<QLineSeries *> plots;
};
#endif // MAINWINDOW_H
