#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    int i, j = 1;
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    struct gameState G, testG;
	int player = 0;
	int pass = 0;
	int currSupply = 0;
	// initialize a game state and player cards
	initializeGame(numPlayer, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));
	
	//testing only the cards that are played in the playdom.c
	printf("----------------- Testing Function: gainCard() ----------------\n");
	
	//printf("%d\n\n", supplyCount(0, &testG));
	testG.supplyCount[0] = 0;
	printf("TEST 1: SupplyCount call is -1 when supply is 0 for all players.\n");
	if (gainCard(0, &testG, j, player) == -1 && gainCard(0, &testG, j, player+1) == -1)
	{
		printf ("PASS: supplyCount expected %d, got  %d\n", -1, gainCard(0, &testG, j, player));
		pass++;
	}
	else
	{
		printf ("FAIL: supplyCount expected %d, got  %d\n", -1, gainCard(0, &testG, j, player));
	}
	
	for(j = 0; j<3; j++)
	{
		if(j == 0)
			printf("\nTEST 2: Cards are gained for player 1 in discard and supplyCount decreases by 1\n");
		else if(j ==1)
			printf("\nTEST 3: Cards are gained for player 1 deck and supplyCount decreases by 1\n");
		else
			printf("\nTEST 4: Cards are gained in hand for player 1 and supplyCount decreases by 1\n");
		
		for(i = 0; i<10; i++)
		{
			currSupply = supplyCount(k[i], &G);
			gainCard(k[i], &G, j, player);

			if (j == 1)
			{
				
			  //printf("%d\n", G.deck[ player ][ G.deckCount[player] ]);
				if(G.deck[ player ][ G.deckCount[player] -1] == k[i] && supplyCount(k[i], &G) == currSupply-1 && G.deck[ player+1 ][ G.deckCount[player+1] -1] != k[i])
				{
				  printf ("PASS: ");
				  pass++;
				}
				else
				{
				  printf ("FAIL: ");
				}
					printf ("deck expected %d, got  %d\n", k[i], G.deck[ player ][ G.deckCount[player]-1]);
					printf ("      supplyCount expected %d, got  %d\n", currSupply-1, supplyCount(k[i], &G));
			
			}
			else if (j == 2)
			{
				
				//printf("%d\n", G.hand[ player ][ G.handCount[player] ]);
				if(G.hand[ player ][ G.handCount[player] -1] == k[i] && supplyCount(k[i], &G) == currSupply-1 && G.hand[ player+1 ][ G.handCount[player+1] -1] != k[i])
				{
				  printf ("PASS: ");
				  pass++;
				}
				else
				{
				  printf ("FAIL: ");
				}
					printf ("hand expected %d, got  %d\n", k[i], G.hand[ player ][ G.handCount[player]-1]);
					printf ("      supplyCount expected %d, got  %d\n", currSupply-1, supplyCount(k[i], &G));

			}
			else
			{
				
			  //printf("%d\n", G.discard[player][ G.discardCount[player] ]);
				if(G.discard[ player ][ G.discardCount[player] -1] == k[i] && supplyCount(k[i], &G) == currSupply-1 && G.discard[ player+1 ][ G.discardCount[player+1] -1] != k[i])
				{
				  printf ("PASS: ");
				  pass++;
				}
				else
				{
				  printf ("FAIL: ");
				}
					printf ("discard expected %d, got  %d\n", k[i], G.discard[ player ][ G.discardCount[player]-1]);
					printf ("      supplyCount expected %d, got  %d\n", currSupply-1, supplyCount(k[i], &G));
			}
		}	

		//memset(&G, 23, sizeof(struct gameState));   // clear the game state
		//initializeGame(numPlayer, k, seed, &G);
	}
	
	if(pass == 31)
	{
		printf("\n >>>>> SUCCESS: Testing complete gainCard() <<<<<\n\n");
	}
	else
	{
		printf("\n >>>>> FAILURE: Testing complete gainCard() <<<<<\n\n");
	}

    return 0;
}