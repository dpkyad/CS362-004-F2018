#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "smithy"

int cardSmithy(int currentPlayer, struct gameState *state, int handPos);

//bug gets 2 cards rather than 3, that's why hand after discard is one less than expected
//also discard function in Cardsmithy discards top card in hand which is not smithy card but the card that was drawn.

int main() {

    int i, j, m;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int handpos = 0;
	int totalTests = 10000;
	int fail = 0;
	
	// random seed
	srand(time(NULL));
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	
	//set player 2 to empty
	G.handCount[thisPlayer+1] = 0;
	
	//randomize hand and deck size
	int deckSize = rand() % (50 + 1);		
	//int deckSize = 5;		
	int handSize = rand() % (50 + 1);
	//int handSize = 5;

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	for(m = 0; m<totalTests; m++)
	{
		//printf("\nRUNNING TEST %d/%d\n", m+1, totalTests);
		
		int currCard = 0;
		int cardsFound = 0;
		int randomCard = 0;
		int topCards [3];

		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		
		testG.deckCount[thisPlayer] = deckSize;
		testG.handCount[thisPlayer] = handSize;
		
		//set hand with random cards
		for(i = 0; i<testG.handCount[thisPlayer]; i++)
		{
			if(i == 0)
			{
				//set first card to smithy
				testG.hand[thisPlayer][testG.handCount[thisPlayer]-(i+1)] = smithy;
			}
			else
			{
				//choose random card from possible cards
				randomCard = rand() % (26 + 1);
			
				//set current hand
				testG.hand[thisPlayer][testG.handCount[thisPlayer]-(i+1)] = randomCard;
			}
			
			//printf("H: %d\n", testG.hand[thisPlayer][testG.handCount[thisPlayer]-(i+1)]);
		}
		
		//set deck with random cards
		for(j = 0; j<testG.deckCount[thisPlayer]; j++)
		{
			//choose random card from possible cards
			randomCard = rand() % (26 + 1);
			
			//set deck
			testG.deck[thisPlayer][testG.deckCount[thisPlayer]-(j+1)] = randomCard;
			
			//get the top 3 cards from deck, those will be put in hand
			if(j < 3)
			{
				topCards[j] = randomCard;
			}
			
			//printf("D: %d\n", randomCard);
		}
		
		//call function
		cardSmithy(thisPlayer, &testG, handpos);
		
		//check how many cards are in hand after running function
		for(i =0; i<testG.handCount[thisPlayer]; i++)
		{
			//printf("%d\n", testG.hand[thisPlayer][testG.handCount[thisPlayer]-(i+1)]);
			
			currCard = testG.hand[thisPlayer][testG.handCount[thisPlayer]-(i+1)];
			
			if(i<3 && currCard == topCards[i])
				cardsFound++;
			
			//printf("H: %d\n", currCard);
		}

		if(cardsFound != 3 || testG.handCount[thisPlayer] !=  handSize+3)
			fail++;
		//else
		//	printf("PASS\n");
		/*
		//
		if(cardsFound != 3)
		{
			printf ("FAIL: cards expected 3, got  %d\n", cardsFound);
		}

		//if the handsize didn't increase by the number of cards found
		if(testG.handCount[thisPlayer] !=  handSize+3)
		{
			printf ("FAIL: handCount expected %d, got  %d\n", (handSize + 3), testG.handCount[thisPlayer]);
		}
		
		//
		if(testG.discard[thisPlayer][testG.discardCount[thisPlayer]-1] != smithy)
		{
			printf ("FAIL: smithy not found in discard pile");
		}*/

	}
	
	if(fail > 0)
	{
		printf ("\n----------------- FAIL: %d tests failed out of %d ----------------\n",fail, totalTests);
	}
	else
	{
		printf ("\n----------------- PASS: All tests passed ----------------\n");
	}
	
	return 0;
}


