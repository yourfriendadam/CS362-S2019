#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "council_room"

int asserttrue(int expVal, int verifyVal) {
        // printf("actual: %d  expected: %d\n", expVal, verifyVal);
        
        if(expVal == verifyVal) {
            // printf("Passed: Results match.\n\n");
            return 1;
        }
        else {
            // printf("Failed: Results do NOT match.\n\n");
            return 0;
        }
}

int main() {
    srand(time(0));
    int seed = 1000;
    int numPlayer = 2;
    int currP = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, cutpurse, great_hall};
    struct gameState state, testState;
    
    int discarded = 1;
    int handpos = 0;  
    int totalPlayers = 0;
    int testsPassed = 0;
    int testsFailed = 0;

/******************************************************************************
    Test 1
******************************************************************************/
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("Random Test: hand count values\n");

    for(int i = 0; i < 5000; i++) {
		initializeGame(numPlayer, k, seed, &state); 
        state.handCount[currP] = rand() % MAX_HAND + 1;
		
	    memcpy(&testState, &state, sizeof(struct gameState)); 
	    
	    // preconditions
		// printf("Cards in hand to begin:\n");
		// asserttrue(state.handCount[currP], testState.handCount[currP]);
		// printf("Cards in deck to begin:\n");
		// asserttrue(state.deckCount[currP], testState.deckCount[currP]);
		
		// printf("Num Buys before play:\n");
		// asserttrue(state.numBuys, testState.numBuys);
		
		// printf("Cards in opponent's hand to begin:\n");
		// asserttrue(state.handCount[otherP], testState.handCount[otherP]);
		// printf("Cards in opponent's deck to begin:\n");
		// asserttrue(state.deckCount[otherP], testState.deckCount[otherP]);
	
		int drawnCards = 4;
		// int numBuyIncrease = 1;
        cardEffect(council_room, 0, 0, 0, &state, handpos, 0);
	    // printf("Ran playCouncilRoom\n\n");
	
	    // post test	
	    // printf("Current cards in hand:\n");
	    if(asserttrue(state.handCount[currP], testState.handCount[currP] + drawnCards - discarded)) {
            testsPassed++;
        }
        else {
            testsFailed++;
        }
		// printf("Current cards in deck:\n");
		// asserttrue(state.deckCount[currP], testState.deckCount[currP] - drawnCards);
		
		// printf("Num Buys before play:\n");
		// asserttrue(state.numBuys, testState.numBuys + numBuyIncrease);
		
	 //   printf("Cards in opponent's hand:\n");
	 //   asserttrue(state.handCount[otherP], testState.handCount[otherP] + oppDrawnCards);
		// printf("Cards in opponent's deck:\n");
		// asserttrue(state.deckCount[otherP], testState.deckCount[otherP] - oppDrawnCards);
    }
	printf("----------------------------------\n");
    printf("Tests passed: %d\n\n", testsPassed);
    printf("Tests failed: %d\n\n", testsFailed);  
    
/******************************************************************************
    Test 2
******************************************************************************/
    testsPassed = 0;
    testsFailed = 0;
	printf("Random Test: deck count values\n");

    for(int i = 0; i < 5000; i++) {
		initializeGame(numPlayer, k, seed, &state); 
        state.deckCount[currP] = rand() % MAX_DECK + 1;
		
	    memcpy(&testState, &state, sizeof(struct gameState)); 
	    
	    // preconditions
		// printf("Cards in hand to begin:\n");
		// asserttrue(state.handCount[currP], testState.handCount[currP]);
		// printf("Cards in deck to begin:\n");
		// asserttrue(state.deckCount[currP], testState.deckCount[currP]);
		
		// printf("Num Buys before play:\n");
		// asserttrue(state.numBuys, testState.numBuys);
		
		// printf("Cards in opponent's hand to begin:\n");
		// asserttrue(state.handCount[otherP], testState.handCount[otherP]);
		// printf("Cards in opponent's deck to begin:\n");
		// asserttrue(state.deckCount[otherP], testState.deckCount[otherP]);
		int drawnCards = 4;	
        cardEffect(council_room, 0, 0, 0, &state, handpos, 0);
	    // printf("Ran playCouncilRoom\n\n");
	
	    // post test	
	    // printf("Current cards in hand:\n");
	    if(asserttrue(state.deckCount[currP], testState.deckCount[currP] - drawnCards)) {
            testsPassed++;
        }
        else {
            testsFailed++;
        }
		// printf("Current cards in deck:\n");
		// asserttrue(state.deckCount[currP], testState.deckCount[currP] - drawnCards);
		
		// printf("Num Buys before play:\n");
		// asserttrue(state.numBuys, testState.numBuys + numBuyIncrease);
		
	 //   printf("Cards in opponent's hand:\n");
	 //   asserttrue(state.handCount[otherP], testState.handCount[otherP] + oppDrawnCards);
		// printf("Cards in opponent's deck:\n");
		// asserttrue(state.deckCount[otherP], testState.deckCount[otherP] - oppDrawnCards);
    }
	printf("----------------------------------\n");
    printf("Tests passed: %d\n\n", testsPassed);
    printf("Tests failed: %d\n\n", testsFailed);   
    
/******************************************************************************
    Test 3
******************************************************************************/
    testsPassed = 0;
    testsFailed = 0;
	printf("Random Test: other players' deck counts\n");

    for(int i = 0; i < 5000; i++) {
        totalPlayers = rand() % MAX_PLAYERS + 1;
		initializeGame(numPlayer, k, seed, &state); 
		
	    memcpy(&testState, &state, sizeof(struct gameState)); 
	    
	    // preconditions
		// printf("Cards in hand to begin:\n");
		// asserttrue(state.handCount[currP], testState.handCount[currP]);
		// printf("Cards in deck to begin:\n");
		// asserttrue(state.deckCount[currP], testState.deckCount[currP]);
		
		// printf("Num Buys before play:\n");
		// asserttrue(state.numBuys, testState.numBuys);
		
		// printf("Cards in opponent's hand to begin:\n");
		// asserttrue(state.handCount[otherP], testState.handCount[otherP]);
		// printf("Cards in opponent's deck to begin:\n");
		// asserttrue(state.deckCount[otherP], testState.deckCount[otherP]);
		int oppDrawnCards = 1;
        cardEffect(council_room, 0, 0, 0, &state, handpos, 0);
	    // printf("Ran playCouncilRoom\n\n");
	
	    // post test	
		// check deckCount for all opposing players- don't have to initialize hands for each player this way
	    for(int k = 0; k < totalPlayers; k++) {
	    	if(k != currP) {
			    if(asserttrue(state.deckCount[k], testState.deckCount[k] - oppDrawnCards)) {
		            testsPassed++;
		        }
		        else {
		            testsFailed++;
		        }	 	    		
	    	}
   	
	    }

		// printf("Current cards in deck:\n");
		// asserttrue(state.deckCount[currP], testState.deckCount[currP] - drawnCards);
		
		// printf("Num Buys before play:\n");
		// asserttrue(state.numBuys, testState.numBuys + numBuyIncrease);
		
	 //   printf("Cards in opponent's hand:\n");
	 //   asserttrue(state.handCount[otherP], testState.handCount[otherP] + oppDrawnCards);
		// printf("Cards in opponent's deck:\n");
		// asserttrue(state.deckCount[otherP], testState.deckCount[otherP] - oppDrawnCards);
    }
	printf("----------------------------------\n");
    printf("Tests passed: %d\n\n", testsPassed);
    printf("Tests failed: %d\n\n", testsFailed);   

/******************************************************************************
    Test 4
******************************************************************************/
    testsPassed = 0;
    testsFailed = 0;
	printf("Random Test: num buys\n");

    for(int i = 0; i < 5000; i++) {
		initializeGame(numPlayer, k, seed, &state); 

		state.numBuys = rand() % 1000 + 1;		
	    memcpy(&testState, &state, sizeof(struct gameState)); 
	    
	    // preconditions
		// printf("Cards in hand to begin:\n");
		// asserttrue(state.handCount[currP], testState.handCount[currP]);
		// printf("Cards in deck to begin:\n");
		// asserttrue(state.deckCount[currP], testState.deckCount[currP]);
		
		// printf("Num Buys before play:\n");
		// asserttrue(state.numBuys, testState.numBuys);
		
		// printf("Cards in opponent's hand to begin:\n");
		// asserttrue(state.handCount[otherP], testState.handCount[otherP]);
		// printf("Cards in opponent's deck to begin:\n");
		// asserttrue(state.deckCount[otherP], testState.deckCount[otherP]);
		int numBuyIncrease = 1;
        cardEffect(council_room, 0, 0, 0, &state, handpos, 0);
	    // printf("Ran playCouncilRoom\n\n");
	
	    // post test	
	    if(asserttrue(state.numBuys, testState.numBuys + numBuyIncrease)) {
            testsPassed++;
        }
        else {
            testsFailed++;
        }	 	    		

		// printf("Current cards in deck:\n");
		// asserttrue(state.deckCount[currP], testState.deckCount[currP] - drawnCards);
		
		// printf("Num Buys before play:\n");
		// asserttrue(state.numBuys, testState.numBuys + numBuyIncrease);
		
	 //   printf("Cards in opponent's hand:\n");
	 //   asserttrue(state.handCount[otherP], testState.handCount[otherP] + oppDrawnCards);
		// printf("Cards in opponent's deck:\n");
		// asserttrue(state.deckCount[otherP], testState.deckCount[otherP] - oppDrawnCards);
    }
	printf("----------------------------------\n");
    printf("Tests passed: %d\n\n", testsPassed);
    printf("Tests failed: %d\n\n", testsFailed);   
    
	return 0;
}