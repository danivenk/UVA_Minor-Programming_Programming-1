#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *tale = "It was the best of times";
    char *bob = "pRoGgRaMmInG In c";
    char *knight = "Batman";
    int i = 0;
    int j = 0;
    int k = 0;
    int up = 'a' - 'A';

    do
    {
        // printf("%c\n", tale[i]);
        if (tale[i] == ' ')
        {
            printf("%c", tale[i - 1]);
        }

        i++;
    } while (tale[i] != '\0');

    printf("\n");

    do
    {
        if (bob[j] >= 'a' && bob[j] <= 'z')
        {
            printf("%c", bob[j] - up);
        }
        else
        {
            printf("%c", bob[j]);
        }

        j++;
    } while (bob[j] != '\0');

    printf("\n");

    do
    {
        // printf("%c\n", knight[k]);
        if (knight[k] == 'a')
        {
            printf("%c", 'o');
        }
        else
        {
            printf("%c", knight[k]);
        }

        k++;
    } while (knight[k] != '\0');

    printf("\n");

    return 0;
}