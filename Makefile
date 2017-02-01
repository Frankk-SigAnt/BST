.PHONY: lib clear test build_test

LIB=bstree
TEST=test_case

lib: $(LIB).o

clear: 
	rm *.o

test: $(TEST).o
	./$^

test_with_message: $(TEST).o
	./$^ --log_level=message

build_test: $(TEST).o
	
$(LIB).o: $(LIB).h
	g++ $^ -o $@ --std=c++1y

# We use the Boost Unit Test Framework
$(TEST).o: $(TEST).cpp $(LIB).h
	g++ $< -o $@ -std=c++1y -lboost_unit_test_framework -g3
