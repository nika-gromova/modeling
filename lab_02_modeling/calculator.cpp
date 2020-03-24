#include "calculator.h"
#include <math.h>
#include <functional>


Calculator::Calculator()
{

}

vector<vector<double>> Calculator::calculate(const double deltat, const bool RK2)
{
    vector<double> voltage; //Uc
    vector<double> current; // I
    vector<double> resistance; //Rp
    vector<double> IRp;
    vector<double> time; // t

    voltage.push_back(data.Uc0);
    current.push_back(data.I0);
    resistance.push_back(calc_Rp(data.I0));
    time.push_back(0);

    double cur_I = data.I0;
    double cur_Uc = data.Uc0;
    double cur_Rp;


    auto method = (RK2) ? (runge2) : (runge4);

    for (double i = deltat; i <= PULSE_TIME; i += deltat)
    {

        cur_Rp = calc_Rp(cur_I);
        vector<double> tmp = method(i, cur_I, cur_Uc,  deltat,
                                    [cur_Rp, this](const double z, const vector<double> args){return (args[1] - (data.Rk + cur_Rp) * args[0]) / data.Lk;},
                                    [this](const double z, const vector<double> args){return (- args[0]) / data.Ck;});
        cur_I = tmp[0];
        cur_Uc = tmp[1];

        time.push_back(i);
        voltage.push_back(cur_Uc);
        current.push_back(cur_I);
        resistance.push_back(cur_Rp);
        IRp.push_back(cur_I * cur_Rp);

    }
    return { time, voltage, current, resistance, IRp };
}
