#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

#include <vector>

using namespace std;

class MathFunctions
{
public:
    void set_k0(const double _k0) { k0 = _k0; }
    void set_kn(const double _kN) { kN = _kN; }
    void set_alpha0(const double _alpha0) { alpha0 = _alpha0; }
    void set_alphan(const double _alphaN) { alphaN = _alphaN; }
    void set_h(const double _h) { h = _h; h2 = h * h; }
    void set_other(const double _len, const double _T0, const double _R, const double _F0) {
        len = _len; T0 = _T0; R = _R; F0 = _F0;
    }
    double get_len(void) {return len; }

    vector<double> calculate_T(void);

private:
    double k(const double x) { return a / (x - b); }
    double alpha(const double x) { return c / (x - d); }
    double chi(const double x1, const double x2) {
        double k1 = k(x1); double k2 = k(x2);
        return 2 * k1 * k2 / (k1 + k2);
    }

    double p(const double x) { return 2 * alpha(x) / R; }
    double f(const double x) { return (2 * T0 * alpha(x)) / R; }

    void calc_left_boundary();
    void calc_right_boundary();

    void calc_coef();

    void calc_eta_ksi();

    void calc_y();

private:
    int N;
    double h = 0.1;
    double h2 = 0.01;
    double k0 = 0.4, kN = 0.1;
    double alpha0 = 0.05, alphaN = 0.01;
    double len = 10;
    double T0 = 300;
    double R = 0.5;
    double F0 = 50;

    double a, b, c, d;

    double K0, M0, P0;
    double KN, MN, PN;

    double yN;

    vector<double> eta;
    vector<double> ksi;
    vector<double> y;

    vector<double> A, B, C, D;
};

#endif // MATH_FUNCTIONS_H
