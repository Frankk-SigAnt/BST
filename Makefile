OBJ=bstree.h

bsttree.o: $(OBJ)
	g++ $^ -o $@ --std=c++17
