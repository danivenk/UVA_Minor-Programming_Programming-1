// Searches for a needle in a haystack

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

// Maximum amount of hay
const int MAX = 65536;

int main(int argc, string argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./find needle\n");
        return -1;
    }

    // Remember needle
    int needle = atoi(argv[1]);

    // Fill haystack
    int size;
    int haystack[MAX];
    for (size = 0; size < MAX; size++)
    {
        // Wait for hay until EOF
        printf("\nhaystack[%i] = ", size);
        int straw = get_int("");
        if (straw == INT_MAX)
        {
            break;
        }

        // Add hay to stack
        haystack[size] = straw;
    }
    printf("\n");

    // Sort the haystack
    sort(haystack, size);

    // Try to find needle in haystack
    if (search(needle, haystack, size))
    {
        printf("\nFound needle in haystack!\n\n");
        return 0;
    }
    else
    {
        printf("\nDidn't find needle in haystack.\n\n");
        return 1;
    }
}
