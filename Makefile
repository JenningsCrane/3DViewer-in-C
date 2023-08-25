CC = gcc -std=c11 -g
FLAGS = -Wall -Werror -Wextra
BD = ../build/
OS = $(shell uname)
LIBSOURCES = FilesOnC/*.c test/tests.c

ifeq ($(OS), Linux)
	CHECKFLAGS=-lcheck -lm -lpthread -lrt -lsubunit
else
	CHECKFLAGS=-lcheck -lm -lpthread -fprofile-arcs -ftest-coverage 
endif

all: tests

install: uninstall build
	make clean_qmake

uninstall:
	rm -rf ../build

build: 3D_Viewer
	cd $(BD); qmake 3D_Viewer.pro; make -C $(BD);

3D_Viewer:
	mkdir ../build;
	mkdir ../build/screen;
	touch ../build/settings.txt
	cp dvi.html $(BD)
	cp 3D_Viewer.pro $(BD)

dist:
	cd $(BD) && tar -czvf dist.tar.gz 3D_Viewer.app dvi.html screen settings.txt
	cp ../build/dist.tar.gz .
	rm -rf ../build/dist.tar.gz

dvi:
	open dvi.html

open:
	open ../build/./3D_Viewer.app

tests: clean 
	$(CC) $(FLAGS) $(LIBSOURCES) -o run $(CHECKFLAGS) -lgcov --coverage 
	./run

test_val:
	$(CC) $(FLAGS) $(LIBSOURCES) -o run $(CHECKFLAGS) -lgcov --coverage
	sh valgrind.sh ./run

gcov_report: tests
	lcov -t "test" -o report.info -c -d .
	genhtml -o report report.info
	open ./report/index.html
	make clean

clean_qmake:
	rm -rf ../build/*.o \
	../build/.qmake.stash \
	../build/ui_graphform.h \
	../build/ui_mainwindow.h \
	../build/Makefile \
	../build/moc_graphform.cpp \
	../build/moc_mainwindow.cpp \
	../build/moc_predefs.h \
	../build/moc_qcustomplot.cpp \
	../build/smart_calc.pro \

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -style=Google -i -n FilesOnC/*.c FilesOnC/*.h \
	main.cpp mainwindow.cpp mainwindow.h autosave.cpp \
	myglwidget.cpp myglwidget.h

clean:
	rm -rf tests.o \
	affine_trans.o \
	parser.o \
	*.gcno \
	*.gcda \
	./run.dSYM \
	report.info

	