#!/usr/bin/env python3
greeting = input("Greeting: ")
greeting = greeting.lower().strip()
hello_string = "hello"
money = 100
for i in range(5):
    try:
        if hello_string[i] != greeting[i]:
            break
    except IndexError:
        break
    if i == 4:
        money = 0

if money == 100 and greeting[0] == 'h':
    money = 20
print("${}".format(money))

