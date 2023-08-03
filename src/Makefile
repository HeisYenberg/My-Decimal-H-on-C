OS := $(shell uname)
CC = -Wall -Werror -Wextra -std=c11
FLAGS = -lcheck -lpthread -fprofile-arcs

ifeq ($(OS),Darwin)
	FLAGS += -ftest-coverage
	OPEN_CMD = open
else
	FLAGS += -lm -lrt -lsubunit -ftest-coverage
	OPEN_CMD = xdg-open
endif

all: clean my_decimal.a test gcov_report

my_decimal.a:
	gcc $(CC) -c my_decimal/my_*.c
	ar -crs my_decimal/my_decimal.a my_*.o

test: my_decimal.a
	gcc $(CC) tests/test*.c my_decimal/my_decimal.a $(FLAGS) -lgcov -coverage -o test
	./test

gcov_report: clean
	gcc $(CC) tests/test*.c my_decimal/my_*.c $(FLAGS) -o test
	./test
	lcov -t "./test"  -o report.info --no-external -c -d .
	genhtml -o report report.info
	$(OPEN_CMD) ./report/index.html

	rm -rf *.gcno *gcda *.gco

rebuild: clean my_decimal.a test

clean:
	rm -rf *.o my_decimal/*.a test
	rm -rf *.gcno *gcda *.gcov gcov
	rm -rf report report.info