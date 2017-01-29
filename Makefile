.PHONY: all clear test build_test

all: bsttree.o

OBJ=bstree.h

bsttree.o: $(OBJ)
	g++ $^ -o $@ --std=c++11

clear: 
	rm *.o

test: build_test
	./test_case.o

build_test: test_case.cpp
	g++ test_case.cpp -o test_case.o -std=c++1y -lboost_unit_test_framework
