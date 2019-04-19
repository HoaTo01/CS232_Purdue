#include "indexPage.h"
#include "crawler.h"
#include "tf_idf.h"
#include <math.h>

int docsContains(char *term, struct listNode *pList)
{
    char word[MAX_CHARACTERS];
    struct listNode *pCur = pList;
    int counter;
    int docs = 0;

    while(pCur!= NULL)
    {
        counter = 0;
        getWordCount(pCur->root,0,word, term,&counter);
        if(counter > 0)
        {
            docs++;
        }
        //printf("Occurences of %s in %s is: %d\n",term,pCur->addr,counter);
        pCur = pCur->next;
    }
    return(docs);
}
double idf(int docs, int indexedDocs)
{
    return(log((1.0+indexedDocs)/(1.0+docs)));
}
double Tf(struct listNode *webPage, char *term)
{
    int total = webPage->root->totalWords;
    int counter=0;
    char word[MAX_CHARACTERS];

    getWordCount(webPage->root,0,word, term, &counter);
    // printf("Total words in %s is: %d\n",webPage->addr,total);
    // printf("Total occurrence of %s in %s is: %d\n",term, webPage->addr, counter);
    //printf("TF (%s) in %s: %.7lf\n",term,webPage->addr,(counter*1.0/total));
    return((counter*1.0/total));
}
void score(struct listNode *pList, char *query)
{
    char *wordToFind;
    struct listNode *pCur;
    double IDF;
    double TF;

    printf("IDF scores are\n");

    wordToFind = strtok(query," ");
    while(wordToFind != NULL)
    {
        pCur = pList->next;
        //pCur->score = 0;

        IDF = idf(docsContains(wordToFind,pCur),size(pList->next));
        //printf("IDF score of %s is: %.7lf\n",wordToFind, IDF);
        //TF = Tf(pCur, wordToFind);
        while(pCur != NULL)
        {
            //printf("Word at the moment: %s\n",wordToFind);
            TF = Tf(pCur,wordToFind);
            //printf("TF score of %s in %s is %.4lf\n",wordToFind,pCur->addr,TF);
            pCur->score += (TF*IDF);
            pCur = pCur->next;
        }
        printf("IDF(%s): %.7lf\n",wordToFind,IDF);
        //TF = Tf(pList->root->totalWords,counter);

        //printf("TF (%s) in %s: %.7lf\n",wordToFind,pCur->addr,TF);
        //printf("Number of webpages contains %s is: %d\n",wordToFind,docsContains(wordToFind,pCur));
        wordToFind = strtok(NULL," ");
    }
}
void topThreeScores(struct listNode *pList)
{
    int i = 0;
    double scoreArr[size(pList)];
    struct listNode *pCur = pList;
    double first, second, third; // values
    int index_first, index_second, index_third; // indexes

    while(pCur != NULL)
    {
        scoreArr[i] = pCur->score;
        pCur = pCur->next;
        i++;
    }
    pCur = pList;
    first = 0.0000;
    second = 0.0000;
    third = 0.0000;
    index_first = index_second = index_third = 0;
    for(i = 0; i<size(pList);i++)
    {
        if(scoreArr[i] > first)
        {
            third = second;
            index_third = index_second;

            second = first;
            index_second = index_first;

            first = scoreArr[i];
            index_first = i;
        }
        else if(scoreArr[i] > second)
        {
            third = second;
            index_third = index_second;

            second = scoreArr[i];
            index_second = i;
        }
        else if (scoreArr[i] > third)
        {
            third = scoreArr[i];
            index_third = i;
        }
        // printf("%d. %s (score: %.4lf)\n",i+1,(pCur->addr),scoreArr[i]);
        // pCur = pCur->next;
    }

    if (first != 0.0)
    {
        printf("1. %s (score: %.4lf)\n",getAddrAt(pCur,index_first),first);
        if(second != 0.0)
        {
            printf("2. %s (score: %.4lf)\n",getAddrAt(pCur,index_second),second);
            if(third != 0.0)
            {
                printf("3. %s (score: %.4lf)\n",getAddrAt(pCur,index_third),third);
            }
        }
    }
    //free(scoreArr);
}
int validInput(char *query)
{
    int i=0;
    while(i<strlen(query))
    {
        if(isalpha(query[i]))
        {
            if(isupper(query[i]))
            {
                printf("Please enter a query containing only lower-case letters.\n");
                return 0;
            }
            i++;
        }
        else if(!isspace(query[i]))
        {
           // printf("Working\n");
            printf("Please enter a query containing only lower-case letters.\n");
            return 0;
        }
        else
        {
            i++;
        }
    }
    return 1;
}