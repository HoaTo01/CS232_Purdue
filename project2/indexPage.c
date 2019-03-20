/* File: indexPage.c */
/* Author: Britton Wolfe */
/* Date: September 3rd, 2010 */

/* This program indexes a web page, printing out the counts of words on that page */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define ALPHABET_SIZE 26 //size of alphabet
#define MAX_CHARACTERS 300000 //max amount of characters the program can handle per web page

struct trie {
  char character; //character of a word
  int timesVisited; //how many times a word was visited
  int isEndOfWord; //boolean

  struct trie *children[ALPHABET_SIZE];
};

struct trie* indexPage(const char* url);

int addWordOccurrence(struct trie *root, const char* word);

void printTrieContents(const struct trie *root, int level, char* word);

int freeTrieMemory(struct trie *root);

int getText(const char* srcAddr, char* buffer, const int bufSize);

struct trie* createNode(void);

int main(int argc, char** argv){
  if (argc <= 1)
    return 0;

  struct trie* root = indexPage(argv[1]);
  char word[MAX_CHARACTERS];
  printTrieContents(root, 0, word);
  freeTrieMemory(root);

  /* argv[1] will be the URL to index, if argc > 1 */

  return 0;
}

struct trie* indexPage(const char* url)
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
      isNewWord = 1;
    }

    buffer[i] = tolower(buffer[i]); //tolower ignores non-alphabetical characters
  }

  // for (i = 0; i < numOfBytes; i++) {
  //   addWordOccurrence(words[i], sizeof(words) / sizeof(words[i]), root);
  // }

  // printf("%s", url);
  // while (tokenWords != NULL)
  // {
  //   printf("\t%s\n",tokenWords);
  //   tokenWords = strtok(NULL, " \0,.-\n");
  // }
  // for (i = 0; words[i] != NULL; i++) {
  //   printf("\t%s", words[i]);
  // }

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

void printTrieContents(const struct trie *root, int level, char* word) {
  if (root == NULL)
    return;

  if (root->isEndOfWord)
  {
   word[level] = 0;
   printf("%s: %d\n", word, root->timesVisited);
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