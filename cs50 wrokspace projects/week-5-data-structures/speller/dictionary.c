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
} node;

// Choose number of buckets in hash table
const unsigned int N = 2000;

// Hash table
node *table[N];

// read the one word 1 time into a buffer
char word_buffer[LENGTH + 1];

// test_hash
unsigned int hash_index[N];
int count = 0;

// sum of the words in dictionary
unsigned int word_sum = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Improve this hash function
    int sum = 0, length = strlen(word);
    for (int i = 0; word[i] != '\0'; i++)
    {
        sum = sum + word[i];
    }
    int index = sum % N;
    return index;

    // unsigned int hashValue = 0;
    // while (*word) {
    //     hashValue = (hashValue << 5) + *word++;
    // }
    // return hashValue % N;
    // return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    int index;
    node *ptr;
    FILE *input = fopen(dictionary, "r");
    while (fscanf(input, "%s", word_buffer) != EOF)
    {
        ptr = malloc(sizeof(node));
        if (ptr == NULL)
        {
            return false;
        }

        ptr->next = NULL;
        strcpy(ptr->word, word_buffer);
        index = hash(word_buffer);

        if (table[index] == NULL)
        {
            table[index] = ptr;
        }
        else
        {
            ptr->next = table[index];
            table[index] = ptr;
        }
        word_sum++;
    }
    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_sum;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *cursor, *temp;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
