from flask import Flask, request
import datetime
import sqlite3
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

app = Flask(__name__)

@app.route("/input/<session>/<count>")
def input(session, count):
    con = sqlite3.connect('wizeview.db')
    session = session
    count = count
    date = datetime.datetime.now()
    cur = con.cursor()
    initstart = cur.execute("SELECT * FROM init WHERE SESSION=('%s')" % (session)).fetchall()[0][1]
    print(initstart)
    initstartobj = datetime.datetime.strptime(initstart, "%Y-%m-%d %H:%M:%S.%f")
    difference = date - initstartobj
    secondsleft = difference.total_seconds()

    cur.execute("INSERT INTO data VALUES ('%s','%s','%s','%s')" % (session, secondsleft, date, count))

    con.commit()

    con.close()
    return "<p>Hello, World!</p>"

#return just as comma separated string
@app.route("/output/<session>")
def output(session):
    con = sqlite3.connect('wizeview.db')
    session = session
    cur=con.cursor()
    date = datetime.datetime.now()
    initstart = cur.execute("SELECT * FROM init WHERE SESSION=('%s')" % (session)).fetchall()[0][1]
    initstartobj = datetime.datetime.strptime(initstart, "%Y-%m-%d %H:%M:%S.%f")
    difference = date - initstartobj
    secondsleft = 30 - difference.total_seconds()
    output=cur.execute("SELECT * FROM data WHERE SESSION=('%s') ORDER BY date DESC LIMIT 1" % (session)).fetchall()
    ret = str(int(round(secondsleft,0)))+","+str(int(round(float(output[0][3]),0)))
    con.close()
    return ret

@app.route("/getstart/<session>")
def getstart(session):
    con = sqlite3.connect('wizeview.db')
    session = session
    initstart = datetime.datetime.now()
    cur=con.cursor()

    cur.execute("INSERT INTO data VALUES ('%s','%s','%s','%s')" % (session, "30", "", "0"))

    cur.execute("DELETE FROM init WHERE SESSION=('%s')" % (session))
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
    ret = ','.join(output[0])
    con.close()
    return ret

@app.route("/delete/<session>")
def delete(session):
    con = sqlite3.connect('wizeview.db')
    session = session
    cur = con.cursor()

    cur.execute("DELETE FROM userattr WHERE session=('%s')" % (session))
    cur.execute("DELETE FROM init WHERE session=('%s')" % (session))
    cur.execute("DELETE FROM data WHERE session=('%s')" % (session))

    con.commit()

    con.close()

    return "<p>Hello, World!</p>"

@app.route("/retgraph/<session>")
def retgraph(session):
    con = sqlite3.connect('wizeview.db')
    session = session
    cur = con.cursor()

    secondsleft=cur.execute("SELECT secondsleft FROM data WHERE SESSION=('%s') ORDER BY date" % (session)).fetchall()
    count=cur.execute("SELECT count FROM data WHERE SESSION=('%s') ORDER BY date" % (session)).fetchall()

    secondsleftlist=[]
    countlist=[]

    secondsleftlist.append(30-int(secondsleft[0][0]))
    for i in range(1, len(secondsleft)):
        secondsleftlist.append(29.999999999-int(secondsleft[i][0]))
        secondsleftlist.append(30-int(secondsleft[i][0]))
    secondsleftlist.append(30)
    
    countlist.append(int(count[0][0]))
    for i in range(1, len(count)):
        countlist.append(int(count[i-1][0]))
        countlist.append(int(count[i][0]))
    countlist.append(int(count[len(count)-1][0]))

    fig, ax = plt.subplots()
    ax.plot(secondsleftlist, countlist)

    ax.set(xlabel='time (s)', ylabel='count',
        title=session + ' data')
    ax.grid()

    fig.savefig("plots/"+session+".png")

    con.close()

    return "<p>Hello, World!</p>"

@app.route("/generatetestdata")
def generatetestdata():
    con = sqlite3.connect('wizeview.db')
    cur = con.cursor()

    cur.execute("INSERT INTO data VALUES ('%s','%s','%s','%s')" % ("testsession", "30", "", "0"))
    cur.execute("INSERT INTO data VALUES ('%s','%s','%s','%s')" % ("testsession", "26", "", "1"))
    cur.execute("INSERT INTO data VALUES ('%s','%s','%s','%s')" % ("testsession", "19", "", "2"))
    cur.execute("INSERT INTO data VALUES ('%s','%s','%s','%s')" % ("testsession", "13", "", "3"))
    cur.execute("INSERT INTO data VALUES ('%s','%s','%s','%s')" % ("testsession", "9", "", "4"))
    cur.execute("INSERT INTO data VALUES ('%s','%s','%s','%s')" % ("testsession", "5", "", "5"))
    cur.execute("INSERT INTO data VALUES ('%s','%s','%s','%s')" % ("testsession", "1", "", "6"))

    con.commit()

    con.close()

    return "<p>Hello, World!</p>"

if __name__ == '__main__':
    app.debug = True
    app.run(host='172.28.77.91', port=5000)