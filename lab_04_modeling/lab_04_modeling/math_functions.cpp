#include "math_functions.h"
#include <algorithm>

vector<vector<double> > MathFunctions::calc_all_T()
{
    d = (alphaN * len) / (alphaN - alpha0);
    c = alpha0 * (-d);
    N = static_cast<int>(floor(len / h)) + 1;
    vector<vector<double>> result;
    vector<double> curr_T(N, T0);
    result.push_back(curr_T);

    vector<double> curr_iteration;
    double t = 0;
    double tmp;
    do
    {
        prev_T = curr_T;
        curr_iteration = prev_T;
        do
        {
            prev_iteration = curr_iteration;
            curr_iteration = calculate_T(t);
            tmp = calc_diff(prev_iteration, curr_iteration);
        } while (tmp > eps);
        curr_T = curr_iteration;
        result.push_back(curr_T);
        t += tau;
        tmp = calc_diff(prev_T, curr_T);
    } while (tmp > eps);
    return result;
}

vector<double> MathFunctions::calculate_T(double t)
{
    /*
    if (t > tau * 100)
    {
        F0 = 0;
    }
    */
    calc_left_boundary();
    calc_right_boundary();
    calc_coef();
    calc_eta_ksi();
    return calc_y();
}

void MathFunctions::calc_left_boundary()
{
    double chi12 = chi(prev_iteration[0], prev_iteration[1]);
    double p0 = p(0);
    double p1 = p(h);
    double f0 = f(0);
    double f1 = f(h);
    double cap0 = cap(prev_iteration[0]);
    double cap1 = cap(prev_iteration[1]);
    double p12 = (p1 + p0) / 2.0;
    double f12 = (f1 + f0) / 2.0;
    double cap12 = (cap0 + cap1) / 2.0;
    K0 = 0.5 * h4 * cap12 + h4 * cap0 + tau * chi12 / h + tau * h4 * 0.5 * p12 + tau * h4 * p0;
    M0 = 0.5 * h4 * cap12 - tau * chi12 / h + tau * h4 * 0.5 * p12;
    P0 = 0.5 * h4 * cap12 * (prev_T[0] + prev_T[1]) + h4 * cap0 * prev_T[0] + F0 * tau + tau * h4 * (f12 + f0);
}

void MathFunctions::calc_right_boundary()
{
    int vsize = prev_iteration.size();
    double chiN12 = chi(prev_iteration[vsize - 1], prev_iteration[vsize - 2]);
    double pN = p(len);
    double pN1 = p(len - h);
    double pN12 = (pN + pN1) / 2.0;
    double fN = f(len);
    double fN1 = f(len - h);
    double fN12 = (fN + fN1) / 2.0;
    double capN = cap(prev_iteration[vsize - 1]);
    double capN1 = cap(prev_iteration[vsize - 2]);
    double capN12 = (capN + capN1) / 2.0;
    KN = h4 * capN + 0.5 * h4 * capN12 + tau * alphaN + tau * chiN12 / h + h4 * tau * pN + 0.5 * h4 * tau * pN12;
    MN = 0.5 * h4 * capN12 - tau * chiN12 / h +  0.5 * h4 * tau * pN12;
    PN = alphaN * tau * T0 + h4 * capN * prev_T[vsize - 1] + 0.5 * h4 * capN12 * (prev_T[vsize - 1] + prev_T[vsize - 2]) + h4 * tau * (fN + fN12);
}

void MathFunctions::calc_coef()
{
    A = vector<double>(N);
    B = vector<double>(N);
    C = vector<double>(N);
    D = vector<double>(N);
    double x = h;
    for (auto i = 1; i < N - 1; i++)
    {
        A[i] = tau * chi(prev_iteration[i], prev_iteration[i - 1]) / h;
        C[i] = tau * chi(prev_iteration[i], prev_iteration[i + 1]) / h;
        B[i] = A[i] + C[i] + cap(prev_iteration[i]) * h + p(x) * h * tau;
        D[i] = f(x) * h * tau + cap(prev_iteration[i]) * prev_T[i] * h;
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

vector<double> MathFunctions::calc_y()
{
    vector<double> y(N);
    y[N - 1] = (PN - MN * eta[N - 1]) / (KN + MN * ksi[N - 1]);
    for (auto i = N - 2; i > -1; i--)
    {
        y[i] = ksi[i + 1] * y[i + 1] + eta [i + 1];
    }
    return y;
}

double MathFunctions::calc_diff(vector<double> prev, vector<double> cur)
{
    vector<double> diff;
    for (auto i = 0; i < prev.size(); i++)
    {
        diff.push_back(abs((cur[i] - prev[i]) / cur[i]));
    }
    return *(max_element(diff.begin(), diff.end()));
}
