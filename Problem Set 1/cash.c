#include <cs50.h>
#include <stdio.h>

int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Prompt the user for change owed, in cents
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    // Calculate how many quarters you should give customer
    // Subtract the value of those quarters from cents
    int quarters = calculate_quarters(cents);
    cents -= quarters * 25;

    // Calculate how many dimes you should give customer
    // Subtract the value of those dimes from remaining cents
    int dimes = calculate_dimes(cents);
    cents -= dimes * 10;

    // Calculate how many nickels you should give customer
    // Subtract the value of those nickels from remaining cents
    int nickels = calculate_nickels(cents);
    cents -= nickels * 5;

    // Calculate how many pennies you should give customer
    // Subtract the value of those pennies from remaining cents
    int pennies = calculate_pennies(cents);
    cents -= pennies;

    // Sum the number of quarters, dimes, nickels, and pennies used
    int total_coins = quarters + dimes + nickels + pennies;
    // Print that sum
    printf("%d\n", total_coins);
}

int calculate_quarters(int cents)
{
    return cents / 25;
}

int calculate_dimes(int cents)
{
    return cents / 10;
}

int calculate_nickels(int cents)
{
    return cents / 5;
}

int calculate_pennies(int cents)
{
    return cents;
}
