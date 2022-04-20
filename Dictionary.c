// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

int hash_value = 0;

// Hash table
node *table[N];

int word_count= 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Hash the word to get hash value
    hash_value = hash(word);
    // Access linked list at hash_value index in the hash table
    node *cursor = table[hash_value];

    // Traverse linked list
    while (cursor != NULL)
    {
        // If the word is in the dictionnary
        // strcasecmp: is case-insensitive
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }

        // Set cursor to next item
        cursor = cursor->next;
    }
    return false;
}

unsigned int hash(const char *word)
{
    unsigned int hash = 5381;
    int c;

    while ((c = *word++))
        hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */

    return hash % N;
}

// Hashes word to a number
unsigned int hash26(const char *word)
{

    int i = 0;
    int len = strlen(word);
    if (len == 0)
    {
        return 0;
    }

    char first = word[0];
    if (first >= 'A' && first <= 'Z')
    {
        i = first - 'A';
    }
    else if (first >= 'a' && first <= 'z')
    {
        i = first - 'a';
    }
    return i;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // open dictionary file using fopen
    FILE *file = fopen(dictionary, "r");
    // check if return value is null, if null is false move on to next function
    if (file == NULL)
    {
        return false;
    }

    // Buffer space for word
    char word[LENGTH + 1];


    // read strings from file one at a time
    // fscanf will return EOF once it reaches end of file
    while(fscanf(file, "%s", word) != EOF)
    {
        // create new node for each word
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }


        // provided in walkthrough
        // n->word = NULL;
        strcpy(n->word, word);
        // obtain hashing index
        int index = hash(word);

        n -> next = table[index];

        table[index] = n;


        // Increment word count
        word_count++;

    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary
unsigned int size(void)
{
    // return number of words in list
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // frees up memory
    // any time you use malloc, you must call free on that memory and unload it
    // return true if successful
    // call free on every item in linked list
    // there was something in the lectures about this
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];
        node *cursor = n;
        // freeing linked lists
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
