from prettytable import PrettyTable
from numpy import arange
from math import sqrt
from poly import *
import warnings
warnings.filterwarnings("ignore")

def Picard1(x):
    return (x * x * x) / 3

def Picard2(x):
    return (x * x * x) / 3 *(1 + x ** 4 / 21)

def Picard3(x):
    return (x * x * x) / 3 *(1 + x ** 4 / 21 + 2 * x ** 8 / 693 + x ** 12 / 19845)

def Picard4(x):
    return (x * x * x) / 3 + x ** 7 / 63 + 2 * x ** 11 / 2079 + 13 * x ** 15 / 218295 + 82 * x ** 19 / 37328445 \
           + 662 * x ** 23 / 1.0438212e10 + 4 * x ** 27 / 3.34187816e9 + x ** 31 / 1.09876903e11 

def explicit(x0, y0, h):
    return y0 + h * (x0 * x0 + y0 * y0)

def implicit(x1, y0, h):
##    D = 1 - 4 * h * (y0 + h * x1 * x1)
##    if (D < 0):
##       return float("NaN")
##    return (1 - sqrt(D)) / (2 * h)

    inv = 1/ h
    dinv = 0.5 * inv
    D = dinv * dinv - inv * y0 -  x1 * x1
    if D < 0:
        return float("NaN")
    return dinv - sqrt(D)
    

def calc_shemes(x_values, step):
    explicit_y, implicit_y = [], []
    explicit_y.append(0)
    implicit_y.append(0)
    for i in range(1, len(x_values)):
        tmp1 = explicit(x_values[i - 1], explicit_y[i - 1], step)
        explicit_y.append(tmp1)
        tmp2 = implicit(x_values[i], implicit_y[i - 1], step)
        implicit_y.append(tmp2)        
    return explicit_y, implicit_y

def calc_picard(x_values):
    p1, p2, p3, p4 = [], [], [], []
    for x in x_values:
        p1.append(Picard1(x))
        p2.append(Picard2(x))
        p3.append(Picard3(x))
        p4.append(Picard4(x))

    return p1, p2, p3, p4

def calc_approx(p, x_values):
    init_poly = Polynominal(4, [0, 0, 0, (1/3)])
    pp1 = Polynominal(3, [0, 0, 1])
    for i in range(p - 1):
        init_poly = (pp1 + (init_poly * init_poly)).integrate()
        
    y_values = []
    for x in x_values:
        tmp_result = 0
        for i in range(len(init_poly.coef)):
            tmp_result += (x ** i) * init_poly.coef[i]
        y_values.append(tmp_result)
    return y_values

def main():
    step = 1e-2
    x_end = 2.5
    
    given = 5 # заданная степень для Пикара
    
    x_values = arange(0, x_end, step)
    for i in range(len(x_values)):
        x_values[i] = round(x_values[i], 5)
        
    expl_y, impl_y = calc_shemes(x_values, step)
    p1, p2, p3, p4 = calc_picard(x_values)

    appr = calc_approx(given, x_values)
    appr_near = calc_approx(given - 1, x_values)

    m = 8
    for i in range(len(p1)):
        p1[i] = round(p1[i], m)
        p2[i] = round(p2[i], m)
        p3[i] = round(p3[i], m)
        p4[i] = round(p4[i], m)
        expl_y[i] = round(expl_y[i], m)
        impl_y[i] = round(impl_y[i], m)
        appr[i] = round(appr[i], m)
        appr_near[i] = round(appr_near[i], m)
    
    

    table = PrettyTable()
    table.add_column('X', x_values)
    table.add_column('1 приближение', p1)
    table.add_column('2 приближение', p2)
    table.add_column('3 приближение', p3)
    table.add_column('4 приближение', p4)
    table.add_column(str(given - 1)+ ' приближение', appr_near)
    table.add_column(str(given)+ ' приближение', appr)
    table.add_column('Явная', expl_y)
    table.add_column('Неявная', impl_y)

    print(table)
    


if __name__ == '__main__':
    main()
