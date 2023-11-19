def print_hash():
    while True:
        try:
            Height = int(input("Heigh: "))
        except ValueError:
            continue
        else:
            if Height <= 0 or Height >= 9:
                continue
            else:
                break
    for i in range(Height):
        print(" " * (Height - i - 1), end="")
        print("#" * (i + 1), end="")
        print()


def main():
    print_hash()


if __name__ == "__main__":
    main()
