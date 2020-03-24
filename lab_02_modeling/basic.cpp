#include "basic.h"

double interpolate(const double x, const vector<vector<double>> values, const size_t ind)
{
    double x0, x1, y0, y1;
    size_t start = 0;
    size_t end = values[0].size() - 1;
    size_t mid;
    if (x <= values[0][0])
    {
        x0 = values[0][0];
        x1 = values[0][1];
        y0 = values[ind][0];
        y1 = values[ind][1];
    }
    else if (x >= values[0][end])
    {
        x0 = values[0][end];
        x1 = values[0][end - 1];
        y0 = values[ind][end];
        y1 = values[ind][end - 1];
    }
    else
    {
        while (start <= end)
        {
            mid = (start + end) / 2;
            if (IS_EQUAL(values[0][mid], x))
                return values[1][mid];
            if (values[0][mid] > x)
                end = mid - 1;
            else
                start = mid + 1;
        }

        x0 = values[0][start];
        x1 = values[0][end];
        y0 = values[ind][start];
        y1 = values[ind][end];
    }

    return (y0 + (x - x0) * (y1 - y0) / (x1 - x0));
}

double integrate(const double a, const double b, const math_function func, const vector<double> args)
{
    const double h = (b - a) / INTGR;
    double k = 0;
    double cur = a + h;
    for(int i = 1; i < INTGR; i++)
    {
        if (i % 2)
            k += 4 * func(cur, args);
        else
            k += 2 * func(cur, args);
      cur += h;
    }

    return (h / 3.0) * (func(a, args) + k + func(b, args));
}

vector<double> runge2(const double x0, const double y0, const double z0, const double h, math_function f, math_function phi)
{
    vector<double> y;
    double nh = h / (2 * alpha);
    double k1 = f(x0, {y0, z0});
    double q1 = phi(x0, {y0, z0});
    double k2 = f(x0 + nh, {y0 + nh * k1, z0 + nh * q1});
    double q2 = phi(x0 + nh, {y0 + nh * k1, z0 + nh * q1});
    double y1 = y0 + h * ((1 - alpha) * k1 + alpha * k2);
    double z1 = z0 + h * ((1 - alpha) * q1 + alpha * q2);
    return {y1, z1};
}

double runge(const double x0, const double y0, const double z0, const double h, math_function f)
{
    double h2 = h / 2;
    double k1 = h * f(x0, {y0, z0});
    double k2 = h * f(x0 + h2, {y0 + k1 / 2, z0 + k1 / 2});
    double k3 = h * f(x0 + h2, {y0 + k2 / 2, z0 + k2 / 2});
    double k4 = h * f(x0 + h, {y0 + k3, z0 + k3});
    return (y0 + (k1 + 2 * k2 + 2 * k3 + k4) / 6);
}

vector<double> runge4(const double x0, const double y0, const double z0, const double h, math_function f, math_function phi)
{
    double h2 = h / 2;
    double k1 = h * f(x0, {y0, z0});
    double q1 = h * phi(x0, {y0, z0});
    double k2 = h * f(x0 + h2, {y0 + k1 / 2, z0 + q1 / 2});
    double q2 = h * phi(x0 + h2, {y0 + k1 / 2, z0 + q1 / 2});
    double k3 = h * f(x0 + h2, {y0 + k2 / 2, z0 + q2 / 2});
    double q3 = h * phi(x0 + h2, {y0 + k2 / 2, z0 + q2 / 2});
    double k4 = h * f(x0 + h, {y0 + k3, z0 + q3});
    double q4 = h * phi(x0 + h, {y0 + k3, z0 + q3});
    double y1 = y0 + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    double z1 = z0 + (q1 + 2 * q2 + 2 * q3 + q4) / 6;
    return {y1, z1};
}
