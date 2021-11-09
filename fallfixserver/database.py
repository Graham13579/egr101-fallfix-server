import sqlite3

con = sqlite3.connect('wizeview.db')

cur = con.cursor()

# Create table
cur.execute('''CREATE TABLE data
               (session text, secondsleft text, date text, count text)''')

cur.execute('''CREATE TABLE init
               (session text, initstart text)''')

cur.execute('''CREATE TABLE userattr
               (session text, gender text, age text)''')