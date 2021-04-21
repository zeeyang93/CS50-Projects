#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int main()
{
    string text = get_string("Text:");
    int letters = 0;
    int words = 1;   //additional word for every number of spaces
    int sentences = 0;

    //run through and compare every array individually
    for (int i = 0; i < strlen(text); i++)

    {
        if (isalpha(text[i])) //true means alphabet, no need additional condition
        {
            letters++;
        }

        if (text[i] == ' ')
        {
            words++;
        }

        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    int index = round(0.0588 * 100 * (float)letters / words - 0.296 * 100 * (float)sentences / words - 15.8);


    if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    else if (index > 16)
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf("Grade %i\n", index);
    }

}