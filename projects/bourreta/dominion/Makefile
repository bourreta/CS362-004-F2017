CFLAGS = -Wall -fpic -coverage -lm

unittest1: 
	gcc -fprofile-arcs -ftest-coverage dominion.o unittest1.c rngs.o -o unittest1 -g $(CFLAGS)

unittest2: 
	gcc -fprofile-arcs -ftest-coverage dominion.o unittest2.c rngs.o -o unittest2 -g $(CFLAGS)

unittest3: 
	gcc -fprofile-arcs -ftest-coverage dominion.o unittest3.c rngs.o -o unittest3 -g $(CFLAGS)

unittest4: 
	gcc -fprofile-arcs -ftest-coverage dominion.o unittest4.c rngs.o -o unittest4 -g $(CFLAGS)

cardtest1:			
	gcc -fprofile-arcs -ftest-coverage dominion.o cardtest1.c rngs.o -o cardtest1 -g $(CFLAGS)			

cardtest2:			
	gcc -fprofile-arcs -ftest-coverage dominion.o cardtest2.c rngs.o -o cardtest2 -g $(CFLAGS)		

cardtest3:			
	gcc -fprofile-arcs -ftest-coverage dominion.o cardtest3.c rngs.o -o cardtest3 -g $(CFLAGS)	
	
cardtest4:			
	gcc -fprofile-arcs -ftest-coverage dominion.o cardtest4.c rngs.o -o cardtest4 -g $(CFLAGS)	

randomtestcard1:			
	gcc -fprofile-arcs -ftest-coverage dominion.o randomtestcard1.c rngs.o -o randomtestcard1 -g $(CFLAGS)

randomtestcard2:			
	gcc -fprofile-arcs -ftest-coverage dominion.o randomtestcard2.c rngs.o -o randomtestcard2 -g $(CFLAGS)

randomtestadventurer:			
	gcc -fprofile-arcs -ftest-coverage dominion.o randomtestadventurer.c rngs.o -o randomtestadventurer -g $(CFLAGS)

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

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

runtests2: 
	./unittest1 &> unittestresult.out
	./unittest2 >> unittestresult.out
	./unittest3 >> unittestresult.out
	./unittest4 >> unittestresult.out
	./cardtest1 >> unittestresult.out
	./cardtest2 >> unittestresult.out
	./cardtest3 >> unittestresult.out
	./cardtest4 >> unittestresult.out
	gcov dominion.c -b >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

runrandomtestcard1:
	./randomtestcard1 &> randomtestcard1.out
	gcov dominion.c -b >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

runrandomtestcard2:
	./randomtestcard2 &> randomtestcard2.out
	gcov dominion.c -b >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

runrandomtestadventurer:
	./randomtestadventurer &> randomtestadventurer.out
	gcov dominion.c -b >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard randomtestcard1 randomtestcard2 randomtestadventurer unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4

clean:
	rm -f *.o playdom.exe playdom player player.exe randomtestcard1 randomtestcard2 randomtestadventurer unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
