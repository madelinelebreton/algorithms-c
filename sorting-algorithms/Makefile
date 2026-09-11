# default target to build only the shared library
all: libmysort.so

# compile shared library
libmysort.so: mySort.o
	gcc -shared -o libmysort.so mySort.o

# compile mySort.o from mySort.c
mySort.o: mySort.c mySort.h
	gcc -Wall -O3 -fPIC -c mySort.c

clean:
	rm -f mySort.o libmysort.so testSort
