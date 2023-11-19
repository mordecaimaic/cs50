import os
import datetime


from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

language = {"EN": 1, "CN": 0}


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    """Show portfolio of stocks"""
    if request.method == "POST":
        if language["EN"] == 1:
            language["EN"] = 0
            language["CN"] = 1
        elif language["CN"] == 1:
            language["EN"] = 1
            language["CN"] = 0
        return redirect("/")

    else:
        stock_lookup = {}
        stockown = db.execute("SELECT * FROM stockown WHERE user_id = ?;", session["user_id"])
        cash = db.execute("SELECT * FROM users WHERE id = ?;", session["user_id"])[0]["cash"]
        # stock_value用来遍历用户持有的股票，计算总共的股值资产
        stock_value = 0
        profit_loss = 0
        # 遍历用户持有的每一项股票仓库
        # 分别通过lookup函数获得股票的价格
        for i in stockown:
            stock_symbol = i["stock_symbol"]
            current_price = lookup(stock_symbol)["price"]
            buy_price = i["buy_price"]
            shares = i["shares"]
            # stock_value: 股票总值 = 股票目前单价 * 持有的股份数量
            stock_value += current_price * shares
            profit_loss += (current_price - buy_price) * shares
            # 将从api接口获取到的价格保存到stock_lookup字典里面
            stock_lookup[stock_symbol] = current_price
        if language["EN"] == 1:
            return render_template("index.html", stockown=stockown, current_price=stock_lookup, cash=cash, stock_value=stock_value, profit_loss=profit_loss)
        elif language["CN"] == 1:
            return render_template("index_cn.html", stockown=stockown, current_price=stock_lookup, cash=cash, stock_value=stock_value, profit_loss=profit_loss)


# 购买股票
@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    row = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    cash=row[0]["cash"]
    if request.method == "POST":
        lookup_result = lookup(request.form.get("symbol"))
        # 检测购入股份数量是否正确
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("shares number is not correct", 400)
        # 检测购入股份数量是否大于0
        if shares <= 0 :
            return apology("shares must greater than 0", 400)
        # 检测是否输入正确股票代码
        elif not lookup_result:
            return apology("stock symbol doesn't exist", 400)

        stock_name = lookup_result["name"]
        price = lookup_result["price"]
        symbol = lookup_result["symbol"]
        # 检测用户是否有足够余额购入股票
        remainder = cash - price * shares
        if remainder < 0:
            return apology("you don't have enough money", 400)
        else:
            cash = remainder

        current_time = datetime.datetime.now()
        formatted_time = current_time.strftime("%Y-%m-%d %H:%M:%S")
        profit_loss = -shares * price

        # 查询用户是否购买过该股票
        stock_own = db.execute("SELECT * FROM stockown WHERE user_id = ? and stock_symbol = ?", session["user_id"], symbol)
        # 更新用户持有股票
        # 如果用户已经购买过该股票，则更新股票的购入价格，以及股份数
        if stock_own:
            old_value = stock_own[0]["buy_price"] * stock_own[0]["shares"]
            new_value = price * shares
            new_shares = shares + stock_own[0]['shares']
            new_price = (old_value + new_value) / new_shares
            db.execute("UPDATE stockown SET buy_price = ?, shares = ? WHERE user_id = ? and stock_symbol = ?", new_price, new_shares, session["user_id"], symbol)
        else:
            # 如果用户没有购买过该股票，则直接加入一行该股票的持有信息
            db.execute("INSERT INTO stockown(stock_name, stock_symbol, user_id, shares, buy_price) VALUES(?, ?, ?, ?, ?);", stock_name, symbol, session["user_id"], shares, price)
        # 添加用户交易记录
        db.execute("INSERT INTO transactions(stock_symbol, user_id, trade_mode, shares, price, profit_loss, time) VALUES(?, ?, ?, ?, ?, ?, ?)", symbol, session["user_id"], "Buy", shares, price, profit_loss, formatted_time)
        # 更新用户当前现金
        db.execute("UPDATE users SET cash=? WHERE id = ?;", cash, session["user_id"])

        return render_template("buy.html", name = row[0]["username"], cash=cash, symbol=symbol, price=price, shares=shares)
    else:
        return render_template("buy.html", name = row[0]["username"], cash=cash)


@app.route("/history", methods=["GET", "POST"])
@login_required
def history():
    """Show history of transactions"""
    if request.method == "POST":
        db.execute("DELETE FROM transactions WHERE user_id = ?", session["user_id"])
        return redirect("/history")
    else:
        transactions = db.execute("SELECT * FROM transactions WHERE user_id = ?;", session["user_id"])
    return render_template("history.html", history = transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    row = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    if request.method == "POST":
        lookup_result = lookup(request.form.get("symbol"))
        # 通过api返回的查询值，判断股票代码是否正确
        if not lookup_result:
            return apology("stock symbol doesn't exist", 400)
        return render_template("quote.html", lookup_result=lookup_result, stock_name=lookup_result["name"], stock_price=lookup_result["price"], username = row[0]["username"], cash=row[0]["cash"])
    else:
        return render_template("quote.html", username = row[0]["username"], cash=row[0]["cash"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # 确保注册者输入用户名
        if not request.form.get("username"):
            return apology("must provide username", 400)
        # 确保注册者输入密码
        elif not request.form.get("password"):
            return apology("must provide password", 400)
        # 确保注册者输入确认密码
        elif not request.form.get("confirmation"):
            return apology("must confirm password", 400)
        # 确保两次输入的密码是相同的
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("the password didn't match", 400)

        username = request.form.get("username")
        name_repeat = db.execute("SELECT * FROM users WHERE username = ?;", username)
        # 确保用户名没有重复
        if name_repeat:
            # 用户名重复，返回提示
            # return render_template("register.html", repeat_name_apology = username, name_repeat=name_repeat)
            return apology("repeated username, try to change a username", 400)
        else:
            # 注册成功，将用户数据保存到数据库，其中密码通过hash加密后保存到sql数据库
            password = request.form.get("password")
            hash = generate_password_hash(password)
            db.execute("INSERT INTO users(username, hash) VALUES(?, ?);", username, hash)
            row = db.execute("SELECT * FROM users WHERE username = ?;", username)
            # 注册成功，写入session自动登录
            session["user_id"] = row[0]["id"]
            return redirect("/")
    else :
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_info = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    cash = user_info[0]["cash"]
    sell_flag = False
    stock_own_all = db.execute("SELECT * FROM stockown WHERE user_id = ?",session["user_id"]) # 获取用户当前拥有的所有股票，用来遍历填充选项里面的option

    if request.method == "POST":
        # 用户出售股票，symbol大小写不敏感
        try:
            symbol = request.form.get("symbol").upper()
        except AttributeError:
            return apology("missing symbol", 400)
        stock_own = db.execute("SELECT * FROM stockown WHERE stock_symbol = ? and user_id = ?", symbol, session["user_id"])

        # 后端验证股票symbol模块，确保股票代码正确
        # 检测用户输入的售出股份数量是否正确，出售股份数量必须为大于0,且不能大于用户持有的股份数量
        # 检测用户是否持有准备出售的股票
        try:
            share_sell = int(request.form.get("shares"))
        except ValueError:
            return apology("shares number is not correct", 400)
        if share_sell <= 0:
            return apology("shares must greater than 0", 400)
        elif not stock_own:
            return apology("you don't own that stock", 400)
        elif share_sell > stock_own[0]["shares"]:
            return apology("not enough shares to sell", 400)

        # 股票出售成功，准备数据进行数据库的更新
        # 变量说明
        # buy_price:购入价格，current_price:当前价格，share_own:目前持有的股份，share_sell:打算出售的股份，revenue:卖出获得的现金💰，stock_return:卖出股票的盈亏，cash:用户持有现金
        buy_price = stock_own[0]["buy_price"]
        current_price = lookup(symbol)["price"]
        share_own = stock_own[0]["shares"]
        revenue = current_price * share_sell
        share_own = share_own - share_sell
        cash += revenue
        stock_return = (current_price - buy_price) * share_sell

        # 获得当前时间并将其格式化
        current_time = datetime.datetime.now()
        formatted_time = current_time.strftime("%Y-%m-%d %H:%M:%S")
        # 更新用户持有的股份数量
        if share_own == 0:
            # 若用户持有的股份为0，则删除该股份信息
            db.execute("DELETE FROM stockown WHERE user_id = ? and stock_symbol = ?;", session["user_id"], symbol)
        else:
            # 用户还有剩余股份，则更新卖出后的剩余股份数量
            db.execute("UPDATE stockown SET shares = ? WHERE user_id = ? and stock_symbol = ?", share_own, session["user_id"], symbol)
        # 更新交易记录
        db.execute("INSERT INTO transactions(stock_symbol, user_id, trade_mode, shares, price, profit_loss, time) VALUES(?, ?, ?, ?, ?, ?, ?)", symbol, session["user_id"], "Sell", share_sell, current_price, stock_return, formatted_time)
        #更新用户余额
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])
        sell_flag = True
        return render_template("sell.html", sell_flag=sell_flag, name=user_info[0]["username"], cash=cash, symbol=symbol, revenue=revenue, stock_return=stock_return, stock_own_all=stock_own_all)
    else:
        return render_template("sell.html", name=user_info[0]["username"], cash=user_info[0]["cash"], stock_own_all=stock_own_all)

# 重置密码功能
@app.route("/reset", methods=["GET", "POST"])
def reset():
    if request.method == "POST":
        username = request.form.get("username")
        user_info = db.execute("SELECT * FROM users WHERE username = ?;", username)
        # 检测用户是否输入有效的用户名
        if not user_info:
            return apology("the username doesn't exist", 403)
        new_password = request.form.get("password")
        confirm_password = request.form.get("confirm_password")
        # 判断两次密码是否相等
        if new_password != confirm_password:
            return apology("the password didn't match", 403)
        else:
            # 对新密码进行哈希加密，并更新到数据库中
            hash = generate_password_hash(new_password)
            db.execute("UPDATE users SET hash = ?;", hash)
        return redirect("/")
    else:
        return render_template("reset.html")

# 用户增加自己的金额
@app.route("/add", methods=["GET", "POST"])
@login_required
def add():
    user_info = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    cash = user_info[0]["cash"]
    if request.method == "POST":
        try:
            add_cash = float(request.form.get("cash"))
        except ValueError:
            return apology("cash number is not correct")
        cash += add_cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])
        return redirect("/add")

    else:
        return render_template("add.html", name=user_info[0]["username"], cash=user_info[0]["cash"])

# 退回到主页目录案件
@app.route("/back", methods=["POST"])
@login_required
def back():
    return redirect("/")

# 用户金额💰归零
@app.route("/zero", methods=["POST"])
@login_required
def zero():
    db.execute("UPDATE users SET cash = 0 WHERE id = ?", session["user_id"])
    return redirect("/add")

# 留言模块
@app.route("/contact", methods=["GET", "POST"])
@login_required
def contact():
    message = db.execute("SELECT * FROM contact WHERE user_id = ?", session["user_id"])
    username = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])[0]["username"]
    current_time = datetime.datetime.now()
    formatted_time = current_time.strftime("%Y-%m-%d %H:%M:%S")
    if request.method == "POST":
        my_message = request.form.get("message")
        db.execute("INSERT INTO contact (user_id, time, my_message) VALUES (?, ?, ?)", session["user_id"], formatted_time, my_message)
        return redirect("/contact")
    return render_template("contact.html", message=message, name=username)

# 用户可以删除消息
@app.route("/message_delete", methods=["POST"])
@login_required
def message_delete():
    try:
        message_id = int(request.form.get("message_id"))
    except ValueError:
        return redirect("/contact")
    user_message_id = db.execute("SELECT id FROM contact WHERE user_id = ?", session["user_id"])
    for row in user_message_id:
        if row["id"] == message_id:
            db.execute("DELETE FROM contact WHERE id = ?", message_id)
            return redirect("/contact")
    else:
        return redirect("/contact")
