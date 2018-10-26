#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

//bug when no treasure cards are found, cards in hand are discarded rather than just the ones drawn.

int main() {

    //int i, j, m;
    int i;
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
	int treasureFound = 0;
	int currCard = 0;
	int handSize = 0;
	int pass = 0;
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	
	//set player 2 to empty
	G.handCount[thisPlayer+1] = 0;

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: Find 1 treasure card --------------
	printf("\nTEST 1: Find 1 treasure cards for player 1 only\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	//set current hand
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-1] = adventurer;
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-2] = embargo;
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-3] = village;
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-4] = minion;
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-5] = cutpurse;
	
	handSize = testG.handCount[thisPlayer];
	treasureFound = 0;
	
	//set deck
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-1] = copper;
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-2] = minion;
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-3] = minion;
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-4] = minion;
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-5] = minion;
	
	//cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	cardAdventurer(thisPlayer, temphand, drawntreasure, z, &testG);
	
	for(i =0; i<testG.handCount[thisPlayer]; i++)
	{
		//printf("%d\n", testG.hand[thisPlayer][testG.handCount[thisPlayer]-(i+1)]);
		
		currCard = testG.hand[thisPlayer][testG.handCount[thisPlayer]-(i+1)];
		
		if (currCard == copper || currCard == silver || currCard == gold)
		{
			treasureFound++;
		}
	}
	
	if(treasureFound == 1 && testG.handCount[thisPlayer] ==  handSize+1 && testG.handCount[thisPlayer+1] == 0)
	{
		printf ("PASS: ");
		pass++;
	}
	else
	{
		printf ("FAIL: ");
	}
	
	printf ("treasure expected %d, got  %d\n", 1, treasureFound);
	printf ("      handCount expected %d, got  %d\n", handSize+1, testG.handCount[thisPlayer]);
	
	
	
	// ----------- TEST2: Find 2 treasure cards --------------
	printf("\nTEST 2: Find 2 treasure cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	//set current hand
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-1] = adventurer;
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-2] = embargo;
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-3] = village;
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-4] = minion;
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-5] = cutpurse;
	
	handSize = testG.handCount[thisPlayer];
	treasureFound = 0;
	
	//set deck
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-1] = copper;
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-2] = silver;
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-3] = minion;
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-4] = minion;
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-5] = minion;
	
	//cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	cardAdventurer(thisPlayer, temphand, drawntreasure, z, &testG);
	
	for(i =0; i<testG.handCount[thisPlayer]; i++)
	{
		//printf("%d\n", testG.hand[thisPlayer][testG.handCount[thisPlayer]-(i+1)]);
		
		currCard = testG.hand[thisPlayer][testG.handCount[thisPlayer]-(i+1)];
		
		if (currCard == copper || currCard == silver || currCard == gold)
		{
			treasureFound++;
		}
	}
	
	if(treasureFound == 2 && testG.handCount[thisPlayer] ==  handSize+2 && testG.handCount[thisPlayer+1] == 0)
	{
		printf ("PASS: ");
		pass++;
	}
	else
	{
		printf ("FAIL: ");
	}
	
	printf ("treasure expected %d, got  %d\n", 2, treasureFound);
	printf ("      handCount expected %d, got  %d\n", handSize+2, testG.handCount[thisPlayer]);
	
	
	// ----------- TEST3: Find no more than 2 treasure cards --------------
	printf("\nTEST 3: Find no more than 2 treasure cards for player 1 only\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	//set current hand
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-1] = adventurer;
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-2] = embargo;
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-3] = village;
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-4] = minion;
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-5] = cutpurse;
	
	handSize = testG.handCount[thisPlayer];
	treasureFound = 0;
	
	//set deck
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-1] = copper;
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-2] = silver;
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-3] = gold;
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-4] = copper;
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-5] = gold;
	
	//cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	cardAdventurer(thisPlayer, temphand, drawntreasure, z, &testG);
	
	for(i =0; i<testG.handCount[thisPlayer]; i++)
	{
		//printf("%d\n", testG.hand[thisPlayer][testG.handCount[thisPlayer]-(i+1)]);
		
		currCard = testG.hand[thisPlayer][testG.handCount[thisPlayer]-(i+1)];
		
		if (currCard == copper || currCard == silver || currCard == gold)
		{
			treasureFound++;
		}
	}
	
	if(treasureFound == 2 && testG.handCount[thisPlayer] ==  handSize+2 && testG.handCount[thisPlayer+1] == 0)
	{
		printf ("PASS: ");
		pass++;
	}
	else
	{
		printf ("FAIL: ");
	}
	
	printf ("treasure expected %d, got  %d\n", 2, treasureFound);
	printf ("      handCount expected %d, got  %d\n", handSize+2, testG.handCount[thisPlayer]);
	
	// ----------- TEST4: Find 0 treasure cards --------------
	printf("\nTEST 4: Find 0 treasure cards for player 1 only\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	//set current hand
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-1] = adventurer;
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-2] = embargo;
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-3] = village;
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-4] = minion;
	testG.hand[thisPlayer][testG.handCount[thisPlayer]-5] = cutpurse;
	
	handSize = testG.handCount[thisPlayer];
	treasureFound = 0;
	
	//set deck
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-1] = sea_hag;
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-2] = tribute;
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-3] = smithy;
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-4] = council_room;
	testG.deck[thisPlayer][testG.deckCount[thisPlayer]-5] = minion;
	
	//cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	cardAdventurer(thisPlayer, temphand, drawntreasure, z, &testG);
	
	for(i =0; i<testG.handCount[thisPlayer]; i++)
	{
		//printf("%d\n", testG.hand[thisPlayer][testG.handCount[thisPlayer]-(i+1)]);
		
		currCard = testG.hand[thisPlayer][testG.handCount[thisPlayer]-(i+1)];
		
		if (currCard == copper || currCard == silver || currCard == gold)
		{
			treasureFound++;
		}
	}
	
	if(treasureFound == 0 && testG.handCount[thisPlayer] ==  handSize && testG.handCount[thisPlayer+1] == 0)
	{
		printf ("PASS: ");
		pass++;
	}
	else
	{
		printf ("FAIL: ");
	}
	
	printf ("treasure expected %d, got  %d\n", 0, treasureFound);
	printf ("      handCount expected %d, got  %d\n", handSize, testG.handCount[thisPlayer]);
	
	
	if(pass == 4)
	{
		printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
	}
	else
	{
		printf("\n >>>>> FAILURE: Testing complete %s <<<<<\n\n", TESTCARD);
	}



	return 0;
}


