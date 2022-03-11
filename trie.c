/* RADU Sabina - 321CB */

#include "trie.h"

int getPosInAlphabet(char c) {
    const char *alphabet = (const char *) "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";
    for (int i = 0; i <= ALPHABET; i++) {
        if (alphabet[i] == c)
            return i;
    }
    return -1;
}


TTrie *createFromString(char *string, void *end) {
    TTrie *trie = (TTrie *) calloc(1, sizeof(TTrie));
    if (!trie)
        return NULL;

    if (*string == 0) {
        trie->info = end;
        return trie;
    }

    int pos = getPosInAlphabet(*string);
    trie->children[pos] = createFromString(string + 1, end);

    return trie;
}

int addFromString(TTrie *trie, char *string, void *end) {
    if (*string == 0) {
        trie->info = end;
        return 1;
    }

    int pos = getPosInAlphabet(*string);
    TTrie *child = trie->children[pos];
    if (child)
        addFromString(child, string + 1, end);
    else {
        trie->children[pos] = createFromString(string + 1, end);
        if (!trie->children[pos])
            return -1;
    }
    return 1;
}

TTrie *searchTrie(TTrie *trie, char *string) {
    if (*string == 0) {
        return trie;
    }

    int pos = getPosInAlphabet(*string);
    TTrie *child = trie->children[pos];

    if (!child)
        return NULL;
    return searchTrie(child, string + 1);
}

TTrie *createBookTrie(TBook *book) {
    return createFromString(book->name, book);
}

TTrie *createAuthorTrie(TBook *book) {
    TTrie *authortrie = createFromString(book->author, book);
    if (!authortrie)
        return NULL;

    TTrie *lastcell = searchTrie(authortrie, book->author);
    TTrie *booktrie = createBookTrie(book);
    if (!booktrie)
        return NULL; 

    lastcell->info = booktrie;

    return authortrie;
}

int addBookTrie(TTrie *trie, TBook *book) {
    return addFromString(trie, book->name, book);
}


int addAuthorTrie(TTrie *trie, TBook *book) {
    TTrie *lastcell = searchTrie(trie, book->author);
    if (!lastcell) {
        addFromString(trie, book->author, NULL);
        lastcell = searchTrie(trie, book->author);

        TTrie *booktrie = createBookTrie(book);
        if (!booktrie)
            return -1; 

        lastcell->info = booktrie;
    }

    TTrie *booktrie = (TTrie *) lastcell->info;
    if (booktrie)
        addBookTrie(booktrie, book);

    return 1;
}

void printBookTrie(TTrie *trie, FILE *out) {
    if (!trie)
        return;
    for (int i = 0; i < ALPHABET; i++) {
        TTrie *child = trie->children[i];
        if (child) {
            if (child->info)
                fprintf(out, "%s\n", ((TBook *) child->info)->name);
            printBookTrie(child, out);
        }
    }
}

void deleteAuthorTrie(TTrie *trie) {
    if (!trie)
        return;
    for (int i = 0; i < ALPHABET; i++) {
        TTrie *child = trie->children[i];
        if (child) {
            if (child->info) {
                deleteBookTrie((TTrie *) child->info);
                trie->children[i]->info = NULL;
            }
            deleteAuthorTrie(child);
        }
    }
    free(trie);
}

void deleteBookTrie(TTrie *trie) {
    if (!trie)
        return;
    for (int i = 0; i < ALPHABET; i++) {
        TTrie *child = trie->children[i];
        if (child) {
            if (child->info) {
                free(child->info);
                trie->children[i]->info = NULL;
            }
            deleteBookTrie(child);
        }
    }
    free(trie);
}
