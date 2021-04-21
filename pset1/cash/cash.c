#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Get value of change
    float change;
    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0);

    // round cents to integer. Reason being it is inprecise to divide float values in C
    int cents = round(change * 100);


    // calculate number of coins, of 25/10/5/1
    int coins = 0;

    while (cents >= 25)
    {
        cents = cents - 25;
        coins++;
    }

    while (cents >= 10)
    {
        cents = cents - 10;
        coins++;
    }

    while (cents >= 5)
    {
        cents = cents - 5;
        coins++;
    }

    while (cents >= 1)
    {
        cents = cents - 1;
        coins++;
    }

    //Print no. of coins
    printf("Coins needed %d\n", coins);



}