#ifndef INDEX_PAGE_H_
#define INDEX_PAGE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26 //size of alphabet
#define MAX_CHARACTERS 300000 //max amount of characters the program can handle per web page

struct trie {
  char character; //character of a word
  int timesVisited; //how many times a word was visited
  int isEndOfWord; //boolean

  struct trie *children[ALPHABET_SIZE];
};

struct trie* indexPage(const char* url, int* pTotalNumTerms);

int addWordOccurrence(struct trie *root, const char* word);

void printTrieContents(const struct trie *root, int level, char* word);

int freeTrieMemory(struct trie *root);

int getText(const char* srcAddr, char* buffer, const int bufSize);

struct trie* createNode(void);

#endif
