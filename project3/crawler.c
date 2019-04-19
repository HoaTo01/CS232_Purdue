#include "crawler.h"
#include "indexPage.h"

int size (struct listNode *pNode)
{
  struct listNode *pCur = pNode;
  int count = 0;
  while(pCur != NULL)
  {
    count++;
    pCur = pCur->next;
  }
  return(count);
}
int contains(const struct listNode *pNode, const char *addr)
{
  if (pNode == NULL)
      return 0;
  else if (strcmp(pNode->addr, addr)==0)
      return 1;
  else
      return (contains(pNode->next, addr));
}

void insertBack(struct listNode *pNode, const char *addr, int *totalTerms)
{

  if (pNode->next == NULL)
  {
    struct listNode *nodeToAdd = (struct listNode*)malloc(sizeof(struct listNode));
    strcpy(nodeToAdd->addr,addr);
    nodeToAdd->next = NULL;
    nodeToAdd->root = indexPage(addr,totalTerms);
    nodeToAdd->score = 0.0000;

    pNode->next = nodeToAdd;
  }
  else
      return (insertBack(pNode->next, addr, totalTerms));
}

void printAddresses(const struct listNode *pNode)
{
  if(pNode == NULL)
    return;
  else
  {
    printf("%s\n",pNode->addr);
    printAddresses(pNode->next);
    return;
  }
}

void destroyList(struct listNode *pNode)
{
  if(pNode->next == NULL)
  {
    freeTrieMemory(pNode->root);
    free(pNode);
    return;
  }
  else
  {
    destroyList(pNode->next);
    freeTrieMemory(pNode->root);
    free(pNode);
    return;
  }
}

int getLink(const char* srcAddr, char* link, const int maxLinkLength){
  const int bufSize = 1000;
  char buffer[bufSize];

  int numLinks = 0;

  FILE *pipe;

  snprintf(buffer, bufSize, "curl -s \"%s\" | python getLinks.py", srcAddr);

  pipe = popen(buffer, "r");
  if(pipe == NULL){
    fprintf(stderr, "ERROR: could not open the pipe for command %s\n",
	    buffer);
    return 0;
  }

  fscanf(pipe, "%d\n", &numLinks);

  if(numLinks > 0){
    int linkNum;
    double r = (double)rand() / ((double)RAND_MAX + 1.0);

    for(linkNum=0; linkNum<numLinks; linkNum++){
      fgets(buffer, bufSize, pipe);

      if(r < (linkNum + 1.0) / numLinks){
		break;
      }
    }

    /* copy the address from buffer to link */
    strncpy(link, buffer, maxLinkLength);
    link[maxLinkLength-1] = '\0';

    /* get rid of the newline */
    {
      char* pNewline = strchr(link, '\n');
      if(pNewline != NULL){
		*pNewline = '\0';
      }
    }
  }

  pclose(pipe);

  if(numLinks > 0){
    return 1;
  }
  else{
    return 0;
  }
}
struct listNode *getLast(struct listNode *pNode)
{
  if (pNode->next== NULL)
      return(pNode);
  else
  {
    return(getLast(pNode->next));
  }
}
void printList(const struct listNode *pNode)
{
  if (pNode == NULL)
      return;
  else
  {
    printf("%s\n",pNode->addr);
    printList(pNode->next);
  }
  return;
}
char *getAddrAt(struct listNode *pNode, int index)
{
    struct listNode *pCur = pNode;
    int i =0;

    while(i<index)
    {
      pCur = pCur->next;
      i++;
    }
    return(pCur->addr);

}
void resetScore(struct listNode *pNode)
{
  struct listNode *pCur = pNode;

  while(pCur != NULL)
  {
    pCur->score = 0.0;
    pCur = pCur->next;
  }
}