#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

bool is_valid_key(string key);
string encrypt(string plaintext, string key);

int main(int argc, string argv[])
{
    // Check for the correct number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check if the key is valid
    if (!is_valid_key(argv[1]))
    {
        printf("Key is invalid. Key must contain 26 characters, each being a unique alphabetic character.\n");
        return 1;
    }

    // Get plaintext from user
    string plaintext = get_string("plaintext: ");

    // Encrypt and print ciphertext
    printf("ciphertext: %s\n", encrypt(plaintext, argv[1]));

    return 0;
}

// Function to check if the key is valid
bool is_valid_key(string key)
{
    // Check if the key length is 26
    if (strlen(key) != 26)
    {
        return false;
    }

    // Initialize an array to mark if each letter has been encountered
    bool encountered[26] = { false };

    // Iterate through the key
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        // Check if character is not an alphabet
        if (!isalpha(key[i]))
        {
            return false;
        }

        // Convert character to uppercase for uniformity
        char c = toupper(key[i]);

        // Check if character has been encountered before
        if (encountered[c - 'A'])
        {
            return false;
        }

        // Mark character as encountered
        encountered[c - 'A'] = true;
    }

    return true;
}

// Function to encrypt plaintext using the given key
string encrypt(string plaintext, string key)
{
    // Initialize a string to store ciphertext
    string ciphertext = plaintext;

    // Iterate through the plaintext
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // Check if character is an alphabet
        if (isalpha(plaintext[i]))
        {
            // Determine if character is uppercase or lowercase
            char base = isupper(plaintext[i]) ? 'A' : 'a';

            // Map plaintext character to corresponding key character
            ciphertext[i] = isupper(plaintext[i]) ? toupper(key[plaintext[i] - 'A']) : tolower(key[plaintext[i] - 'a']);
        }
    }

    return ciphertext;
}
