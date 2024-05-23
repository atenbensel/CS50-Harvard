#include <stdio.h>
#include <cs50.h>

void print_row(int spaces, int bricks);

int main(void)
{
    // Ask the user for pyramid height
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1);

    // Print pyramid height
    for (int i = 0; i < n; i++)
    {
        // Print rows of bricks
        print_row (n - i - 1, i + 1);
    }
}

void print_row(int spaces, int bricks)
{
    // Spaces
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }
    // Bricks
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
    printf("\n");
}
