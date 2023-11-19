import csv
from cs50 import SQL


db = SQL("sqlite:///new_roster.db")

# create the schema of the sql data_base
# If raise Runtimeerror when creating schema
# That mean the table is already exist
# The programne will ask if the user want to drop all the tables
# If the users say yes, and it will drop all tables
# The programe will re-create the schema of the data_base in next running
def create_schema():

    table_count = 0
    try:
        db.execute(
        '''
            CREATE TABLE students(
            id INTEGER,
            student_name TEXT,
            PRIMARY KEY(id)
            );
            '''
        )
        print("Table students create!")
        table_count += 1
    except RuntimeError:
        ...

    try:
        db.execute(
        '''
            CREATE TABLE houses(
            id INTEGER,
            house TEXT,
            head TEXT,
            PRIMARY KEY(id)
            );
            '''
        )
        print("Table houses create!")
        table_count += 1
    except RuntimeError:
        ...

    try:
        db.execute(
        '''
            CREATE TABLE assignments(
            student_id INTEGER,
            house_id INTEGER,
            FOREIGN KEY(student_id) REFERENCES students(id),
            FOREIGN KEY(house_id) REFERENCES houses(id)
            );
            '''
        )
        print("Table assignments create!")
        table_count += 1
    except RuntimeError:
        ...

    if table_count !=3 :
        Drop = input("Schema alreay exist.Would you like to Drop all the tables>(Y/N)")
        if Drop.lower() == 'y' or Drop.lower() == 'yes':
            try:
                db.execute("DROP TABLE assignments;")
                print("Table assignments drop!")
            except RuntimeError:
                ...

            try:
                db.execute("DROP TABLE students;")
                print("Table students drop!")
            except RuntimeError:
                ...

            try:
                db.execute("DROP TABLE houses;")
                print("Table houses drop!")
            except RuntimeError:
                ...



def write_students():

    with open("students.csv", "r") as input_file:
        input_put = csv.DictReader(input_file)
        for row in input_put:
            # print(row["student_name"])
            db.execute("""
                INSERT INTO students (student_name)
                VALUES(?)
                ;""", row["student_name"])


def write_houses():
    # houses is list contain the unique house and the house id
    houses = []
    dict = {}
    with open("students.csv", "r") as input_file:
        input_file = csv.DictReader(input_file)
        for row in input_file:
            # print(row["house"], row["head"])
            # dict = {}
            dict["house"] = row["house"]
            dict["head"] = row["head"]
            print(dict)
            for i in houses:
                # If we ha
                if dict == i:
                    break
            else:
                # If the house never happen befoere
                # It will be added to the houses table
                houses.append(dict)
                db.execute("""
                    INSERT INTO houses (house, head)
                    VALUES(?, ?)
                    ;""", dict["house"], dict["head"])


def write_aggignments():

    sql_houses = db.execute("""
                    SELECT *
                    FROM houses;
                    """)
    # print(sql_houses)

    with open("students.csv","r") as input_file:
        input_file = csv.DictReader(input_file)
        for row in input_file:
            student_id = row["id"]
            house_name = row["house"]
            for i in sql_houses:
                if i["house"] == house_name:
                    house_id = i["id"]

            print(f"student_id = {student_id}, house_id = {house_id}")
            db.execute("""
                INSERT INTO assignments (student_id, house_id)
                VALUES(?, ?)
                ;""", student_id, house_id)
            # print(f"student_id = {student_id}, house_id = {house_id}")







def main():
    create_schema()
    try:
        write_students()
        write_houses()
        write_aggignments()
    except RuntimeError:
        print("Empty table, RUN the programe again")




if __name__ == "__main__":
    main()

