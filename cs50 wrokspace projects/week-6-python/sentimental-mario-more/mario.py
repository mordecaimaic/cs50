def print_hash():
    while True:
        try:
            Height = int(input("Height: "))
            if Height <=0 or Height >=9:
                continue
            break
        except ValueError:
            ...
    for i in range(Height):
        print(" " * (Height - i - 1), end="")
        print("#" * (i + 1), end="")
        print("  ", end="")
        print("#" * (i + 1), end="")
        print()

def main():
    print_hash()

if __name__ == "__main__":
    main()