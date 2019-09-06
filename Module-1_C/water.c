// Bottles per water in a shower session
// According to exercise error-checking is omitted

//including standard I/O header
#include <stdio.h>

//main loop
int main(void)
{
    //minutes variable
    int minutes;

    //user input
    printf("How many minutes do you shower? (in whole minutes) ");
    scanf("%d", &minutes);

    //conversion to bottles
    int bottles = 1.5 * 128 / 16 * minutes;

    //output
    printf("This costs you %d bottles of water!\n", bottles);
}