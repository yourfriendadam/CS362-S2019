#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "council_room"

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
	printf("Test 1: +4 cards to hand, +1 buy in state, +1 card to other players' hand, -1 to their deck\n\n");
	
    // initialize game with hand and deck amounts reset from any previous tests
	initializeGame(numPlayer, k, seed, &state); 
    memcpy(&testState, &state, sizeof(struct gameState)); 
    
    // preconditions
	printf("Cards in hand to begin:\n");
	asserttrue(state.handCount[currP], testState.handCount[currP]);
	printf("Cards in deck to begin:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP]);
	
	printf("Num Buys before play:\n");
	asserttrue(state.numBuys, testState.numBuys);
	
	printf("Cards in opponent's hand to begin:\n");
	asserttrue(state.handCount[otherP], testState.handCount[otherP]);
	printf("Cards in opponent's deck to begin:\n");
	asserttrue(state.deckCount[otherP], testState.deckCount[otherP]);

	int drawnCards = 4;
	int numBuyIncrease = 1;
	int oppDrawnCards = 1;
    cardEffect(council_room, 0, 0, 0, &state, handpos, 0);
    // printf("Ran playCouncilRoom\n\n");

    // post test	
    printf("Current cards in hand:\n");
    asserttrue(state.handCount[currP], testState.handCount[currP] + drawnCards - discarded);
	printf("Current cards in deck:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP] - drawnCards);
	
	printf("Num Buys before play:\n");
	asserttrue(state.numBuys, testState.numBuys + numBuyIncrease);
	
    printf("Cards in opponent's hand:\n");
    asserttrue(state.handCount[otherP], testState.handCount[otherP] + oppDrawnCards);
	printf("Cards in opponent's deck:\n");
	asserttrue(state.deckCount[otherP], testState.deckCount[otherP] - oppDrawnCards);

    printf("Victory card supplies:\n");
    printf("Estates:\n");
    asserttrue(state.supplyCount[estate], testState.supplyCount[estate]);
    printf("Duchies:\n");
    asserttrue(state.supplyCount[duchy], testState.supplyCount[duchy]);
    printf("Provinces:\n");
    asserttrue(state.supplyCount[province], testState.supplyCount[province]);


	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("Test 2: try other valid player value\n\n");

	currP = 1;
	otherP = 0;
	
    // initialize game with hand and deck amounts reset from any previous tests
	initializeGame(numPlayer, k, seed, &state); 
    
    memcpy(&testState, &state, sizeof(struct gameState)); 
    
    // preconditions
	printf("Cards in hand to begin:\n");
	asserttrue(state.handCount[currP], testState.handCount[currP]);
	printf("Cards in deck to begin:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP]);
	
	printf("Num Buys before play:\n");
	asserttrue(state.numBuys, testState.numBuys);
	
	printf("Cards in opponent's hand to begin:\n");
	asserttrue(state.handCount[otherP], testState.handCount[otherP]);
	printf("Cards in opponent's deck to begin:\n");
	asserttrue(state.deckCount[otherP], testState.deckCount[otherP]);	

	drawnCards = 4;
	numBuyIncrease = 1;
	oppDrawnCards = 1;
    cardEffect(council_room, 0, 0, 0, &state, handpos, 0);
    // printf("Ran playCouncilRoom\n\n");

    // post test	
    printf("Current cards in hand:\n");
    asserttrue(state.handCount[currP], testState.handCount[currP] + drawnCards - discarded);
	printf("Current cards in deck:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP] - drawnCards);
	
	printf("Num Buys before play:\n");
	asserttrue(state.numBuys, testState.numBuys + numBuyIncrease);
	
    printf("Cards in opponent's hand:\n");
    asserttrue(state.handCount[otherP], testState.handCount[otherP] + oppDrawnCards);
	printf("Cards in opponent's deck:\n");
	asserttrue(state.deckCount[otherP], testState.deckCount[otherP] - oppDrawnCards);
	
    printf("Victory card supplies:\n");
    printf("Estates:\n");
    asserttrue(state.supplyCount[estate], testState.supplyCount[estate]);
    printf("Duchies:\n");
    asserttrue(state.supplyCount[duchy], testState.supplyCount[duchy]);
    printf("Provinces:\n");
    asserttrue(state.supplyCount[province], testState.supplyCount[province]);

	
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("Test 3: set currentPlayer to one beyond valid (== numPlayers)\n\n");
	
	currP = 2;
	otherP = 0;
	
    // initialize game with hand and deck amounts reset from any previous tests
	initializeGame(numPlayer, k, seed, &state); 
    memcpy(&testState, &state, sizeof(struct gameState)); 
    
    // preconditions
	printf("Cards in hand to begin:\n");
	asserttrue(state.handCount[currP], testState.handCount[currP]);
	printf("Cards in deck to begin:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP]);
	
	printf("Num Buys before play:\n");
	asserttrue(state.numBuys, testState.numBuys);
	
	printf("Cards in opponent's hand to begin:\n");
	asserttrue(state.handCount[otherP], testState.handCount[otherP]);
	printf("Cards in opponent's deck to begin:\n");
	asserttrue(state.deckCount[otherP], testState.deckCount[otherP]);	

	drawnCards = 4;
	numBuyIncrease = 1;
	oppDrawnCards = 1;
    cardEffect(council_room, 0, 0, 0, &state, handpos, 0);
    // printf("Ran playCouncilRoom\n\n");

    // post test	
    printf("Current cards in hand:\n");
    asserttrue(state.handCount[currP], testState.handCount[currP] + drawnCards - discarded);
	printf("Current cards in deck:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP] - drawnCards);
	
	printf("Num Buys before play:\n");
	asserttrue(state.numBuys, testState.numBuys + numBuyIncrease);
	
    printf("Cards in opponent's hand:\n");
    asserttrue(state.handCount[otherP], testState.handCount[otherP] + oppDrawnCards);
	printf("Cards in opponent's deck:\n");
	asserttrue(state.deckCount[otherP], testState.deckCount[otherP] - oppDrawnCards);
	
    printf("Victory card supplies:\n");
    printf("Estates:\n");
    asserttrue(state.supplyCount[estate], testState.supplyCount[estate]);
    printf("Duchies:\n");
    asserttrue(state.supplyCount[duchy], testState.supplyCount[duchy]);
    printf("Provinces:\n");
    asserttrue(state.supplyCount[province], testState.supplyCount[province]);
		
	
	// printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	// printf("Test 4: set currentPlayer to max int\n\n");
	
	// currP = 2147483647;
	// otherP = 0;
	
 //   // initialize game with hand and deck amounts reset from any previous tests
	// initializeGame(numPlayer, k, seed, &state); 
 //   memcpy(&testState, &state, sizeof(struct gameState)); 
    
 //   // preconditions
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

	// drawnCards = 4;
	// numBuyIncrease = 1;
	// oppDrawnCards = 1;
 //   playCouncilRoom(currP, &state, handpos); 
 //   printf("Ran playCouncilRoom\n\n");

 //   // post test	
 //   printf("Current cards in hand:\n");
 //   asserttrue(state.handCount[currP], testState.handCount[currP] + drawnCards - discarded);
	// printf("Current cards in deck:\n");
	// asserttrue(state.deckCount[currP], testState.deckCount[currP] - drawnCards);
	
	// printf("Num Buys before play:\n");
	// asserttrue(state.numBuys, testState.numBuys + numBuyIncrease);
	
 //   printf("Cards in opponent's hand:\n");
 //   asserttrue(state.handCount[otherP], testState.handCount[otherP] + oppDrawnCards);
	// printf("Cards in opponent's deck:\n");
	// asserttrue(state.deckCount[otherP], testState.deckCount[otherP] - oppDrawnCards);
	
 //   printf("Victory card supplies:\n");
 //   printf("Estates:\n");
 //   asserttrue(state.supplyCount[estate], testState.supplyCount[estate]);
 //   printf("Duchies:\n");
 //   asserttrue(state.supplyCount[duchy], testState.supplyCount[duchy]);
 //   printf("Provinces:\n");
 //   asserttrue(state.supplyCount[province], testState.supplyCount[province]);

	return 0;
}