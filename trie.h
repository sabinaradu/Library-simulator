/* RADU Sabina - 321CB */

#ifndef TEMA2_TRIE_H
#define TEMA2_TRIE_H

#include "book.h"

#define ALPHABET 68

typedef struct trie TTrie;

struct trie {
    void *info;
    TTrie *children[ALPHABET];
};

TTrie *createFromString(char *string, void *end);

TTrie *createAuthorTrie(TBook *book);

TTrie *createBookTrie(TBook *book);

TTrie *searchTrie(TTrie *trie, char *string);

int addFromString(TTrie *trie, char *string, void *end);

int addBookTrie(TTrie *trie, TBook *book);

int addAuthorTrie(TTrie *trie, TBook *book);

int getPosInAlphabet(char c);

void printBookTrie(TTrie *trie, FILE *out);

void deleteAuthorTrie(TTrie *trie);

void deleteBookTrie(TTrie *trie);

#endif 
