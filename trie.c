#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"
#ifdef MATRICE
#include "matrice.h"
#else 
#include "hachage.h"
#endif
#include "trie.h"
/* #include "macro.h", aussi sur makefile en tar: clean ("colors.h" "macro.h" "matrice.h")*/

#define INITIAL_STATE_SYMB "-->"
#define FINAL_STATE_SYMB "<--"


Trie createTrie(int maxNode) {
  if (maxNode <= 0){
		printf("Le nombre que vous avez rentre est egale ou inferieur a zero \n");
		exit(EXIT_FAILURE);
	}

  Trie trie = (Trie) malloc(sizeof(*trie));
  if(trie == NULL ){
		fprintf(stderr, RED "echec de l'allocation > createTrie\n" RESET);
		free(trie);
		exit(EXIT_FAILURE);
	}
	printf("Trie cree avec succes !\n");

  trie->maxNode = maxNode;
  trie->nextNode = 1;

  trie->finite = (char *) calloc((size_t) maxNode, sizeof(char));
	if(trie->finite == NULL){
		fprintf(stderr, RED "echec de l'allocation de la table finite > createTrie\n" RESET);
		free(trie->finite);
		free(trie->transition);
		free(trie);
		exit(EXIT_FAILURE);
	}
	printf("Trie->finite cree avec succes !\n");
	

  #ifdef MATRICE
  trie->transition = (int **) malloc(sizeof(int *) * UCHAR_MAX);
  for (int i = 0; i < UCHAR_MAX; ++i) {
    trie->transition[i] = (int *) malloc(sizeof(int) * (size_t) maxNode);
    if(trie->transition[i] == NULL){
			fprintf(stderr, RED "echec de l'allocation de la matrice de transition 2 > createTrie\n" RESET);
			free(trie->transition);
			free(trie);
			exit(EXIT_FAILURE);
		}
  }
  
  // init array
  for (int j = 0; j < UCHAR_MAX; ++j) {
    for (int i = 0; i < trie->maxNode; ++i) {
      (trie->transition)[j][i] = -1;
    }
  }
  #else
  trie->transition = (List *) calloc((size_t) maxNode, sizeof(List*));
   if(trie->transition[i] == NULL){
			fprintf(stderr, RED "echec de l'allocation de la matrice de transition 3 > createTrie\n" RESET);
			free(trie->transition);
			free(trie);
			exit(EXIT_FAILURE);
		}

  #endif
  return trie;
}

void insertInTrie(Trie trie, unsigned char *w) {
  if (isInTrie(trie,w)) {
    return;
  }
  int currEtat = 0;
  while (*w != '\0') {
    if (HAS_NEXT_STATE(trie, currEtat, *w)) {
      currEtat = NEXT_STATE(trie, currEtat, *w);
    } else {
      ADD_STATE(trie, currEtat, *w);
      currEtat = trie->nextNode;
      trie->nextNode += 1;
      if (trie->maxNode < trie->nextNode) {
        fprintf(stderr, RED "maxNodes is below trie->nextNode  > createTrie\n" RESET);
        exit(EXIT_FAILURE);
      }
    }
    ++w;
  }
  trie->finite[currEtat] = true;
}

int isInTrie(Trie trie, unsigned char *w) {
  int currEtat = 0;
  while (*w != '\0') {
    if (HAS_NEXT_STATE(trie, currEtat, *w)) {
      currEtat = NEXT_STATE(trie, currEtat, *w);
    } else {
      return false;
    }
    ++w;
  }
  return trie->finite[currEtat];
}

void insertPrefixInTrie(Trie trie, unsigned char *w) {
  
  unsigned char *word = (unsigned char *) calloc(strlen((const char *)w),
  sizeof(char));
  if (word == NULL) {
    return;
  }
  for (size_t i = 0; w[i] != '\0'; ++i) {
      word[i] = w[i];
      insertInTrie(trie, word);
  }
}

void insertSufixInTrie(Trie trie, unsigned char *w) {
  size_t lenWord = strlen((const char *) w);
  for (size_t i = 0; i < lenWord; ++i) {
      insertInTrie(trie, w + i);
  }
}

void insertFactInTrie(Trie trie, unsigned char *w) {
  insertSufixInTrie(trie, w);
  size_t lenWord = strlen((const char *) w);
  for (size_t i = 0; i < lenWord; ++i) {
      insertPrefixInTrie(trie, w + i);
  }
}

void draw(Trie trie, FILE* stream) {
  //print header
  fprintf(stream, "\t");
  for (int i = 'a'; i <= 'z'; ++i) {
    fprintf(stream, "%c\t",i);
  }
  fprintf(stream, "\n");
  //print body
  for (int i = 0; i < trie->nextNode; ++i) {
    if (i == 0) {
      fprintf(stream, INITIAL_STATE_SYMB);
    }
    if (trie->finite[i]) {
      fprintf(stream, FINAL_STATE_SYMB);
    }
    fprintf(stream, "%d\t",i);
    for (int label = 'a'; label <= 'z'; ++label) {
      #ifdef MATRICE
      int nextNode = trie->transition[label][i];
      #else
      int nextNode = search(trie, i, (unsigned char) label);
      #endif
      if (nextNode == -1) {
        fprintf(stream, "\t");
      } else {
        fprintf(stream, "%d\t", nextNode);
      }
    }
    fprintf(stream, "\n");
  }
}
