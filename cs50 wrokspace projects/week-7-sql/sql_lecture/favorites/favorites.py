from cs50 import SQL

db = SQL("sqlite:///favorites.db")

favorite_question = input("Your favorite question: ")

rows = db.execute("SELECT COUNT(*) as nums FROM favorites WHERE problem = ?", favorite_question)

print(rows[0]['nums'])
