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

all: clean s21_decimal.a test gcov_report

s21_decimal.a:
	gcc $(CC) -c s21_*.c
	ar -crs s21_decimal.a s21_*.o

gcov_report: clean
	gcc $(CC) tests/test*.c s21_*.c $(FLAGS) -o test
	./test
	lcov -t "./test"  -o report.info --no-external -c -d .
	genhtml -o report report.info
	$(OPEN_CMD) ./report/index.html

	rm -rf *.gcno *gcda *.gco

clean:
	rm -rf *.o *.a test
	rm -rf *.gcno *gcda *.gcov gcov
	rm -rf report report.info

rebuild: clean s21_decimal.a test

test: s21_decimal.a
	gcc $(CC) tests/test*.c s21_decimal.a $(FLAGS) -lgcov -coverage -o test
	./test
