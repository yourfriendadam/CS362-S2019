#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "adventurer"

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
    
    int i;
    int discarded = 1;
    int handpos = 0;    
	int treasureAdded = 2; //used for verification with testState
	int deckCardsRemoved = 2; //used for verification with testState, begins at 2 for 2 drawntreasure
    int testsPassed = 0;
    int testsFailed = 0;

/******************************************************************************
    Test 1
******************************************************************************/
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("Random Test: hand count values\n");
	
    for(int j = 0; j < 5000; j++) {
		initializeGame(numPlayer, k, seed, &state); 
		state.deckCount[currP] = 10;
		
		// set deck order to control draws
		// printf("Deck order:\n");
		for(i = 0; i < 10; i++) {
			if(i > 4) {
				// top half of deck, first cards drawn
				state.deck[currP][i] = estate;
				// printf("Card %d		estate\n", i);
				deckCardsRemoved++;
			}
			else {
				// bottom half of deck, last cards drawn
				state.deck[currP][i] = copper;			
				// printf("Card %d		copper\n", i);
			}
		}
	
	    state.handCount[currP] = rand() % MAX_HAND + 1;
	    memcpy(&testState, &state, sizeof(struct gameState)); 
	    
	    // preconditions
		// printf("\nNumber of cards in hand to begin:\n");
		// asserttrue(state.handCount[currP], testState.handCount[currP]);
		// printf("Cards in deck to begin:\n");
		// asserttrue(state.deckCount[currP], testState.deckCount[currP]);
		// printf("Cards in hand:\n");
	    
	    // set handpos 0 to adventurer card
	    state.hand[currP][0] = 7;
		
	    cardEffect(adventurer, 0, 0, 0, &state, handpos, 0);
	    // printf("\nRan playAdventurer\n\n");
	
	    // post test	
	    // printf("Current cards in hand:\n");
	    if(asserttrue(state.handCount[currP], testState.handCount[currP] + treasureAdded - discarded)) {
	        testsPassed++;
	    }
	    else {
	        testsFailed++;
	    }
		// printf("Current cards in deck:\n");
		// asserttrue(state.deckCount[currP], testState.deckCount[currP] - deckCardsRemoved);
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
	
    for(int j = 0; j < 5000; j++) {
		initializeGame(numPlayer, k, seed, &state); 
		state.deckCount[currP] = rand() % MAX_DECK + 1;
		
		// set deck order to control draws
		// printf("Deck order:\n");
		for(i = 0; i < state.deckCount[currP]; i++) {
			if(i > 4) {
				// top half of deck, first cards drawn
				state.deck[currP][i] = estate;
				// printf("Card %d		estate\n", i);
				deckCardsRemoved++;
			}
			else {
				// bottom half of deck, last cards drawn
				state.deck[currP][i] = copper;			
				// printf("Card %d		copper\n", i);
			}
		}
	
	    state.handCount[currP] = rand() % MAX_HAND + 1;
	    memcpy(&testState, &state, sizeof(struct gameState)); 
	    
	    // preconditions
		// printf("\nNumber of cards in hand to begin:\n");
		// asserttrue(state.handCount[currP], testState.handCount[currP]);
		// printf("Cards in deck to begin:\n");
		// asserttrue(state.deckCount[currP], testState.deckCount[currP]);
		// printf("Cards in hand:\n");
	    
	    // set handpos 0 to adventurer card
	    state.hand[currP][0] = 7;
		
	    cardEffect(adventurer, 0, 0, 0, &state, handpos, 0);
	    // printf("\nRan playAdventurer\n\n");
	
	    // post test	
	    // printf("Current cards in hand:\n");
	    if(asserttrue(state.deckCount[currP], testState.deckCount[currP] - deckCardsRemoved)) {
	        testsPassed++;
	    }
	    else {
	        testsFailed++;
	    }
    }
	printf("----------------------------------\n");
    printf("Tests passed: %d\n\n", testsPassed);
    printf("Tests failed: %d\n\n", testsFailed);
	
/******************************************************************************
    Test 3
******************************************************************************/
    testsPassed = 0;
    testsFailed = 0;
	printf("Random Test: num player values\n");
	
    for(int j = 0; j < 5000; j++) {
        numPlayer = rand() % MAX_PLAYERS + 1;
		initializeGame(numPlayer, k, seed, &state); 
		
		// set deck order to control draws
		// printf("Deck order:\n");
		for(i = 0; i < state.deckCount[currP]; i++) {
			if(i > 4) {
				// top half of deck, first cards drawn
				state.deck[currP][i] = estate;
				// printf("Card %d		estate\n", i);
				deckCardsRemoved++;
			}
			else {
				// bottom half of deck, last cards drawn
				state.deck[currP][i] = copper;			
				// printf("Card %d		copper\n", i);
			}
		}
	
	    memcpy(&testState, &state, sizeof(struct gameState)); 
	    
	    // preconditions
		// printf("\nNumber of cards in hand to begin:\n");
		// asserttrue(state.handCount[currP], testState.handCount[currP]);
		// printf("Cards in deck to begin:\n");
		// asserttrue(state.deckCount[currP], testState.deckCount[currP]);
		// printf("Cards in hand:\n");
	    
	    // set handpos 0 to adventurer card
	    state.hand[currP][0] = 7;
		
	    cardEffect(adventurer, 0, 0, 0, &state, handpos, 0);
	    // printf("\nRan playAdventurer\n\n");
	
	    // post test	
	    // printf("Current cards in hand:\n");
	    if(asserttrue(state.handCount[currP], testState.handCount[currP] + treasureAdded - discarded)) {
	        testsPassed++;
	    }
	    else {
	        testsFailed++;
	    }
    }
	printf("----------------------------------\n");
    printf("Tests passed: %d\n\n", testsPassed);
    printf("Tests failed: %d\n\n", testsFailed);

/******************************************************************************
    Test 4
******************************************************************************/
    testsPassed = 0;
    testsFailed = 0;
	printf("Random Test: handpos values\n");
	
    for(int j = 0; j < 5000; j++) {
		initializeGame(numPlayer, k, seed, &state); 

        handpos = rand() % state.handCount[currP] + 1;		
		// set deck order to control draws
		// printf("Deck order:\n");
		for(i = 0; i < state.deckCount[currP]; i++) {
			if(i > 4) {
				// top half of deck, first cards drawn
				state.deck[currP][i] = estate;
				// printf("Card %d		estate\n", i);
				deckCardsRemoved++;
			}
			else {
				// bottom half of deck, last cards drawn
				state.deck[currP][i] = copper;			
				// printf("Card %d		copper\n", i);
			}
		}
	
	    memcpy(&testState, &state, sizeof(struct gameState)); 
	    
	    // preconditions
		// printf("\nNumber of cards in hand to begin:\n");
		// asserttrue(state.handCount[currP], testState.handCount[currP]);
		// printf("Cards in deck to begin:\n");
		// asserttrue(state.deckCount[currP], testState.deckCount[currP]);
		// printf("Cards in hand:\n");
	    
	    // set handpos 0 to adventurer card
	    state.hand[currP][0] = 7;
		
	    cardEffect(adventurer, 0, 0, 0, &state, handpos, 0);
	    // printf("\nRan playAdventurer\n\n");
	
	    // post test	
	    // printf("Current cards in hand:\n");
	    if(asserttrue(state.handCount[currP], testState.handCount[currP] + treasureAdded - discarded)) {
	        testsPassed++;
	    }
	    else {
	        testsFailed++;
	    }
    }
	printf("----------------------------------\n");
    printf("Tests passed: %d\n\n", testsPassed);
    printf("Tests failed: %d\n\n", testsFailed);
    
	return 0;
}