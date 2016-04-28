#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define PlayerNum 2
void assertTrue_village(struct gameState *CardTest);

int main() {
	struct gameState *CardTest;
	CardTest = newGame();
	int Kingdom_Card[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };
	initializeGame(PlayerNum, Kingdom_Card, 1, CardTest);
	printf("Test Start+++++++++++++++++++Card Test 2 ++++++++test card: village \n");
	assertTrue_village(CardTest);
	printf("Test End+++++++++++++++++++++Card Test 2 ++++++++test card: village \n");
	return 0;
}

void assertTrue_village(struct gameState *CardTest) {
	int player;
	player = CardTest->whoseTurn;
	CardTest->hand[player][0] = silver;
	CardTest->hand[player][1] = copper;
	CardTest->hand[player][2] = copper;
	CardTest->hand[player][3] = copper;
	CardTest->hand[player][4] = village;
	_cardEffect_village(player, CardTest, 4);
	printf("Case:           whoseTurn = 0, handCount[0] = 5,  hand[0][4] = village\n");
	printf("Correct Result: played card is 1, player hand count is 5, action is 3 \n");
	if (CardTest->playedCardCount == 1 
			&& CardTest->playedCards[0] == village 
			&& CardTest->handCount[player] == 5
			&& CardTest->numActions == 3)
		printf("work\n");
	else
		printf(" wrong\n");
}
