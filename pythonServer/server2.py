from flask import Flask, jsonify, request, abort, make_response, render_template
from flask_socketio import SocketIO, emit
import json

with open('jsonAPI.txt') as f:
    data = f.read()
      
js = json.loads(data)


app = Flask(__name__)
app.debug = True
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app, cors_allowed_origins="*")

@socketio.on('connect')
def test_connect():
    print("Se conecto un cliente nuevo")
    #emit('update')

@socketio.on('send_puertas')
def send_puertas(json):
    print("Enviando estado puerta: "+str(json))
    emit('update')


@socketio.on('disconnect')
def test_disconnect():
    print("Se desconecto un cliente")


""" @app.route("/hello")
def hello_world():
    return render_template("index.html")

@app.route('/luces', methods=['GET'])
def get_luces():
    return jsonify(js['luces'])

@app.route('/puertas', methods=['GET'])
def get_puertas():
    return jsonify(js['puertas'])

@app.route('/camara', methods=['GET'])
def get_foto():
    return jsonify(js['camara'])

@app.route('/luces/<int:luz_id>', methods=['PATCH'])
def update_luz(luz_id):
    req = request.json

    luz = [luz for luz in js['luces'] if luz['id'] == luz_id]
    if len(luz) == 0:
        abort(404)
    if not req:
        abort(400)
    if 'state' in req and type(req['state']) is not int:
        abort(400)
    luz[0]['state'] = req['state']
    with open('jsonAPI.txt', 'w') as f:
        json.dump(js, f, ensure_ascii=False)
    if req['state'] == 1:
        return make_response(jsonify({"message": "Luz "+ str(luz_id) +" encendida correctamente"}), 200)
    else:
        return make_response(jsonify({"message": "Luz "+ str(luz_id) +" apagada correctamente"}), 200)
 """

if __name__ == '__main__':
    app.run(host='192.168.1.4', port=7000, debug=True, threaded=True)
