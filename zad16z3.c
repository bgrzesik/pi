//
// Created by Bartłomiej Grzesik on 02/06/2020.
//
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define MAX_WORD_LEN 256
#define N_LETTERS ('z' - 'a' + 1)
#define JUMP_LIST_LEN (N_LETTERS + 1)
#define JUMP_LIST_CHR_IDX(c) ((c) - 'a')
#define JUMP_LIST_FILE_END (JUMP_LIST_LEN - 1)


/*
    Strukura przechowująca pozycje w pliku przy których
    po raz pierwszy występuje dana pierwsza litera.
 */
typedef struct jump_list {
    size_t jumps[JUMP_LIST_LEN];
} jump_list;

/*
    Procedura inicjalizuje tablice z wartością maksymalną,
    a następnie minimalizuje jej wartości na podstawie pozycji w których
    dana litera pojawia się po raz pierwszy.
    Ostania pozycja tablicy jest pozycją ostatniego wyrazu w pliku.
 */
void create_jump_list(jump_list *list, FILE *file) {
    char buf[MAX_WORD_LEN];
    for (int i = 0; i < JUMP_LIST_LEN; ++i) {
        list->jumps[i] = SIZE_MAX;
    }
    long pos;
    while (!feof(file)) {
        pos = ftell(file);

        fgets(buf, MAX_WORD_LEN, file);
        int idx = JUMP_LIST_CHR_IDX(buf[0]);
        list->jumps[idx] = min(list->jumps[idx], pos);
    }
    list->jumps[JUMP_LIST_FILE_END] = pos;
}

/*
    Funkcja generująca liczby pseudo losowe większe od RAND_MAX.
 */
int bigrand(int max) {
    int m = max;
    int r = 0;
    do {
        r += rand();
        m -= RAND_MAX;
    } while (m > 0);
    return r % max;
}

/*
    Funkcja czytająca następny wyraz po podanej pozycji w pliku.
 */
void read_word(FILE *file, size_t pos, char *dst) {
    fseek(file, pos, SEEK_SET);
    fgets(dst, MAX_WORD_LEN, file);
    fgets(dst, MAX_WORD_LEN, file);
}

/*
    Funkcja losuje pierwszy wyraz, a następnie losuje wyrazy spośród tych które
    zaczynają się na kolejne litery pierwszego wyrazu.
 */
void create_crossword(FILE *file, jump_list *list) {
    char vert[MAX_WORD_LEN];
    char hori[MAX_WORD_LEN];

    int pos = bigrand(list->jumps[JUMP_LIST_FILE_END]);
    read_word(file, pos, vert);

    for (size_t i = 0; i < strnlen(vert, MAX_WORD_LEN); i++) {
        if (vert[i] == '\n' || vert[i] == '\r') {
            break;
        }
        size_t c_start = list->jumps[JUMP_LIST_CHR_IDX(vert[i])];
        size_t c_end = list->jumps[JUMP_LIST_CHR_IDX(vert[i]) + 1];
        size_t pos2 = bigrand((int) (c_end - c_start)) + c_start;

        read_word(file, pos2, hori);
        printf("%c%s", vert[i], &hori[1]);
    }

}

int main(int argc, const char *argv[])
{
    srand(time(0));

    FILE *file = fopen("polski3.txt", "r");
    if (!file) {
        fprintf(stderr, "Nie można otworzyć pliku './polski3.txt'");
        return -1;
    }

    jump_list list;
    create_jump_list(&list, file);
    rewind(file);

    create_crossword(file, &list);

    fclose(file);
}