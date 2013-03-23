CC=gcc
CFLAGS=-O3 -Wall -ansi

all:
	$(CC) $(CFLAGS) core.c -o core -ldl
	$(CC) $(CFLAGS) -c -fPIC module1.c -o module1.o
	$(CC) -shared module1.o -o module1.so 
	$(CC) $(CFLAGS) -c -fPIC module2.c -o module2.o
	$(CC) -shared module2.o -o module2.so 
	$(CC) $(CFLAGS) -c -fPIC module3.c -o module3.o
	$(CC) -shared module3.o -o module3.so 
	
test:
	./core configuration.conf
