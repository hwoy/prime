cc = gcc
bin = prime.exe
CFLAGS =  -O2  -ansi -pedantic -Wall -Werror

.PHONY: all clean

all:	$(bin)

$(bin):	main.o prime.o
	$(cc) -o $(bin) main.o prime.o
main.o:
	$(cc) -c -o main.o $(CFLAGS) main.c
prime.o:
	$(cc) -c -o prime.o $(CFLAGS) prime.c
clean:
	del main.o prime.o $(bin) *~
