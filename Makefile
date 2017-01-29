.PHONY: all clear test build_test

LIB=bstree
TEST=test_case

lib: $(LIB).o

clear: 
	rm *.o

test: $(TEST).o
	./test_case.o

build_test: $(TEST).o
	
$(LIB).o: $(LIB)
	g++ $^ -o $@ --std=c++1y

# We use the Boost Unit Test Framework
$(TEST).o: $(TEST).cpp
	g++ $^ -o $@ -std=c++1y -lboost_unit_test_framework
