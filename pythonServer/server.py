from flask import Flask, jsonify, request, abort, make_response
import json
import os
import include.utils as util

from ctypes import *
control_so = "/home/lsk8/Documentos/tec/2022 I Semestre/Embebidos/Proyecto1Embebidos/Proyecto1Embebidos/Cprogram/GPIOControl.so"
controlFunctions = CDLL(control_so)

app = Flask(__name__)

@app.route('/login', methods=['POST'])
def login():
    req = request.json

    js = util.readFile('jsonAPI.txt')

    user = [user for user in js['users'] if user['user'] == req['user']]
    if len(user) == 0:
        return make_response(jsonify({"resp": 2}), 404)
    if not req:
        return make_response(jsonify({"resp": 3}), 400)
    user[0]['pass'] = req['user']
    if user[0]['password'] == req['password']:
        return make_response(jsonify({"resp": 1}), 200)
    else:
        return make_response(jsonify({"resp": 0}), 200)


@app.route('/luces', methods=['GET'])
def get_luces():
    js = util.readFile('jsonAPI.txt')
    luces = js['luces']
    for luz in luces:
        #state = controlFunctions.state_led(luz['id'])
        luz['state'] = 1
    util.writeFile('jsonAPI.txt', js)
    #print(controlFunctions.square(4))
    return jsonify(js['luces'])


@app.route('/puertas', methods=['GET'])
def get_puertas():
    js = util.readFile('jsonAPI.txt')
    puertas = js['puertas']
    print(puertas)
    for puerta in puertas:
        #state = controlFunctions.state_door(puerta['id'])
        puerta['state'] = 1
    print(puertas)
    util.writeFile('jsonAPI.txt', js)
    return jsonify(puertas)


@app.route('/camara', methods=['GET'])
def get_foto():
    #Llamar camara
    os.system("fswebcam image.jpg")
    imageB64 = util.readImage('image.jpg')
    return jsonify({"camara": imageB64})


@app.route('/luces/<int:luz_id>', methods=['PATCH'])
def update_luz(luz_id):
    req = request.json

    js = util.readFile('jsonAPI.txt')

    luz = [luz for luz in js['luces'] if luz['id'] == luz_id]
    if len(luz) == 0:
        abort(404)
    if not req:
        abort(400)
    if 'state' in req and type(req['state']) is not int:
        abort(400)
    
    luz[0]['state'] = req['state']
    util.writeFile('jsonAPI.txt',js)

    if req['state'] == 1:
        #poner llamada a C
        #controlFunctions.led_on(luz_id)
        return make_response(jsonify({"message": "Luz "+ str(luz_id) +" encendida correctamente"}), 200)
    else:
        #poner llamada a C
        #controlFunctions.led_off(luz_id)
        return make_response(jsonify({"message": "Luz "+ str(luz_id) +" apagada correctamente"}), 200)


if __name__ == '__main__':
    #controlFunctions.reserve_all()
    app.run(host='192.168.100.195', port=7000, debug=True, threaded=False)
    
