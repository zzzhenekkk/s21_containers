all: clean test

test:
	g++ test.cpp -lgtest -lgtest_main -o test
	./test

ansrey:
	g++ containers/list.cpp -o my_test
	./my_rest

clean:
	rm -rf *.o my_test test