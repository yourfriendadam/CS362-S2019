#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "smithy"

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
    int testsPassed = 0;
    int testsFailed = 0;
    // state.deckCount[currP]=10;
    // int maxHandCount = 5;
	// MAX_HAND is 500 
    memset(&state, 0, sizeof(struct gameState));
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
    // 	printf("Cards in hand to begin:\n");
    // 	asserttrue(state.handCount[currP], testState.handCount[currP]);
    // 	printf("Cards in deck to begin:\n");
    // 	asserttrue(state.deckCount[currP], testState.deckCount[currP]);
    	
    	int drawnCards = 3;
        cardEffect(smithy, 0, 0, 0, &state, handpos, 0);
        // printf("Ran playSmithy\n\n");
        
        // post test	
        // printf("cards in hand after playing Smithy:\n");
        if(asserttrue(state.handCount[currP], testState.handCount[currP] + drawnCards - discarded)) {
            testsPassed++;
        }
        else {
            testsFailed++;
        }
    // 	printf("cards in deck after playing Smithy:\n");
    // 	if(asserttrue(state.deckCount[currP], testState.deckCount[currP] - drawnCards)) {
    //         testsPassed++;
    //     }
    //     else {
    //         testsFailed++;
    // 	}        
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
    // initialize game with hand and deck amounts reset from any previous tests
    for(int i = 0; i < 5000; i++) {
	    initializeGame(numPlayer, k, seed, &state); 
        state.deckCount[currP] = rand() % MAX_DECK + 1;
        memcpy(&testState, &state, sizeof(struct gameState));     
        // preconditions
    // 	printf("Cards in hand to begin:\n");
    // 	asserttrue(state.handCount[currP], testState.handCount[currP]);
    // 	printf("Cards in deck to begin:\n");
    // 	asserttrue(state.deckCount[currP], testState.deckCount[currP]);
    	
    	int drawnCards = 3;
        cardEffect(smithy, 0, 0, 0, &state, handpos, 0);
        // printf("Ran playSmithy\n\n");
        
        // post test	
        // printf("cards in hand after playing Smithy:\n");
        // if(asserttrue(state.handCount[currP], testState.handCount[currP] + drawnCards - discarded)) {
        //     testsPassed++;
        // }
        // else {
        //     testsFailed++;
        // }
    // 	printf("cards in deck after playing Smithy:\n");
    	if(asserttrue(state.deckCount[currP], testState.deckCount[currP] - drawnCards)) {
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
    // initialize game with hand and deck amounts reset from any previous tests
    for(int i = 0; i < 5000; i++) {
        numPlayer = rand() % MAX_PLAYERS + 1;
	    initializeGame(numPlayer, k, seed, &state); 
        memcpy(&testState, &state, sizeof(struct gameState));     
        // preconditions
    // 	printf("Cards in hand to begin:\n");
    // 	asserttrue(state.handCount[currP], testState.handCount[currP]);
    // 	printf("Cards in deck to begin:\n");
    // 	asserttrue(state.deckCount[currP], testState.deckCount[currP]);
    	
    	int drawnCards = 3;
        cardEffect(smithy, 0, 0, 0, &state, handpos, 0);
        // printf("Ran playSmithy\n\n");
        
        // post test	
        // printf("cards in hand after playing Smithy:\n");
        if(asserttrue(state.handCount[currP], testState.handCount[currP] + drawnCards - discarded)) {
            testsPassed++;
        }
        else {
            testsFailed++;
        }
    // 	printf("cards in deck after playing Smithy:\n");
    // 	if(asserttrue(state.deckCount[currP], testState.deckCount[currP] - drawnCards)) {
    //         testsPassed++;
    //     }
    //     else {
    //         testsFailed++;
    // 	}        
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
    // initialize game with hand and deck amounts reset from any previous tests
    for(int i = 0; i < 5000; i++) {
        handpos = rand() % state.handCount[currP] + 1;
	    initializeGame(numPlayer, k, seed, &state); 
        memcpy(&testState, &state, sizeof(struct gameState));     
        // preconditions
    // 	printf("Cards in hand to begin:\n");
    // 	asserttrue(state.handCount[currP], testState.handCount[currP]);
    // 	printf("Cards in deck to begin:\n");
    // 	asserttrue(state.deckCount[currP], testState.deckCount[currP]);
    	
    	int drawnCards = 3;
        cardEffect(smithy, 0, 0, 0, &state, handpos, 0);
        // printf("Ran playSmithy\n\n");
        
        // post test	
        // printf("cards in hand after playing Smithy:\n");
        if(asserttrue(state.handCount[currP], testState.handCount[currP] + drawnCards - discarded)) {
            testsPassed++;
        }
        else {
            testsFailed++;
        }
    // 	printf("cards in deck after playing Smithy:\n");
    // 	if(asserttrue(state.deckCount[currP], testState.deckCount[currP] - drawnCards)) {
    //         testsPassed++;
    //     }
    //     else {
    //         testsFailed++;
    // 	}        
    }
	printf("----------------------------------\n");
    printf("Tests passed: %d\n\n", testsPassed);
    printf("Tests failed: %d\n\n", testsFailed);
    
    return 0;
}