// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// Here, we use arbitary 100000
const unsigned int N = 100000;

// Initialise word count
int word_count = 0;


// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Hash word we intend to search for to get hash value
    int hash_value = hash(word);

    // Access the linked list to a temporary cursor
    node *cursor = table[hash_value];

    // Compare to the linked list by going through it
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }

        // moves cursor to the next node. This will keep looping until cursor reaches the end
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
// Define our own hash function. There are many ways to do it.
unsigned int hash(const char *word)
{
    // TODO
    // Function will take a string and return an index
    // This function add the ASCII values of each character in the word together (will take a lot of memory N !!)
    long sum = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }

    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dictionary
    FILE *file = fopen(dictionary, "r");

    // If file is not opened, return false
    if (file == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }

    // Initialise word array
    char next_word[LENGTH + 1];


    // Scan dictionary for strings that are not at the end of the file. Keep reading %s string until EOF (End of file) and store it in next_word
    while (fscanf(file, "%s", next_word) != EOF)
    {
        // Allocate memory for new node to store the new word
        node *n = malloc(sizeof(node));

        // Always check for NULL
        if (n == NULL)
        {
            return false;
        }

        // Copy the new word into the pointer
        strcpy(n->word, next_word);

        // Now to determine how to insert this new word into hash table

        // Hash the word to get hash value;
        int hash_value = hash(next_word);

        // Now to update the new node's pointer to point to the first element of the linked list in the hash table CURRENTLY
        n->next = table[hash_value];

        // Next, we should update the hash table index to point at our new node
        table[hash_value] = n;

        // Implement word counter for size whenever a word is loaded into the array
        word_count++;

    }

    // Close file
    fclose(file);

    //If dict is loaded, return true
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (word_count > 0)
    {
        return word_count;
    }

    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    // Interates over hash table, free node in each linked list of Table[]
    for (int i = 0; i < N; i++)
    {
        // Assign cursor pointing to the linked list
        node *n = table[i];

        // Loop through linked list
        while (n != NULL)
        {
            // Create temporary cursor
            node *temp = n;

            // Point the cursor to the next element first;
            n = n->next;

            // free temp
            free(temp);

            // in the end, n will reach until the end of list, and freeing all the memory it loops and interates on its way
        }

        // Cursor will reach a point where it is pointing to NULL. Here we need to return
        // we need the condition i == N - 1 too, as there are other possible conditions where n == NULL, eg. Table is invalid !
        if (n == NULL && i == N - 1)
        {
            // return true when free is successful
            return true;
        }
    }

    return false;
}
