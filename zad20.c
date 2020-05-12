//
// Created by Bartłomiej Grzesik on 12/05/2020.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

typedef struct world_list_node
{
    size_t len; /* długość słowa */
    size_t count; /* krotnośc słowa */
    char *ptr; /* wskaźnik na słowo */
    struct world_list_node *next;
} word_list_node;

typedef struct word_list
{
    word_list_node *head;
} word_list;


bool is_letter(char c)
{
    if (c >= 'a' && c <= 'z') {
        return true;
    }
    if (c >= 'A' && c <= 'Z') {
        return true;
    }
    return false;
}

bool is_alpha(char c)
{
    if (is_letter(c)) {
        return true;
    }
    if (c >= '0' && c <= '9') {
        return true;
    }
    if (c == '-' || c == '\'') {
        return true;
    }
    return false;
}

/*
    Własna implementacja funkcji porównującej ciągi znaków,
    funkcja strncmp ze standardowej biblioteki nie uwzględnia wielkości liter.
 */
int strcmp2(char *a, char *b, int max)
{
    while (*a == *b && max > 0) {
        a++;
        b++;
        max--;
    }

    if (max == 0) {
        return 0;
    }

    if (is_letter(*a) && is_letter(*b)) {
        int aa = *a;
        int bb = *b;

        if (*a >= 'a' && *a <= 'z') {
            aa -= 'a';
        } else {
            aa -= 'A';
        }
        if (*b >= 'a' && *b <= 'z') {
            bb -= 'a';
        } else {
            bb -= 'A';
        }

        if (aa > bb) {
            return 1;
        } else {
            return -1;
        }
    }

    if (*a > *b) {
        return 1;
    } else {
        return -1;
    }
}

void word_list_add(word_list *list, char *ptr, size_t len)
{
    word_list_node sentinel;
    sentinel.next = list->head;

    word_list_node *cur = &sentinel;
    int r = 1;
    while (cur->next != NULL) {
        r = strcmp2(cur->next->ptr, ptr, min(cur->next->len, len));
        if (r > 0) {
            break;
        }
        if (r == 0 && len <= cur->next->len) {
            break;
        }
        cur = cur->next;
    }

    if (cur->next != NULL && r == 0 && len == cur->next->len) {
        cur->next->count++;
    } else {
        word_list_node *node = (word_list_node *) malloc(sizeof(word_list_node));
        node->ptr = ptr;
        node->len = len;
        node->count = 1;
        node->next = cur->next;
        cur->next = node;

    }

    list->head = sentinel.next;
}

void load_words(char *input, word_list *list)
{
    char *i = input;

    if (i == NULL) {
        return;
    }

    while (*i != '\0') {
        while (*i != '\0' && !is_letter(*i)) {
            i++;
        }

        char *start = i;

        while (*i != '\0' && is_alpha(*i)) {
            i++;
        }

        size_t len = i - start;
        if (len > 0) {
            word_list_add(list, start, len);
        }
    }
}

void word_list_destroy(word_list *list)
{
    while (list->head != NULL) {
        word_list_node *tmp = list->head->next;
        free(list->head);
        list->head = tmp;
    }
}

void word_list_write_list(word_list *list, FILE *file)
{
    for (word_list_node *node = list->head; node != NULL; node = node->next) {
        fprintf(file, "%d %.*s\n", (int) node->count, (int) node->len, node->ptr);
    }
    fflush(file);
}

/*
    Funkcja wczytująca listę z krotnościami słów,
    funkcja odtwarza listę, nie dopisuje słów.
 */
void word_list_load_list(word_list *list, FILE *file)
{
    word_list_node sentinel;
    sentinel.next = NULL;
    word_list_node *last = &sentinel;

    while (file != NULL && !feof(file)) {
        int count = 0;
        char buf[128];

        if (fscanf(file, "%d %s", &count, buf) != 2) {
            break;
        }

        word_list_node *node = (word_list_node *) malloc(sizeof(word_list_node));
        node->len = strnlen(buf, 128);
        node->ptr = strndup(buf, 128);
        node->count = count;

        last->next = node;
        last = node;
    }

    list->head = sentinel.next;
}

int main(int argc, const char *argv[])
{
    word_list list = { NULL };

    /*
        Wczytanie całego pliku tekst.txt do pamięci. Personalnie nie przepadam za tym podejściem i
        raczej wolałbym albo kopiować słowa do pamięci (strdup), albo wolałbym zmapować plik do pamięci (mmap, DMA),
        natomiast takie rozwiązanie wykorzystywałoby funkcje spoza standardowej biblioteki.
     */
    FILE *file = fopen("tekst.txt", "r");
    if (fseek(file, 0, SEEK_END) != 0) {
        return -1;
    }

    long fsize = ftell(file);
    if (fseek(file, 0, SEEK_SET) != 0) {
        return -2;
    }

    char *bigbuf = malloc(fsize + 1);
    fread(bigbuf, fsize, 1, file);

    load_words(bigbuf, &list);
    fclose(file);

    word_list_write_list(&list, stdout);

    printf("====================================================\n");

    file = fopen("words.list", "w");
    word_list_write_list(&list, file);
    fclose(file);
    word_list_destroy(&list);
    free(bigbuf);

    file = fopen("words.list", "r");
    word_list_load_list(&list, file);
    word_list_write_list(&list, stdout);
    fclose(file);

    for (word_list_node *node = list.head; node != NULL; node = node->next) {
        free(node->ptr);
    }
    word_list_destroy(&list);

    return 0;
}