#include <stdio.h>

int get_number(char str[124])
{
    int output = 0;

    while (1)
    {
        char input[24];
        char numbers[10] = "0123456789";
        int power_10 = 0;

        printf("%s", str);
        scanf("%s", &input[0]);

        for (int i = 23; i >= 0; i--)
        {
            for (int j = 0; j < 10; j++)
            {
                if (input[i] == numbers[j])
                {
                    output += j*power(10, power_10);
                    power_10++;
                } else
                {
                    return 0;
                }
            }
        }
    }

    return output;
}

int power(int x, int y)
{
    int result = x;

    if (y == 0)
    {
        result = 1;
    } else if (y == 1)
    {
        return result;
    } else
    {
        while (y > 1)
        {
            result *= x;
            y--;
        }
    }

    return result;
}