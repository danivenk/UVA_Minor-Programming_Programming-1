// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

#define LF 0x0A
#define ALPHA 26

typedef struct node_array
{
    char letter[ALPHA];
    struct node *next[ALPHA];
}
node_array;

typedef struct node
{
    char letter;
    struct node *next;
}
node;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    printf("%s\n", word);
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *inptr = fopen(dictionary, "r");
    if (!inptr)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;

    }

    // get file_size
    fseek(inptr, 0L, SEEK_END);
    int file_size = 10 * sizeof(char);//ftell(inptr);
    fseek(inptr, 0L, SEEK_SET);

    // node (*pos_node)[LENGTH] = malloc(LENGTH * sizeof(node));
    while(file_size > ftell(inptr))
    {
        int word_size = 0;

        char *letter = malloc(sizeof(char));

        while (*letter != LF)
        {
            fread(letter, sizeof(char), 1, inptr);
            word_size++;
        }

        fseek(inptr, -word_size * sizeof(char), SEEK_CUR);

        char *current_word = malloc(word_size * sizeof(char));

        fread(current_word, word_size * sizeof(char), 1, inptr);
    }

    // close infile
    fclose(inptr);

    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
