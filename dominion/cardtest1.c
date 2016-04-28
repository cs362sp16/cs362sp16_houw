#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define PlayerNum 2
void assertTrue_cardEffect_smithy(struct gameState *CardTest);

int main() {
	struct gameState *CardTest;
	CardTest = newGame();
	int Kingdom_Card[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };
	initializeGame(PlayerNum, Kingdom_Card, 1, CardTest);
	printf("Test Start+++++++++++++++++++Card Test 1 ++++++++test card: smithy \n");
	assertTrue_cardEffect_smithy(CardTest);
	printf("Test End+++++++++++++++++++++Card Test 1 ++++++++test card: smithy \n");
	return 0;
}

void assertTrue_cardEffect_smithy(struct gameState *CardTest) {
	int player;
	player = CardTest->whoseTurn;
	CardTest->hand[player][0] = silver;
	CardTest->hand[player][1] = copper;
	CardTest->hand[player][2] = copper;
	CardTest->hand[player][3] = copper;
	CardTest->hand[player][4] = smithy;
	printf("Case:           whoseTurn = 0, handCount[0] = 5,  hand[0][4] = smithy\n");
	printf("Correct Result: played card is 1, player hand count is 7 (5-1+3)\n");
	_cardEffect_smithy(player, CardTest, 4);
	if (CardTest->playedCardCount == 1 
			&& CardTest->playedCards[0] == smithy 
			&& CardTest->handCount[player] == 7)
		printf("work\n");
	else
		printf(" wrong\n");
}
