//Dani van Enk, 11823526

//including standard I/O header and cs50 headers
#include <stdio.h>
#include <cs50.h>

int valid(long num);

int main(void)
{
    long cred_num = get_long("Please type your credit-card number here: ");

    printf("%d\n", valid(cred_num));
}

int valid(long num)
{
    long num1 = num/10;
    long num2 = num;
    int first = 0;
    int second = 0;

    while (num1 != 0)
    {

        int digit = 2*(num1 - num1/10*10);

        printf("digit: %d\n", digit);

        if (digit >= 10 && digit < 20)
        {
            int digitdigit = 0;

            printf("bigger\n");

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

    return first;
}