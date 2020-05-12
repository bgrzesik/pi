//
// Created by Bartłomiej Grzesik on 01/05/2020.
//

#include <string.h>
#include <stdio.h>

enum { NO_COMMENT, COMMENT_SINGLE, COMMENT_MULTI };

/*
    Zdecydowałem się na wykorzystanie fgetc ponieważ umożliwia odczytywanie plików znak po znaku,
    co mnie szczególnie interesuje, gdyż osobiście unikam używania funkcji alokacji pamięci dynamicznej (malloc, calloc etc)
    ze względu na wydajność. Dodatkowym atutem tego podejścia jest fakt że pozwala na przetwarzanie bardzo dużych plików bez
    wykorzystywania sporych zasobów pamięci.

    Moje podejście się opiera na tym że oba typy komentarzy wykorzystują dwa znaki na rozpoczęcie komentarza, zatem wystarczy
    że będę przechowywał poprzednio i aktualnie wczytany znak z pliku wejściowego. Zmienna 'buf' pozwala mi na kontrolę przesyłu
    znaków do pliku wyjściowego, metoda polega na tym że znaki są zapisawane do pliku wyjściowego z opóźnieniem jednego znaku.
    Pozwala to na ominięcie problemów z wczytaniem pliku źródłowego który wykorzystuje symbol arytmetyczny /.
 */

void remove_comments(FILE *in, FILE *out)
{
    if (in == NULL || out == NULL || feof(in)) {
        return;
    }

    int c1 = fgetc(in);
    if (c1 == EOF){
        return;
    }

    int buf = EOF;

    int mode = NO_COMMENT;
    while (!feof(in)) {
        int c = fgetc(in);

        if (c1 == '/' && mode == NO_COMMENT) {
            if (c == '*') {
                mode = COMMENT_MULTI;
                buf = EOF;
            } else if (c == '/') {
                mode = COMMENT_SINGLE;
                buf = EOF;
            }
        }

        if (buf != EOF) {
            fputc(buf, out);
        }
        if (mode == NO_COMMENT) {
            buf = c;
        } else {
            buf = EOF;
        }

        if (mode == COMMENT_SINGLE && c == '\n') {
            mode = NO_COMMENT;
        } else if (mode == COMMENT_MULTI && c1 == '*' && c == '/') {
            mode = NO_COMMENT;
        }

        c1 = c;
    }

    if (buf != EOF) {
        fputc(buf, out);
    }

    fflush(out);
}

/*
    W komentarzu jest przykładowe wykorzystanie funkcji z zapisem do pliku wyjściowego.
 */
int main(int argc, const char *argv[])
{
    double a = 2.0/1.0;
    FILE *f = fopen("src/zad18.c", "r");
//    FILE *out = fopen("src/zad18.tmp.c", "w");
//    remove_comments(f, out);
    remove_comments(f, stdout);
    fclose(f);
//    fclose(out);
}