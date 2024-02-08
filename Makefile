CC = g++ -g -Wall -Werror -Wextra -std=c++17
COVFLAGS = -fprofile-arcs  -lcheck -ftest-coverage
TESTF = -lgtest -lgtest_main

all: clean test

test:
	$(CC) test.cpp $(TESTF) $(COVFLAGS) --coverage -o test
	./test

gcov_report: clean test
	gcov -f *.gcda
	# geninfo --ignore-errors mismatch ...
	lcov -t "test" -o test.info -c -d . --rc lcov_branch_coverage=0
	genhtml -o report test.info  --rc lcov_branch_coverage=0
	make clean
	open report/index.html

andrey:
	$(CC) containers/list.cpp -o my_test
	./my_test

clean:
	rm -rf *.o my_test test *.gcov *.info *.gcda *.gcno