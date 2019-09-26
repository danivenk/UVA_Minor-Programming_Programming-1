#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int numbers1[] = {7, 3, 4, 5};
    int length1 = 4;
    int numbers2[] = {5, 7, 2, 4, 6};
    int length2 = 5;
    int avg = 0;

    for (int i = 0; i < length1; i++)
    {
        if (numbers1[i] == 3)
        {
            printf("%d\n", numbers1[i]);
        }
    }

    for (int i=0; i < length2; i++)
    {
        avg += numbers2[i];
    }

    printf("%0.1f\n", (avg * 1.0) / length2);

    return 0;
}