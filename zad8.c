#include <stdio.h>

//
// Created by Bartłomiej Grzesik on 29/03/2020.
//

/*
 Zadanie nr 8. Suma macierzy

Zadanie analogiczne do zadania 6, ale operacja dodawania jest wykonywana na tablicach 2-wymiarowych.
Główny problem - jak przekazać informacje o tablicach do funkcji.

Wersje:

 A. Funkcja nie jest uniwersalna - działa tylko na tablicach o ustalonym (w czasie pisania programu) rozmiarze,
    tzn. rozmiar dodawanych w funkcji macierzy jest stałą.

 B. Funkcja uniwersalna - z wykorzystaniem VLA.

 C. Funkcja uniwersalna - bez korzystania z VLA - kompilowana w standardzie C90 (chciaż niektóre kompilatory C90 tolerują VLA).
    W tej wersji proszę zwrócić uwagę na "elegancki" sposób zapisu argumentów aktualnych wywołania funkcji.


    Wybrałem wariant C.

 */

/*

  Zdecydowałem się na przekazanie rozmiaru macierzy jako iloczyn wymiarów,
  ze względu na potencjalną optymalizację wyniku iloczynu przez kompilator,
  który jest niezbędny do wykonania sumy, a nie wpływa na wynik.

    n = rows * cols

 */
void matsum(const double *m1, const double *m2, double *sum, size_t n)
{
    for (size_t i = 0; i < n; ++i) {
        sum[i] = m1[i] + m2[i];
    }
}

void mat_print(const double *m, size_t rows, size_t cols)
{
    for (size_t r = 0; r < rows; ++r) {
        for (size_t c = 0; c < cols; ++c) {
            printf("%0.2lf\t", m[r * cols + c]);
        }
        printf("\n");
    }
}

int main(int argc, const char *argv[])
{
    double m1[3][3] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1},
    };

    double m2[3][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
    };

    double sum[3][3];

    matsum(&m1[0][0], &m2[0][0], &sum[0][0], 3 * 3);

    mat_print(&m1[0][0], 3, 3);
    printf("\n");

    mat_print(&m2[0][0], 3, 3);
    printf("\n");

    mat_print(&sum[0][0], 3, 3);
    printf("\n");

    return 0;
}