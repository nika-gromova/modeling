#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "data.h"
#include "mathfunctions.h"

#define TIME 0
#define VOLTAGE 1
#define CURRENT 2
#define RESISTANCE 3
#define CURRES 4

const double PULSE_TIME = 0.03;


class Calculator
{
public:
    Calculator();

    vector<vector<double>> calculate(const double deltat, const bool RK2); //RK2 == true ? (runge 2) : (runge 4)

    void set_I0(const double I0) { data.I0 = I0; }
    void set_Uc0(const double Uc0) { data.Uc0 = Uc0; }
    void set_Ck(const double Ck) { data.Ck = Ck; }
    void set_Lk(const double Lk) { data.Lk = Lk; }
    void set_Rk(const double Rk) { data.Rk = Rk; }

private:
    Data data;

};

#endif // CALCULATOR_H
