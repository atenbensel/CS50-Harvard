#include <cs50.h>
#include <stdio.h>

bool check_validity(long long ccn);
int find_length(long long n);
bool checksum(long long ccn);
void print_credit_card_brand(long long ccn);

int main(void)
{
    long long credit_card_number;

    // Get credit card number from user
    do
    {
        credit_card_number = get_long("Number: ");
    }
    while (credit_card_number < 0);

    // Check if the credit card number is valid and print the appropriate credit card brand
    if (checksum(credit_card_number))
    {
        print_credit_card_brand(credit_card_number);
    }
    else
    {
        printf("INVALID\n");
    }
}

// Function to check the validity of the credit card number
bool checksum(long long ccn)
{
    int sum = 0;
    int length = find_length(ccn);
    for (int i = 0; i < length; i++, ccn /= 10)
    {
        if (i % 2 == 0)
        {
            sum += ccn % 10;
        }
        else
        {
            int digit = 2 * (ccn % 10);
            sum += digit / 10 + digit % 10;
        }
    }
    return (sum % 10 == 0);
}

// Function to determine the length of the number
int find_length(long long n)
{
    int length;
    for (length = 0; n != 0; n /= 10, length++);
    return length;
}

// Function to print the credit card brand based on the number prefix and length
void print_credit_card_brand(long long ccn)
{
    int length = find_length(ccn);
    int first_two_digits = (int)(ccn / pow(10, length - 2));

    if ((first_two_digits == 34 || first_two_digits == 37) && length == 15)
    {
        printf("AMEX\n");
    }
    else if ((first_two_digits >= 51 && first_two_digits <= 55) && length == 16)
    {
        printf("MASTERCARD\n");
    }
    else if ((first_two_digits / 10 == 4) && (length == 13 || length == 16))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
