CC = gcc
FLAG = -std=c11 -Wall -Wextra -Werror -D_GNU_SOURCE

OS = $(shell uname)
ifeq ($(OS), Darwin)
LEAK_CHECK = CK_FORK=no leaks --atExit -- ./s21_cat
endif
ifeq ($(OS), Linux)
LEAK_CHECK = valgrind --leak-check=full -s -q ./s21_cat
endif

all: s21_cat

s21_cat: 
	$(CC) $(CFLAG) -o s21_cat s21_cat.c

test: s21_cat
	cat Makefile > txt1.txt && ./s21_cat Makefile > txt2.txt && diff txt1.txt txt2.txt
	cat -bensv Makefile > txt1.txt && ./s21_cat -bensv Makefile > txt2.txt && diff txt1.txt txt2.txt
	cat -tvs Makefile > txt1.txt && ./s21_cat -tvs Makefile > txt2.txt && diff txt1.txt txt2.txt
	cat -nb Makefile > txt1.txt && ./s21_cat -nb Makefile > txt2.txt && diff txt1.txt txt2.txt
	cat -stv Makefile > txt1.txt && ./s21_cat -stv Makefile > txt2.txt && diff txt1.txt txt2.txt

code_style: 
	@cp -f ../../materials/linters/.clang-format .
	@clang-format -i *.c *.h
	clang-format -n *.c *.h
	rm -rf .clang-format

leaks: s21_cat
	cat Makefile > txt1.txt && $(LEAK_CHECK) && ./s21_cat Makefile > txt2.txt && diff txt1.txt txt2.txt
	cat -bensv Makefile > txt1.txt && $(LEAK_CHECK) && ./s21_cat -bensv Makefile > txt2.txt && diff txt1.txt txt2.txt
	cat -tvs Makefile > txt1.txt && $(LEAK_CHECK) && ./s21_cat cat -tvs Makefile > txt2.txt && diff txt1.txt txt2.txt
	cat -nb Makefile > txt1.txt && $(LEAK_CHECK) && ./s21_cat cat -nb Makefile > txt2.txt && diff txt1.txt txt2.txt
	cat -stv Makefile > txt1.txt && $(LEAK_CHECK) && ./s21_cat -stv Makefile > txt2.txt && diff txt1.txt txt2.txt

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

rebuild: clean all

clean:
	@rm -rf s21_cat.o
	@rm -rf s21_cat
	@rm -rf *.txt
	@rm -rf *.o
