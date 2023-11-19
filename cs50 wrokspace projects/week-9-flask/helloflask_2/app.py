from flask import Flask, render_template, request

app = Flask(__name__)

color = ["blue, "]
@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        color = request.form.get("color")
        return render_template("color.html", color=color)
    else:
        return render_template("index.html")