people = {
    "john" :"1234",
    "mike" :"5678",
    "lucy" : "1357"
}

name = input("Input the name:")

if name in people:
    print(f"the number is {people[name]}")
else:
    print(f"not found \"{name}\"")