from flask import Flask, render_template, request, redirect

app = Flask(__name__)

tasks = ["Go to School", "Help Grandma"]

@app.route('/')  # rendering page in initial state
def home():
    return render_template('index.html', tasks=tasks)

@app.route('/addTask', methods=['POST'])
def addTask():
    toAdd = request.form['Input for Tasks']  # get data from form
    tasks.append(toAdd)
    return redirect('/')  #update home page

@app.route('/deleteTask', methods=['POST'])
def deleteTask():
    toDelete = request.form['Input for Tasks']
    tasks.remove(toDelete)
    return redirect('/')

@app.route('/clearAll', methods=['POST'])
def clearAll():
    tasks.clear()
    return redirect('/')



if __name__ == '__main__':
    app.run(debug=True)
