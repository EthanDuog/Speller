// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// declare variables,
unsigned int number_of_word;
unsigned int hash_value;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // figure out hash value of the word
    hash_value = hash(word);

    // point cursor to the first node of the table
    node *cursor = table[hash_value];

    //go through the linked list
    while (cursor != 0)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor -> next;

    }
    return false;
}

// TODO: Improve this hash function
// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long word_sum = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        word_sum += tolower(word[i]);
    }
    return word_sum % N;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open dictionary
    FILE *file = fopen(dictionary, "r");
    // check file
    if (file == NULL)
    {
        printf("Unable to open the file");
        return false;
    }

    // declare the variable call word
    char word[LENGTH + 1];

    // Scan dictionary for strings up until the end of the file
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory for new node
        node *n = malloc(sizeof(node));
        // make sure there is space for malloc
        if (n == NULL)
        {
            return false;
        }

        // copy word into node
        strcpy(n->word, word);
        hash_value = hash(word);
        n->next = table[hash_value];
        table[hash_value] = n;
        number_of_word++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (number_of_word > 0)
    {
        return number_of_word;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    // TODO
    // Iterate through buckets
    for (int i = 0; i < N; i++)
    {
        // Set cursor to the start of the linked list
        node *cursor = table[i];

        // if cursul not null, free memory
        while (cursor != NULL)
        {
            // create a temporary variable so can still access the linked list while free the memory
            node *tmp = cursor;

            // move cursor to the next node
            cursor = cursor->next;

            // free the temporary variable (cursor already move to the next node)
            free(tmp);
        }
        // if cursor is null, we reach the end of the memory
        if (cursor == NULL)
        {
            return true;
        }
    }
    return false;
}
