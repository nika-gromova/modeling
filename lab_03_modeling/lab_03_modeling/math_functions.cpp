#include "math_functions.h"
#include <math.h>

vector<double> MathFunctions::calculate_T()
{
    b = (kN * len) / (kN - k0);
    a = k0 * (-b);
    d = (alphaN * len) / (alphaN - alpha0);
    c = alpha0 * (-d);
    calc_left_boundary();
    calc_right_boundary();
    calc_coef();
    calc_eta_ksi();
    calc_y();
    return y;
}

void MathFunctions::calc_left_boundary()
{
    double chi12 = chi(0, h);
    double p0 = p(0);
    double p1 = p(h);
    double f0 = f(0);
    double f1 = f(h);
    double p12 = (p1 + p0) / 2.0;
    double f12 = (f1 + f0) / 2.0;
    K0 = chi12 + h2 * p12 / 8 + h2 * p0 / 4;
    M0 = h2 * p12 / 8 - chi12;
    P0 = h * F0 + (h2 * (f12 + f0)) / 4;
}

void MathFunctions::calc_right_boundary()
{
    double chiN12 = chi(len, len - h);
    double pN = p(len);
    double pN1 = p(len - h);
    double fN = f(len);
    double fN1 = f(len - h);

    KN = (-chiN12) - alphaN * h - pN * h2 / 4 - (pN + pN1) * h2 / 16;
    MN = chiN12 - (pN + pN1) * h2 / 16;
    PN = (-alphaN * h * T0) - (h2 * (fN + (fN + fN1) / 2)) / 4;
}

void MathFunctions::calc_coef()
{
    N = static_cast<int>(floor(len / h)) + 1;
    A = vector<double>(N);
    B = vector<double>(N);
    C = vector<double>(N);
    D = vector<double>(N);
    double x = h;
    for (auto i = 1; i < N; i++)
    {
        A[i] = chi(x, x + h) / h;
        C[i] = chi(x, x - h) / h;
        B[i] = A[i] + C[i] + p(x) * h;
        D[i] = f(x) * h;
        x += h;
    }
}

void MathFunctions::calc_eta_ksi()
{
    ksi = vector<double>(N);
    eta = vector<double>(N);
    ksi[1] = -M0 / K0;
    eta[1] = P0 / K0;

    for (auto i = 1; i < N - 1; i++)
    {
        double tmp = B[i] - A[i] * ksi[i];
        ksi[i + 1] = C[i] / tmp;
        eta[i + 1] = (D[i] + A[i] * eta[i]) / tmp;
    }
}

void MathFunctions::calc_y()
{
    y = vector<double>(N);
    y[N - 1] = (PN - MN * eta[N - 1]) / (KN + MN * ksi[N - 1]);
    for (auto i = N - 2; i > -1; i--)
    {
        y[i] = ksi[i + 1] * y[i + 1] + eta [i + 1];
    }
}
