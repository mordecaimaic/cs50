from sqlalchemy import text, create_engine
from cs50 import SQL


engine = create_engine("sqlite+pysqlite:///test.db", future=True)# with engine.connect() as conn:
db = SQL("sqlite:///test.db")
# db.execute("INSERT INTO users (name,scores)VALUES (?,?)", "Mike", 90)


# with engine.connect() as conn:
#     result = conn.execute(text("select 'hello world'"))
#     print(result.all())

# with engine.connect() as conn:
    # conn.execute(text("CREATE TABLE some_table (x int, y int)"))
    # conn.execute(
    #     text("INSERT INTO some_table (x, y) VALUES (:x, :y)"),
    #     [{"x": 1, "y": 1}, {"x": 2, "y": 4}],
    # )
    # conn.commit()



with engine.connect().execution_options() as conn:
    # conn.execute(text("INSERT INTO some_table (x,y) VALUES (11,22);"))
    # conn.execute(text("DELETE FROM some_table WHERE y = 12"))
    # conn.execute(text("INSERT INTO some_table (x,y) VALUES (1,1);"))
    # conn.execute(text("UPDATE some_table SET x=2, y=3"))
    # conn.execute(text("INSERT INTO some_table (x, y) VALUES (:x, :y)"), [{"x": 11, "y": 12}])
    # conn.execute(text("INSERT INTO users (name, scores) VALUES (:name,:scores)"), [{"name": "Carte", "scores":93}])
    # result = conn.execute(text("SELECT * FROM users WHERE name = (:name_insert);"), {"name_insert":"Mike"})
    result = conn.execute(text("SELECT *  FROM users"))
    for i in result:
        print(i)
        # print(i.name, i.scores)
    # result = conn.execute(text("SELECT * FROM some_table"))
    # conn.commit()
    # for row in result:
    #     print(f"x: {row.x}  y: {row.y}")
    # print(list(result))
    # result = conn.execute(text("select x, y from some_table"))
