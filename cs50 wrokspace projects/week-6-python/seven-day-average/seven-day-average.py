import csv
import requests
import sys
from datetime import datetime, timedelta

def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    date_list = get_date()
    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader, date_list)


    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")


    while True:
        state = input("State: ")
        # if state in new_cases:
        states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")
    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states, date_list)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader, date_list):
    new_case = []
    index = 0
    create = 0
    for i in reader:
        for j in date_list:
            if i["date"] == j:
                # print("1 case in",i["state"], "date:", i["date"])
                create = 0
                for k in new_case:
                    if i["state"] == k["state"] and i["date"] == k["date"]:
                        k["cases"] += i["cases"]
                        create = 1
                if create == 0:
                    dict = {}
                    dict["date"] = i["date"]
                    dict["state"] = i["state"]
                    dict["cases"] = i["cases"]
                    new_case.append(dict)


    return new_case



# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states, date_list):
    list_print = []
    current_week = date_list[0:7]
    previous_week = date_list[7:14]
    # print(current_week)
    # print(previous_week)
    for i in states[0: len(states) - 1]:
        current_case = 0
        previous_case = 0
        current_case_0 = 0
        current_case_1 = 0
        previous_case_0 = 0
        previous_case_1 = 0
        for j in new_cases:
            if j["state"] == i:
                print(j)
            if j["date"] == date_list[0] and i == j["state"]:
                current_case_0 = int(j["cases"])
            if j["date"] == date_list[6] and i == j["state"]:
                current_case_1 = int(j["cases"])
            if j["date"] == date_list[7] and i == j["state"]:
                previous_case_0 = int(j["cases"])
            if j["date"] == date_list[13] and i == j["state"]:
                previous_case_1 = int(j["cases"])
            current_case = current_case_0 - current_case_1
            previous_case = previous_case_0 - previous_case_1
        try:
            percent = (current_case - previous_case) / previous_case
        except ZeroDivisionError:
            percent = 0
        if (percent > 0):
            print(f"From {date_list[6]} to {date_list[0]},:::Compare from, {date_list[13]} to {date_list[7]:.3f}.")
            print(f"{i}, had a 7-day average of {current_case} and an increase of {percent}%.")
        else:
            print(f"From {date_list[6]} to {date_list[0]},:::Compare from, {date_list[13]} to {date_list[7]}.")
            print(f"{i}, had a 7-day average of {current_case} and an decrease of {abs(percent):.3f}%.")




def get_date():
    day_14 = []
    date = input("Input the date, and the 7 days Covid data of that day will be calculated.\nFormat(YYYY--MM--DD): ")
    try:
        input_date = datetime.strptime(date, "%Y-%m-%d")
    except ValueError:
        print("Invalid date, please use \"YYYY-MM-DD\" and input the correct date.")
        sys.exit(1)
    else:
        # 遍历并输出前6天的日期
        for i in range(14):
            current_date = input_date - timedelta(days = i)
            day_14.append(current_date.strftime("%Y-%m-%d"))
            # print(current_date.strftime("%Y-%m-%d"))

    return day_14

main()
