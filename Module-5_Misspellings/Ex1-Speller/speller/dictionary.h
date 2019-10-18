// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// LF is the value of linebreak and single quote
#define LF 0x0A
#define QUOTE 0x27

// number of possible characters
#define ALPHA 27

// definition of a node in a TRIE datastructure
typedef struct node_array
{
    int letter[ALPHA];
    struct node_array *next[ALPHA];
    bool c_word_end;
}
node_array;

// declare global first_node
extern struct node_array *first_node;

// Prototypes
bool check(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);
void init_node(node_array *node);
int get_pos(char character);
void delNode(node_array *node);

#endif // DICTIONARY_H
