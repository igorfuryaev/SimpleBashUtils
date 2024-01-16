CC = gcc
FLAG = -std=c11 -Wall -Wextra -Werror -D_GNU_SOURCE

OS = $(shell uname)
ifeq ($(OS), Darwin)
LEAK_CHECK = CK_FORK=no leaks --atExit -- ./s21_grep
endif
ifeq ($(OS), Linux)
LEAK_CHECK = valgrind --leak-check=full -s -q ./s21_grep
endif

all: s21_grep

s21_grep: 
	$(CC) $(CFLAG) -o s21_grep s21_grep.c

test: s21_grep
	grep make Makefile > txt1.txt && ./s21_grep make Makefile > txt2.txt && diff txt1.txt txt2.txt
	grep -e make Makefile > txt1.txt && ./s21_grep -e make Makefile > txt2.txt && diff txt1.txt txt2.txt
	grep -i make Makefile > txt1.txt && ./s21_grep -i make Makefile > txt2.txt && diff txt1.txt txt2.txt
	grep -c make Makefile > txt1.txt && ./s21_grep -c make Makefile > txt2.txt && diff txt1.txt txt2.txt
	grep -l make Makefile > txt1.txt && ./s21_grep -l make Makefile > txt2.txt && diff txt1.txt txt2.txt
	grep -f test.txt Makefile > txt1.txt && ./s21_grep -f test.txt Makefile > txt2.txt && diff txt1.txt txt2.txt
	grep -n make Makefile > txt1.txt && ./s21_grep -n make Makefile > txt2.txt && diff txt1.txt txt2.txt
	grep -h make Makefile > txt1.txt && ./s21_grep -h make Makefile > txt2.txt && diff txt1.txt txt2.txt
	grep -s make Makefile > txt1.txt && ./s21_grep -s make Makefile > txt2.txt && diff txt1.txt txt2.txt
	grep -v make Makefile > txt1.txt && ./s21_grep -v make Makefile > txt2.txt && diff txt1.txt txt2.txt
	grep -o make Makefile > txt1.txt && ./s21_grep -o make Makefile > txt2.txt && diff txt1.txt txt2.txt
	grep -ie make Makefile > txt1.txt && ./s21_grep -ie make Makefile > txt2.txt && diff txt1.txt txt2.txt
	grep -cn make Makefile > txt1.txt && ./s21_grep -cn make Makefile > txt2.txt && diff txt1.txt txt2.txt
	grep -so make Makefile > txt1.txt && ./s21_grep -so make Makefile > txt2.txt && diff txt1.txt txt2.txt
	grep -sol make Makefile > txt1.txt && ./s21_grep -sol make Makefile > txt2.txt && diff txt1.txt txt2.txt
	grep -svol make Makefile > txt1.txt && ./s21_grep -svol make Makefile > txt2.txt && diff txt1.txt txt2.txt
	grep -svolhn make Makefile > txt1.txt && ./s21_grep -svolhn make Makefile > txt2.txt && diff txt1.txt txt2.txt
	grep make Makefile Makefile > txt1.txt && ./s21_grep make Makefile Makefile > txt2.txt && diff txt1.txt txt2.txt

leaks: s21_grep
	$(LEAK_CHECK) file Makefile
	$(LEAK_CHECK) -i make Makefile
	$(LEAK_CHECK) -n make Makefile
	$(LEAK_CHECK) -s make Makefile
	$(LEAK_CHECK) -ie make Makefile
	$(LEAK_CHECK) -svol make Makefile
	$(LEAK_CHECK) make Makefile Makefile

code_style: 
	@cp -f ../../materials/linters/.clang-format .
	@clang-format -i *.c *.h
	clang-format -n *.c *.h
	rm -rf .clang-format

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

rebuild: clean all

clean:
	@rm -rf s21_grep.o
	@rm -rf s21_grep
	@rm -rf txt1.txt
	@rm -rf txt2.txt
	@rm -rf *.o
