// counter.c
// Dani van Enk, 11823526

// include used libraries
#include <stdio.h>

// main loop
int main(void)
{
    // initialize counter
    int counter = 1;

    // loop and print counter
    while (counter < 10)
    {
        printf("%d\n", counter);
        counter += 2;
    }
}