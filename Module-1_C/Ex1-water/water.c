// Bottles per water in a shower session
// According to exercise error-checking is omitted

//including standard I/O header and cs50 headers
#include <stdio.h>
#include <cs50.h>

//main loop
int main(void)
{
    //user input
    int minutes = get_int("How many minutes do you shower? (in whole minutes) ");

    //conversion to bottles
    int bottles = 1.5 * 128 / 16 * minutes;

    //output
    printf("This costs you %d bottles of water!\n", bottles);

    //exit main loop
    return 0;
}