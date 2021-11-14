from flask import Flask, request
import datetime
import sqlite3
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import base64

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
    c=cur.execute("SELECT count FROM data WHERE SESSION=('%s') ORDER BY date" % (session)).fetchall()

    size=len(secondsleft)

    for i in range(1, len(c)):
        if c[i] == 0:
            size = i
            break
    
    secondsleft = secondsleft[:i]
    c = c[:i]

    secondsleftlist=[]
    countlist=[]

    gender = cur.execute("SELECT gender FROM userattr WHERE SESSION=('%s')" % (session)).fetchall()[0][0]
    age = int(cur.execute("SELECT age FROM userattr WHERE SESSION=('%s')" % (session)).fetchall()[0][0])
    count = int(c[len(c) - 1][0])

    secondsleftlist.append(30-int(secondsleft[0][0]))
    for i in range(1, len(secondsleft)):
        secondsleftlist.append(29.999999999-int(secondsleft[i][0]))
        secondsleftlist.append(30-int(secondsleft[i][0]))
    secondsleftlist.append(30)
    
    countlist.append(int(c[0][0]))
    for i in range(1, len(c)):
        countlist.append(int(c[i-1][0]))
        countlist.append(int(c[i][0]))
    countlist.append(int(c[len(c)-1][0]))

    fig, ax = plt.subplots()
    ax.plot(secondsleftlist, countlist)

    ax.set(xlabel='time (s)', ylabel='count',
        title=session + ' data')
    ax.grid()

    fig.savefig("plots/"+session+".png")

    con.close()

    base = base64.b64encode(open("plots/"+session+".png","rb").read())
    
    success = True

    if int(age) >= 90:
        if gender:
            mincount=4
            if count >= 4:
                success = True
            else:
                success = False
        else:
            mincount=7
            if count >= 7:
                success = True
            else:
                success = False
    elif int(age) >= 85:
        if gender:
            mincount=8
            if count >= 8:
                success = True
            else:
                success = False
        else:
            mincount=8
            if count >= 8:
                success = True
            else:
                success = False
    elif int(age) >= 80:
        if gender:
            mincount=9
            if count >= 9:
                success = True
            else:
                success = False
        else:
            mincount=10
            if count >= 10:
                success = True
            else:
                success = False
    elif int(age) >= 75:
        if gender:
            mincount=10
            if count >= 10:
                success = True
            else:
                success = False
        else:
            mincount=11
            if count >= 11:
                success = True
            else:
                success = False
    elif int(age) >= 70:
        if gender:
            mincount=10
            if count >= 10:
                success = True
            else:
                success = False
        else:
            mincount=12
            if count >= 12:
                success = True
            else:
                success = False
    elif int(age) >= 65:
        if gender:
            mincount=11
            if count >= 11:
                success = True
            else:
                success = False
        else:
            mincount=12
            if count >= 12:
                success = True
            else:
                success = False
    else:
        if gender:
            mincount=12
            if count >= 12:
                success = True
            else:
                success = False
        else:
            mincount=14
            if count >= 14:
                success = True
            else:
                success = False
    
    if success:
        result = "You passed! Great job! In order to pass you needed to have had a score of " + str(mincount) + ", and you had a score of " + str(count) + " so we have not found you to be at risk of falling!"
    else:
        result = "Unfortunately, you did not pass. In order to pass, you needed to have a score of " + str(mincount) + ", but you had a score of " + str(count) + " so we have found you to be at risk of falling. Don't get discouraged! We believe in you!"

    return result + ",-," + str(base)[2:len(str(base))-1]

@app.route("/generatetestdata")
def generatetestdata():
    con = sqlite3.connect('wizeview.db')
    cur = con.cursor()

    cur.execute("INSERT INTO userattr VALUES ('%s','%s','%s')" % ("testsession", "false", "72"))

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