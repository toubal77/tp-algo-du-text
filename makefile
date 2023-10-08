CC = gcc
CFLAGS = -std=c11 -g -Wall -Wconversion -Werror -Wextra -Wpedantic             \
         -Wwrite-strings -O2 -DTEST -DMATRICE
objects = main.o trie.o trie_test.o hachage.o
executable = automate

all: $(executable)

clear:
	$(RM) $(objects) $(executable) "TP1a.tar.gz"

$(executable): $(objects)
	$(CC) $(objects) $(LDFLAGS) -o $(executable)

tar: clear
	tar -zcf "TP1a.tar.gz" main.c trie.c trie.h makefile trie_test.c trie_test.h  \
	         "colors.h" "matrice.h" "hachage.h" "hashtable.c"

main.o: main.c trie.h trie_test.h
trie_test.o: trie_test.c trie_test.h trie.h
hachage.o: hachage.c hachage.h
trie.o: matrice.h hachage.h trie.c trie.h 