/* RADU Sabina - 321CB */

#include "book.h"

TBook *createBook(char *name, char *author, int rating, int pages) {
    TBook *book = (TBook *) calloc(1, sizeof(TBook));
    if (!book)
        return NULL;

    strncpy(book->name, name, BOOK_NAME_LEN);
    strncpy(book->author, author, AUTHOR_NAME_LEN);
    book->rating = rating;
    book->pages = pages;

    return book;
}

void printBook(TBook *book, FILE *out) {
    fprintf(out, "Informatii recomandare: %s, %s, %d, %d\n",
            book->name, book->author, book->rating, book->pages);
}