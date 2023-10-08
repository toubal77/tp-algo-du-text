#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie_test.h"
#include "trie.h"

int main(int argc, const char *argv[]) {
  #ifdef MATRICE
  printf("----avec MATRICE----\n");
  #else
  printf("----avec hachage----\n");
  #endif
  // test c'est a supprime a la fin normalement
  #ifdef TEST 
    testAll();
  #endif
  // each args is a word to add in the Trie
  size_t wordsLength = 1;
  for (int i = 1; i < argc; i++) {
    wordsLength = wordsLength + strlen(argv[i]);
  }
  Trie trie = createTrie((int) wordsLength);
  for (int i = 1; i < argc; i++) {
    printf("Insertion du mot : %s \n", argv[i]);
    insertInTrie(trie, (unsigned char*) argv[i]);
  }
  for (int i = 1; i < argc; i++) {
    if (isInTrie(trie, (unsigned char*) argv[i])) {
      printf("is in %s\n",argv[i]);
    } else {
      printf("Not is in %s\n",argv[i]);
    }
  }
  FILE * file;
  file = fopen("automataArray", "w");
  draw(trie, file);
  fclose(file);
  return EXIT_SUCCESS;
}