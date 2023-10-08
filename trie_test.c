#include "trie_test.h"
#include "trie.h"
#include <stdio.h>
#include "colors.h"

#define PRINT_STATE(NOM_FNCT, RESULTAT)                               \
  if (RESULTAT) {                                                 \
    printf("\n" "succes : " NOM_FNCT "\n");                                \
  } else {                                                         \
    printf("\n" "echec : " NOM_FNCT "\n");                                 \
  }



int testInsertInTrie() {
  Trie trie = createTrie(100);
  insertInTrie(trie, (unsigned char*) "toubal");
  insertInTrie(trie, (unsigned char*) "zine");
  insertInTrie(trie, (unsigned char*) "eddine");
  return 
    isInTrie(trie, (unsigned char*) "toubal") &&
    isInTrie(trie, (unsigned char*) "zine") &&
    isInTrie(trie, (unsigned char*) "eddine");
}

int testInsertPrefixTrie() {
  Trie trie = createTrie(100);
  insertPrefixInTrie(trie, (unsigned char*) "toubal");
  return isInTrie(trie, (unsigned char*) "t") &&
    isInTrie(trie, (unsigned char*) "to") &&
    isInTrie(trie, (unsigned char*) "tou") &&
    isInTrie(trie, (unsigned char*) "toub") &&
    isInTrie(trie, (unsigned char*) "toubal");
}

int testInsertSufixTrie() {
  Trie trie = createTrie(100);
  insertSufixInTrie(trie, (unsigned char*) "toubal");
  return isInTrie(trie, (unsigned char*) "l") &&
    isInTrie(trie, (unsigned char*) "al") &&
    isInTrie(trie, (unsigned char*) "bal") &&
    isInTrie(trie, (unsigned char*) "ubal") &&
    isInTrie(trie, (unsigned char*) "oubal")&&
    isInTrie(trie, (unsigned char*) "toubal");
}

int testInsertFactTrie() {
  Trie trie = createTrie(100);
  insertFactInTrie(trie, (unsigned char*) "toubal");
  return 
    //sufix
    isInTrie(trie, (unsigned char*) "l") &&
    isInTrie(trie, (unsigned char*) "al") &&
    isInTrie(trie, (unsigned char*) "bal") &&
    isInTrie(trie, (unsigned char*) "ubal") &&
    isInTrie(trie, (unsigned char*) "oubal") &&
    isInTrie(trie, (unsigned char*) "toubal") &&
    //prefix
    isInTrie(trie, (unsigned char*) "t") &&
    isInTrie(trie, (unsigned char*) "to") &&
    isInTrie(trie, (unsigned char*) "tou") &&
    isInTrie(trie, (unsigned char*) "toub") &&
    isInTrie(trie, (unsigned char*) "touba") &&
    isInTrie(trie, (unsigned char*) "toubal") &&
    // other
    isInTrie(trie, (unsigned char*) "u") &&
    isInTrie(trie, (unsigned char*) "ou") &&
    isInTrie(trie, (unsigned char*) "out") &&
    isInTrie(trie, (unsigned char*) "tou");
}

void testAll() {
  PRINT_STATE("testInsertInTrie", testInsertInTrie())
  PRINT_STATE("testInsertPrefixTrie", testInsertPrefixTrie())
  PRINT_STATE("testInsertSufixTrie", testInsertSufixTrie())
  PRINT_STATE("insertFactInTrie", testInsertFactTrie())
}