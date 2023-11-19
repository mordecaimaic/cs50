CREATE TABLE transactions(
    id INTEGER PRIMARY KEY,
    stock_symbol TEXT NOT NULL,
    user_id INTEGER NOT NULL,
    trade_mode TEXT NOT NULL,
    shares INTEGER NOT NULL,
    price NUMERIC NOT NULL,
    profit_loss NUMERIC NOT NULL,
    time TEXT NOT NULL,
    FOREIGN KEY (user_id) REFERENCES users(id)
);

CREATE TABLE stockown(
    id INTEGER PRIMARY KEY,
    stock_name TEXT NOT NULL,
    stock_symbol TEXT NOT NULL,
    user_id INTEGER NOT NULL,
    shares INTEGER NOT NULL,
    buy_price NUMERIC NOT NULL,
    FOREIGN KEY (user_id) REFERENCES users(id)
);

CREATE TABLE contact(
    id INTEGER PRIMARY KEY,
    user_id INTEGER NOT NULL,
    time TEXT NOT NULL,
    my_message TEXT,
    FOREIGN KEY (user_id) REFERENCES users(id)
);