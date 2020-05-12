//
// Created by Bartłomiej Grzesik on 01/05/2020.
//
#include "zad17f.h"
#include <math.h>
#include <stdio.h>

/*
    To podejście już wcześniej przysyłałem w ramach zadania 14, jedynie przeniosłęm funkcje podcałkowe
    do osobnego pliku i utworzyłem plik nagłówkowy z deklaracjami tych funkcji.
 */
double _intergral(double a, double b,
                  double fun_a, double fun_c, double fun_b,
                  double (*fun)(double), double delta,
                  long recur)
{
    double h = fabs(b - a);
    double c = (a + b) / 2.0;

    double s = h * (fun_a + 4 * fun_c + fun_b) / 6.0;

    double fun_ac = fun((a + c) / 2.0);
    double fun_cb = fun((c + b) / 2.0);

    double s1 = h / 2.0 * (fun_a + 4 * fun_ac + fun_c) / 6.0;
    double s2 = h / 2.0 * (fun_c + 4 * fun_cb + fun_b) / 6.0;

    if (fabs(s - (s1 + s2)) <= delta) {
        return s;
    } else {
        if (recur <= 0) {
            return NAN;
        }

        return _intergral(a, c, fun_a, fun_ac, fun_c, fun, delta / 2, recur - 1) +
               _intergral(c, b, fun_c, fun_cb, fun_b, fun, delta / 2, recur - 1);
    }
}

double intergral(double a, double b, double (*fun)(double), double delta)
{
    double fun_a = fun(a);
    double fun_ab = fun((a + b) / 2.0);
    double fun_b = fun(b);

    return _intergral(a, b, fun_a, fun_ab, fun_b, fun, delta, 10);
}

int main(int argc, const char *argv[])
{
    double v1 = intergral(0.0, 1.0, f1, 0.1);
    double v2 = intergral(0.0, 1.0, f2, 0.1);

    printf("%f\n%f\n", v1, v2);

    return 0;
}

