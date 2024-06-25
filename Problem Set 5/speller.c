#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Define number of buckets in hash table
const unsigned int N = 10007;  // A larger number of buckets to reduce collisions maybe?

// Hash table
node *table[N];

// Number of words in dictionary
unsigned int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get the hash value for the word
    unsigned int index = hash(word);
    node *cursor = table[index];

    // Traverse the linked list at the hash table index
    while (cursor != NULL)
    {
        // Compare word case-insensitively
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // A better hash function based on the djb2 algorithm
    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + tolower(c);  // hash * 33 + c
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // Buffer to hold each word
    char word[LENGTH + 1];

    // Read each word from the dictionary
    while (fscanf(dict, "%s", word) != EOF)
    {
        // Create a new node for each word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(dict);
            return false;
        }

        // Copy the word into the new node
        strcpy(new_node->word, word);

        // Get the hash value for the word
        unsigned int index = hash(word);

        // Insert the node into the hash table at that index
        new_node->next = table[index];
        table[index] = new_node;

        // Increment the word count
        dict_size++;
    }

    // Close the dictionary file
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate over each bucket in the hash table
    for (unsigned int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        // Traverse and free the linked list
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    return true;
}
