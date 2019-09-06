#include <stdio.h>

int main(void)
{
    while (1)
    {
        char input[24];
        char numbers[10] = "0123456789";

        printf("integer please: ");
        scanf("%s", &input[0]);

        for (int i = 0; i < 24; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (input[i] == numbers[j])
                {
                    printf("%d\n", j);
                }
            }
        }

        printf("%s\n", input);

        return 0;
    }

    return 0;
}