.PHONY: all clear

all: bsttree.o

OBJ=bstree.h

bsttree.o: $(OBJ)
	g++ $^ -o $@ --std=c++11
clear: 
	rm *.o
