#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

//bug gets 2 cards rather than 3, that's why hand after discard is one less than expected

int main() {

    //int i, j, m;
    int i;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int handSize = 0;
	int currCard = 0;
	int cardsFound = 0;
	//int handpos = 0;
	int pass = 0;
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	
	//set player 2 to empty
	G.handCount[thisPlayer+1] = 0;

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: Draw 3 cards --------------
	printf("\nTEST 1: Draw 3 cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	//set current hand
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-1] = smithy;
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-2] = embargo;
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-3] = village;
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-4] = minion;
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-5] = cutpurse;
	
	handSize = testG.handCount[thisPlayer];
	cardsFound = 0;
	
	//set deck
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-1] = copper;
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-2] = mine;
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-3] = sea_hag;
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-4] = tribute;
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-5] = silver;
	
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
	//cardSmithy(thisPlayer, &testG, handpos);
	
	for(i =0; i<testG.handCount[thisPlayer]; i++)
	{
		//printf("%d\n", testG.hand[thisPlayer][testG.handCount[thisPlayer]-(i+1)]);
		
		currCard = testG.hand[thisPlayer][testG.handCount[thisPlayer]-(i+1)];
		
		if (currCard == copper || currCard == mine || currCard == sea_hag)
		{
			cardsFound++;
		}
	}
	//discardCard(0, thisPlayer, &testG, 0);
	//draw three cards and discard smithy since it was used
	if(cardsFound == 3 && testG.handCount[thisPlayer] ==  handSize+2 && testG.handCount[thisPlayer+1] == 0)
	{
		printf ("PASS: ");
		pass++;
	}
	else
	{
		printf ("FAIL: ");
	}
	
	printf ("cards expected %d, got  %d\n", 3, cardsFound);
	printf ("      handCount expected %d, got  %d\n", handSize+2, testG.handCount[thisPlayer]);

	if(pass == 1)
	{
		printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
	}
	else
	{
		printf("\n >>>>> FAILURE: Testing complete %s <<<<<\n\n", TESTCARD);
	}


	return 0;
}


