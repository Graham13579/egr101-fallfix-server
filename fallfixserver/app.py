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
    initstart = cur.execute("SELECT * FROM init WHERE SESSION=('%s') LIMIT 1" % (session)).fetchall()[0][1]
    initstartobj = datetime.datetime.strptime(initstart, "%Y-%m-%d %H:%M:%S.%f")
    difference = date - initstartobj
    secondsleft = difference.total_seconds()

    cur.execute("INSERT INTO data VALUES ('%s','%s','%s','%s','%s')" % (session, secondsleft, date, force, count))

    con.commit()

    con.close()
    return "<p>Hello, World!</p>"

#return just as comma separated string
@app.route("/output/<session>")
def output(session):
    con = sqlite3.connect('wizeview.db')
    session = session
    cur=con.cursor()
    output=cur.execute("SELECT * FROM data WHERE SESSION=('%s') ORDER BY date DESC LIMIT 1" % (session)).fetchall()
    print(','.join(output[0]))
    con.close()
    return "<p>Hello, World!</p>"

@app.route("/getstart/<session>")
def getstart(session):
    con = sqlite3.connect('wizeview.db')
    session = session
    initstart = datetime.datetime.now()
    cur=con.cursor()

    cur.execute("INSERT INTO init VALUES ('%s','%s')" % (session, initstart))

    con.commit()

    con.close()
    return "<p>Hello, World!</p>"

@app.route("/setuser/<session>/<gender>/<age>")
def setuser(session, gender, age):
    con = sqlite3.connect('wizeview.db')
    session = session
    gender = gender
    age = age
    cur = con.cursor()

    cur.execute("INSERT INTO userattr VALUES ('%s','%s','%s')" % (session, gender, age))

    con.commit()

    con.close()
    return "<p>Hello, Word!</p>"

@app.route("/getuser/<session>")
def getuser(session):
    con = sqlite3.connect('wizeview.db')
    session = session
    cur=con.cursor()
    output=cur.execute("SELECT * FROM userattr WHERE session=('%s')" % (session)).fetchall()
    print(','.join(output[0]))
    con.close()
    return "<p>Hello, World!</p>"

if __name__ == '__main__':
    app.debug = True
    app.run(host='0.0.0.0', port=5000)