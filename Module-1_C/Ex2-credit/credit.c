//Dani van Enk, 11823526

//including standard I/O header and cs50 headers
#include <stdio.h>
#include <cs50.h>

char valid(long num);

int main(void)
{
    long cred_num = get_long("Please type your credit-card number here: ");
    int validation = valid(cred_num);
    // char output

    // if (validation == 1)
    // {
    //     output = "VALID\n";
    // } else
    // {
    //     output = "INVALID\n";
    // }

    printf("%d\n", validation);

    return 0;
}

char valid(long num)
{
    long num1 = num/10;
    long num2 = num;
    int first = 0;
    int second = 0;

    while (num1 != 0)
    {

        int digit = 2*(num1 - num1/10*10);

        if (digit >= 10 && digit < 20)
        {
            int digitdigit = 0;

            while (digit != 0)
            {
                digitdigit += (digit - digit/10*10);
                digit /= 10;
            }

            first += digitdigit;
        } else if (digit > 20)
        {
            printf("Something went wrong, please try again.\n");
        } else
        {
            first += digit;
        }

        num1 /= 100;
    }

    while (num2 != 0)
    {
        second += (num2 - num2/10*10);

        num2 /= 100;
    }

    if ((first + second) % 10 == 0)
    {
        return 1;
    } else
    {
        return 0;
    }
}