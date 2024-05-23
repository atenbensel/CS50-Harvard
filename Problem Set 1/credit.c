#include <cs50.h>
#include <stdio.h>

void print_pyramid(int height);

int main(void)
{
    int height;
    // Prompt the user for pyramid height between 1 and 8
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Print the pyramid
    print_pyramid(height);
}

void print_pyramid(int height)
{
    for (int i = 1; i <= height; i++)
    {
        // Print leading spaces for alignment
        for (int j = 0; j < height - i; j++)
        {
            printf(" ");
        }
        // Print the left half of the pyramid
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        // Print the gap between pyramids
        printf("  ");
        // Print the right half of the pyramid
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        // Move to the next line
        printf("\n");
    }
}
