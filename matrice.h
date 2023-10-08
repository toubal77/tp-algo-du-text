struct _trie {
  int maxNode;        /* Nombre maximal de noeuds du trie    */
  int nextNode;       /* Indice du prochain noeud disponible */
  int **transition;   /* matrice de transition               */
  char *finite;       /* etats terminaux                     */
};

typedef struct _trie *Trie;

/* ajout de la transition a l'automate trie */
#define ADD_STATE(trie, currEtat, w)                                       \
  NEXT_STATE(trie, currEtat, w) = trie->nextNode

/* retourne le prochain etat de l'automate  */
#define NEXT_STATE(trie, currEtat ,w)                                      \
  trie->transition[w][currEtat]

/* TRUE si l'automate trie possede un prochain etat */
#define HAS_NEXT_STATE(trie, currEtat, w)                                  \
  NEXT_STATE(trie, currEtat, w) != -1
