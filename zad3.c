//
// Created by Bartłomiej Grzesik on 14/03/2020.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*

    Argumenty:

        xmin - początek przedziału całki oznaczonej
        xmax - koniec przedziału całki oznaczonej

        ymin - minimalna wartość całkowanej funkcji w przedziałe
        ymin - maksymalna wartość całkowanej funkcji w przedziałe

        fun  - wskaźnik do całkowanej funkcji np.

                double sin(double x) { ... }

 */
double intergral(double xmin, double xmax, double ymin, double ymax, double (*fun)(double))
{
    double hits = 0.0;
    double prec = 1000000;

    for (int i = 0; i < prec; ++i) {
        double u1 = ((double) rand() / (double) RAND_MAX);
        double u2 = ((double) rand() / (double) RAND_MAX);

        double x = xmin + (xmax - xmin) * u1;
        double y = ymin + (ymax - ymin) * u2;

        if (fun(x) > y) {
            hits += 1.0;
        }
    }

    return (hits * fabs(xmax - xmin) * fabs(ymax - ymin)) / prec;
}

int main(int argc, const char *argv[])
{
    printf("Wynik: %lf\n", intergral(0.0, M_PI, 0.0, 1.0, sin));
}