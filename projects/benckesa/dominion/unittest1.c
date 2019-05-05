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
    int otherP = 1;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, cutpurse, great_hall};
    struct gameState state, testState;
    
    int discarded = 1;
    int handpos = 0;
    // state.deckCount[currP]=10;
    // int maxHandCount = 5;
	// MAX_HAND is 500 
	
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("Test 1: +3 cards to hand, -3 cards to deck, discard card\n\n");
	
    // initialize game with hand and deck amounts reset from any previous tests
	initializeGame(numPlayer, k, seed, &state); 
    memcpy(&testState, &state, sizeof(struct gameState)); 
    
    // preconditions
	printf("Cards in hand to begin:\n");
	asserttrue(state.handCount[currP], testState.handCount[currP]);
	printf("Cards in deck to begin:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP]);
	
	printf("Cards in opponent's hand to begin:\n");
	asserttrue(state.handCount[otherP], testState.handCount[otherP]);
	printf("Cards in opponent's deck to begin:\n");
	asserttrue(state.deckCount[otherP], testState.deckCount[otherP]);
	
	int drawnCards = 3;
    playSmithy(currP, &state, handpos); 
    printf("Ran playSmithy\n\n");
    
    // post test	
    printf("Current cards in hand:\n");
    asserttrue(state.handCount[currP], testState.handCount[currP] + drawnCards - discarded);
	printf("Current cards in deck:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP] - drawnCards);
	
    printf("Cards in opponent's hand:\n");
    asserttrue(state.handCount[otherP], testState.handCount[otherP]);
	printf("Cards in opponent's deck:\n");
	asserttrue(state.deckCount[otherP], testState.deckCount[otherP]);
	
    printf("Victory card supplies:\n");
    printf("Estates:\n");
    asserttrue(state.supplyCount[estate], testState.supplyCount[estate]);
    printf("Duchies:\n");
    asserttrue(state.supplyCount[duchy], testState.supplyCount[duchy]);
    printf("Provinces:\n");
    asserttrue(state.supplyCount[province], testState.supplyCount[province]);
	
	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("Test 2: +3 cards to hand when hand is at max size\n\n");	        

    // initialize game with hand and deck amounts reset from any previous tests
	initializeGame(numPlayer, k, seed, &state); 
    memcpy(&testState, &state, sizeof(struct gameState)); 
    
	state.handCount[currP] = MAX_HAND;
	testState.handCount[currP] = MAX_HAND;
	state.deckCount[currP] = MAX_DECK;
	testState.deckCount[currP] = MAX_DECK;
	
    // preconditions
	printf("Cards in hand to begin:\n");
	asserttrue(state.handCount[currP], testState.handCount[currP]);
	printf("Cards in deck to begin:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP]);
	
	printf("Cards in opponent's hand to begin:\n");
	asserttrue(state.handCount[otherP], testState.handCount[otherP]);
	printf("Cards in opponent's deck to begin:\n");
	asserttrue(state.deckCount[otherP], testState.deckCount[otherP]);
	
	drawnCards = 3;
    playSmithy(currP, &state, handpos);
    	
    // post test	
    printf("Current cards in hand:\n");
    asserttrue(state.handCount[currP], testState.handCount[currP] + drawnCards - discarded);
	printf("Current cards in deck:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP] - drawnCards);
	
    printf("Cards in opponent's hand:\n");
    asserttrue(state.handCount[otherP], testState.handCount[otherP]);
	printf("Cards in opponent's deck:\n");
	asserttrue(state.deckCount[otherP], testState.deckCount[otherP]);
	
    printf("Victory card supplies:\n");
    printf("Estates:\n");
    asserttrue(state.supplyCount[estate], testState.supplyCount[estate]);
    printf("Duchies:\n");
    asserttrue(state.supplyCount[duchy], testState.supplyCount[duchy]);
    printf("Provinces:\n");
    asserttrue(state.supplyCount[province], testState.supplyCount[province]);

	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("Test 3: +3 cards from deck when deck is empty and played card pile is empty\n\n");	        

    // initialize game with hand and deck amounts reset from any previous tests
	initializeGame(numPlayer, k, seed, &state); 
    memcpy(&testState, &state, sizeof(struct gameState)); 
    
	state.deckCount[currP] = 0;
	testState.deckCount[currP] = 0;
	
    // preconditions
	printf("Cards in hand to begin:\n");
	asserttrue(state.handCount[currP], testState.handCount[currP]);
	printf("Cards in deck to begin:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP]);
	
	printf("Cards in opponent's hand to begin:\n");
	asserttrue(state.handCount[otherP], testState.handCount[otherP]);
	printf("Cards in opponent's deck to begin:\n");
	asserttrue(state.deckCount[otherP], testState.deckCount[otherP]);
	
    // no cards in deck to draw
	drawnCards = 0;
    playSmithy(currP, &state, handpos);
    	
    // post test	
    printf("Current cards in hand:\n");
    asserttrue(state.handCount[currP], testState.handCount[currP] + drawnCards - discarded);
	printf("Current cards in deck:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP] - drawnCards);
	
    printf("Cards in opponent's hand:\n");
    asserttrue(state.handCount[otherP], testState.handCount[otherP]);
	printf("Cards in opponent's deck:\n");
	asserttrue(state.deckCount[otherP], testState.deckCount[otherP]);
	
    printf("Victory card supplies:\n");
    printf("Estates:\n");
    asserttrue(state.supplyCount[estate], testState.supplyCount[estate]);
    printf("Duchies:\n");
    asserttrue(state.supplyCount[duchy], testState.supplyCount[duchy]);
    printf("Provinces:\n");
    asserttrue(state.supplyCount[province], testState.supplyCount[province]);
	
	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("Test 4: +3 cards from deck when deck has less than 3\n\n");
	
    // initialize game with hand and deck amounts reset from any previous tests
	initializeGame(numPlayer, k, seed, &state); 
    memcpy(&testState, &state, sizeof(struct gameState)); 
    
	state.deckCount[currP] = 1;
	testState.deckCount[currP] = 1;
	
    // preconditions
	printf("Cards in hand to begin:\n");
	asserttrue(state.handCount[currP], testState.handCount[currP]);
	printf("Cards in deck to begin:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP]);
	
	printf("Cards in opponent's hand to begin:\n");
	asserttrue(state.handCount[otherP], testState.handCount[otherP]);
	printf("Cards in opponent's deck to begin:\n");
	asserttrue(state.deckCount[otherP], testState.deckCount[otherP]);
	
	// no cards in deck to draw
	drawnCards = 1;
    playSmithy(currP, &state, handpos);
    	
    // post test	
    printf("Current cards in hand:\n");
    asserttrue(state.handCount[currP], testState.handCount[currP] + drawnCards - discarded);
	printf("Current cards in deck:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP] - drawnCards);
	
    printf("Cards in opponent's hand:\n");
    asserttrue(state.handCount[otherP], testState.handCount[otherP]);
	printf("Cards in opponent's deck:\n");
	asserttrue(state.deckCount[otherP], testState.deckCount[otherP]);
	
    printf("Victory card supplies:\n");
    printf("Estates:\n");
    asserttrue(state.supplyCount[estate], testState.supplyCount[estate]);
    printf("Duchies:\n");
    asserttrue(state.supplyCount[duchy], testState.supplyCount[duchy]);
    printf("Provinces:\n");
    asserttrue(state.supplyCount[province], testState.supplyCount[province]);
    
    return 0;
}