#ifndef BASIC_H
#define BASIC_H

#include <vector>
#include <math.h>
#include <functional>

#define EPS 1e-10
#define IS_EQUAL(x, y) (fabs((x) - (y)) <= EPS)
#define INTGR 40
#define PI 3.14159265

const double alpha = 1;

using namespace std;

typedef function<double(const double x, const vector<double> args)> math_function;

double interpolate(const double x, const vector<vector<double> > values, const size_t ind);
double integrate(const double a, const double b, math_function func, const vector<double> args);

double runge(const double x0, const double y0, const double z0, const double h, math_function f);
vector<double> runge2(const double x0, const double y0, const double z0, const double h, math_function f, math_function phi);
vector<double> runge4(const double x0, const double y0, const double z0, const double h, math_function f, math_function phi);

#endif // BASIC_H
