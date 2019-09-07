#include <stdio.h>

int power(int x, int y);
int get_number(char str[124]);

int main(void)
{
    int minutes = get_number("How many minutes do you shower? (in whole minutes) ");

    printf("%d\n", minutes);
}

int get_number(char str[124])
{
    int output = 0;

    while (1)
    {
        char input[128];
        char numbers[10] = "0123456789";
        int power_10 = 0;
        int found = 0;

        for (int k = 0; k < 128; k++)
        {
            input[k] = 0;
        }

        output = 0;

        printf("%s", str);
        scanf("%128s", &input[0]);


        for (int i = 127; i >= 0; i--)
        {
            found = 0;

            for (int j = 0; j < 10; j++)
            {
                if (input[i] == numbers[j])
                {
                    output += j*power(10, power_10);
                    power_10++;
                    found++;
                    break;
                }
            }

            if (input[i] == 0)
            {
                continue;
            } else if (found == 0)
            {
                break;
            }
        }

        if (found != 0)
        {
            break;
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