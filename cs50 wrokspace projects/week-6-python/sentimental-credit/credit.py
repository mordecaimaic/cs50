def main():
    card_num = get_card_num()
    card_num_str = str(card_num)
    num_digits = len(card_num_str)

    if (num_digits == 15):
        if check_American_press(card_num_str):
            print("AMEX")
            return

    if (num_digits == 16):
        if check_Master_card(card_num_str):
            print("MASTERCARD")
            return


    if (num_digits == 13 or num_digits == 16) and card_num_str[0] == '4':
        if check_visa(card_num_str):
            print("VISA")
            return
    print("INVALID")

def get_card_num():
    while True:
        try:
            card_num_str = input("Number: ")
            card_num = int(card_num_str)
            return card_num
        except ValueError:
            pass

def check_visa(card_num_str):
    check_point = 0
    for i in range(len(card_num_str) - 2,-1, -2):
        pluse_2 = int(card_num_str[i]) * 2
        if pluse_2 > 10:
            digit = pluse_2 % 10
            check_point += digit + 1
        else:
            check_point += pluse_2
    for i in range(len(card_num_str) - 1, -1, -2):
        check_point += int(card_num_str[i])
    if check_point % 10 == 0:
        return True
    else:
        # print(check_point)
        return False

def check_American_press(card_num_str):
    if card_num_str[0:2] == "34" or card_num_str[0:2] == "37":
        return True
    else:
        return False


def check_Master_card(card_num_str):
    if card_num_str[0:2] == "51" or card_num_str[0:2] == "52" or card_num_str[0:2] == "53" or card_num_str[0:2] == "54" or card_num_str[0:2] == "55":
        return True
    else:
        return False





if __name__ == "__main__":
    main()