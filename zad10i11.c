//
// Created by Bartłomiej Grzesik on 08/04/2020.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
Zadanie 10: Książka

W programie przechowywane są informacje o książce:
- imiona i nazwisko autora (w jednej tablicy znakowej albo łańcuchu) - znaków nie więcej niż AUTOR_MAX,
- tytuł - jak wyżej, znaków nie więcej niż TYTUL_MAX,
- rok wydania (wydawnictwo, liczbę stron itd. - pominiemy),
- cena w PLN.
Na zewnątrz funkcji należy umieścić deklarację struktury dla opisu książki.
W segmencie głównym należy zdefiniować zmienną tego typu i zainicjować przykładowymi danymi
i wywołać funkcję, która wszystkie informacje zapisane w strukturze wyoisze na ekran.

Zadnie 11: Ksiązka z funkcją

Deklaracja struktury - jak w zadaniu 10.
Zamiast inicjowania, wczytywanie danych jest realizowane w funkcji.
Wyprowadzenie danych - jak w zadaniu 10.

Program należy napisać w 2 wersjach (jeżeli to jest możliwe), z dwoma sposobami przekazania informacji do/z funkcji:
A. przez wartość,
B. przez adres.
 */

/*

    Osobiście zawsze wybierałbym przekazywanie przez adres, aby uniknąć zbędnego kopiowania.

 */

#define AUTOR_MAX 128
#define TYTUL_MAX 128

struct book
{
    char author[AUTOR_MAX];
    char title[TYTUL_MAX];
    int release_year;
    int price;
};

/*
    Funckja napisana żeby uniknąć blędu liczb zmienno przecinkowych.
    Prawdopodobnie zbyteczna.
 */
int read_price()
{
    int price = 0, price_cents = 0;

    char buf[200], *end, *end2 = NULL;
    fscanf(stdin, "%s", buf);
    price = (int) strtol(buf, &end, 10);

    if (*end == ',' || *end == '.') {
        end++;
        price_cents = (int) strtol(end, &end2, 10);

        if (end2 - end < 2) {
            price_cents *= 10;
        }
    }

    price *= 100;
    price += price_cents;

    return price;
}

void read_book(struct book *book)
{
    fprintf(stdout, "Podaj Autora: ");
    fgets(book->author, AUTOR_MAX, stdin);
    book->author[strnlen(book->author, AUTOR_MAX) - 1] = '\0';

    fprintf(stdout, "Podaj tytuł: ");
    fgets(book->title, TYTUL_MAX, stdin);
    book->title[strnlen(book->title, TYTUL_MAX) - 1] = '\0';

    fprintf(stdout, "Podaj rok wydania: ");
    fscanf(stdin, "%d", &book->release_year);

    fprintf(stdout, "Podaj cenę: ");
    book->price = read_price();
    fflush(stdin);
}

void print_book(const struct book *book)
{
    fprintf(stdout, "Autor: %s\n", book->author);
    fprintf(stdout, "Tytuł: %s\n", book->title);
    fprintf(stdout, "Rok wydania: %d\n", book->release_year);
    fprintf(stdout, "Cena: %d.%02d\n", book->price / 100, book->price % 100);
    fflush(stdout);
}

struct book read_book2()
{
    /*
     Używam fprintf, fscanf zamiast printf, scanf dla konsystencji kodu.
     */

    struct book book;
    fprintf(stdout, "Podaj Autora: ");
    fgets(book.author, AUTOR_MAX, stdin);
    book.author[strnlen(book.author, AUTOR_MAX) - 1] = '\0';

    fprintf(stdout, "Podaj tytuł: ");
    fgets(book.title, TYTUL_MAX, stdin);
    book.title[strnlen(book.title, TYTUL_MAX) - 1] = '\0';

    fprintf(stdout, "Podaj rok wydania: ");
    fscanf(stdin, "%d", &book.release_year);

    fprintf(stdout, "Podaj cenę: ");
    book.price = read_price();

    fflush(stdin);

    return book;
}

void print_book2(struct book book)
{
    fprintf(stdout, "Autor: %s\n", book.author);
    fprintf(stdout, "Tytuł: %s\n", book.title);
    fprintf(stdout, "Rok wydania: %d\n", book.release_year);
    fprintf(stdout, "Cena: %d.%02d\n", book.price / 100, book.price % 100);
    fflush(stdout);
}


int main(int argc, const char *argv[])
{
    struct book book;
    read_book(&book);
    print_book(&book);

    struct book book2;
    book2 = read_book2();
    print_book2(book2);

    return EXIT_SUCCESS;
}