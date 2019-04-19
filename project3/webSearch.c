#include "crawler.c"
#include "indexPage.c"
#include "tf_idf.c"

#define MAX_QUERY_SIZE 100

int main(int argc, char** argv)
{
    char startAddr[MAX_ADDR_LENGTH];
    char destAddr[MAX_ADDR_LENGTH];
    char url[MAX_ADDR_LENGTH];
    char query[MAX_QUERY_SIZE];
    FILE *fp;

    long seed;
    int hopNum, hopLimit, MAX_N;
    int n=0;
    struct listNode *pListStart;

    if(argc != 4)
    {
        printf( "Not enough arguments were passed.\n" );
        return(-1);
    }
    else
    {
        fp=fopen(argv[1],"r");
        MAX_N = atoi(argv[2]);

        seed = atol(argv[3]);

        srand(seed);
    }

    pListStart = malloc(sizeof(struct listNode));
    if(pListStart == NULL)
    {
        fprintf(stderr, "ERROR: could not allocate memory\n");
        return -2;
    }
    else
    {
        pListStart->next = NULL;
        pListStart->root = NULL;
    }


    printf("Indexing...\n");
    while((fscanf(fp,"%s %d",url,&hopLimit) != EOF) && (n <MAX_N))
    {
        strncpy(startAddr,url,MAX_ADDR_LENGTH);
        hopNum = 0;
        while(1)
        {
            if(contains(pListStart->next, startAddr)==0)
            {
                int totalNumTerms = 0;

                insertBack(pListStart, startAddr, &totalNumTerms);
                char word[MAX_CHARACTERS];
                //printf("\"%s\n\n\"",getLast(pListStart)->root->)
                printTrieContents((getLast(pListStart))->root, 0, word);
                //(getLast(pListStart))->root->totalWords=totalNumTerms;
                //printf("Total number of words is: %d\n",totalNumTerms);
                n++;
            }
            hopNum++;
            if((hopNum <= hopLimit) && (n<MAX_N))
            {
                int res = getLink(startAddr, destAddr, MAX_ADDR_LENGTH);

                if(!res)
                {
                    break;
                }
                strncpy(startAddr, destAddr, MAX_ADDR_LENGTH);
            }
            else
            {
                break;
            }
        }
    }
    printf("\nEnter a web query: ");
    while(fgets(query,MAX_QUERY_SIZE,stdin))
    {
        if(query[0] == '\n')
            break;
        query[strlen(query)-1] = '\0';
        //printf("Length of query: %d\n",(int)strlen(query));
        if(validInput(query)==0)
        {
            printf("\nEnter a web query: ");
            continue;
        }
        printf("Query is \"%s\".\n",query);
        score(pListStart,query);

        printf("Web pages:\n");
        topThreeScores(pListStart->next);
        resetScore(pListStart->next);
        printf("\nEnter a web query: ");
    }
    printf("Exiting the program\n");
    fclose(fp);
    destroyList(pListStart);

    return(0);
}
