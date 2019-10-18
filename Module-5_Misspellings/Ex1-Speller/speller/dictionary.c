/*
** implements a dictionary's functionality
** Dani van Enk, 11823526
*/

// used libraries
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// including the dictionary header
#include "dictionary.h"

// declaring first_node
struct node_array *first_node;

/*
** returns true if word is in dictionary else false
*/
bool check(const char *word)
{
    // initialize pointer for searching the word
    node_array *ptr = NULL;

    // get length of the word
    int len = strlen(word);

    // when the words ends with quotes (twice) exclude those
    if (word[len - 1] == QUOTE && word[len - 2] == QUOTE)
    {
        len -= 2;
    }

    // start pointer as first_node
    ptr = first_node;

    // loop over the characters in the word
    for (int i = 0; i < len; i++)
    {
        // get the position of the letter if a -> 0, b -> 1 etc.
        int pos = get_pos(word[i]);

        // if get_pos gives error exit
        if (pos == 100)
        {
            fprintf(stderr, "Incorrect charcter found.");

            return false;
        }

        // find the possible last node of the word
        if(ptr->letter[pos] != 0)
        {
            ptr = ptr->next[pos];
        }
        else
        {
            return false;
        }

    }

    // if the last node contains a end of word return true
    if(ptr->c_word_end == true)
    {
        return true;
    }

    // exit
    return false;
}

/*
** loads dictionary into memory, returning true if successful else false
*/
bool load(const char *dictionary)
{
    // open dictionary file and exit if not opened
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

    // allocate memory for first node
    first_node = malloc(sizeof(node_array));
    if (!first_node)
    {
        fprintf(stderr, "Could not allocate memory.");

        // free allocated memory
        free(first_node);

        // close infile
        fclose(inptr);

        return false;
    }

    // initialize first_node
    init_node(first_node);

    // declare current_node
    node_array *current_node = NULL;

    // loop over the entire dictionary
    while(file_size > ftell(inptr))
    {
        // initialize character count and set current node to first node
        int character_count = 0;
        current_node = first_node;

        // allocate memory for letter
        char *letter = malloc(sizeof(char));
        if (!letter)
        {
            fprintf(stderr, "Could not allocate memory.");

            // free allocated memory
            free(first_node);
            free(current_node);

            // close infile
            fclose(inptr);

            return false;
        }

        // read a character and increase character count
        fread(letter, sizeof(char), 1, inptr);
        character_count++;

        // repeat untill a linebreak is encountered
        while (*letter != LF)
        {
            character_count++;
            fread(letter, sizeof(char), 1, inptr);
        }

        // free allocated memory for letter
        free(letter);

        // go back in filestream to later read this word
        fseek(inptr, -character_count * sizeof(char), SEEK_CUR);

        // get word_size
        int word_size = character_count - 1;

        // allocate memory for current_word
        char *current_word = malloc(word_size * sizeof(char));
        if (!current_word)
        {
            fprintf(stderr, "Could not allocate memory.");

            // free allocated memory
            free(first_node);
            free(current_node);
            free(letter);

            // close infile
            fclose(inptr);

            return false;
        }

        // read the currentword
        fread(current_word, word_size * sizeof(char), 1, inptr);

        // skip over the linebreak
        fseek(inptr, sizeof(char), SEEK_CUR);

        // loop over the word
        for (int i = 0; i < word_size; i++)
        {
            // get the position of the letter if a -> 0, b -> 1 etc.
            int pos = get_pos(current_word[i]);

            // if get_pos gives error exit
            if (pos == 100)
            {
                fprintf(stderr, "Incorrect charcter found.");

                return false;
            }

            // add letter to current_node
            current_node->letter[pos] += 1;

            // initialize next_node
            node_array *next_node = NULL;

            // if there is no next node for this letter make new node
            if (!current_node->next[pos])
            {
                // allocate memory for next_node
                next_node = malloc(sizeof(node_array));
                if (!next_node)
                {
                    fprintf(stderr, "Could not allocate memory.");

                    // free allocated memory
                    free(first_node);
                    free(current_node);
                    free(letter);
                    free(current_word);

                    // close infile
                    fclose(inptr);

                    return false;
                }

                // initialize next_node
                init_node(next_node);

                // set next in current_node to be next_node
                current_node->next[pos] = next_node;
            }

            // advance current node to next_node
            current_node = current_node->next[pos];
        }

        // declare end of word
        current_node->c_word_end = true;

        // free allocated memory for current word
        free(current_word);
    }

    // close infile
    fclose(inptr);

    // exit
    return true;
}

/*
** returns number of words in dictionary if loaded else 0 if not yet loaded
*/
unsigned int size(void)
{
    // set words to 0
    int words = 0;

    // count the number of letters in first_node
    for (int i = 0; i < ALPHA; i++)
    {
        words += first_node->letter[i];
    }

    // return the number of words
    return words;
}

/*
** unloads dictionary from memory, returning true if successful else false
*/
bool unload(void)
{
    // free full first_node T TRIE
    delNode(first_node);

    return true;
}

/*
** init_node initializes a node_array structure with 0 and false
*/
void init_node(node_array *node)
{
    // for all array entries set to zero
    for (int i = 0; i < ALPHA; i++)
    {
        node->letter[i] = 0;
        node->next[i] = NULL;
        node->c_word_end = false;
    }
}

/*
** get_pos gets position of character if a->0; b->1 etc and apostrophe->26
*/
int get_pos(char character)
{
    // initialize pos
    int pos;

    // if alpha a must be 0
    if (isalpha(character))
    {
        pos = tolower(character) - 'a';
    }
    // if apostrophe -> 26
    else if (character == QUOTE)
    {
        pos = ALPHA - 1;
    }
    // else exit code 100
    else
    {
        pos = 100;
    }

    return pos;
}

/*
** frees all memory of a TRIE node in a reqursive manner
*/
void delNode(node_array *node)
{
    // if node does not exist exit
    if (!node)
    {
        return;
    }

    // for all adresses in the node execute delNode
    for (int i = 0; i < ALPHA; i++)
    {
        node_array *node_next = node->next[i];

        delNode(node_next);
    }

    // free allocated memory of node
    free(node);

    return;
}