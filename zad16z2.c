//
// Created by Bartłomiej Grzesik on 02/06/2020.
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_WORD_LEN 256

/*
    Prosta struktura listy dowiązań przechowująca najdłuższe wyrazy.
 */
typedef struct word_list_node {
    struct word_list_node *next;
    char word[MAX_WORD_LEN];
} word_list_node, *word_list;

void free_word_list(word_list *list) {
    if (*list == NULL) {
        return;
    }
    word_list_node *node = *list;
    free_word_list(&(node->next));
    free(node);
    *list = NULL;
}

void word_list_add(word_list *list, char *word) {
    word_list_node *node = malloc(sizeof(word_list_node));
    strncpy(node->word, word, MAX_WORD_LEN);
    node->next = *list;
    *list = node;
}

bool word_list_is_empty(word_list *list) {
    return *list == NULL;
}

void word_list_pop(word_list *list) {
    word_list_node *node = *list;
    *list = node->next;
    free(node);
}

int main(int argc, const char *argv[])
{
    FILE *file = fopen("polski3.txt", "r");
    if (!file) {
        fprintf(stderr, "Nie można otworzyć pliku './polski3.txt'");
        return -1;
    }

    word_list list = NULL;
    size_t max = 0;
    char buf[MAX_WORD_LEN];

    /*
        Jeżeli zostanie znalezione dłuższe słowo, to dotychczasowa lista
        jest usuwana, a następnie utworzona na nowo z nowym najdłuższym wyrazem.
        Jeżeli długość aktualnego wyrazy jest tak samo długa, wyraz jest dodawany do listy.
     */
    while (!feof(file)) {
        fgets(buf, MAX_WORD_LEN, file);
        size_t len = strnlen(buf, MAX_WORD_LEN);

        if (len > max) {
            max = len;
            free_word_list(&list);
            word_list_add(&list, buf);
        } else if (len == max) {
            word_list_add(&list, buf);
        }
    }

    while (!word_list_is_empty(&list)) {
        printf("%s", list->word);
        word_list_pop(&list);
    }

    free_word_list(&list);
    fclose(file);
}