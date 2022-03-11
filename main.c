/* RADU Sabina - 321CB */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "trie.h"


int main(int argc, char **argv) {
    if (argc != 3)
        return 1;

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    char *token, line[1000];
    TTrie *books = NULL;
    TTrie *authors = NULL;

    while (fgets(line, 1000, input) != NULL) {
        token = strtok(line, " ");

        if (token == NULL)
            break;
        else if (!strcmp(token, "add_book")) {
            token = strtok(NULL, ":");
            char name[BOOK_NAME_LEN];
            strncpy(name, token, BOOK_NAME_LEN);

            token = strtok(NULL, ":");
            char author[AUTHOR_NAME_LEN];
            strncpy(author, token, AUTHOR_NAME_LEN);

            token = strtok(NULL, ":");
            int rating = atoi(token);

            token = strtok(NULL, "\n");
            int pages = atoi(token);

            TBook *book = createBook(name, author, rating, pages);
            if (!book)
                return 1; 

            TBook *bookAuthor = createBook(name, author, rating, pages);
            if (!bookAuthor)
                return 1; 

            if (!books) {
                books = createBookTrie(book);
                authors = createAuthorTrie(bookAuthor);
                continue;
            }
            addBookTrie(books, book);
            addAuthorTrie(authors, bookAuthor);

        } else if (!strcmp(token, "search_book")) {
            token = strtok(NULL, "\n");
            TTrie *bookCell = searchTrie(books, token);
            if (!bookCell)
                fprintf(output, "Cartea %s nu exista in recomandarile tale.\n",
                        token);
            else {
                TBook *book = (TBook *) bookCell->info;
                if (!book) {
                    fprintf(output,
                            "Cartea %s nu exista in recomandarile tale.\n",
                            token);
                    continue;
                }
                printBook(book, output);
            }

        } else if (!strcmp(token, "list_author")) {
            token = strtok(NULL, "\n");
            TTrie *authorCell = searchTrie(authors, token);
            if (!authorCell)
                fprintf(output,
                        "Autorul %s nu face parte din recomandarile tale.\n",
                        token);
            else {
                TTrie *bookTrie = (TTrie *) authorCell->info;
                if (!bookTrie) {
                    fprintf(output, "Autorul %s nu face parte din "
                                    "recomandarile tale.\n", token);
                    continue;
                }
                printBookTrie(bookTrie, output);
            }
        } else if (!strcmp(token, "search_by_author")) {
            token = strtok(NULL, ":");
            TTrie *authorCell = searchTrie(authors, token);
            if (!authorCell)
                fprintf(output,
                        "Autorul %s nu face parte din recomandarile tale.\n",
                        token);
            else {
                TTrie *bookTrie = (TTrie *) authorCell->info;
                if (!bookTrie) {
                    fprintf(output, "Autorul %s nu face parte din "
                                    "recomandarile tale.\n", token);
                    continue;
                }
                token = strtok(NULL, "\n");
                TTrie *bookCell = searchTrie(bookTrie, token);
                if (!bookCell)
                    fprintf(output,
                            "Cartea %s nu exista in recomandarile tale.\n",
                            token);
                else {
                    TBook *book = (TBook *) bookCell->info;
                    if (!book) {
                        fprintf(output,
                                "Cartea %s nu exista in recomandarile tale.\n",
                                token);
                        continue;
                    }
                    printBook(book, output);
                }

            }
        } else if (!strcmp(token, "delete_book")) {
            continue;
        }
    }
    deleteBookTrie(books);
    deleteAuthorTrie(authors);

    fclose(input);
    fclose(output);
    return 0;
}