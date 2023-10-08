#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "colors.h"
#include "hachage.h"

struct _list {
  int startNode,        /* etat de depart de la transition */
  targetNode;           /* cible de la transition          */
  unsigned char letter; /* etiquette de la transition      */
  struct _list *next;   /* maillon suivant                 */
};

int search(Trie trie, int state, unsigned char w) {
  List currentElement = trie->transition[state];
  while (currentElement != NULL) {
    if (currentElement->letter == w) { 
      return currentElement->targetNode;
    }
    currentElement = currentElement->next;
  }
  return -1;
}

void ajoutTransition(Trie trie, int currEtat, unsigned char w) {
  List cell = (List) malloc(sizeof(*cell));
  if (cell == NULL) {
    fprintf(stderr, RED "echec de l'allocation > ajout transition\n" RESET);
    exit(EXIT_FAILURE);
  }
  cell->startNode = currEtat;
  cell->targetNode = trie->nextNode;
  cell->letter = w;
  cell->next = trie->transition[currEtat];
  trie->transition[currEtat] = cell;
}