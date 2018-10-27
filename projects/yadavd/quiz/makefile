CFLAGS = -Wall -std=c99

default: randomtest

randomtest: testme.c
	
	echo "Result for running testme.c:" > testme.out
	gcc -o testme -g testme.c $(CFLAGS)
	./testme >> testme.out