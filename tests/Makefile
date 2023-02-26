CC = g++
CFLAGS = -g
STD = -std=c++2b

clean:
	rm -f genTest*

tuple:
	echo "creating tests for tuple"
	$(CC) $(STD) $(CFLAGS) tuple_tests.cpp -o genTestTuple

vector:
	echo "creating tests for vector"
	$(CC) $(STD) $(CFLAGS) vector_tests.cpp -o genTestVector
