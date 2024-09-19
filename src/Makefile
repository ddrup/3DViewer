GCC := g++ -Werror -Wextra -Wall --std=c++17 -lstdc++ -lm
SANITIZER :=  -fsanitize=address -fsanitize=leak -fsanitize=undefined
SOURSE :=  My3DViewer/Backend/*.cc My3DViewer/Test/*.cc
FLAGS_LCOV := -g -fprofile-arcs -ftest-coverage
FLAGS_GTEST := -lgtest -lgcov -pthread

all: clean install

tests: clean
	$(GCC) $(FLAGS_LCOV) $(SOURSE) $(FLAGS_GTEST) -o s21_test_file
	./s21_test_file

gcov_report: tests #--ignore-errors mismatch 
	@lcov -t test -o rep.info -c -d . --exclude '*/usr/*' --exclude '*/12/*'
	@genhtml -o report rep.info
	@rm -rf gcovreport gcovreport.info *.gcda *.gcno math_test.gcda math_test.gcno
	@open ./report/index.html

rebuild: clean all

clean: 
	rm -rf *.o s21_test_file s21_report *.a a.out *.gcno *.gcda s21_test.dSYM *.info report 3DViewer dist

check:
	clang-format --style=Google -n $(shell find . -name '*.cc') $(shell find . -name '*.h') $(shell find . -name '*.cpp')
	clang-format --style=Google -i $(shell find . -name '*.cc') $(shell find . -name '*.h') $(shell find . -name '*.cpp')

install:
	mkdir 3DViewer
	cd 3DViewer && qmake ../My3DViewer && make

open:
	./3DViewer/My3DViewer

uninstall:
	rm -rf 3DViewer

dvi:
	open ../README.md

dist:
	mkdir dist
	cp -R My3DViewer Makefile dist
	cd dist && tar cvzf 3DViewer.tgz *
	cd dist && rm -rf *.c *.cpp *.h *.ui calc* My3DViewer Makefile Test_core