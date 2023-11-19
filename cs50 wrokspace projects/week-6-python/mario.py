def main():
        height = get_length()
        print_hash(height)
        n = int(input("input the length:"))



def print_hash(n):
    for i in range(n):
         print("#")


def get_length():
    while True:
        try:
            n = int(input("input the length:"))
            if n > 0:
                 return n
        except ValueError:
            print("error input")


main()