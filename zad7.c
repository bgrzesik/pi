#include <stdio.h>
#include <math.h>

//
// Created by Bartłomiej Grzesik on 29/03/2020.
//

/*
 Zadanie nr 7. Max i min w tablicy

W main tworzymy tablicę 1-wymiarową - rozmiar musi być ustalony, ale w tym zadaniu nie jest istotny.
Wywołujemy (tylko raz) funkcję (uniwersalną jak w zadaniu 6), która szuka wartości maksymalnej i minimalnej.
Znalezione wartości są wyprowadzane przez maina.

 Wskazówki:
- Oczywiste jest użycie pętli - dobrze byłoby, aby to była tylko jedna pętla.
  Oczywiście - jeżeli ktoś ma z tym problem, niech najpierw napisze dwie petle,
  ale później pomyśli jak (w oszczędny sposób, tzn. bez zbędnych operacji) zrealizować oba poszukiwania w jednej pętli.

- Zwykle algorytm porównuje każdy element z najlepszym dotychczas znalezionym.
  Jaką jego wartość przewidzieć przed rozpoczęciem pętli - bezpiecznie, ale także oszczędnie.

- Najważniejsze: Jak przekazać informację o znalezionych wartościach z funkcji do maina?
  Nie polecam tu dwuelementowej tablicy ani struktury.

 */

void minmax(const double tab[], size_t size, double *pmin, double *pmax)
{
    if (size <= 0) {
        *pmin = NAN;
        *pmax = NAN;
    }

    if (pmin != NULL) {
        *pmin = tab[0];
    }

    if (pmax != NULL) {
        *pmax = tab[0];
    }

    for (size_t i = 1; i < size; ++i) {
        if (pmin != NULL && *pmin > tab[i]) {
            *pmin = tab[i];
        }
        if (pmax != NULL && *pmax < tab[i]) {
            *pmax = tab[i];
        }
    }
}

int main(int argc, const char *argv[])
{
    const double tab[7] = {1, 2, 3, 4, 5, 6, 7};

    double min, max;
    minmax(tab, 7, &min, &max);

    printf("%0.2lf\t%0.2lf\n", min, max);

    return 0;
}