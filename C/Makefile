# source /opt/poky/2.3.3/environment-setup-cortexa7hf-neon-vfpv4-poky-linux-gnueabi

MAKE = make
LIB = lib
SRC = src

all:
		cd $(LIB) && $(MAKE) && cd ..
		cd $(SRC) && $(MAKE)

clean:
		cd $(LIB) && $(MAKE) clean && cd ..
		cd $(SRC) && $(MAKE) clean
