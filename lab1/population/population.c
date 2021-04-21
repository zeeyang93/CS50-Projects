#include <cs50.h>
#include <stdio.h>

//Variables: s = start size, e = end size, y = number of years

int main(void)
{
    // TODO: Prompt for start size
    int s;
    do
    {
        s = get_int("What is the starting number?\n");
    }
    while (s < 9);

    // TODO: Prompt for end size

    int e;
    do
    {
        e = get_int("What is the final number?\n");
    }
    while (e < s);

    // TODO: Calculate number of years until we reach threshold
    // Initialise variably y = years. While start < end number, year + 1
    int y = 0;
    while (s < e)
    {
        s = (s + s / 3 - s / 4);
        y++;
    }
    // Self note: FOR loop also possible.


    // TODO: Print number of years
    printf("Years: %i\n", y);

}