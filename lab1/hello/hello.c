
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Request user input for name
    string name = get_string("What is your name?\n");
    printf("hello, %s!\n", name);
}
