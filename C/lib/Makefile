#Makefile carpeta lib
CC = arm-poky-linux-gnueabi-gcc
LD = arm-poky-linux-gnueabi-ld
SYSROOT = --sysroot=/opt/poky/3.1.2/sysroots/cortexa7t2hf-neon-vfpv4-poky-linux-gnueabi/
VAR = -mthumb -mfpu=neon-vfpv4 -mfloat-abi=hard -mcpu=cortex-a7 -fstack-protector-strong -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security
all: dynamic

dynamic:
	$(CC) ${SYSROOT} -c -fpic home-control.c -o home-control.o $(VAR) 
	$(LD) ${SYSROOT} -shared -o libhome-control.so home-control.o

clean:
	rm -f *.o
