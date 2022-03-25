from ctypes import *
so_file = "/home/lsk8/Documentos/tec/2022 I Semestre/Embebidos/Proyecto1Embebidos/Proyecto1Embebidos/pythonServer/root.so"
my_functions = CDLL(so_file)
print(my_functions.square(5))