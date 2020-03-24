#ifndef DATA_H
#define DATA_H

#include <vector>
using namespace std;

#define T0VALUES 1
#define mVALUES 2
#define SIGMAVALUES 1

class Data
{
public:
    Data();
    double Ck = 150 * 10e-6;
    double Lk = 60 * 10e-6;
    double Rk = 0.5;
    double Uc0 = 1500;
    double I0 = 0.5;
};

const vector<vector<double>> ITm = { { 0.5, 1, 5, 10, 50, 200, 400, 800, 1200 },
                                     { 6400, 6790, 7150, 7270, 8010, 9185, 10010, 11140, 12010 },
                                     { 0.4, 0.55, 1.7, 3, 11, 32, 40, 41, 39} };
const vector<vector<double>> TSigma = { { 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000, 13000, 14000 },
                                        { 0.031, 0.27, 2.05, 6.06, 12.0, 19.9, 29.6, 41.1, 54.1, 67.7, 81.5 } };

const double R = 0.35; // радиус разрядной трубки
const double Tw = 2000;
const double Le = 12; // длина трубки


#endif // DATA_H
