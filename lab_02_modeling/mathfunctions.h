#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

#include <vector>
#include <math.h>

#include "data.h"
#include "basic.h"

const double ZLBORDER = 0;
const double ZRBORDER = R;

double calc_T(const double m, const double T0, const double Tw, const double z);
double calc_m(const double I);
double calc_T0(const double I);
double calc_sigma(const double T);
double calc_integral(const double I0);
double calc_Rp(const double I);

#endif // MATHFUNCTIONS_H
