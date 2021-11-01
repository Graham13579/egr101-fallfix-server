import sqlite3

con = sqlite3.connect('wizeview.db')

cur = con.cursor()

# Create table
cur.execute('''CREATE TABLE data
               (session text, date text, force real, count real)''')

cur.execute('''CREATE TABLE userattr
               (session text, gender boolean, age real)''')