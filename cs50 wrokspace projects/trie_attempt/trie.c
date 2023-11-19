#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define alphabet_legth 26
typedef struct trie
{
    struct trie *next[26];
    unsigned int is_word;
} trie;
char dog_name_buffer[30];
trie *root;

trie *make_trie(trie* root, char *string);
void free_trie(trie *node);
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage :./tries dog_name_file.txt\n");
        return 1;
    }
    FILE *dog_name_fp = fopen(argv[1], "r");
    if (dog_name_fp == NULL)
    {
        printf("Error open the file %s\n", argv[1]);
    }

    // allocate the memory for the root node
    root = malloc(sizeof(trie));
    // set the all the next as "NULL"
    for (int i = 0; i < alphabet_legth; i++)
    {
        root->next[i] = NULL;
    }
    root->is_word = 0;

    while (fscanf(dog_name_fp, "%s", dog_name_buffer) == 1)
    {
        make_trie(root, dog_name_buffer);
    }

    fclose(dog_name_fp);
    free_trie(root);
    return 0;
}

trie *make_trie(trie* node, char *string)
{
    int length = strlen(string);
    int index;
    trie *ptr = node;
    for (int i = 0; i < length; i++)
    {
        index = tolower(string[i]) - 'a';
        if (ptr->next[index] == NULL)
        {
            trie *new_node = malloc(sizeof(trie));
            ptr->next[index] = new_node;
            for (int j = 0; j < alphabet_legth; j++)
            {
                new_node->next[j] = NULL;
            }
            new_node->is_word = 0;
        }
        if (i == length - 1)
        {
            ptr->is_word = 1;
        }
        ptr = ptr->next[index];
    }
    return 0;
}

void free_trie(trie *node)
{
    for (int i = 0; i < alphabet_legth; i++)
    {
        if (node->next[i] != NULL)
        {
            free_trie(node->next[i]);
        }
    }
    free(node);

    return;
}

