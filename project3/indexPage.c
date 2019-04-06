#include "indexPage.h"

struct trie* indexPage(const char* url, int* pTotalNumTerms)
{
  struct trie* root = createNode();
  char* buffer = (char*)malloc(sizeof(char) * MAX_CHARACTERS);
  if (root == NULL || buffer == NULL)
    return NULL;

  int numOfBytes = getText(url, buffer, MAX_CHARACTERS);
  int isNewWord = 0; //boolean that signifies whether or not the current word has been added/printed
  int startIndex = 0;
  int endIndex = 0;

  printf("%s\n", url);
  int i, j;
  for (i = 0; i < numOfBytes; i++)
  {
    if (!isalpha(buffer[i]) && isNewWord)
    {
      endIndex = i;
      buffer[endIndex] = '\0';

      printf("\t");
      for (j = startIndex; j < endIndex; j++)
        printf("%c", buffer[j]);
      printf("\n");

      addWordOccurrence(root, buffer + startIndex);

      isNewWord = 0;
    }
    else if (isalpha(buffer[i]) && !isNewWord)
    {
      startIndex = i;
      (*pTotalNumTerms)++;
      isNewWord = 1;
    }

    buffer[i] = tolower(buffer[i]); //tolower ignores non-alphabetical characters
  }
  free(buffer);

  return root;
}

int addWordOccurrence(struct trie* root, const char* word)
{
  if (root == NULL)
    return 0;

  int charIndex = *word - 'a';

  if(root->children[charIndex] == NULL)
  {
    root->children[charIndex] = createNode();

    if (root->children[charIndex] == NULL)
      return 0;
    else
    {
      root->children[charIndex]->character = *word;
      if(*(word+1) == '\0')
      {
        root->children[charIndex]->timesVisited++;
        root->children[charIndex]->isEndOfWord=1;

        return 1;
      }
      else
        return addWordOccurrence(root->children[charIndex], word+1);
    }
  }
  else
  {
    if(*(word+1) == '\0')
    {
      root->children[charIndex]->timesVisited++;
      root->children[charIndex]->isEndOfWord=1;

      return 1;
    }
    else
    {
        return addWordOccurrence(root->children[charIndex], word+1);
    }
  }
}

void printTrieContents(const struct trie *root, int level, char* word)
{
  if (root == NULL)
    return;

  if (root->isEndOfWord)
  {
   word[level] = 0;
   //printf("%s: %d\n", word, root->timesVisited);
  }

  int i;
  for (i = 0; i < ALPHABET_SIZE; i++)
  {
    if (root->children[i] != NULL)
    {
        word[level] = i + 'a';
        printTrieContents(root->children[i], level+1, word);
    }
  }
}

int freeTrieMemory(struct trie* root)
{
  if (root == NULL)
    return 0;

  int i;
  for(i = 0; i < ALPHABET_SIZE; i++)
    if (root->children[i] != NULL)
      freeTrieMemory(root->children[i]);

  free(root);

  return 1;
}

/* You should not need to modify this function */
int getText(const char* srcAddr, char* buffer, const int bufSize){
  FILE *pipe;
  int bytesRead;

  snprintf(buffer, bufSize, "curl -s \"%s\" | python getText.py", srcAddr);

  pipe = popen(buffer, "r");
  if(pipe == NULL){
    fprintf(stderr, "ERROR: could not open the pipe for command %s\n",
     buffer);
    return 0;
  }

  bytesRead = fread(buffer, sizeof(char), bufSize-1, pipe);
  buffer[bytesRead] = '\0';

  pclose(pipe);

  return bytesRead;
}

struct trie* createNode(void) {
  struct trie *newNode = NULL;
  newNode = (struct trie*)malloc(sizeof(struct trie));

  if (newNode != NULL)
  {
    newNode->isEndOfWord = 0; //false
    newNode->timesVisited = 0;
    newNode->character = 0;

    int i;
    for (i = 0; i < ALPHABET_SIZE; i++)
      newNode->children[i] = NULL;
  }

  return newNode;
}

void getWordCount(const struct trie *root, int level, char* word, char *wordToFind, int *occurrence)
{
  if (root == NULL)
    return;

  if (root->isEndOfWord)
  {
   word[level] = 0;
   if(strcmp(wordToFind,word)==1)
   {
     (*occurrence) = root->timesVisited;
   }
   //printf("%s: %d\n", word, root->timesVisited);
  }

  int i;
  for (i = 0; i < ALPHABET_SIZE; i++)
  {
    if (root->children[i] != NULL)
    {
        word[level] = i + 'a';
        printTrieContents(root->children[i], level+1, word);
    }
  }
}
