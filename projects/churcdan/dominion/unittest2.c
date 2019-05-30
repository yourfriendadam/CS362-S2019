#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "village"

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

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("Test 1: +1 card to hand, +2 actions in state\n\n");
	
    // initialize game with hand and deck amounts reset from any previous tests
	initializeGame(numPlayer, k, seed, &state); 
    memcpy(&testState, &state, sizeof(struct gameState)); 
    
    // preconditions
	printf("Cards in hand to begin:\n");
	asserttrue(state.handCount[currP], testState.handCount[currP]);
	printf("Cards in deck to begin:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP]);
	
	printf("Num Actions before play:\n");
	asserttrue(state.numActions, testState.numActions);
	
	printf("Cards in opponent's hand to begin:\n");
	asserttrue(state.handCount[otherP], testState.handCount[otherP]);
	printf("Cards in opponent's deck to begin:\n");
	asserttrue(state.deckCount[otherP], testState.deckCount[otherP]);

	int drawnCards = 1;
	int numActionIncrease = 2;
    cardEffect(village, 0, 0, 0, &state, handpos, 0);
    // printf("Ran playVillage\n\n");

    // post test	
    printf("Current cards in hand:\n");
    asserttrue(state.handCount[currP], testState.handCount[currP] + drawnCards - discarded);
	printf("Current cards in deck:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP] - drawnCards);
	
	printf("Num Actions after play:\n"); 
	asserttrue(state.numActions, testState.numActions + numActionIncrease);
	
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


	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("Test 2: +1 card to hand, +2 actions in state when deck is -1\n\n");
	
    // initialize game with hand and deck amounts reset from any previous tests
	initializeGame(numPlayer, k, seed, &state); 
    memcpy(&testState, &state, sizeof(struct gameState)); 
    
	state.deckCount[currP] = -1;
	testState.deckCount[currP] = -1;
	
    // preconditions
	printf("Cards in hand to begin:\n");
	asserttrue(state.handCount[currP], testState.handCount[currP]);
	printf("Cards in deck to begin:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP]);
	
	printf("Num Actions before play:\n");
	asserttrue(state.numActions, testState.numActions);
	
	printf("Cards in opponent's hand to begin:\n");
	asserttrue(state.handCount[otherP], testState.handCount[otherP]);
	printf("Cards in opponent's deck to begin:\n");
	asserttrue(state.deckCount[otherP], testState.deckCount[otherP]);

	drawnCards = 0;
    cardEffect(village, 0, 0, 0, &state, handpos, 0);
    // printf("Ran playVillage\n\n");

    // post test	
    printf("Current cards in hand:\n");
    asserttrue(state.handCount[currP], testState.handCount[currP] + drawnCards - discarded);
	printf("Current cards in deck:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP] - drawnCards);
	
	printf("Num Actions after play:\n"); 
	asserttrue(state.numActions, testState.numActions + numActionIncrease);
	
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
    

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("Test 3: +1 card to hand, +2 actions in state when deck is lowest possible int\n\n");
	
    // initialize game with hand and deck amounts reset from any previous tests
	initializeGame(numPlayer, k, seed, &state); 
    memcpy(&testState, &state, sizeof(struct gameState)); 
    
	state.deckCount[currP] = -2147483648;
	testState.deckCount[currP] = -2147483648;
	
    // preconditions
	printf("Cards in hand to begin:\n");
	asserttrue(state.handCount[currP], testState.handCount[currP]);
	printf("Cards in deck to begin:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP]);
	
	printf("Num Actions before play:\n");
	asserttrue(state.numActions, testState.numActions);
	
	printf("Cards in opponent's hand to begin:\n");
	asserttrue(state.handCount[otherP], testState.handCount[otherP]);
	printf("Cards in opponent's deck to begin:\n");
	asserttrue(state.deckCount[otherP], testState.deckCount[otherP]);	

    cardEffect(village, 0, 0, 0, &state, handpos, 0);
    // printf("Ran playVillage\n\n");

    // post test	
    printf("Current cards in hand:\n");
    asserttrue(state.handCount[currP], testState.handCount[currP] + drawnCards - discarded);
	printf("Current cards in deck:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP] - drawnCards);
	
	printf("Num Actions after play:\n"); 
	asserttrue(state.numActions, testState.numActions + numActionIncrease);
	
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