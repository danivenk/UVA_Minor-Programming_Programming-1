// initials.c give the initials of any name the user prompts
// Dani van Enk, 11823526

// including the standard I/O, standard library and ctype library
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// main loop
int main(void)
{
    // defining SIZE and predefining the user_input
    int size = 1028;
    char input[size];

    // promting user_input
    printf("Please put your name: ");
    fgets(input, size, stdin);

    // loop for the initials
    for (int i = 0; i < size; i++)
    {
        // print the character after an space character
        if (input[i] == ' ' && input[i + 1] != ' ' && input[i] != '\n')
        {
            printf("%c", toupper(input[i + 1]));
        }
        // print the fist character
        else if (i == 0 && input[i] != ' ')
        {
            printf("%c", toupper(input[i]));
        }
        // break at end of string
        else if (input[i] == '\0')
        {
            break;
        }
    }

    // line break
    printf("\n");

    // end program
    return 0;
}