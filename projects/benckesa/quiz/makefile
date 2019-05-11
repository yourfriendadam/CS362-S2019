CFLAGS= -Wall -fpic -coverage -lm -std=c99
	
testme: testme.o
	gcc -o testme testme.c -g $(CFLAGS)
	
testme.o: testme.c
	gcc -c testme.c -g $(CFLAGS)
	
runtests: testme 
	./testme &> testresult.out
	gcov testme.c >> testresult.out
	cat testme.c.gcov >> testresult.out

all: testme

clean:
	rm -f *.o testme
