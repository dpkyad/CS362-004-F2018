#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "adventurer"

int cardAdventurer(int currentPlayer, int temphand [], int drawntreasure, int z, struct gameState *state);

//bug when no treasure cards are found, cards in hand are discarded rather than just the ones drawn.

int main() {

    //int i, j, m;
    int i, j, m;
    //int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int temphand[MAX_HAND];
	int drawntreasure=0;
	int z = 0;
	//int treasureFound = 0;
	//int currCard = 0;
	//int pass = 0;
	//int handTreasures = 0;
	//int deckTreasures = 0;
	//int randomCard = 0;
	//int totalTreasures = 0;
	int totalTests = 1000000;
	int fail = 0;
	
	// random seed
	srand(time(NULL));
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	
	//set player 2 to empty
	G.handCount[thisPlayer+1] = 0;
	
	//randomize hand and deck size
	int deckSize = rand() % (50 + 1);		
	//int deckSize = 20;		
	int handSize = rand() % (50 + 1);
	//int handSize = 20;

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	for(m = 0; m<totalTests; m++)
	{
		//printf("\nRUNNING TEST %d/%d\n", m+1, totalTests);
		
		int currCard = 0;
		int treasureFound = 0;
		int handTreasures = 0;
		int deckTreasures = 0;
		int randomCard = 0;
		int totalTreasures = 0;
		int treasure = 0;
		int treasureInDiscard = 0;

		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		
		testG.deckCount[thisPlayer] = deckSize;
		testG.handCount[thisPlayer] = handSize;
		
		//set hand with random cards
		for(i = 0; i<testG.handCount[thisPlayer]; i++)
		{
			//choose random card from possible cards
			randomCard = rand() % (26 + 1);
			
			//set current hand
			testG.hand[thisPlayer][testG.handCount[thisPlayer]-(i+1)] = randomCard;

			//count how many current treasures exist in hand
			if(randomCard == copper || randomCard == silver || randomCard == gold)
				handTreasures++;
			
			//printf("H: %d\n", randomCard);
		}
		
		//handSize = testG.handCount[thisPlayer];
		treasureFound = 0;
		
		//set deck with random cards
		for(j = 0; j<testG.deckCount[thisPlayer]; j++)
		{
			//choose random card from possible cards
			randomCard = rand() % (26 + 1);
			
			//set deck
			testG.deck[thisPlayer][testG.deckCount[thisPlayer]-(j+1)] = randomCard;
			
			if((randomCard == copper || randomCard == silver || randomCard == gold) && deckTreasures < 2)
				deckTreasures++;
			
			//printf("D: %d\n", randomCard);
		}
		
		//call function
		//cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
		cardAdventurer(thisPlayer, temphand, drawntreasure, z, &testG);
		
		//check how many treasures are in hand after running function
		for(i =0; i<testG.handCount[thisPlayer]; i++)
		{
			//printf("%d\n", testG.hand[thisPlayer][testG.handCount[thisPlayer]-(i+1)]);
			
			currCard = testG.hand[thisPlayer][testG.handCount[thisPlayer]-(i+1)];
			
			if (currCard == copper || currCard == silver || currCard == gold)
			{
				treasureFound++;
			}
			
			//printf("H: %d\n", currCard);
		}
		
		totalTreasures = handTreasures + deckTreasures;
		
		//printf ("treasure expected %d, got  %d\n", totalTreasures, treasureFound);
		//printf ("handCount expected %d, got  %d\n", (handSize + deckTreasures), testG.handCount[thisPlayer]);
		
		//check discard pile to make sure treasure cards aren't being discarded
		for(i =0; i<testG.discardCount[thisPlayer]; i++)
		{
			treasure = testG.discard[thisPlayer][testG.discardCount[thisPlayer]-(i+1)];
			
			if (treasure == copper || treasure == silver || treasure == gold)
				treasureInDiscard = 1;
		}
		
		if(treasureFound != totalTreasures || testG.handCount[thisPlayer] !=  handSize+deckTreasures || treasureInDiscard)
			fail++;
		//else
		//	printf("PASS\n");
		
		//if treasure found less than 0 or greater than 2
		//if(treasureFound < 0 || treasureFound > 2)
		/*if(treasureFound != totalTreasures)
		{
			printf ("FAIL: treasure expected %d, got  %d\n", totalTreasures, treasureFound);
		}

		//if the handsize didn't increase by the number of treasure cards found
		if(testG.handCount[thisPlayer] !=  handSize+deckTreasures)
		{
			printf ("FAIL: handCount expected %d, got  %d\n", (handSize + deckTreasures), testG.handCount[thisPlayer]);
		}
		
		if(treasureInDiscard)
		{
			printf ("FAIL: treasure found in discard pile");
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


