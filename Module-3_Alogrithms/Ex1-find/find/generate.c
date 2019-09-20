// Generates pseudorandom numbers in [0,LIMIT), one per line

#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // If the wrong number of arguments are given return 1
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // number of generated numbers
    int n = atoi(argv[1]);

    // if seed is given, generate numbers with seed. else use time
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    // generate n integers between 0 and LIMIT, print those.
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // Success
    return 0;
}
