#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "sea_hag"

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
               , remodel, smithy, village, cutpurse, sea_hag};
    struct gameState state, testState;
    
    int i;
    int discarded = 1;
    int handpos = 0;    

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("Test 1: discard top card from opponent's deck, replace with a curse, discard sea hag\n\n");
	
    // initialize game with hand and deck amounts reset from any previous tests
	initializeGame(numPlayer, k, seed, &state); 
	
	state.deckCount[otherP] = 10;
    printf("Opponent's deck size: %d\n", state.deckCount[otherP]);
    
    //set opposing player's deck order so card on top of deck is controlled 
	printf("Opponent's deck order:\n");
	for(i = 0; i < state.deckCount[otherP]; i++) {
		if(i == state.deckCount[otherP] - 1) {
			// card on top of deck
			state.deck[otherP][i] = baron;
			printf("Card %d		baron, enum 15\n", i);
		}
		else {
			// rest of deck
			state.deck[otherP][i] = copper;			
			printf("Card %d		copper\n", i);
		}
	}
	
    memcpy(&testState, &state, sizeof(struct gameState)); 
    

    // preconditions
	printf("\nCards in player's hand to begin:\n");
	asserttrue(state.handCount[currP], testState.handCount[currP]);
	printf("Cards in player's deck to begin:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP]);
	
    cardEffect(sea_hag, 0, 0, 0, &state, handpos, 0);
    printf("Ran sea hag\n\n");

    // post test	
    printf("Current cards in hand:\n");
    asserttrue(state.handCount[currP], testState.handCount[currP] - discarded);
	printf("Current cards in deck:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP]);


    printf("Opponent's deck size: %d\n", state.deckCount[otherP]);
	printf("Opponent's deck order:\n");
	for(i = 0; i < state.deckCount[otherP]; i++) {
		if(state.deck[otherP][i] == 0) {
			printf("Card %d		Curse, enum 0\n", i);
		}
		else if(state.deck[otherP][i] == 15) {;			
			printf("Card %d		baron\n", i);		    
		}
		else if(state.deck[otherP][i] == 4) {;			
			printf("Card %d		copper\n", i);		    
		}
		else {
			printf("Card %d		other\n", i);
		}
	}
	
    printf("\nVictory card supplies:\n");
    printf("Estates:\n");
    asserttrue(state.supplyCount[estate], testState.supplyCount[estate]);
    printf("Duchies:\n");
    asserttrue(state.supplyCount[duchy], testState.supplyCount[duchy]);
    printf("Provinces:\n");
    asserttrue(state.supplyCount[province], testState.supplyCount[province]);
    

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("Test 2: test sea hag with max opponent's deck size\n\n");
	
    // initialize game with hand and deck amounts reset from any previous tests
	initializeGame(numPlayer, k, seed, &state); 
	
	state.deckCount[otherP] = MAX_DECK;

    printf("Opponent's deck size: %d\n", state.deckCount[otherP]);
    //set opposing player's deck order so card on top of deck is controlled 	
	printf("Opponent's deck order:\n");
	for(i = 0; i < state.deckCount[otherP]; i++) {
		if(i == state.deckCount[otherP] - 2) {
			// card on top of deck
			state.deck[otherP][i] = baron;
			printf("Card %d		baron, enum 15\n", i);
		}
		else {
			// rest of deck
			state.deck[otherP][i] = copper;			
		}
	}
	printf("Cards 0 through %d are all coppers.\n", state.deckCount[otherP]-1);
	
    memcpy(&testState, &state, sizeof(struct gameState)); 
    
    // preconditions
	printf("\nCards in player's hand to begin:\n");
	asserttrue(state.handCount[currP], testState.handCount[currP]);
	printf("Cards in player's deck to begin:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP]);
	
    cardEffect(sea_hag, 0, 0, 0, &state, handpos, 0);
    printf("Ran sea hag\n\n");

    // post test	
    printf("Current cards in hand:\n");
    asserttrue(state.handCount[currP], testState.handCount[currP] - discarded);
	printf("Current cards in deck:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP]);


    printf("Opponent's deck size: %d\n", state.deckCount[otherP]);
	printf("Opponent's deck order (excluding 400+ coppers):\n");
	for(i = 0; i < state.deckCount[otherP]; i++) {
		if(state.deck[otherP][i] == 0) {
			printf("Card %d		Curse, enum 0\n", i);
		}
		else if(state.deck[otherP][i] == 15) {;			
			printf("Card %d		baron\n", i);		    
		}
		else if(state.deck[otherP][i] != 4) {
			printf("Card %d		other\n", i);
		}
	}


	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("Test 3: opponent's deck size 0\n\n");
	
    // initialize game with hand and deck amounts reset from any previous tests
	initializeGame(numPlayer, k, seed, &state); 
	
	state.deckCount[otherP] = 0;
    printf("Opponent's deck size: %d\n", state.deckCount[otherP]);
    
    //set opposing player's deck order so card on top of deck is controlled 	
	printf("Opponent's deck order:\n");
	for(i = 0; i < state.deckCount[otherP]; i++) {
		if(i == state.deckCount[otherP] - 1) {
			// card on top of deck
			state.deck[otherP][i] = baron;
			printf("Card %d		baron, enum 15\n", i);
		}
		else {
			// rest of deck
			state.deck[otherP][i] = copper;			
			printf("Card %d		copper\n", i);
		}
	}
	
    memcpy(&testState, &state, sizeof(struct gameState)); 
    
    // preconditions
	printf("\nCards in player's hand to begin:\n");
	asserttrue(state.handCount[currP], testState.handCount[currP]);
	printf("Cards in player's deck to begin:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP]);
	
    cardEffect(sea_hag, 0, 0, 0, &state, handpos, 0);
    printf("Ran sea hag\n\n");

    // post test	
    printf("Current cards in hand:\n");
    asserttrue(state.handCount[currP], testState.handCount[currP] - discarded);
	printf("Current cards in deck:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP]);


    printf("Opponent's deck size: %d\n", state.deckCount[otherP]);
	printf("Opponent's deck order:\n");
	for(i = 0; i < state.deckCount[otherP]; i++) {
		if(state.deck[otherP][i] == 0) {
			printf("Card %d		Curse, enum 0\n", i);
		}
		else if(state.deck[otherP][i] == 15) {;			
			printf("Card %d		baron\n", i);		    
		}
		else if(state.deck[otherP][i] == 4) {;			
			printf("Card %d		copper\n", i);		    
		}
		else {
			printf("Card %d		other\n", i);
		}
	}

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("Test 4: opponent's deck size -1\n\n");
	
    // initialize game with hand and deck amounts reset from any previous tests
	initializeGame(numPlayer, k, seed, &state); 
	
	state.deckCount[otherP] = -1;
    printf("Opponent's deck size: %d\n", state.deckCount[otherP]);
    
    //set opposing player's deck order so card on top of deck is controlled 	
	printf("Opponent's deck order:\n");
	for(i = 0; i < state.deckCount[otherP]; i++) {
		if(i == state.deckCount[otherP] - 1) {
			// card on top of deck
			state.deck[otherP][i] = baron;
			printf("Card %d		baron, enum 15\n", i);
		}
		else {
			// rest of deck
			state.deck[otherP][i] = copper;			
			printf("Card %d		copper\n", i);
		}
	}
	
    memcpy(&testState, &state, sizeof(struct gameState)); 
    
    // preconditions
	printf("\nCards in player's hand to begin:\n");
	asserttrue(state.handCount[currP], testState.handCount[currP]);
	printf("Cards in player's deck to begin:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP]);
	
    cardEffect(sea_hag, 0, 0, 0, &state, handpos, 0);
    printf("Ran sea hag\n\n");

    // post test	
    printf("Current cards in hand:\n");
    asserttrue(state.handCount[currP], testState.handCount[currP] - discarded);
	printf("Current cards in deck:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP]);


    printf("Opponent's deck size: %d\n", state.deckCount[otherP]);
	printf("Opponent's deck order:\n");
	for(i = 0; i < state.deckCount[otherP]; i++) {
		if(state.deck[otherP][i] == 0) {
			printf("Card %d		Curse, enum 0\n", i);
		}
		else if(state.deck[otherP][i] == 15) {;			
			printf("Card %d		baron\n", i);		    
		}
		else if(state.deck[otherP][i] == 4) {;			
			printf("Card %d		copper\n", i);		    
		}
		else {
			printf("Card %d		other\n", i);
		}
	}
	
	return 0;
}