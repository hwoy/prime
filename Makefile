CC = gcc
bin = prime
CFLAGS =  -O2  -ansi -Wpedantic -Wall -Wextra

.PHONY: all clean

all:	$(bin)

$(bin):	main.o prime.o function.o opt.o
	$(CC) -o $(bin) main.o prime.o function.o opt.o

clean:
	rm -rf *.o *.exe $(bin) *~


function.o: function.c function.h
main.o: main.c prime.h function.h opt.h
opt.o: opt.c opt.h
prime.o: prime.c prime.h
