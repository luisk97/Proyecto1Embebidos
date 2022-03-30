#Makefile de la carpeta src
CC = arm-poky-linux-gnueabi-gcc
SYSROOT = --sysroot=/opt/poky/3.1.2/sysroots/cortexa7t2hf-neon-vfpv4-poky-linux-gnueabi/
VAR = -mthumb -mfpu=neon-vfpv4 -mfloat-abi=hard -mcpu=cortex-a7 -fstack-protector-strong -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security 
all: dynamic

dynamic:
	$(CC) ${SYSROOT} main.c -L ../lib -lhome-control -o ../bin/main_d -lm $(VAR) 
