from flask import Flask, request
import datetime
import sqlite3

app = Flask(__name__)

@app.route("/input/<session>/<force>/<count>")
def input(session, force, count):
    con = sqlite3.connect('wizeview.db')
    session = session
    force = force
    count = count
    date = datetime.datetime.now()
    cur = con.cursor()

    cur.execute("INSERT INTO data VALUES ('%s','%s','%s','%s')" % (session, date, force, count))

    con.commit()

    con.close()
    return "<p>Hello, World!</p>"

@app.route("/output/<session>")
def outpot(session):
    con = sqlite3.connect('wizeview.db')
    session = session
    cur=con.cursor()
    output=cur.execute("SELECT * FROM data ORDER BY date DESC LIMIT 1").fetchall()
    print(output)
    con.close()
    return "<p>Hello, World!</p>"

@app.route("/test")
def test():
    return "Hello"

if __name__ == '__main__':
    app.debug = True
    app.run(host='172.28.105.180', port=5000)