all: clean test

test:
	g++ test.cpp -lgtest -lgtest_main -o test
	./test

andrey:
	g++ containers/list.cpp -o my_test
	./my_test

clean:
	rm -rf *.o my_test test