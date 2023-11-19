a_list = []

state_1 = {"state" : "new york", "number" : 5}
state_2 = {"state" : "penny", "number" : 8}
state_3 = {"state" : "new york", "number" : 8}

a_list.append(state_1)
a_list.append(state_2)
a_list.append(state_3)


a_tuple = (3,"abc")

print(a_tuple[1])

from cs50 import get_float

f = get_float("input float")
print(f)