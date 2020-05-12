#include <stdlib.h>
#include <stdio.h>

//
// Created by Bartłomiej Grzesik on 29/03/2020.
//

/*

 Zadanie nr 9. Tablica wskaźników

 1. Jak utworzyć (zdefiniować) tablicę wskaźników, a jak wskaźnik do tablicy?
    Jeżeli są wątpliwości, to proszę sobie napisać programik testujący oba przypadki.

 2. Proszę napisać program, w którym są zdefiniowane (w main) dwie tablice
    - znakowa tablica 2-wymiarowa zawierająca nazwy miesięcy (bez polskich znaków),
    - tablica wskaźników do łańcuchów, w których są zapisane nazwy miesięcy (j.w.).

  W main jest wywoływana funkcja, która oblicza liczbę liter 'a' w nazwach wszystkich miesięcy.
  Czy ta sama funkcja może być użyta dla obu tablic?

 */

/*
    Łańcuch znaków jest wskaźnikiem na pierwszy element tablicy znakowej (char[]) zakończonej bajtem '\0',
    dlatego drugi wariant tablicy potraktowałem jako char **tab[].

    Przy takiej interpretacji tego zadania nie można użyć tej samej funkcji do obu wariantów.
    Taki wariant nie jest optymalny i bardzo żadko może być przydany, ponieważ elementem tablicy drugiego wariantu
    jest wskaźnik na wskaźnik. A najczęściej stosowaną praktyką jest alokacja bufora który przechowywałby
    ciąg znaków i w ten sposób zachowujemy większą kontrolę podczas "serializacji" takiego bufora (np zawartego w strukturze).
 */

size_t count_a(char *arr[], size_t n)
{
    size_t count = 0;
    for (size_t i = 0; i < n; i++) {
        char *c = arr[i];

        while (*c != '\0') {
            if (*c == 'a') {
                count++;
            }
            c++;
        }
    }
    return count;
}

size_t count_a2(char **arr[], size_t n)
{
    size_t count = 0;
    for (size_t i = 0; i < n; i++) {
        char *c = *arr[i];

        while (*c != '\0') {
            if (*c == 'a') {
                count++;
            }
            c++;
        }
    }
    return count;
}

int main(int argc, const char *argv[])
{
    char *months[12] = {
        "styczen",
        "luty",
        "marzec",
        "kwiecien",
        "maj",
        "czerwiec",
        "lipiec",
        "sierpien",
        "wrzesien",
        "pazdziernik",
        "listopad",
        "grudzien",
    };

    printf("%zu\n", count_a(months, 12));

    char **months2[12] = {
        &months[0],
        &months[1],
        &months[2],
        &months[3],
        &months[4],
        &months[5],
        &months[6],
        &months[7],
        &months[8],
        &months[9],
        &months[10],
        &months[11],
    };

    printf("%zu\n", count_a2(months2, 12));

    return 0;
}