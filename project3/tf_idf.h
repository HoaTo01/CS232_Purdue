#ifndef TF_IDF_H_
#define TF_IDF_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int docsContains(char *term, struct listNode *pList);
double idf(int docs, int indexedDocs);
double Tf(struct listNode *webPage, char *term);
void score(struct listNode *pList, char *query);
void topThreeScores(struct listNode *pList);
int validInput(char *query);

#endif