import json
import base64

def readFile(ruta):
    with open(ruta) as f:
        data = f.read()
    return json.loads(data)

def writeFile(ruta, js):
    with open(ruta, 'w') as f:
        json.dump(js, f, ensure_ascii=False)

def readImage(ruta):
    with open(ruta, "rb") as img_file:
        B64string = base64.b64encode(img_file.read())
    return B64string