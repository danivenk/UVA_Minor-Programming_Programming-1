
// Dani van Enk, 11823526

// including the standard I/O, standard library and ctype library
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void)
{
    // defining SIZE and predefining the user_input
    int size = 128;
    char input[size];

    printf("Please put your name: ");
    fgets(input, size, stdin);

    for (int i = 0; i < size; i++)
    {

        if (input[i] == ' ' && input[i + 1] != ' ' && input[i] != '\n')
        {
            printf("%c", toupper(input[i + 1]));
        }
        else if (i == 0 && input[i] != ' ')
        {
            printf("%c", toupper(input[i]));
        }
        else if (input[i] == '\0')
        {
            break;
        }
    }

    printf("\n");
}