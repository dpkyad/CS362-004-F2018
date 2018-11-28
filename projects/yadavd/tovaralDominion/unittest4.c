#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 4;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    struct gameState G;
	int pass = 0;
	
	// initialize a game state and player cards
	initializeGame(numPlayer, k, seed, &G);
	
	//testing each player with a max of 4
	printf("----------------- Testing Function: whoseTurn() ----------------\n");
	
	printf("TEST 1: Correct number of players are returned\n");
	
	for(i=0; i<numPlayer; i++)
	{
		if(whoseTurn(&G) == i)
		{
			pass++;
			printf ("PASS: expected %d, got  %d\n", i, whoseTurn(&G));
		}
		else
		{
			printf ("FAIL: expected %d, got  %d\n", i, whoseTurn(&G));
			//break;
		}
		
		//increment whoseTurn to next player.
		G.whoseTurn = i+1;
	}
	
	if(pass == numPlayer)
	{
		printf("\n >>>>> SUCCESS: Testing complete whoseTurn() <<<<<\n\n");
	}
	else
	{
		printf("\n >>>>> FAILURE: Testing complete whoseTurn() <<<<<\n\n");
	}
	
    return 0;
}