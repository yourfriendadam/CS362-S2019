#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "adventurer"

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
    
    int i;
    int discarded = 1;
    int handpos = 0;    
	int treasureAdded = 2; //used for verification with testState
	int deckCardsRemoved = 2; //used for verification with testState, begins at 2 for 2 drawntreasure

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("Test 1: test function with choice 1 positive value instead of 0\n\n");
	
    // initialize game with hand and deck amounts reset from any previous tests
	initializeGame(numPlayer, k, seed, &state); 
	
	state.deckCount[currP] = 10;
	
	// set deck order to control draws
	printf("Deck order:\n");
	for(i = 0; i < 10; i++) {
		if(i > 4) {
			// top half of deck, first cards drawn
			state.deck[currP][i] = estate;
			printf("Card %d		estate\n", i);
			deckCardsRemoved++;
		}
		else {
			// bottom half of deck, last cards drawn
			state.deck[currP][i] = copper;			
			printf("Card %d		copper\n", i);
		}
	}

    memcpy(&testState, &state, sizeof(struct gameState)); 
    
    // preconditions
	printf("\nNumber of cards in hand to begin:\n");
	asserttrue(state.handCount[currP], testState.handCount[currP]);
	printf("Cards in deck to begin:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP]);
	printf("Cards in hand:\n");
    
    // set handpos 0 to adventurer card
    state.hand[currP][0] = 7;
    
    // print values of cards in hand prior to playing the card
    for(i = 0; i < state.handCount[currP]; i++) {
    	printf("Enum value of card: %d", state.hand[currP][i]);
    	if(state.hand[currP][i] == 4) {
    		printf("	Copper\n");
    	}
    	else {
    		printf("\n");
    	}
    }
	
    cardEffect(adventurer, 1, 0, 0, &state, handpos, 0);
    printf("\nRan playAdventurer\n\n");

    // post test	
    printf("Current cards in hand:\n");
    asserttrue(state.handCount[currP], testState.handCount[currP] + treasureAdded - discarded);
	printf("Current cards in deck:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP] - deckCardsRemoved);

	// print values of cards in hand after playing the card
	printf("Cards in hand:\n");
    for(i = 0; i < state.handCount[currP]; i++) {
    	printf("Enum value of card: %d", state.hand[currP][i]);
    	if(state.hand[currP][i] == 4) {
    		printf("	Copper\n");
    	}
    	else {
    		printf("\n");
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
	printf("Test 2: test function with choice 1 negative value instead of 0\n\n");
 
    // initialize game with hand and deck amounts reset from any previous tests
	initializeGame(numPlayer, k, seed, &state); 
	
	state.deckCount[currP] = 10;

	// set deck order to control draws	
	printf("Deck order:\n");
	for(i = 0; i < 10; i++) {
		if(i > 4) {
			// top half of deck, first cards drawn
			state.deck[currP][i] = estate;
			printf("Card %d		estate\n", i);
			deckCardsRemoved++;
		}
		else {
			// bottom half of deck, last cards drawn
			state.deck[currP][i] = copper;			
			printf("Card %d		copper\n", i);
		}
	}

    memcpy(&testState, &state, sizeof(struct gameState)); 
    
    // preconditions
	printf("\nNumber of cards in hand to begin:\n");
	asserttrue(state.handCount[currP], testState.handCount[currP]);
	printf("Cards in deck to begin:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP]);
	printf("Cards in hand:\n");
    
    // set handpos 0 to adventurer card
    state.hand[currP][0] = 7;
    
    // print values of cards in hand prior to playing the card
    for(i = 0; i < state.handCount[currP]; i++) {
    	printf("Enum value of card: %d", state.hand[currP][i]);
    	if(state.hand[currP][i] == 4) {
    		printf("	Copper\n");
    	}
    	else {
    		printf("\n");
    	}
    }
	
    cardEffect(adventurer, -1, 0, 0, &state, handpos, 0);
    printf("\nRan playAdventurer\n\n");

    // post test	
    printf("Current cards in hand:\n");
    asserttrue(state.handCount[currP], testState.handCount[currP] + treasureAdded - discarded);
	printf("Current cards in deck:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP] - deckCardsRemoved);

	// print values of cards in hand after playing the card
	printf("Cards in hand:\n");
    for(i = 0; i < state.handCount[currP]; i++) {
    	printf("Enum value of card: %d", state.hand[currP][i]);
    	if(state.hand[currP][i] == 4) {
    		printf("	Copper\n");
    	}
    	else {
    		printf("\n");
    	}
    }	

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("Test 3: test function with choice 1 max int\n\n");
 
    // initialize game with hand and deck amounts reset from any previous tests
	initializeGame(numPlayer, k, seed, &state); 
	
	state.deckCount[currP] = 10;

	// set deck order to control draws	
	printf("Deck order:\n");
	for(i = 0; i < 10; i++) {
		if(i > 4) {
			// top half of deck, first cards drawn
			state.deck[currP][i] = estate;
			printf("Card %d		estate\n", i);
			deckCardsRemoved++;
		}
		else {
			// bottom half of deck, last cards drawn
			state.deck[currP][i] = copper;			
			printf("Card %d		copper\n", i);
		}
	}

    memcpy(&testState, &state, sizeof(struct gameState)); 

    
    // preconditions
	printf("\nNumber of cards in hand to begin:\n");
	asserttrue(state.handCount[currP], testState.handCount[currP]);
	printf("Cards in deck to begin:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP]);
	printf("Cards in hand:\n");
    
    // set handpos 0 to adventurer card
    state.hand[currP][0] = 7;
    
    // print values of cards in hand prior to playing the card
    for(i = 0; i < state.handCount[currP]; i++) {
    	printf("Enum value of card: %d", state.hand[currP][i]);
    	if(state.hand[currP][i] == 4) {
    		printf("	Copper\n");
    	}
    	else {
    		printf("\n");
    	}
    }
	
    cardEffect(adventurer, 2147483647, 0, 0, &state, handpos, 0);
    printf("\nRan playAdventurer\n\n");

    // post test	
    printf("Current cards in hand:\n");
    asserttrue(state.handCount[currP], testState.handCount[currP] + treasureAdded - discarded);
	printf("Current cards in deck:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP] - deckCardsRemoved);

	// print values of cards in hand after playing the card
	printf("Cards in hand:\n");
    for(i = 0; i < state.handCount[currP]; i++) {
    	printf("Enum value of card: %d", state.hand[currP][i]);
    	if(state.hand[currP][i] == 4) {
    		printf("	Copper\n");
    	}
    	else {
    		printf("\n");
    	}
    }	
    
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("Test 4: test function with choice 1 smallest possible int\n\n");
	
     // initialize game with hand and deck amounts reset from any previous tests
	initializeGame(numPlayer, k, seed, &state); 
	
	state.deckCount[currP] = 10;

	// set deck order to control draws	
	printf("Deck order:\n");
	for(i = 0; i < 10; i++) {
		if(i > 4) {
			// top half of deck, first cards drawn
			state.deck[currP][i] = estate;
			printf("Card %d		estate\n", i);
			deckCardsRemoved++;
		}
		else {
			// bottom half of deck, last cards drawn
			state.deck[currP][i] = copper;			
			printf("Card %d		copper\n", i);
		}
	}

    memcpy(&testState, &state, sizeof(struct gameState)); 
    
    // preconditions
	printf("\nNumber of cards in hand to begin:\n");
	asserttrue(state.handCount[currP], testState.handCount[currP]);
	printf("Cards in deck to begin:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP]);
	printf("Cards in hand:\n");
    
    // set handpos 0 to adventurer card
    state.hand[currP][0] = 7;
    
    // print values of cards in hand prior to playing the card
    for(i = 0; i < state.handCount[currP]; i++) {
    	printf("Enum value of card: %d", state.hand[currP][i]);
    	if(state.hand[currP][i] == 4) {
    		printf("	Copper\n");
    	}
    	else {
    		printf("\n");
    	}
    }
	
    cardEffect(adventurer, -2147483648, 0, 0, &state, handpos, 0);
    printf("\nRan playAdventurer\n\n");

    // post test	
    printf("Current cards in hand:\n");
    asserttrue(state.handCount[currP], testState.handCount[currP] + treasureAdded - discarded);
	printf("Current cards in deck:\n");
	asserttrue(state.deckCount[currP], testState.deckCount[currP] - deckCardsRemoved);

	// print values of cards in hand after playing the card
	printf("Cards in hand:\n");
    for(i = 0; i < state.handCount[currP]; i++) {
    	printf("Enum value of card: %d", state.hand[currP][i]);
    	if(state.hand[currP][i] == 4) {
    		printf("	Copper\n");
    	}
    	else {
    		printf("\n");
    	}
    }	
	return 0;
}