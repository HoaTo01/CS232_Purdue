#ifndef CRAWLER_H_
#define CRAWLER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ADDR_LENGTH 1000

struct listNode{
  char addr[MAX_ADDR_LENGTH];
  struct trie *root;
  double score;

  struct listNode *next;
};

int size (struct listNode *pNode);
int contains(const struct listNode *pNode, const char *addr);
void insertBack(struct listNode *pNode, const char *addr, int *totalTerms);
void printAddresses(const struct listNode *pNode);
void destroyList(struct listNode *pNode);
int getLink(const char* srcAddr, char* link, const int maxLinkLength);
void printList(const struct listNode *pNode);
struct listNode *getLast(struct listNode *pNode);
char *getAddrAt(struct listNode *pNode, int index);
void resetScore(struct listNode *pNode);

#endif