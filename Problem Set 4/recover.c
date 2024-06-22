#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Define BYTE as an alias for uint8_t for clarity
typedef uint8_t BYTE;

// Define the block size as a constant
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Check if exactly one command-line argument is provided
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open the forensic image file for reading
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Buffer to store a block of data
    BYTE buffer[BLOCK_SIZE];

    // Counter to keep track of the number of JPEG files recovered
    int cnt = 0;

    // File pointer for the output JPEG file
    FILE *output = NULL;

    // Array to hold the filename of the output JPEG
    char filename[8];

    // Read the forensic image file block by block
    // Do I look like I know what a JPEG is???
    // I just want a picture of a gosh dang hot dog
    while (fread(&buffer, BLOCK_SIZE, 1, input))
    {
        // Check if the block indicates the start of a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If this is not the first JPEG, close the previous output file
            if (cnt > 0)
            {
                fclose(output);
            }

            // Generate a new filename for the new JPEG
            sprintf(filename, "%03i.jpg", cnt);

            // Open a new file for writing the JPEG
            output = fopen(filename, "w");
            if (output == NULL)
            {
                printf("Could not create file %s.\n", filename);
                fclose(input);
                return 1;
            }

            // Increment the JPEG counter
            cnt++;
        }

        // If a JPEG file is open, write the current block to it
        if (output != NULL)
        {
            fwrite(&buffer, BLOCK_SIZE, 1, output);
        }
    }

    // Close any remaining open files
    fclose(input);
    if (output != NULL)
    {
        fclose(output);
    }

    return 0;
}
