import sys
menu = {
    "Baja Taco": 4.00,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
}

def main():
    total = 0
    while True:
        try:
            item = input("Item: ")
        except EOFError:
            print()
            sys.exit(0)
        if(len(item) == 0):
            sys.exit(0)
        item = item.title()
        if item in menu:
            total += menu[item]
            print(f"Total: ${total:.2f}")

if __name__ == "__main__":
    main()