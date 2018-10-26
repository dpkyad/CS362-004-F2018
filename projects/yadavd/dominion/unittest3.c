#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    int i, j, k;
    int seed = 1000;
    int numPlayer = 2;
	int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	
	int sets[4][5] = { {adventurer, gardens, embargo, village, minion},
					{adventurer, adventurer, adventurer, adventurer, adventurer},
					{embargo, adventurer, adventurer, embargo, smithy}, 
					{100, 100, 100, 100, 100} 
				  };
    struct gameState G;
	int player = 0;
	int count = 0;
	int set3Totals[5] = {1,1,2,2,1};
	char str[10];
	memset(str, '\0', sizeof(str));
	int *ptr;
	int pass = 0;
	
	// initialize a game state and player cards
	//memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayer, cards, seed, &G);
	
	//testing only the cards that are played in the playdom.c
	printf("----------------- Testing Function: fullDeckCount() ----------------\n");
	

	//for each set
	for(i = 0; i<4; i++)
	{
		if(i == 0)
			printf("TEST 1: Counts for deck, hand, and discard are 1 since there are no repeats in the set 1\n");
		else if(i ==1)
			printf("TEST 2: Counts for deck, hand, and discard are incremental since there are repeats in the set 2\n");
		else if (i == 2)
			printf("TEST 3: Counts for deck, hand, and discard are as defined since there are a mix of cards in the set 3\n");
		else
			printf("TEST 4: Unknown cards\n");
		
		//for deck then hand then discard
		for (k = 0; k<3; k++)
		{
			//add to a deck/hand/discard
			if(k == 0)
			{
				//TESTING deck
				//G.deck[player][j] = sets[i][j];
				
				ptr = G.deck[player];
				strcpy(str, "deck");
			}
			else if(k == 1)
			{
				//TESTING hand
				//G.hand[player][j] = sets[i][j];
				
				ptr = G.hand[player];
				strcpy(str, "hand");
			}
			else
			{
				//TESTING discard
				//G.discard[player][j] = sets[i][j];
				
				//discard needs to be set to 5 since it is currently empty;
				G.discardCount[player] = 5;
				ptr = G.discard[player];
				strcpy(str, "discard");
			}
			
			//for each card in a set
			for(j = 0; j<5; j++)
			{
				ptr[j] = sets[i][j];
				
				count = fullDeckCount(player, sets[i][j], &G);
				
				//for set 1, count should be one each for each card since there are no repeats in the set
				if(i == 0)
				{
					if(count == 1)
					{
					  printf ("PASS: %s set 1 expected %d, got  %d\n", str, 1, count);
					  pass++;
					}
					else
					{
					  printf ("FAIL: %s set 1 expected %d, got  %d\n", str, 1, count);
					}
				}
				//for set 2, count should be five since there are five repeats in the set, j+1 since it increments 
				
				else if (i == 1)
				{
					if(count == j+1)
					{
					  printf ("PASS: %s set 2 expected %d, got  %d\n", str, j+1, count);
					  pass++;
					}
					else
					{
					  printf ("FAIL: %s set 2 expected %d, got  %d\n", str, j+1, count);
					}
				}
				//for set 3, count should be the number of cards each as defined in set3Totals
				else if(i == 2)
				{
					if(count == set3Totals[j])
					{
					  printf ("PASS: %s set 3 expected %d, got  %d\n", str, set3Totals[j], count);
					  pass++;
					}
					else
					{
					  printf ("FAIL: %s set 3 expected %d, got  %d\n", str, set3Totals[j], count);
					}
				}
				else if(i == 3)
				{
					if(count == 0)
					{
					  printf ("PASS: %s set 4 expected %d, got  %d\n", str, 0, count);
					  pass++;
					}
					else
					{
					  printf ("FAIL: %s set 4 expected %d, got  %d\n", str, 0, count);
					}
				}
			}
			//reset to clear out current set for next set
			memset(&G, 23, sizeof(struct gameState));   // clear the game state
			//initalize with the set
			initializeGame(numPlayer, cards, seed, &G);
		} 
		printf("\n");
		
	}
	
	if(pass == 60)
	{
		printf("\n >>>>> SUCCESS: Testing complete fullDeckCount() <<<<<\n\n");
	}
	else
	{
		printf("\n >>>>> FAILURE: Testing complete fullDeckCount() <<<<<\n\n");
	}
	

    return 0;
}