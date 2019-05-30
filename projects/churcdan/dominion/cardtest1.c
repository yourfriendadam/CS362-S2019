#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "smithy"

int asserttrue(int expVal, int verifyVal) {
        printf("actual: %d  expected: %d\n", expVal, verifyVal);
        
        if(expVal == verifyVal) {
            printf("Results match.\n\n");
            return 0;
        }
        else {
            printf("Results do NOT match.\n\n");
            return 1;
        }
}

int main() {
    int seed = 1000;
    int numPlayer = 2;
    int currP = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, cutpurse, great_hall};
    struct gameState state, testState;
    
    int discarded = 1;
    int handpos = 0;
    // state.deckCount[currP]=10;
    // int maxHandCount = 5;
	// MAX_HAND is 500 
	
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("Test 1: check large valid handpos\n\n");
	
	handpos = 4;
	
    // initialize game with hand and deck amounts reset from any previous tests
	initializeGame(numPlayer, k, seed, &state); 
    memcpy(&testState, &state, sizeof(struct gameState)); 
    
    // preconditions
    printf("Handpos is: %d\n", handpos);
	printf("Cards in hand to begin:\n");
	asserttrue(state.handCount[currP], testState.handCount[currP]);
	
	int drawnCards = 3;
    cardEffect(smithy, 0, 0, 0, &state, handpos, 0);
    printf("Ran playSmithy\n\n");
    
    // post test	
    printf("Current cards in hand:\n");
    asserttrue(state.handCount[currP], testState.handCount[currP] + drawnCards - discarded);

    printf("Victory card supplies:\n");
    printf("Estates:\n");
    asserttrue(state.supplyCount[estate], testState.supplyCount[estate]);
    printf("Duchies:\n");
    asserttrue(state.supplyCount[duchy], testState.supplyCount[duchy]);
    printf("Provinces:\n");
    asserttrue(state.supplyCount[province], testState.supplyCount[province]);
	
	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("Test 2: check large invalid handpos - handpos greater than handsize\n\n");
	
	handpos = 10;

    // initialize game with hand and deck amounts reset from any previous tests
	initializeGame(numPlayer, k, seed, &state); 
    memcpy(&testState, &state, sizeof(struct gameState)); 
	
    // preconditions
    printf("Handpos is: %d\n", handpos);
	printf("Cards in hand to begin:\n");
	asserttrue(state.handCount[currP], testState.handCount[currP]);
	
	drawnCards = 3;
    cardEffect(smithy, 0, 0, 0, &state, handpos, 0);
    printf("Ran playSmithy\n\n");
    	
    // post test	
    printf("Current cards in hand:\n");
    asserttrue(state.handCount[currP], testState.handCount[currP] + drawnCards - discarded);


	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("Test 3: negative value for handpos\n\n");	        

    // initialize game with hand and deck amounts reset from any previous tests
	initializeGame(numPlayer, k, seed, &state); 
    memcpy(&testState, &state, sizeof(struct gameState)); 
    
    handpos = -1;
	
    // preconditions
    printf("Handpos is: %d\n", handpos);
	printf("Cards in hand to begin:\n");
	asserttrue(state.handCount[currP], testState.handCount[currP]);

	
    // no cards in deck to draw
	drawnCards = 0;
    cardEffect(smithy, 0, 0, 0, &state, handpos, 0);
    printf("Ran playSmithy\n\n");
    	
    // post test	
    printf("Current cards in hand:\n");
    asserttrue(state.handCount[currP], testState.handCount[currP] + drawnCards - discarded);

	
// 	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);
// 	printf("Test 4: large negative handpos\n\n");
	
// 	handpos = -1000;
	
//     // initialize game with hand and deck amounts reset from any previous tests
// 	initializeGame(numPlayer, k, seed, &state); 
//     memcpy(&testState, &state, sizeof(struct gameState)); 
	
//     // preconditions
//     printf("Handpos is: %d\n", handpos);
// 	printf("Cards in hand to begin:\n");
// 	asserttrue(state.handCount[currP], testState.handCount[currP]);

//     // no cards in deck to draw
// 	drawnCards = 1;
//     cardEffect(smithy, 0, 0, 0, &state, handpos, 0);
//     printf("Ran playSmithy\n\n");
    	
//     // post test	
//     printf("Current cards in hand:\n");
//     asserttrue(state.handCount[currP], testState.handCount[currP] + drawnCards - discarded);
    
    return 0;
}