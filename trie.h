#ifndef TRIE__H
#define TRIE__H

#include <stdio.h>

typedef struct _trie *Trie;

extern Trie createTrie(int maxNode);

/**
 * Insére le mot w dans l'automate si il n'est pas dejà présent.
 * Stoppe le programme si le nombre de noeud maximale de l'automate est dépassé.
 * */
extern void insertInTrie(Trie trie, unsigned char *w);

/**
 * Retourne true si le mot w est dans l'automate. Sinon false.
 * */
extern int isInTrie(Trie trie, unsigned char *w);

/**
 * Ajoute tout les préfixes du mot w à l'automate trie.
 * */
extern void insertPrefixInTrie(Trie trie, unsigned char *w);

/**
 * Ajoute tout les suffixes du mot w à l'automate trie.
 * */
extern void insertSufixInTrie(Trie trie, unsigned char *w);

/**
 * Ajoute tout les facteurs du mot w à l'automate trie.
 * */
extern void insertFactInTrie(Trie trie, unsigned char *w);

/**
 * Dessine la table de transition de l'automate.
 * Pour une lecture aisée seul les caractères de a à z sont pris en compte.
 * */ 
extern void draw(Trie trie, FILE* stream);

#endif