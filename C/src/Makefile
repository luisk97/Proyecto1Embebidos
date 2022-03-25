SRC = main
DST = ../bin/$(SRC)
INCLUDE = -I../include
LIB = -L../lib

CC = arm-poky-linux-gnueabi-gcc
SYSROOT = --sysroot=/opt/poky/2.3.3/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/
SHARED = ../lib/libControlCasa

all: main

main:
		# static
		# $(CC) ${SYSROOT} -o $(DST) $(SRC).c $(INCLUDE) $(SHARED).a -mfloat-abi=hard
		# dynamic
		$(CC) $(SYSROOT) -o $(DST) $(SRC).c $(INCLUDE) $(LIB) -lControlCasa -fPIC -mfloat-abi=hard
		# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH: 
		echo "\n[***Prueba unitaria 2] Ejecutable creado con exito\n"
#ingles
clean:
		rm $(DST)*
