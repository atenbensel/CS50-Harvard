from cs50 import get_float

dollars = 0
while dollars <= 0:
    try:
        dollars = float(input("Change owed: $"))
        if dollars <= 0:
            print("Please enter a value greater than 0.")
    except ValueError:
        print("Enter a valid number.")

cents = round(dollars * 100)
quarters = cents // 25
cents %= 25
dimes = cents // 10
cents %= 10
nickels = cents // 5
cents %= 5
pennies = cents
coins = quarters + dimes + nickels + pennies

print(coins)
