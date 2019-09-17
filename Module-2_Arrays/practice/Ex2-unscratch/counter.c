// counter.c
// Dani van Enk, 11823526

// include used libraries
#include <stdio.h>

// main loop
int main(void)
{
    // initialize counter
    int counter = 11;

    // loop and print counter 6 times
    for (int i = 0; i < 6; i++)
    {
        printf("%d\n", counter);
        counter -= 2;
    }
}