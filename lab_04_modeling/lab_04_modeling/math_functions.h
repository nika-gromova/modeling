#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

#include <vector>
#include <math.h>

const double eps = 1e-3;

using namespace std;

class MathFunctions
{
public:
    void set_alpha0(const double _alpha0) { alpha0 = _alpha0; }
    void set_alphan(const double _alphaN) { alphaN = _alphaN; }
    void set_h(const double _h) { h = _h; h4 = h / 4; }
    void set_other(const double _len, const double _T0, const double _R, const double _F0) {
        len = _len; T0 = _T0; R = _R; F0 = _F0;
    }
    double get_len(void) {return len; }

    vector<vector<double>>calc_all_T(void);

private:
    double k(const double T) { return a1 * (b1 + c1 * pow(T, m1)); }
    double cap(const double T) { return a2 + b2 * pow(T, m2) - c2 / (T * T); }

    double alpha(const double x) { return c / (x - d); }
    double chi(const double T1, const double T2) {
        double k1 = k(T1); double k2 = k(T2);
        return 2 * k1 * k2 / (k1 + k2);
    }

    double p(const double x) { return 2 * alpha(x) / R; }
    double f(const double x) { return (2 * T0 * alpha(x)) / R; }

    void calc_left_boundary();
    void calc_right_boundary();

    void calc_coef();

    void calc_eta_ksi();

    vector<double> calc_y();

    double calc_diff(vector<double> prev, vector<double> cur);

    vector<double> calculate_T(double t);


private:
    int N;
    double a1 = 0.0134, b1 = 1, c1 = 4.35e-4, m1 = 1;
    double a2 = 2.049, b2 = 0.563e-3, c2 = 0.528e-5, m2 = 1;

    double h = 1e-4, h4 = 1e-4/ 4.0;

    double tau = 1e-1;

    double k0 = 0.4, kN = 0.1;
    double alpha0 = 0.05, alphaN = 0.01;
    double len = 10;
    double T0 = 300;
    double R = 0.5;
    double F0 = 50;

    double c, d;

    double K0, M0, P0;
    double KN, MN, PN;

    double yN;

    vector<double> eta;
    vector<double> ksi;

    vector<double> A, B, C, D;

    vector<double> prev_iteration;
    vector<double> prev_T;
};

#endif // MATH_FUNCTIONS_H
