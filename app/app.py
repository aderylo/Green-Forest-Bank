from pam import pam
from flask import Flask, request, jsonify, render_template
import os
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
        return jsonify({"status": "success"})
    else:
        return jsonify({"status": "failure"}), 401

if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO)
    # Bind to PORT if defined, otherwise default to 5000.
    port = int(os.environ.get('PORT', 5000))
    app.run(host='0.0.0.0', port=port, debug=True)
