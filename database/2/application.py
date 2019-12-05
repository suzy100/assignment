# powershell
# $env:FLASK_APP = "application"

from flask import Flask, render_template, request
import psycopg2
import time
from getpass import getpass

# searched_name = ''

app = Flask(__name__)

time.sleep(1)

localhost = input("localhost: ")
dbname = input("dbname: ")
user = input("user: ")
password = getpass()

conn_string = f'host=\'{localhost}\' dbname=\'{dbname}\' user=\'{user}\' password=\'{password}\''
conn = psycopg2.connect(conn_string)
cur = conn.cursor()

sql = f'CREATE TABLE IF NOT EXISTS contact (name char(50) NOT NULL, phone char(11) NOT NULL);'
cur.execute(sql)
conn.commit()

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search", methods=["POST"])
def search():
    searched_name = request.form.get("name")
    sql = f'SELECT * FROM contact WHERE name like \'{searched_name}%\';'
    cur.execute(sql)
    selected = cur.fetchall()
    sql = f'SELECT COUNT(*) FROM contact WHERE name like \'{searched_name}%\';'
    cur.execute(sql)
    count = cur.fetchall()

    return render_template("search.html", name = searched_name, result = selected, count = count)

@app.route("/insert", methods=["GET"])
def insert():
    return render_template("insert.html")

@app.route("/insert_complete", methods=["POST"])
def insert_complete():
    insert_name = request.form.get("name")
    insert_phone = request.form.get("num")
    sql = f'INSERT INTO contact VALUES (\'{insert_name}\', \'{insert_phone}\');'
    cur.execute(sql)
    conn.commit()
    return render_template("index.html")

@app.route("/modify", methods=["POST"])
def modify():
    modify_from = request.form.get("name")
    return render_template("modify.html", modify_from = modify_from)

@app.route("/modify_complete", methods=["POST"])
def modify_complete():
    before_name = request.form.get("before_name")
    modify_name = request.form.get("name")
    modify_phone = request.form.get("num")
    print(modify_name)
    if modify_name == '\0':
        return render_template("index.html", fail = "fail")
    sql = f'UPDATE contact SET name = \'{modify_name}\', phone = \'{modify_phone}\' WHERE ctid IN ( SELECT ctid FROM contact WHERE name=\'{before_name}\' ORDER BY phone LIMIT 1 );'
    cur.execute(sql)
    conn.commit()
    return render_template("index.html")

@app.route("/delete", methods=["POST"])
def delete():
    deleted_name = request.form.get("name")
    sql = f'DELETE FROM contact WHERE ctid IN ( SELECT ctid FROM contact WHERE name=\'{deleted_name}\' ORDER BY phone LIMIT 1 );'
    cur.execute(sql)
    conn.commit()
    alert = f'Deleted \'{deleted_name}\''
    return render_template("index.html", deleted = alert)
