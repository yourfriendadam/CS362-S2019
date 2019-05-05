CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)
	
unittest1.o: unittest1.c dominion.o rngs.o
	gcc -c unittest1.c -g $(CFLAGS)

unittest2.o: unittest2.c dominion.o rngs.o
	gcc -c unittest2.c -g $(CFLAGS)

unittest3.o: unittest3.c dominion.o rngs.o
	gcc -c unittest3.c -g $(CFLAGS)

unittest4.o: unittest4.c dominion.o rngs.o
	gcc -c unittest4.c -g $(CFLAGS)

cardtest1.o: cardtest1.c dominion.o rngs.o
	gcc -c cardtest1.c -g $(CFLAGS)

cardtest2.o: cardtest2.c dominion.o rngs.o
	gcc -c cardtest2.c -g $(CFLAGS)
	
cardtest3.o: cardtest3.c dominion.o rngs.o
	gcc -c cardtest3.c -g $(CFLAGS)
	
cardtest4.o: cardtest4.c dominion.o rngs.o
	gcc -c cardtest4.c -g $(CFLAGS)
	
playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

#########

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittest1: unittest1.o dominion.o
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)
	
unittest2: unittest2.o dominion.o
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.o dominion.o
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.o dominion.o
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.o dominion.o
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.o dominion.o
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)
	
cardtest3: cardtest3.o dominion.o
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)
	
cardtest4: cardtest4.o dominion.o
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)
	
unittestresults: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 dominion.o
	./unittest1 &> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov unittest1.c >> unittestresults.out
	gcov unittest2.c >> unittestresults.out
	gcov unittest3.c >> unittestresults.out
	gcov unittest4.c >> unittestresults.out
	gcov cardtest1.c >> unittestresults.out
	gcov cardtest2.c >> unittestresults.out
	gcov cardtest3.c >> unittestresults.out
	gcov cardtest4.c >> unittestresults.out
	cat unittest1.c.gcov >> unittestresults.out
	cat unittest2.c.gcov >> unittestresults.out
	cat unittest3.c.gcov >> unittestresults.out
	cat unittest4.c.gcov >> unittestresults.out
	cat cardtest1.c.gcov >> unittestresults.out
	cat cardtest2.c.gcov >> unittestresults.out
	cat cardtest3.c.gcov >> unittestresults.out
	cat cardtest4.c.gcov >> unittestresults.out
	
	
testUpdateCoins: dominion.o
	gcc -o testUpdateCoins testUpdateCoins.c -g dominion.o rngs.o $(CFLAGS)
    
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
