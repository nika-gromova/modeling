#include "mathfunctions.h"

double calc_T(const double m, const double T0, const double Tw, const double z)
{
    return (Tw - T0) * pow(z, m) + T0;
}

double calc_m(const double I)
{
    return interpolate(I, ITm, mVALUES);
}

double calc_T0(const double I)
{
    return interpolate(I, ITm, T0VALUES);
}

double calc_sigma(const double T)
{
    return interpolate(T, TSigma, SIGMAVALUES);
}

double integrand(const double z, const vector<double> args)
{
    double T = calc_T(args[0], args[1], args[2], z);
    double sigma = calc_sigma(T);
    return z * sigma;
}

double calc_integral(const double I0)
{
    double m = calc_m(I0);
    double T0 = calc_T0(I0);
    return integrate(ZLBORDER, ZRBORDER, integrand, {m, T0, Tw});
}

double calc_Rp(const double I)
{
    return Le / (2 * PI * calc_integral(I));
}
