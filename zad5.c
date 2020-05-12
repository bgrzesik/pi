//
// Created by Bartłomiej Grzesik on 23/03/2020.
//
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/*
    W swojej implementacji polegam silnie na standardowej
    specyfice ciągów znakowych w C oraz na arytmetyce wskaźników.
 */
bool _check_brackets(char **c, char expected, char *end)
{
    while (*(++(*c)) != '\0' && *c != end) {
        if (**c == expected) {
            return true;
        }

        switch (**c) {
            case '(':
                if (!_check_brackets(c, ')', end)) {
                    return false;
                }
                break;
            case '{':
                if (!_check_brackets(c, '}', end)) {
                    return false;
                }
                break;
            case '[':
                if (!_check_brackets(c, ']', end)) {
                    return false;
                }
                break;
            case ')':
            case '}':
            case ']':return false;
        }
    }
    return **c == '\0' && expected == '\0';
}

bool check_brackets(char *c, size_t size)
{
    char *end = c + size;   // Wskaźnik jeden po końcu bufora/tablicy
    c--;                    // Pierwsze sprawdzenie pętli preinkrementuje wskaźnik
    char **p = &c;
    return _check_brackets(p, '\0', end);
}

int main(int argc, const char *argv[])
{
    char buf[100];

    if (fgets(buf, 100, stdin) == NULL) {
        fprintf(stderr, "Błąd wczytywania ciągu znaku z konsoli\n");
        return 1;
    }

    if (check_brackets(buf, 100)) {
        printf("Ciąg nawisów jest poprawny\n");
    } else {
        printf("Ciąg nawisów NIE jest poprawny\n");
    }
    return 0;
}