#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "cutpurse"

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

    int handpos = 0;    
	int coinIncrease = 2;
	int discardedCopper = 1;
	int i;
	int coppers[5];
	int estates[5];

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("Test 1: current player +2 coins, other player discards a copper\n\n");
	
    // initialize game with hand and deck amounts reset from any previous tests
	initializeGame(numPlayer, k, seed, &state); 

	//set up other players hand to have 5 cards, all coppers
	for(i=0; i < 5; i++) {
		drawCard(otherP, &state);
		estates[i] = estate;
	}
	
	// set other players hand to 4 estates and 1 copper
	memcpy(state.hand[otherP], estates, sizeof(int) * 5);
	state.hand[otherP][2] = copper;
	
    memcpy(&testState, &state, sizeof(struct gameState)); 
    
    // preconditions
	printf("Coins to begin:\n");
	asserttrue(state.coins, testState.coins);
	
	printf("Cards in opponent's hand to begin:\n");
	asserttrue(state.handCount[otherP], testState.handCount[otherP]);
	
	// print out cards from hand - note the coppers
    for(i = 0; i < state.handCount[otherP]; i++) {
    	printf("Enum value of card: %d", state.hand[otherP][i]);
    	if(state.hand[otherP][i] == 4) {
    		printf("	Copper\n");
    	}
    	else {
    		printf("\n");
    	}
    }
    
	printf("\nRunning playCouncilRoom\n\n");	
    playCutpurse(currP, &state, handpos); 

    // post test	
    printf("Coins after cutpurse:\n");
    asserttrue(state.coins, testState.coins + coinIncrease);

	printf("Cards in opponent's hand:\n");
	asserttrue(state.handCount[otherP], testState.handCount[otherP] - discardedCopper);
	
    printf("Victory card supplies:\n");
    printf("Estates:\n");
    asserttrue(state.supplyCount[estate], testState.supplyCount[estate]);
    printf("Duchies:\n");
    asserttrue(state.supplyCount[duchy], testState.supplyCount[duchy]);
    printf("Provinces:\n");
    asserttrue(state.supplyCount[province], testState.supplyCount[province]);

	
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("Test 2: other player has full hand of coppers, discards only one copper\n\n");
	
    // initialize game with hand and deck amounts reset from any previous tests
	initializeGame(numPlayer, k, seed, &state); 

	//set up other players hand to have 5 cards, all coppers
	for(i=0; i < 5; i++) {
		drawCard(otherP, &state);
		coppers[i] = copper;
	}
	
	// set other players hand to 5 coppers
	memcpy(state.hand[otherP], coppers, sizeof(int) * 5);
	
    memcpy(&testState, &state, sizeof(struct gameState)); 
    
    // preconditions
	printf("Cards in opponent's hand to begin:\n");
	asserttrue(state.handCount[otherP], testState.handCount[otherP]);
	
	// print out cards from hand - note the coppers
    for(i = 0; i < state.handCount[otherP]; i++) {
    	printf("Enum value of card: %d", state.hand[otherP][i]);
    	if(state.hand[otherP][i] == 4) {
    		printf("	Copper\n");
    	}
    	else {
    		printf("\n");
    	}
    }
    
	printf("\nRunning playCouncilRoom\n\n");	
    playCutpurse(currP, &state, handpos); 

    // post test	
 	printf("Cards in opponent's hand:\n");
 	asserttrue(state.handCount[otherP], testState.handCount[otherP] - discardedCopper);


	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("Test 3: other player has no coppers, only shows hand- no discarded copper\n\n");
	
    // initialize game with hand and deck amounts reset from any previous tests
	initializeGame(numPlayer, k, seed, &state); 

	//set up other players hand to have 5 cards, no coppers
	for(i=0; i < 5; i++) {
		drawCard(otherP, &state);
		estates[i] = estate;
	}
	
	// set other players hand to 5 estates, no coppers
	memcpy(state.hand[otherP], estates, sizeof(int) * 5);
	
    memcpy(&testState, &state, sizeof(struct gameState)); 
    
    // preconditions
	printf("Cards in opponent's hand to begin:\n");
	asserttrue(state.handCount[otherP], testState.handCount[otherP]);
	
	// print out cards from hand - note the coppers
    for(i = 0; i < state.handCount[otherP]; i++) {
    	printf("Enum value of card: %d", state.hand[otherP][i]);
    	if(state.hand[otherP][i] == 4) {
    		printf("	Copper\n");
    	}
    	else {
    		printf("\n");
    	}
    }
    
	printf("\nRunning playCouncilRoom\n\n");	
	discardedCopper = 0;
    playCutpurse(currP, &state, handpos); 

    // post test	
	printf("Cards in opponent's hand:\n");
	asserttrue(state.handCount[otherP], testState.handCount[otherP]);
				
	return 0;
}