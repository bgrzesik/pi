//
// Created by Bartłomiej Grzesik on 01/06/2020.
//
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_WORD_LEN 256

#define max(a, b) ((a) > (b) ? (a) : (b))

/*
    Typ enumeryczny przechowujący typ nowej lini.
 */
typedef enum ENDLINE_TYPE
{
    ENDLINE_LF,
    ENDLINE_CRLF,
    ENDLINE_CR,
    ENDLINE_UNKNOWN
} ENDLINE_TYPE;

/*
    Funkcja wczyjąca wiersz do bufora, oraz zwracająca typ nowej lini w wierszu.
 */
ENDLINE_TYPE read_row(FILE *file, char *buf, size_t n)
{
    fgets(buf, n, file);

    int len = strnlen(buf, n);

    for (int i = max(0, len - 3); i < len; i++) {
        printf("%02X ", buf[i]);
    }
    printf("\n");

    if (len >= 2 && buf[len - 2] == 0x0D && buf[len - 1] == 0x0A) {
        return ENDLINE_CRLF;
    } else if (len >= 1) {
        if (buf[len - 1] == 0x0A) {
            return ENDLINE_LF;
        } else if (buf[len - 1] == 0x0D) {
            return ENDLINE_CR;
        }
    }
    return ENDLINE_UNKNOWN;
}

/*
    Funkcja kopiująca listę wyrazów powyżej 3 liter do pliku wyjściowego,
    funkcja usuwa dla danego typu nowych lini znak nowej lini i dodaje podany.
 */
void copy_file3(FILE *file, FILE *out, ENDLINE_TYPE src, ENDLINE_TYPE dst)
{
    char buf[MAX_WORD_LEN];
    while (!feof(file)) {
        fscanf(file, "%s", buf);
        size_t len = strnlen(buf, MAX_WORD_LEN);
        if (len >= 4) { // 123\n
            switch (src) {
                case ENDLINE_LF:
                case ENDLINE_CR:
                    len -= 1;
                    buf[len] = '\0';
                    break;
                case ENDLINE_CRLF:
                    len -= 2;
                    buf[len] = '\0';
                    buf[len + 1] = '\0';
                    break;

            }

            if (len < 3) {
                continue;
            }

            fputs(buf, out);

            switch (dst) {
                case ENDLINE_LF:
                    fputc(0x0A, out);
                    break;
                case ENDLINE_CRLF:
                    fputc(0x0D, out);
                    fputc(0x0A, out);
                    break;
                case ENDLINE_CR:
                    fputc(0x0D, out);
                    break;
            }
        }
    }
}

int main(int argc, const char *argv[])
{
    FILE *file = fopen("./polski.txt", "r");
    if (!file) {
        fprintf(stderr, "Nie można otworzyć pliku './polski.txt'");
        return -1;
    }

    char buf[MAX_WORD_LEN];
    ENDLINE_TYPE endline_type = read_row(file, buf, MAX_WORD_LEN);
    switch (endline_type) {
        case ENDLINE_CR:
            printf("Koniec lini: CR\n");
            break;
        case ENDLINE_LF:
            printf("Koniec lini: LF\n");
            break;
        case ENDLINE_CRLF:
            printf("Koniec lini: CRLF\n");
            break;
        case ENDLINE_UNKNOWN:
            printf("Koniec lini: nierozpoznany\n");
            break;
    }

    char input[MAX_WORD_LEN];
    fscanf(stdin, "%s", input);

    printf("Wynik funkcji porównawczej: %d\n", strncmp(buf, input, MAX_WORD_LEN));

    int rows = 1;
    while (!feof(file)) {
        fgets(buf, MAX_WORD_LEN, file);
        printf("%s", buf);
        rows += 1;
    }
    printf("Liczba lini: %d\n", rows);


    FILE *out = fopen("polski3.txt", "w");

    rewind(file);
    copy_file3(file, out, endline_type, ENDLINE_LF);

    printf("Długość pliku wejściowego %ld\n", ftell(file));

    fflush(out);
    fclose(out);
    fclose(file);
}