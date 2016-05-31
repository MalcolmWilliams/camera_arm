from flask import Flask, render_template
app = Flask(__name__)

@app.route("/")
def hello():
    return render_template("index.html")

@app.route('/webcam')
def webcam():
    return render_template("webcam.html")
'''
@app.route('/webcam2')
def webcam2():
    return render_template("webcam2.html")

@app.route('/webcam3')
def webcam3():
    return render_template("webcam3.html")
'''
if __name__ == "__main__":
    app.run(debug=True, host='0.0.0.0' , port=80)

