/* RADU Sabina - 321CB */

#ifndef TEMA2_BOOK_H
#define TEMA2_BOOK_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BOOK_NAME_LEN 51
#define AUTHOR_NAME_LEN 41

typedef struct book {
    char name[BOOK_NAME_LEN];
    char author[AUTHOR_NAME_LEN];
    int rating;
    int pages;
} TBook;

TBook *createBook(char name[BOOK_NAME_LEN], char author[AUTHOR_NAME_LEN],
                  int rating, int pages);

void printBook(TBook *book, FILE *out);

#endif 
