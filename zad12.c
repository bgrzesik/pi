//
// Created by Bartłomiej Grzesik on 08/04/2020.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
Zadanie 12: Tablica struktur dla kilku ksiązek

Program najpierw wczytuje liczbę książek, których dane będą wczytane.
Do wczytania danych program używa funkcji, która - i tu znów 2 wersje:
A. wczytuje dane tylko jednej książki,
B. raz wywołana - wczytuje dane wszystkich książek.

Uwaga: VLA jest dozwolone.
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

void read_n_books(size_t n, struct book *books)
{
    for (size_t i = 0; i < n; ++i) {
        read_book(&books[i]);
    }
}

int main(int argc, const char *argv[])
{
    size_t size;
    fscanf(stdin, "%zd", &size);
    struct book books[size];
    read_n_books(size, books);

    /*
    for (size_t i = 0; i < n; ++i) {
        read_book(&books[i]);
    }
     */

    return EXIT_SUCCESS;
}