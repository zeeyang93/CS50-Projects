#include <cs50.h>
#include <stdio.h>

// MASTERCARD: 16-Digit #'s, Start with: 51, 52, 53, 54, or 55
// VISA: 13-16-Digit #'s, Start with: 4
// AMEX: 15-Digit #'s, Star with: 34 or 37

// Luhn's Algorithm:
// 1. Multiply every other digit by 2, starting with the second number to the last
// 2. Add the sum of those digits
// 3. Add the sum of the other digits
// 4. If the total sum ends with a 0, it is valid!

int main(void)
{   int number;
    int digits;

    number = get_long("Card number: ");

    //count number of digits
    while (number > 0)
    {
    number = number / 10;
    digits++;
    }

    if (digits = 13 || digits = 15 || digits = 16)
    {
        for (int i = 0, i < digits, i++)
        {
            if (i % 2 == 0)
        }

    }

    else
    printf ("INVALID")

}