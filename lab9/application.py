import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

# "/" will trigger Flask function
@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database

        # Access form data
        # Variable matches the name of the form input fields
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        # Insert data into database. Note: ? is the placeholder for SQL
        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)

        return redirect("/")

    # return method is "GET"
    else:

        # TODO: Display the entries in the database on index.html

        # Query for all birthdays from Database
        birthdays = db.execute("SELECT * FROM birthdays")

        # Render birthday page by passing a variable birthday equal to the variable we queried for
        return render_template("index.html", birthdays=birthdays)


