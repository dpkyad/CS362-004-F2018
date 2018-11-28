#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int k[28]= {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost,salvager, sea_hag, treasure_map, 28};
	int costs[28] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4, -1};
	
    struct gameState G;
	int pass = 0;
	
	// initialize a game state and player cards
	initializeGame(numPlayer, cards, seed, &G);
	
	//testing only the cards that are played in the playdom.c
	printf("----------------- Testing Function: getCost() ----------------\n");
	
	printf("TEST 1: Cards value equal function return value\n");
	for(i=0; i<27; i++)
	{
		if(costs[i] == getCost(k[i]))
		{
			pass++;
			printf ("PASS: expected %d, got  %d\n", costs[i], getCost(k[i]));
		}
		else
		{
			printf ("FAIL: expected %d, got  %d\n", costs[i], getCost(k[i]));
			//break;
		}
	}
	
	printf("\nTEST 2: Unknown card returns -1\n");
	if(costs[27] == getCost(k[27]))
	{
		pass++;
		printf ("PASS: expected %d, got  %d\n", costs[27], getCost(k[27]));
	}
	else
	{
		printf ("FAIL: expected %d, got  %d\n", costs[27], getCost(k[27]));
		//break;
	}
	
	if(pass == 28)
	{
		printf("\n >>>>> SUCCESS: Testing complete getCost() <<<<<\n\n");
	}
	else
	{
		printf("\n >>>>> FAILURE: Testing complete getCost() <<<<<\n\n");
	}
	
    return 0;
}