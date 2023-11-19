import os

# 我使用了老师推荐的sqlalchemy没有没有使用cs50sql，两种方法均可以可以运行数据库，cs50的库是老师制作的，功能简单但是好上手
# sqlalchemy是一个开源的库，功能更加强大，但是需要阅读文档。
# 如果使用过cs50的库再来使用sqlalchemy的话，读一下文档就很快可以上手了。

# from cs50 import SQL # use cs50 sql
from sqlalchemy import text, create_engine # use sqlalchemy
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
# db = SQL("sqlite:///birthdays.db") # use cs50 sql
engine = create_engine("sqlite+pysqlite:///birthdays.db", future=True)

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/", methods=["GET", "POST"])
def index():
    with engine.connect().execution_options() as conn:
        if request.method == "POST":

            # Add the user's entry into the database
            name = request.form.get("name")
            try:
                month = int(request.form.get("month"))
                day = int(request.form.get("day"))
            except ValueError:
                return("Please Input info")
            if month >= 1 and month <=12 and day >=1 and day <= 31:
                # db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?);", name, month, day) // use cs50 sql
                conn.execute(text("INSERT INTO birthdays (name, month, day) VALUES (:name,:month, :day)"), [{"name": name, "month":month, "day": day}])
                conn.commit()
                return redirect("/")
            else:
                return("please Input the correct info")
        else:

            # Display the entries in the database on index.html
            # rows = db.execute("SELECT * FROM birthdays;") # use cs50 sql
            rows = conn.execute(text("SELECT * FROM birthdays"))
            return render_template("index.html",rows=rows)


# delete the database
@app.route("/delete", methods=["POST"])
def delete():
    with engine.connect().execution_options() as conn:
        id = request.form.get("id")
        # db.execute("DELETE FROM birthdays where id = ?;", id) # use cs50 sql
        conn.execute(text("DELETE FROM birthdays WHERE id = (:id)"), [{"id": id}])
        conn.commit()
    return redirect("/")

