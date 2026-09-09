kalkul: calculate.o main.o
	gcc calculate.o main.o -o kalkul -lm

calculate.o: calculate.c calculate.h
	gcc -c calculate.c

main.o: main.c calculate.h
	gcc -c main.c

clean:
	rm -f kalkul calculate.o main.o

install:
	cp kalkul /usr/local/bin/kalkul

uninstall:
	rm -f /usr/local/bin/kalkul