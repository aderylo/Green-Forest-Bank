from pam import pam
from flask import Flask, request, session, jsonify, render_template, redirect
import os, pwd
import logging

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def login():
    # get the username and password from the request
    username = request.form.get('username')
    password = request.form.get('password')

    print(f"user : {username}") 

    # authenticate using PAM
    if pam().authenticate(username, password):
        session['username'] = request.form['username']
        return redirect('/view')
    else:
        return jsonify({"status": "failure"}), 401

@app.route('/view')
def view():
    return render_template('view.html')

@app.route('/view/credits')
def credits():
    return viewer("credits")

@app.route('/view/deposits')
def deposits():
    return viewer("deposits")

def viewer(directory : str):
    all_filenames = os.listdir(directory)
    print("whoamiI")
    os.system("whoami")
    user = session["username"]
    filenames = []
    file_contents = {}

    for filename in all_filenames:
        path = f"{directory}/{filename}"
        if os.stat(path).st_uid == pwd.getpwnam(user).pw_uid:
            filenames.append(filename)
            with open(os.path.join(directory, filename),) as f:
                file_contents[filename] = f.readlines() 

    return render_template('viewer.html', filenames=filenames, file_contents=file_contents)

# really secret key, in production we would use a secret manager
app.secret_key = 'A0Zr98j/3yX R~XHH!jmN]LWX/,?RT'

if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO)
    # Bind to PORT if defined, otherwise default to 5000.
    port = int(os.environ.get('PORT', 5000))
    app.run(host='0.0.0.0', port=port, debug=True)