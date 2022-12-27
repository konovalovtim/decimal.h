CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
TFLAGS=-fprofile-arcs -ftest-coverage
DComp=Comparison/*.c
DConv=Converters/*.c
DAux=Auxiliary/*.c
DArith=Arithmetic/*.c
Dunit=unit_tests/*.c
DO=Other/*.c

all: s21_decimal.a test gcov_report

s21_decimal.a:
	$(CC) $(CFLAGS) -c $(DComp) $(DConv) $(DAux) $(DArith) $(DO)
	ar r s21_decimal.a *.o
	rm *.o

test: objectsLib objects_test
	$(CC) $(TFLAGS) object_files/*.o -o test -lcheck
	./test
	mv *.gcda object_files

objects_test:
	$(CC) $(CFLAGS) -c $(Dunit)
	mv *.o object_files

objectsLib:
	$(CC) $(CFLAGS) -c $(TFLAGS) $(DComp) $(DConv) $(DArith) $(DO)
	$(CC) $(CFLAGS) -c $(DAux)
	mv *.o object_files
	mv *.gcno object_files

gcov_report:
	lcov -t test -o rep.info -c -d .
	genhtml -o report rep.info
	open ./report/index.html

style:
	clang-format -n $(DComp) $(DConv) $(DAux) $(DArith) $(DO) *.h

clean:
	rm Report/report.* object_files/*.* *.a *.html *.info Report/* test

rebuild: clean all
