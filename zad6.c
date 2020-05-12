//
// Created by Bartłomiej Grzesik on 29/03/2020.
//

#include <stdlib.h>
#include <stdio.h>

/*
 Zadanie nr 6. Suma wektorów

W segmencie głównym są tworzone dwie pary tablic 1-wymiarowych
(dwie pary wektorów, w sumie 4 tablice, np. dwie o rozmiarze 5 i dwie o rozmiarze 8).
Rozmiary tych tablic są ustalone w czasie pisania programu.
Najpierw jest wywoływana funkcja, która obliczy sumę pierwszej pary wektorów.
Po powrocie do maina są wyprowadzane na ekran 3 tablice (wektory) - składniki i suma.
Następnie wywoływana jest ta sama funkcja dla drugiej pary tablic i po powrocie wyprowadzane 3 tablice (składniki i suma).

Uwaga: Gdzie powinna być zdefiniowana tablica dla sumy - w main czy w funkcji?.
Rada dla wahających się: Zrobić eksperymenty dla obu przypadków.

Pytania:
- Jaka jest minimalna liczba parametrów tej funkcji (czyli - jaką najmniejszą informację koniecznie trzeba przekazać do funkcji)?
- Czy w funkcji, dla rozpoznania długości tablicy, można użyć operatora sizeof?
Rada dla wahających się: j.w.
 */
void sum(const double *a, const double *b, double *sum, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        sum[i] = a[i] + b[i];
    }
}

/*
- Jaka jest minimalna liczba parametrów tej funkcji (czyli - jaką najmniejszą informację koniecznie trzeba przekazać do funkcji)?

    Przy definicji tablicy wynikowej na zewnątrz funkcji, to minimalna liczba parametrów to 4 tak jak w implementacji powyżej.
    Preferuję taką implementację ponieważ w sytuacji gdy chcemy żeby jakaś struktura posiadająca wektor mogła korzystać z takiej funkcji
    to druga metoda wymagałaby kopii tablicy wynikowej do struktury.

    Przy alokacji tablicy wynikowej wewnątrz funkcji, wymagane są 3 parametry.

- Czy w funkcji, dla rozpoznania długości tablicy, można użyć operatora sizeof?

    W funkcji nie można wykorzystać operatora sizeof, ponieważ operator ten jest rozwijany w trakcie kompilacji,
    a nie dynamicznie w trakcie wykonywania programu, tak jak wymaga implementacja tej funkcji.

 */

void print_vec(FILE *f, double *v, size_t size)
{
    fprintf(f, "( ");
    for (int i = 0; i < size; ++i) {
        fprintf(f, "%0.2lf ", v[i]);
    }
    fprintf(f, ")\n");
}

int main(int argc, const char *argv[])
{
    double v1[5] = { 1, 1, 1, 1, 1};
    double v2[5] = { 1, 0, 2, 0, 3};
    double v3[5];

    sum(v1, v2, v3, 5);

    printf("   ");
    print_vec(stdout, v1, 5);
    printf(" + ");
    print_vec(stdout, v2, 5);
    printf(" = ");
    print_vec(stdout, v3, 5);

    double v4[8] = { 1, 1, 1, 1, 1, 1, 1, 1};
    double v5[8] = { 1, 0, 2, 0, 3, 0, 1, 2};
    double v6[8];

    sum(v4, v5, v6, 8);

    printf("\n   ");
    print_vec(stdout, v4, 8);
    printf(" + ");
    print_vec(stdout, v5, 8);
    printf(" = ");
    print_vec(stdout, v6, 8);

    return 0;
}