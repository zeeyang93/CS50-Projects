#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void substitute(); //function to do substitution. Void function as we do not expect return value to feed elsewhere
void plaintext_alphabet_array(char plaintext, string key);
//function to get alphabet array value of plain text[i], to compare with Encryption Key[i]. Then, print out the Encrypted Key [i]

//check if entered key is 26 characters
int main(int argc, string argv [])
{
    if (argc == 2) //argc is number of commands in terminal
    {
        if (strlen(argv[1]) == 26)
        {
            for (int i = 0; i < strlen(argv[1]); i++)
            {
                if (isalpha(argv[1][i]) == 0) //non-alphabet will return 0
                {
                    printf("Key must contain 26 characters.\n");
                    return 1;
                }

                //Nested for loop within for loop. This one particular Encryption Key[i] will check against the whole of Encryption Key. j = 1 + 1 because we are comparing with the next character.
                for (int j = i + 1; j < strlen(argv[1]); j++)
                {
                    if (toupper(argv[1][j]) == toupper(argv[1][i]))
                    {
                        printf("Key must not contain repeated alphabets.\n");
                        return 1;
                    }
                }

            }

            substitute(argv[1]);
            return 0;

        }

        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}


void substitute(string Encryptkey) //function to substitute plain text to cipher text. Requires string input "Encryption key"
{
    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i])) //check if plaintext array is alphabet. Result is true/false
        {
            char x = plaintext[i];
            if (islower(plaintext[i]))
            {
                plaintext_alphabet_array(tolower(x), Encryptkey); //this function will take 2 inputs (character, string), and print out result
            }
            else
            {
                plaintext_alphabet_array(toupper(x), Encryptkey);
            }
        }

        else
        {
            printf("%c", plaintext[i]); //this is to print elements that is not alphabet, eg. space, special characters, commas...
        }
    }

    printf("\n");
}

//Further substitution of Function(Substitute). Converting single chracter plaintext[i] into array value of alphabet array. (Eg. plaintext = j | aphabet array = 10). Then, matches that alphabet array with Encryption Key array
void plaintext_alphabet_array(char p, string Encryptkey)
{
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < strlen(alphabet); i++) //this will compare the input single character with each element in alphabet array
    {
        if (islower(p)) //Plain text is lower case
        {
            if (p == tolower(alphabet[i])) //if temporary placeholder matches alphabet array
            {
                printf("%c", tolower(Encryptkey[i])); //it will print out the Encrypted Key for that value/position of i
            }
        }
        else
        {
            if (p == toupper(alphabet[i]))
            {
                printf("%c", toupper(Encryptkey[i]));
            }
        }
    }
}