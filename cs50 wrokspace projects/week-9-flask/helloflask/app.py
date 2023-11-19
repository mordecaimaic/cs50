from flask import Flask, render_template, request

app = Flask(__name__)

color_list = ["red", "green", "blue"]

@app.route("/", methods = ["GET", "POST"])
def index():
    if request.method == "GET":
        return render_template("index.html", colors=color_list)
    else:
        color = request.form.get("color")
        if color not in color_list:
            return("your chose a color that is not exist!")
        return render_template("favorite_color.html", color_p = color)