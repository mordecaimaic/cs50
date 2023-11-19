# cash function,  greedy algorithm
from cs50 import get_float


def main():
    counts = 0
    change = get_change()
    # change = get_float("Change: ")

    quarters = get_quarters(change)
    change -= 25 * quarters

    dimes = get_dimes(change)
    change -= 10 * dimes

    nickels = get_nickels(change)
    change -= 5 * nickels

    pennies = get_pennies(change)
    change -= 1 * pennies

    counts = quarters + dimes + nickels + pennies
    print(counts)


def get_change():
    while True:
        try:
            change = float(input("change owed: "))
            if change < 0:
                continue
            else:
                return change * 100
        except ValueError:
            pass


def get_quarters(change):
    counts = 0
    while change - 25 >= 0:
        counts += 1
        change -= 25
    return counts


def get_dimes(change):
    counts = 0
    while change - 10 >= 0:
        counts += 1
        change -= 10
    return counts


def get_nickels(change):
    counts = 0
    while change - 5 >= 0:
        counts += 1
        change -= 5
    return counts


def get_pennies(change):
    counts = 0
    while change - 1 >= 0:
        counts += 1
        change -= 1
    return counts


if __name__ == "__main__":
    main()
