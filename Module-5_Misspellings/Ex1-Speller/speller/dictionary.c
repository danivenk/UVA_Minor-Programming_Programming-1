// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

struct node_array *first_node;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node_array *ptr = malloc(sizeof(node_array));
    if (!ptr)
    {
        fprintf(stderr, "Could not allocate memory.");
        return false;
    }

    *ptr = *first_node;

    for (int i = 0; word[i]; i++)
    {
        int pos = get_pos(word[i]);

        if (pos == 100)
        {
            fprintf(stderr, "Incorrect charcter found.");
            return false;
        }

        if(ptr->letter[pos] != 0)
        {
            ptr = ptr->next[pos];
        }
        else
        {
            return false;
        }

    }

    delNode(ptr);

    return true;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *inptr = fopen(dictionary, "r");
    if (!inptr)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);

        // close infile
        fclose(inptr);

        return false;
    }

    // get file_size
    fseek(inptr, 0L, SEEK_END);
    int file_size = ftell(inptr);
    fseek(inptr, 0L, SEEK_SET);

    first_node = realloc(first_node, sizeof(node_array));
    node_array *current_node = malloc(sizeof(node_array));
    if (!first_node || !current_node)
    {
        fprintf(stderr, "Could not allocate memory.");

        free(first_node);
        free(current_node);

        // close infile
        fclose(inptr);

        return false;
    }

    init_node(first_node);

    while(file_size > ftell(inptr))
    {
        int character_count = 0;
        current_node = first_node;

        char *letter = malloc(sizeof(char));
        if (!letter)
        {
            fprintf(stderr, "Could not allocate memory.");

            free(first_node);
            free(current_node);

            free(letter);

            // close infile
            fclose(inptr);

            return false;
        }

        fread(letter, sizeof(char), 1, inptr);
        character_count++;

        while (*letter != LF)
        {
            character_count++;
            fread(letter, sizeof(char), 1, inptr);
        }

        free(letter);

        fseek(inptr, -character_count * sizeof(char), SEEK_CUR);

        int word_size = character_count - 1;

        char *current_word = malloc(word_size * sizeof(char));
        if (!current_word)
        {
            fprintf(stderr, "Could not allocate memory.");

            free(first_node);
            free(current_node);

            free(letter);
            free(current_word);

            // close infile
            fclose(inptr);

            return false;
        }

        fread(current_word, word_size * sizeof(char), 1, inptr);

        // skip over the enter characters
        fseek(inptr, sizeof(char), SEEK_CUR);

        for (int i = 0; i < word_size; i++)
        {
            int pos = get_pos(current_word[i]);

            if (pos == 100)
            {
                fprintf(stderr, "Incorrect charcter found.");
                return false;
            }

            current_node->letter[pos] += 1;

            if (current_node->next[pos] == NULL)
            {
                node_array (*next_node) = malloc(sizeof(node_array));
                if (!next_node)
                {
                    fprintf(stderr, "Could not allocate memory.");


                    free(first_node);
                    free(current_node);

                    free(letter);
                    free(current_word);

                    free(next_node);

                    // close infile
                    fclose(inptr);

                    return false;
                }

                init_node(next_node);

                current_node->next[pos] = next_node;

                next_node = NULL;

                free(next_node);
            }

            current_node = current_node->next[pos];
        }

        free(current_word);


        current_node = NULL;

        free(current_node);

    }

    // close infile
    fclose(inptr);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int words = 0;
    for (int i = 0; i < ALPHA; i++)
    {
        words += first_node->letter[i];
    }

    return words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    delNode(first_node);

    free(first_node);

    return true;
}

void init_node(node_array *node)
{
    for (int i = 0; i < ALPHA; i++)
    {
        node->letter[i] = 0;
        node->next[i] = NULL;
    }
}

int get_pos(char character)
{
    int pos;

    if (isalpha(character))
    {
        pos = tolower(character) - 'a';
    }
    else if (character == QUOTE)
    {
        pos = ALPHA - 1;
    }
    else
    {
        pos = 100;
    }

    return pos;
}

void delNode(node_array *node)
{
    for (int i = 0; i < ALPHA; i++)
    {
        node_array *node_next = node->next[i];

        if (node_next != NULL)
        {
            for (int j = 0; j < ALPHA; j++)
            {
                if (node_next->next[i] != NULL)
                {
                    delNode(node_next);

                    node_next->next[i] = NULL;
                }
            }
        }

        free(node_next);
    }

    return;
}