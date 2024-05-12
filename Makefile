
dirs=$(shell find ./*/ -name "Makefile")
all:
	find ./*/ -name "Makefile" -execdir make \;
clean:
	find ./*/ -name "Makefile" -execdir make clean \;
