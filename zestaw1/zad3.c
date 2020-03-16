//
// Created by Bartłomiej Grzesik on 14/03/2020.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    double hits = 0.0;
    double prec = 1000000;

    double xmin = 0.0;
    double xmax = M_PI;

    double ymin = 0.0;
    double ymax = 1.0;


    for (int i = 0; i < prec; ++i) {
        double u1 = ((double) rand() / (double) RAND_MAX);
        double u2 = ((double) rand() / (double) RAND_MAX);

        double x = xmin + (xmax - xmin) * u1;
        double y = ymin + (ymax - ymin) * u2;

        if (sin(x) > y) {
            hits += 1.0;
        }
    }

    double solution = (hits * (xmax - xmin) * (ymax - ymin)) / prec;

    printf("Wynik: %lf\n", solution);
}