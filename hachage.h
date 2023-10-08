typedef struct _list *List;

struct _trie {
  int maxNode;        /* Nombre maximal de noeuds du trie    */
  int nextNode;       /* Indice du prochain noeud disponible */
  List *transition;   /* listes d’adjacence                  */
  char *finite;       /* etats terminaux                     */
};

typedef struct _trie *Trie;

/**
 * Retourne le prochain état de l'automate trie passant par l'étiquette w
 * à l'état state. Si la transition n'existe pas retourne -1. 
 */
extern int search(Trie trie, int state, unsigned char w);

/* Ajoute la transition à l'automate trie.*/
extern void ajoutTransition(Trie trie, int currEtat, unsigned char w);

#define NEXT_STATE(trie, currEtat , w)                                     \
  search(trie, currEtat, w)

/**
 * Retourne vrai si l'automate trie posséde un prochain état à partir de l'état
 * currEtat en passant par l'étiquette w.
 * */
#define HAS_NEXT_STATE(trie, currEtat, w)                                  \
  NEXT_STATE(trie, currEtat, w) != -1

/**
 * Ajoute la transition (currrentState, w, trie->nextNode) à l'automate trie
 * */
#define ADD_STATE(trie, currEtat, w)                                       \
  ajoutTransition(trie, currEtat, w);
